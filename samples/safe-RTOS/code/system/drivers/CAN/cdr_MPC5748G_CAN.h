#ifndef CDR_MPC5748G_CAN_INCLUDED
#define CDR_MPC5748G_CAN_INCLUDED
/**
 * @file cdr_MPC5748G_CAN.h
 *   The MCU derivative header file, MPC5748G.h, doesn't contain macros for accessing some
 * of the CAN device's registers. Here, we complete the set of definitions to the extend
 * required for the CAN I/O driver.
 
 * Copyright (C) 2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

/*
 * Include files
 */


/*
 * Defines
 */

/* Here we have the access macros for the fields of the C/S word of a normal (i.e. not
   FIFO) mailbox. */
#define CAN_MBCS_EDL_MASK           0x80000000u
#define CAN_MBCS_EDL_SHIFT          31u
#define CAN_MBCS_EDL_WIDTH          1u
#define CAN_MBCS_EDL(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_EDL_SHIFT))&CAN_MBCS_EDL_MASK)
#define CAN_MBCS_BRS_MASK           0x40000000u
#define CAN_MBCS_BRS_SHIFT          30u
#define CAN_MBCS_BRS_WIDTH          1u
#define CAN_MBCS_BRS(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_BRS_SHIFT))&CAN_MBCS_BRS_MASK)
#define CAN_MBCS_ESI_MASK           0x20000000u
#define CAN_MBCS_ESI_SHIFT          29u
#define CAN_MBCS_ESI_WIDTH          1u
#define CAN_MBCS_ESI(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_ESI_SHIFT))&CAN_MBCS_ESI_MASK)
#define CAN_MBCS_CODE_MASK          0x0f000000u
#define CAN_MBCS_CODE_SHIFT         24u
#define CAN_MBCS_CODE_WIDTH         4u
#define CAN_MBCS_CODE(x)            (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_CODE_SHIFT))&CAN_MBCS_CODE_MASK)
#define CAN_MBCS_SRR_MASK           0x00400000u
#define CAN_MBCS_SRR_SHIFT          22u
#define CAN_MBCS_SRR_WIDTH          1u
#define CAN_MBCS_SRR(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_SRR_SHIFT))&CAN_MBCS_SRR_MASK)
#define CAN_MBCS_IDE_MASK           0x00200000u
#define CAN_MBCS_IDE_SHIFT          21u
#define CAN_MBCS_IDE_WIDTH          1u
#define CAN_MBCS_IDE(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_IDE_SHIFT))&CAN_MBCS_IDE_MASK)
#define CAN_MBCS_RTR_MASK           0x00100000u
#define CAN_MBCS_RTR_SHIFT          20u
#define CAN_MBCS_RTR_WIDTH          1u
#define CAN_MBCS_RTR(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_RTR_SHIFT))&CAN_MBCS_RTR_MASK)
#define CAN_MBCS_DLC_MASK           0x000f0000u
#define CAN_MBCS_DLC_SHIFT          16u
#define CAN_MBCS_DLC_WIDTH          4u
#define CAN_MBCS_DLC(x)             (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_DLC_SHIFT))&CAN_MBCS_DLC_MASK)
#define CAN_MBCS_TIME_STAMP_MASK    0x0000ffffu
#define CAN_MBCS_TIME_STAMP_SHIFT   0u
#define CAN_MBCS_TIME_STAMP_WIDTH   16u
#define CAN_MBCS_TIME_STAMP(x)      (((uint32_t)(((uint32_t)(x))<<CAN_MBCS_TIME_STAMP_SHIFT))&CAN_MBCS_TIME_STAMP_MASK)

/* Here we have the access macros for the fields of the CAN ID word of a normal (i.e. not
   FIFO) mailbox.
     Note, the access macros for standard ID and extended ID overlap. You need to use them
   either/or. */
#define CAN_MBID_PRIO_MASK          0xe0000000u
#define CAN_MBID_PRIO_SHIFT         29u
#define CAN_MBID_PRIO_WIDTH         3u
#define CAN_MBID_PRIO(x)            (((uint32_t)(((uint32_t)(x))<<CAN_MBID_PRIO_SHIFT))&CAN_MBID_PRIO_MASK)
#define CAN_MBID_ID_STD_MASK        0x1ffc0000u
#define CAN_MBID_ID_STD_SHIFT       18u
#define CAN_MBID_ID_STD_WIDTH       11u
#define CAN_MBID_ID_STD(x)          (((uint32_t)(((uint32_t)(x))<<CAN_MBID_ID_STD_SHIFT))&CAN_MBID_ID_STD_MASK)
#define CAN_MBID_ID_EXT_MASK        0x1fffffffu
#define CAN_MBID_ID_EXT_SHIFT       0u
#define CAN_MBID_ID_EXT_WIDTH       29u
#define CAN_MBID_ID_EXT(x)          (((uint32_t)(((uint32_t)(x))<<CAN_MBID_ID_EXT_SHIFT))&CAN_MBID_ID_EXT_MASK)

/* Here we have the access macros for the fields of the C/S word of the mailbox, which is
   the head element of the FIFO. The macros map RM 43.4.43, Table 43-17, p. 1786.*/
#define CAN_FIFOCS_IDHIT_MASK           0xff800000u
#define CAN_FIFOCS_IDHIT_SHIFT          23u
#define CAN_FIFOCS_IDHIT_WIDTH          9u
#define CAN_FIFOCS_IDHIT(x)             (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_IDHIT_SHIFT))&CAN_FIFOCS_IDHIT_Mask)
#define CAN_FIFOCS_SRR_MASK             0x00400000u
#define CAN_FIFOCS_SRR_SHIFT            22u
#define CAN_FIFOCS_SRR_WIDTH            1u
#define CAN_FIFOCS_SRR(x)               (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_SRR_SHIFT))&CAN_FIFOCS_SRR_MASK)
#define CAN_FIFOCS_IDE_MASK             0x00200000u
#define CAN_FIFOCS_IDE_SHIFT            21u
#define CAN_FIFOCS_IDE_WIDTH            1u
#define CAN_FIFOCS_IDE(x)               (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_IDE_SHIFT))&CAN_FIFOCS_IDE_MASK)
#define CAN_FIFOCS_RTR_MASK             0x00100000u
#define CAN_FIFOCS_RTR_SHIFT            20u
#define CAN_FIFOCS_RTR_WIDTH            1u
#define CAN_FIFOCS_RTR(x)               (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_RTR_SHIFT))&CAN_FIFOCS_RTR_MASK)
#define CAN_FIFOCS_DLC_MASK             0x000f0000u
#define CAN_FIFOCS_DLC_SHIFT            16u
#define CAN_FIFOCS_DLC_WIDTH            4u
#define CAN_FIFOCS_DLC(x)               (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_DLC_SHIFT))&CAN_FIFOCS_DLC_MASK)
#define CAN_FIFOCS_TIME_STAMP_MASK      0x0000ffffu
#define CAN_FIFOCS_TIME_STAMP_SHIFT     0u
#define CAN_FIFOCS_TIME_STAMP_WIDTH     16u
#define CAN_FIFOCS_TIME_STAMP(x)        (((uint32_t)(((uint32_t)(x))<<CAN_FIFOCS_TIME_STAMP_SHIFT))&CAN_FIFOCS_TIME_STAMP_MASK)

/* Here we have the access macros for the fields of the received CAN ID word of the
   mailbox, which is the head element of the FIFO. The macros map RM 43.4.43, Table 43-17,
   p. 1786.
     Note, the access macros for standard ID and extended ID overlap. You need to use them
   either/or. */
#define CAN_FIFOID_ID_STD_MASK          0x1ffc0000u
#define CAN_FIFOID_ID_STD_SHIFT         18u
#define CAN_FIFOID_ID_STD_WIDTH         11u
#define CAN_FIFOID_ID_STD(x)            (((uint32_t)(((uint32_t)(x))<<CAN_FIFOID_ID_STD_SHIFT))&CAN_FIFOID_ID_STD_MASK)
#define CAN_FIFOID_ID_EXT_MASK          0x1fffffffu
#define CAN_FIFOID_ID_EXT_SHIFT         0u
#define CAN_FIFOID_ID_EXT_WIDTH         29u
#define CAN_FIFOID_ID_EXT(x)            (((uint32_t)(((uint32_t)(x))<<CAN_FIFOID_ID_EXT_SHIFT))&CAN_FIFOID_ID_EXT_MASK)

/* Here we have the access macros for the fields of the FIFO Filter ID word, i.e. an entry
   from the FIFO acceptance filter table. The macros map RM 43.4.43, Table 43-18, p. 1786.
     Note, the access macros for standard ID and extended ID overlap. You need to use them
   either/or. */
#define CAN_FIFOFILTER_RTR_MASK         0x80000000u
#define CAN_FIFOFILTER_RTR_SHIFT        31u
#define CAN_FIFOFILTER_RTR_WIDTH        1u
#define CAN_FIFOFILTER_RTR(x)           (((uint32_t)(((uint32_t)(x))<<CAN_FIFOFILTER_RTR_SHIFT))&CAN_FIFOFILTER_RTR_MASK)
#define CAN_FIFOFILTER_IDE_MASK         0x40000000u
#define CAN_FIFOFILTER_IDE_SHIFT        30u
#define CAN_FIFOFILTER_IDE_WIDTH        1u
#define CAN_FIFOFILTER_IDE(x)           (((uint32_t)(((uint32_t)(x))<<CAN_FIFOFILTER_IDE_SHIFT))&CAN_FIFOFILTER_IDE_MASK)
#define CAN_FIFOFILTER_RXIDA_STD_MASK   0x3ff80000u
#define CAN_FIFOFILTER_RXIDA_STD_SHIFT  19u
#define CAN_FIFOFILTER_RXIDA_STD_WIDTH  11u
#define CAN_FIFOFILTER_RXIDA_STD(x)     (((uint32_t)(((uint32_t)(x))<<CAN_FIFOFILTER_RXIDA_STD_SHIFT))&CAN_FIFOFILTER_RXIDA_STD_MASK)
#define CAN_FIFOFILTER_RXIDA_EXT_MASK   0x3ffffffeu
#define CAN_FIFOFILTER_RXIDA_EXT_SHIFT  1u
#define CAN_FIFOFILTER_RXIDA_EXT_WIDTH  29u
#define CAN_FIFOFILTER_RXIDA_EXT(x)     (((uint32_t)(((uint32_t)(x))<<CAN_FIFOFILTER_RXIDA_EXT_SHIFT))&CAN_FIFOFILTER_RXIDA_EXT_MASK)


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */



/*
 * Global inline functions
 */


#endif  /* CDR_MPC5748G_CAN_INCLUDED */
