/**
 * @file nif_interfaceEthToLwIP.c
 * Interface between Ethernet driver and lwIP, according to the outline given at
 * https://www.nongnu.org/lwip/2_0_x/group__lwip__nosys.html (visited Sep 24, 2023).
 *
 * Copyright (C) 2023-2024 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/* Module interface
 *   nif_initNetIfForENETDriver
 *   nif_processPendingEthRxFrame
 *   nif_onEthBufferTxComplete
 * Local functions
 *   setMacFilterForIgmp
 *   setMacFilterForMld
 *   sendUnchainedPBufAsEthFrame
 *   sendPBufAsEthFrame
 *   onFreePBufEthRx
 *   provideEthRxDataToLwIP
 */

/*
 * Include files
 */

#include "nif_interfaceEthToLwIP.h"

#include <assert.h>
#include <string.h>
#include <stdio.h> // Temporarily for iprintf
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "lwip/tcpip.h"

#include "lwipcfg.h"
#include "lwip/sys.h"

#include "eth_ethernet.h"
#include "nif_queueTxPBuf.h"

/*
 * Defines
 */

#if LWIP_SUPPORT_CUSTOM_PBUF != 1
# error Custom pbufs are required
#endif

/*
 * Local type definitions
 */

/** A custom pbuf extends the normal pbuf with information about the buffer of the ETH
    driver, whose content it carries as payload. Used for safely returning memory to the
    driver on deletion of the pbuf. */
struct ethRxCustomPBuf_t
{
  /** A lwIP custom pbuf, i.e., normal pbuf plus custom destructor. */
  struct pbuf_custom customPBuf;

  /** The beginning of the memory area, which had been filled by the ETH driver on frame
      reception. The same address is needed to return the memory buffer to the driver for a
      future reception. */
  uint8_t *bufferEthDrvRx;
};

/* Type extension requires well-defined placement of "base class" in derived class. */
_Static_assert(offsetof(struct pbuf_custom, pbuf) == 0u, "Bad type definition");
_Static_assert(offsetof(struct ethRxCustomPBuf_t, customPBuf) == 0u, "Bad type definition");

/*
 * Local prototypes
 */


/*
 * Data definitions
 */

/** We use an lwIP memory pool for those pbufs, which deliver the Ethernet Rx frames to
    lwIP. For these pbufs, the use of a pool is doubtless advantageous as both the number
    of elements and their size is fixed and known beforehand.\n
      The decision to use a pool rather than heap technology is made independently from the
    general project configuration in lwipopts.h, #MEMP_USE_CUSTOM_POOLS and #MEM_USE_POOLS.
    This is implemented by using the macros #LWIP_MEMPOOL_DECLARE, #LWIP_MEMPOOL_ALLOC and
    #LWIP_MEMPOOL_FREE, which create and use a dedicated pool, that is not known to the
    rest of the implementation, by direct reference to the pool's name. */
LWIP_MEMPOOL_DECLARE( NIF_MEM_POOL_PBUF_RX_ETH
                    , ETH_ENET0_RING0_NO_RXBD
                    , sizeof(struct ethRxCustomPBuf_t)
                    , "Mempool for ETH RX frames"
                    )

/*
 * Function implementation
 */

/* The code has been made for buffer descriptor ring zero. Any other value requires careful
   code review; the three rings are not equivalent and it is not clear beforehand if ring 1
   or 2 will work well without code modification. */
_Static_assert(ETH_ENET0_IDX_RING_IN_USE==0, "Review code prior to use of ring other than 0");


#if LWIP_IGMP && LWIP_IPV4
/**
 * Modify/configure Ethernet driver setting to forward (or stop forwarding) multicast
 * packet for IGMP (IPv4).\n
 * - If "action" = NETIF_ADD_MAC_FILTER, the ETH driver will forward multicast packet of
 *   the group corresponding to "group".\n
 * - If "action" = NETIF_DEL_MAC_FILTER, the ETH driver will stop forwarding multicast
 *   packet of the group corresponding to "group".\n
 *   @return
 * The function always returns success, ERR_OK.
 *   @param pNetIf
 * The network interface by reference.
 *   @param group
 * The IP address of the Multicast group the message have to be forwarded by the ETH driver.
 *   @param action
 * The action to be taken. (Remove group from the forwarded packet or add group.)
 */
static err_t setMacFilterForIgmp( struct netif * const pNetIf
                                , const ip4_addr_t *group
                                , enum netif_mac_filter_action action
                                )
{
    /* Generate MAC address based on IP address. */
    uint8_t group_MAC[6];
    group_MAC[0] = 0x01;
    group_MAC[1] = 0x00;
    group_MAC[2] = 0x5e;
    group_MAC[3] = (0x7f & ip4_addr2(group));
    group_MAC[4] = ip4_addr3(group);
    group_MAC[5] = ip4_addr4(group);

    /*call function modifying the enet driver*/
    eth_setMulticastForward( pNetIf->num
                           , group_MAC
                           , /* enable */ action != NETIF_DEL_MAC_FILTER
                           );
    return ERR_OK;

} /* setMacFilterForIgmp */
#endif /* LWIP_IGMP && LWIP_IPV4 */


#if LWIP_IPV6
/**
 * Modify/configure Ethernet driver setting to forward (or stop forwarding) multicast packet
 * for MLD (ICMPv6).\n
 * - If "action" = NETIF_ADD_MAC_FILTER, the ETH driver will forward multicast packet of
 *   the group corresponding to "group".
 * - If "action" = NETIF_DEL_MAC_FILTER, the ETH driver will stop forwarding multicast
 *   packet of the group corresponding to "group".
 *   @return
 * The function always returns success, ERR_OK.
 *   @param pNetIf
 * The network interface by reference.
 *   @param group
 * The IP address of the Multicast group the message have to be forwarded by the ETH driver.
 *   @param action
 * The action to be taken. (Remove group from the forwarded packet or add group.)
 */
static err_t setMacFilterForMld( struct netif * const pNetIf
                               , const ip6_addr_t *group
                               , enum netif_mac_filter_action action
                               )
{
    /* Generate MAC address based on IP address. */
    uint8_t group_MAC[6];
    group_MAC[0] = 0x33;
    group_MAC[1] = 0x33;
    group_MAC[2] = (uint8_t)((IP6_ADDR_BLOCK7(group)) >> 8);
    group_MAC[3] = (uint8_t)(IP6_ADDR_BLOCK7(group));
    group_MAC[4] = (uint8_t)((IP6_ADDR_BLOCK8(group)) >> 8);
    group_MAC[5] = (uint8_t)(IP6_ADDR_BLOCK8(group));

    /*call function modifying the enet driver*/
    eth_setMulticastForward( pNetIf->num
                           , group_MAC
                           , /* enable */ action != NETIF_DEL_MAC_FILTER
                           );
    return ERR_OK;

} /* setMacFilterForMld */
#endif /*LWIP_IPV6*/



/**
 * Hand the payload of a pbuf over to the ETH driver, in order to make it send the payload
 * as a single Ethernet frame.
 *   @return
 * If the frame was successfully enqueued for transmission, then the driver returns a
 * handle of the transmission job. It can be used to query the state of the * transmission,
 * in particular whether the transmission has been completed.\n
 *   Otherwise, if there is no available space for the frame in the ring buffer of the MAC
 * device, the function returns zero.
 *   @param idxEthDev
 * The ENET device to use for transmission. Needs to be enabled and configured. Range is
 * 0..1.
 *   @param pPBuf
 * The payload of this pbuf is submitted to the ETH driver as an entire frame.
 */
static inline uintptr_t submitPBufToEthDriver( unsigned int idxEthDev
                                             , struct pbuf * const pPBuf
                                             )
{
    /* Try to put the data as frame into the ring buffer of the MAC device. Return value is
       NULL if there is (currently) no space in the ring buffer. */
    return eth_sendFrame( idxEthDev
                        , ETH_ENET0_IDX_RING_IN_USE
                        , pPBuf->payload
                        , pPBuf->tot_len
                        );
} /* submitPBufToEthDriver */


/**
 * Send a single ETH frame.
 *   @return
 * - ERR_OK if the pbuf could be successfully submitted for transmission.\n
 * - ERR_MEM if there is a memory limitation hindering from submission of the buffer. The
 *   pbuf won't be transmitted in this case.
 *   @param pNetIf
 * The lwIP network interface to apply for frame transmission by reference.
 *   @param pPBuf
 * The pBuf to send by reference. The ETH frame contents are taken from this pBuf, which
 * must not be a chained one. (Only the first element of the chain is read.) The function
 * gets the buffer for read access only. The caller keeps ownership, e.g., to enable
 * re-transmission for the TCP protocol. The reference count of the pBuf must therefore
 * not be changed.
 */
static err_t sendUnchainedPBufAsEthFrame( const struct netif * const pNetIf
                                        , struct pbuf * const pPBuf
                                        )
{
    const err_t stsEnqueue = nif_queueTxPBuf_enqueue(pNetIf->num, pPBuf);

    /* Try sending, the driver may have space to take the just enqueued buffer. */
    if(stsEnqueue == ERR_OK)
        nif_onEthBufferTxComplete();

    return stsEnqueue;

} /* sendUnchainedPBufAsEthFrame */


/**
 * Transmit a packet.\n
 *   The packet is contained in the pBuf that is passed to the function. This pBuf might be
 * chained.
 *   @return
 * - ERR_OK if the pbuf could be successfully submitted for transmission.\n
 * - ERR_MEM if there is a memory limitation hindering from submission of the buffer. The
 *   pbuf won't be transmitted in this case.
 *   @param pNetIf
 * The lwIP network interface to apply for frame transmission by reference.
 *   @param pPBuf
 * The pBuf to send by reference. The buffer denotes a complete Ethernet frame. The
 * function gets the buffer for read access only. The caller keeps ownership, e.g., to
 * enable re-transmission for the TCP protocol. The reference count of the pBuf must
 * therefore not be lowered.
 */
static err_t sendPBufAsEthFrame(struct netif * const pNetIf, struct pbuf * const pPBuf)
{
    assert(pPBuf != NULL);
#if LWIP_NETIF_TX_SINGLE_PBUF && !(LWIP_IPV4 && IP_FRAG) && (LWIP_IPV6 && LWIP_IPV6_FRAG)
    assert(pPBuf->next == NULL  &&  pPBuf->len == pPBuf->tot_len);
#endif

    /* We use the Ethernet driver such that a frame is a solid, contiguous block of memory.
       Therefore we need to check if the delivered pbuf is a chained one - in which case we
       need to copy all chained data into a single, solid pbuf. */
    /// @todo The driver should support fragmented frames; we need to spend many more control blocks and do the coalescing only if there are too few available
    const bool isPBufSolid = pPBuf->next == NULL;

    err_t stsEthTx;
    if(isPBufSolid)
        stsEthTx = sendUnchainedPBufAsEthFrame(pNetIf, pPBuf);
    else
    {
        /* Increment the reference count of the pbuf: If coalescing takes place and
           succeeds then that function would decrement the pbufs' ref counter, while this
           function must not change it. */
        pbuf_ref(pPBuf);

        /* Concatenate the payload of all pbufs' chain elements into a new pbuf, which is
           unchained. */
        struct pbuf * const pPBufClone = pbuf_coalesce(pPBuf, PBUF_RAW);

        /* pbuf_coalesce returns the unmodified pbuf if it is not possible to allocate a
           new pBuf with the concatenated payload of *pPBuf's chain. */
        if(pPBufClone != pPBuf)
        {
            /* Operation succeed, we have a clone with solid block of memory holding the
               ETH frame payload and can send it out. */
            stsEthTx = sendUnchainedPBufAsEthFrame(pNetIf, pPBufClone);

            /* The clone is no longer needed, we can delete it again. */
            pbuf_free(pPBufClone);
        }
        else
        {
            /* Same buffer has been returned instead of a coalesced clone; no memory was
               available for the clone. We loose a Tx frame. */
            stsEthTx = ERR_MEM;

            /* We can restore the reference counter of the original pbuf. */
            pbuf_free(pPBuf);
        }
    }

    return stsEthTx;

} /* sendPBufAsEthFrame */


/**
 * Callback, invoked on deletion of a custom pbuf, as used to pass Rx frames got from the
 * Ethernet driver to the lwIP stack.
 *   @param pPBuf
 * The custom pbuf to free by reference.
 */
static void onFreePBufEthRx(struct pbuf * const pPBuf)
{
    /* Interface indexes always start at one per RFC 3493, section 4, but we use zero based
       indexes. */
    const uint8_t idxEthDev = pPBuf->if_idx - 1u;
    assert(LWIP_SINGLE_NETIF == 0u || idxEthDev == 0u);
    assert(idxEthDev < ENET_INSTANCE_COUNT);
    //assert(netif_get_by_index(pPBuf->if_idx)->num == idxEthDev);

    /* Indicate to the ETH driver that the payload area of the pbuf is again valid memory
       space for an Rx frame.
         Note, we must not use pbuf->payload for identification of the released memory space.
      lwIP changes this field during pbuf evaluation; it advances the pointer when parsing
      the protocol headers. */
    const struct ethRxCustomPBuf_t * const pCustomPBuf = (struct ethRxCustomPBuf_t*)pPBuf;
    eth_releaseRxFramePayloadBuffer( idxEthDev
                                   , ETH_ENET0_IDX_RING_IN_USE
                                   , pCustomPBuf->bufferEthDrvRx
                                   );
    /* Return the allocated memory for the pbuf to the dedicated memory pool. */
    LWIP_MEMPOOL_FREE(NIF_MEM_POOL_PBUF_RX_ETH, pPBuf);

} /* onFreePBufEthRx */


/**
 * Frame data, received by the ETH driver, is wrapped into a (custom) pbuf object and
 * handed over to the lwIP stack for evaluation.
 *   @return
 * ERR_OK if the packet is being handled by lwIP. The lwIP stack took ownership of the pbuf.
 * ERR_MEM if lwIP can't handle the packet. lwIP doesn't take ownership of the pbuf,
 * therefore the caller should release it.
 *   @param pNetIf
 * The netinterface object in use.
 *   @param pEthRxFrame
 * The pointer to the received Ethernet Rx frame.
 *   @param sizeOfFrame
 * The length of the contents of the Rx frame.
 */
static err_t provideEthRxDataToLwIP( struct netif * const pNetIf
                                   , uint8_t * const pEthRxFrame
                                   , uint16_t sizeOfFrame
                                   )
{

    /* Allocate a PBUF_REF pointing to the receive buffer. To avoid data copying, we use a
       pbuf with reference, which references the Rx frame buffer owned by the Ethernet
       driver. This requires a custom pbuf, which provides a callback on freeing. This
       callback signals when lwIP no longer requires the buffer so that it can be returned
       to the Ethernet driver. */
    struct ethRxCustomPBuf_t * const pCustomPBuf =
                    (struct ethRxCustomPBuf_t*)LWIP_MEMPOOL_ALLOC(NIF_MEM_POOL_PBUF_RX_ETH);
    err_t status;
    if(pCustomPBuf != NULL)
    {
        /* Store the original buffer address for later return to the ETH driver. */
        pCustomPBuf->bufferEthDrvRx = pEthRxFrame;

        /* Set the callback, which is invoked on deletion of pbuf. */
        pCustomPBuf->customPBuf.custom_free_function = onFreePBufEthRx;

        /* Initialize the allocated memory as a PBUF_REF, which points to the data received
           by the ETH driver. The function returns the address of the custom pbuf
           typedef'ed to a normal pbuf object. */
        struct pbuf * const pPBuf = pbuf_alloced_custom( /* pbuf_layer */ PBUF_RAW
                                                       , /* length */ sizeOfFrame
                                                       , /* type */ PBUF_REF
                                                       , &pCustomPBuf->customPBuf
                                                       , /* payload_mem */ pEthRxFrame
                                                       , /* payload_mem_len */ sizeOfFrame
                                                       );
        assert((uintptr_t)pPBuf == (uintptr_t)pCustomPBuf);

        /* Hand over the pbuf to lwIP. */
assert(pEthRxFrame == pPBuf->payload);
        status = pNetIf->input(pPBuf, pNetIf);
        if(status != ERR_OK)
        {
            /* Error, lwIP has not accepted the pbuf, ownership has not been transferred.
               We need to delete the object. */
            (void)pbuf_free(pPBuf);
        }
    }
    else
        status = ERR_OK;

    return status;

} /* provideEthRxDataToLwIP */



/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param pNetIf - the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 * Implements nif_initNetIfForENETDriver_Activity
 */
err_t nif_initNetIfForENETDriver(struct netif * const pNetIf)
{
    assert(pNetIf != NULL);

    /* Initialize the memory pool holding a pbuf for each Rx frame buffer owned by the
       Ethernet driver. */
    LWIP_MEMPOOL_INIT(NIF_MEM_POOL_PBUF_RX_ETH);

    const unsigned int idxNetIf = pNetIf->num;
    pNetIf->name[0] = 'I';
    if(idxNetIf <= 9u)
        pNetIf->name[1] = '1' + idxNetIf;
    else
    {
        assert(false);
        pNetIf->name[1] = 'x';
    }

#if LWIP_IPV4
#if LWIP_ARP
    /* We directly use etharp_output() here to save a function call.
     * You can instead declare your own function and call etharp_output()
     * from it if you have to do some checks before sending (e.g. if link
     * is available...) */
    pNetIf->output = etharp_output;
#else /* LWIP_ARP */
    pNetIf->output = NULL; /* not used for PPPoE */
#endif /* LWIP_ARP */
#endif /* LWIP_IPV4 */
#if LWIP_IPV6
    pNetIf->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
    pNetIf->linkoutput = sendPBufAsEthFrame;
#if LWIP_NETIF_HOSTNAME
    /* Initialize interface hostname */
    pNetIf->hostname = NIF_ETHERNET_HOST_NAME;
#endif /* LWIP_NETIF_HOSTNAME */
#if LWIP_SNMP
    /*
     * Initialize the snmp variables and counters inside the struct netif.
     * The last argument should be replaced with your link speed, in units
     * of bits per second.
     */
    NETIF_INIT_SNMP(pNetIf, (u8_t)snmp_ifType_ethernet_csmacd, 100000000u);
#endif /* LWIP_SNMP */

    /* Set MAC hardware address. We are prepared for two interfaces, for the two ENET
       devices onboard the MPC5748G. */
    assert(idxNetIf < 2u);
    pNetIf->hwaddr_len = NETIF_MAX_HWADDR_LEN;
    const uint8_t hwAddrAry[2u][NETIF_MAX_HWADDR_LEN] =
    {
        [0] = NIF_MAC_ADDR_ENET0,
        [1] = NIF_MAC_ADDR_ENET1,
    };
    for(unsigned int u=0u; idxNetIf<2u && u<NETIF_MAX_HWADDR_LEN; ++u)
        pNetIf->hwaddr[u] = hwAddrAry[idxNetIf][u];

    /* Set the maximum transfer unit. */
    pNetIf->mtu = 1500u;

    /* Make netif aware of device or driver capabilities. */

    /* Don't set NETIF_FLAG_ETHARP if this device is not an Ethernet one. */
    pNetIf->flags = (u8_t)(NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET);
#if LWIP_IGMP
    pNetIf->flags = pNetIf->flags | (u8_t)NETIF_FLAG_IGMP;

    /* Will add the function igmp_mac_filter to the netif. */
    pNetIf->igmp_mac_filter = setMacFilterForIgmp;
#endif /*LWIP_IGMP*/

    /* The driver for the ENET device calculates and inserts the IP and TCP checksums
       into the frames. This doesn't need to be done by SW in lwIP. */
    NETIF_SET_CHECKSUM_CTRL(pNetIf, NETIF_CHECKSUM_DISABLE_ALL);

#if LWIP_IPV6 && LWIP_IPV6_MLD
    pNetIf->flags = pNetIf->flags | (u8_t)NETIF_FLAG_MLD6;

    /* If flag MLD6 flag is set, add mdl_enet_filter function to netif. */
    pNetIf->mld_mac_filter = setMacFilterForMld;

    /*
     * For hardware/netifs that implement MAC filtering.
     *   All-nodes link-local is handled by default, so we must let the hardware know
     * to allow multicast packets in.
     *   Should set mld_mac_filter previously.
     */
    ip6_addr_t ip6_allnodes_ll;
    ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
    (void)pNetIf->mld_mac_filter(pNetIf, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */

    return ERR_OK;

} /* nif_initNetIfForENETDriver */


/**
 * This function polls the ETH driver for received frames and forwards them to lwIP in
 * case.\n
 *   This is the major API of the lwIP stack to keep it running. The function shall be
 * called from the integrating code either regularly or when the Ethernet driver notifies
 * the reception of a new frame. The latter option is preferred. The former option actually
 * means polling and requires the Ethernet driver to have enough buffer space for storing
 * all frames potentially arriving within the polling cycle time.
 *   @param pNetIf
 * An lwIP network interface object by reference. The ENET device, which is controlled by
 * this interface is polled for Rx frames.
 *   @param pNoRxFrameAnymore
 * \a true if and only if the net interface reported an empty queue. In case of \a false
 * it is possible but not for sure that the interface still has another queued Rx buffer.
 */
err_t nif_processPendingEthRxFrame(struct netif * const pNetIf, bool *pNoRxFrameAnymore)
{
    uint8_t idxEthDev = pNetIf->num;
    assert(LWIP_SINGLE_NETIF == 0u || idxEthDev == 0u);

    /* Check if there are any new RX frames and provide them to lwip stack */
    unsigned int sizeOfPayloadData;
    uint8_t * const pFrameData = eth_readFrame( idxEthDev
                                              , ETH_ENET0_IDX_RING_IN_USE
                                              , &sizeOfPayloadData
                                              );
    if(pFrameData != NULL)
    {
        /* Wrap the Rx data in a pbuf object and hand it over to lwIP. */
        provideEthRxDataToLwIP(pNetIf, pFrameData, (uint16_t)sizeOfPayloadData);
        *pNoRxFrameAnymore = false;
    }
    else
        *pNoRxFrameAnymore = true;

    return ERR_OK;

} /* nif_processPendingEthRxFrame */



/**
 * This function checks the Tx queue for frames (or fragments of such), which have been
 * submitted for transmission on the Ethernet bus but which have not been handed over to
 * the Ethernet driver yet - likely due to a temporary lack of buffer space in the
 * driver.\n
 *   This function is the second API of the lwIP stack to keep it running. The function
 * shall be called from the integrating code either regularly or when the Ethernet driver
 * notifies the transmission of a frame so that it'll have some buffer space freed and can
 * accept a new frame for transmission. The latter option is preferred.\n
 *   The former option actually means polling and has two disadvantages. The maximum Ethernet
 * throughput is reduced. Most likely, an Ethernet driver will submit a frame faster then the
 * polling cycle time. Instead of using the ready driver for the next frame, the
 * application waits for the next polling cycle to submit the next frame. Secondary, during
 * this time span, the lwIP stack may continue to submit frame fragments (pbufs) and the
 * pbuf queue may overflow and Tx frames were lost.
 *   @note
 * The lwIP core stack implementation is single-threaded. For this API and
 * nif_processPendingEthRxFrame() it means that they must not be used from concurrent
 * context. If both are connected to the Ethernet drivers interrupts then these need to
 * implement mutual exclusion, e.g., by being served by the same core and having same
 * priority.
 */
void nif_onEthBufferTxComplete(void)
{
    /* Check the pbufs, which had been handed over to the ETH driver, whether their
       transmission has completed meanwhile so that we can release the pbuf memory.
         The check for transmission-complete is limited to the heading elements in the
       queue because queuing, handing over to the ETH driver and transmission on the wire
       occur all in strictly same order. If we hit a still pending element in the queue
       then we know that all later enqueued pbufs won't have completed their transmission,
       neither. */
    while(true)
    {
        /* Get access to head element in the queue, which is the pbuf, which had been
           handed over to the ETH driver longest ago. Note, the queue is not modified by
           this operation. */
        const struct nif_queueElemTxPBuf_t * const pQElemTxPBuf =
                                    nif_queueTxPBuf_getPBufWaitingForTransmissionComplete();

        /* The queue returns NULL if not any pbuf is contained, which had been handed over
           to the ETH driver for transmission. */
        if(pQElemTxPBuf == NULL)
            break;

        assert(pQElemTxPBuf->hTxFrame != 0u);

        /* Note, when the query for the transmission status returns "transmission complete"
           then the related ring buffer is at the same time released for re-use. */
        if(eth_isTransmissionCompleted(pQElemTxPBuf->hTxFrame))
        {
            /* The next pbuf in the chain has been entirely processed by the ETH driver and
               we can remove it from the queue. This will implicitly free the pbuf and
               make the memory available to lwIP again. */
            nif_queueTxPBuf_dequeue();
        }
        else
        {
            /* The frame is not transmitted yet and the pbuf -- input to the frame -- needs
               to stay alive. We leave the loop, which is correct as sending frames is done
               in strict order of submitting pbuf for transmission. If this one has not
               completed, yet, then all others in the queue won't have, neither. */
            break;
        }
    } /* while(ETH driver has pending Tx frames.) */

    /* Check for pbufs, which had been submitted by lwIP for transmission, whether the ETH
       driver is in the state to transmit them, i.e., whether it has a free ring buffer
       element available for its (shortly later) transmission. */
    while(true)
    {
        /* Get access to queued pbuf, which is the next one in tcp_write() order to be
           handed over to the ETH driver. Note, the queue is not modified by this
           operation. */
        struct nif_queueElemTxPBuf_t * const pQElemTxPBuf =
                                                nif_queueTxPBuf_getPBufWaitingForSubmission();
        if(pQElemTxPBuf != NULL)
        {
            assert(pQElemTxPBuf->hTxFrame == 0u);
            pQElemTxPBuf->hTxFrame = submitPBufToEthDriver( pQElemTxPBuf->idxEthDev
                                                          , pQElemTxPBuf->pPBuf
                                                          );
            if(pQElemTxPBuf->hTxFrame != 0u)
            {
                /* The driver has accepted the pbuf, so we can advance its state to
                   "waiting for transmission complete". */
                nif_queueTxPBuf_advancePBufWaitingForSubmission();
            }
            else
            {
                /* ETH driver is currently busy or its ring buffer full, respectively. No
                   chance to submit further pbufs for transmission. */
                break;
            }
        }
        else
        {
            /* There are no queued pbuf waiting for submission any more. */
            break;
        }
    } /* while(Queue still holds pbufs, which need to be handed over to the ETH driver.) */

} /* nif_onEthBufferTxComplete */



