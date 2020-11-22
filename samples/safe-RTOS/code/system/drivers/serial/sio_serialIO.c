/**
 * @file sio_serialIO.c
 * Support of the LINFlex 2 device of the MPC5748G for serial text I/O. The device is
 * configured as UART and fed by DMA. We get a serial RS 232 output channel of high
 * throughput with a minimum of CPU interaction. It can be used by all three cores.\n
 *   Input is done by interrupt on a received character. The bandwidth of the input channel
 * is by far lower than the output. This is fine for the normal use case, controlling an
 * application by some input commands, but would become a problem if the intention is to
 * download large data amounts, e.g. for a kind of boot loader.\n
 *   Note, serial input is possible only from one core. Which core, is a compile time
 * configuration, see #INTC_IRQ_TARGET_CORE. Using the techniques from the implementation
 * of serial output for serial input, too, it would be possible to permit multi-core access
 * but it must be doubted that a reasonable use case exists and the implementation would
 * inherit the involved disadvantages (see sio_osWriteSerial() for details).\n
 *   The API is a small set of basic read and write routines, which adopt the conventions
 * of the C standard library so that the C functions for formatted output become usable.\n
 *   Note, the binding to the formatted output functions of the C library is not part of
 * this module.\n
 *   Note, formatted input is not possible through C standard functions.
 * 
 * @todo Doc allocated devices: LINFLex, SIUL, DMA, DMAMUX, PBridge, PIT, input interrupt
 * on which core
 *
 * Copyright (C) 2017-2020 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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
 *   sio_osInitSerialInterface
 *   sio_scFlHdlr_writeSerial
 *   sio_writeSerial (inline)
 *   sio_osWriteSerial
 *   sio_osGetChar
 *   sio_osGetLine
 * Local functions
 *   configPeripheralBridgeForDMA
 *   configSIULForUseWithOpenSDA
 *   configPITAsDMATrigger
 *   stopDMATrigger
 *   startDMATrigger
 *   configDMA
 *   configLINFlex
 *   linFlexRxInterrupt
 *   registerInterrupts
 */

/*
 * Include files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "MPC5748G.h"
#include "typ_types.h"
#include "rtos.h"
#include "sio_serialIO.h"
#include "sio_serialIO_defSysCalls.h"
#include "mtx_mutex.h"



/*
 * Defines
 */
 
/** The MPC has 18 LINFlex devices. The code is not specific for a certain device but not
    optimal for of all them, neither. The devices 0 and 1 can communicate with the DMA and
    could be run more optimal than implemented in this module, which has been made mainly
    for LINFlexD_2, which has no direct handshake with the DMA.\n
      Possible is the assignment of 0 .. 17.
      @remark With the DEVKIT-MPC5748G evaluation board the device LINFlexD_2 is the
    preferred choice. This device is connected to the host machine through USB and can be
    used with a terminal software on the host without any additional hardware or wiring.
      @remark Setting this define to a value other than 2 has never been tested. */
#define IDX_LINFLEX_D 2

/** The DMA channel to serve the UART with sent data bytes. Since most of the LINFlex
    devices are not connected to the DMA we need to use a timer triggered channel. This
    limits the choice of DMA channels to 0, 1, 16 and 17. By default we use 0, the one out
    of this set with lowest standard priority.
      @remark The DMA is triggered by a timer. The choice of the DMA channel implies the
    choice of a particular timer at the same time. This is: PIT 0, 1, 4, 5 for DMA 0, 1,
    16, 17, respectively. This timer needs to be available. */
#define DMA_CHN_FOR_SERIAL_OUTPUT   0

/** The interrupt priority for serial input. The interrupt is requested by the UART when
    another byte has been received. The range is 1..15.
      @remark The chosen priority needs to be greater than the priority of any context,
    that makes use of the input related API functions of this module. */
#define INTC_PRIO_IRQ_UART_FOR_SERIAL_INPUT     5u

/** In principal, all cores can serve the on-character-received interrupt. Here, we chose,
    which one is in charge. The range is 0 (Z4A), 1 (Z4B) or 2 (Z2). */
#define INTC_IRQ_TARGET_CORE    0

/** The size of the ring buffer for serial output can be chosen as a power of two of bytes.
      @remark The permitted range of values depends on the reservation of space made
    in the linker control file. The macro here needs to be maintained in sync with the
    symbol ld_noBitsDmaRingBuffer, that is maintained in the linker file. */
#define SERIAL_OUTPUT_RING_BUFFER_SIZE_PWR_OF_TWO   10

/** The size of the ring buffer for serial input as number of bytes. The maximum capacity
    is one Byte less than the size. For this buffer, there's no penalty in not using a
    power-of-two size. */
#define SERIAL_INPUT_RING_BUFFER_SIZE   257

/** The default behavior of terminal programs is to send a CR at the end of a message. By
    configuration, this can also be a pair of CR and LF. For serial input, this module
    handles this by compile time settings. Each of the two characters can be configured to
    be understood as end of line and the other one can be filtered out. If it is not
    filtered out then it behaves like any ordinary character, it becomes part of the read
    message that is passed on to the application.\n
      Here we have the end of line character. Should normally be carriage return but may
    also be the linefeed. Which one can depend on the terminal software you use.\n
      Note, for serial output, this module doesn't handle EOL at all. */
#define SERIAL_INPUT_EOL    '\r'

/** See #SERIAL_INPUT_EOL for an explanation. Here we have a character to be filtered out
    from the input stream. Should normally be the other one as configured for
    #SERIAL_INPUT_EOL. Filtering inactive is expressed by '\0' (but the zero byte is not
    filtered). */
#define SERIAL_INPUT_FILTERED_CHAR  '\n'

/** Compute the size of the output ring buffer as number of bytes. */
#define SERIAL_OUTPUT_RING_BUFFER_SIZE  (1u<<(SERIAL_OUTPUT_RING_BUFFER_SIZE_PWR_OF_TWO)) 

/** Used for index arithemtics: A mask for the index bits in an integer word. Here for the
    serial output buffer. */
#define SERIAL_OUTPUT_RING_BUFFER_IDX_MASK  (SERIAL_OUTPUT_RING_BUFFER_SIZE-1)


/* The LINFlex device to be used is selected by name depending on the setting of
   #IDX_LINFLEX_D. */
#if IDX_LINFLEX_D >= 0  &&  IDX_LINFLEX_D <= 17
# define LINFLEX_BY_IDX(idx)                                                            \
                ((LINFlexD_Type*)((((idx)&0x1u)==0? LINFlexD_0_BASE: LINFlexD_1_BASE)   \
                                  + ((idx)>>1u)*(LINFlexD_2_BASE-LINFlexD_0_BASE)       \
                                 )                                                      \
                )
# define LINFLEX LINFLEX_BY_IDX(IDX_LINFLEX_D)
#else
# error Invalid configuration, unknown LINFlex device specified
#endif

/* Direct Memory Access Multiplexer (DMAMUX), RM, section 71, p. 3563: The DMA is
   triggered to do a minor loop cycle by the data request of some I/O device.
   Unfortunately is the LINFlex device on the DEVKIT-MPC5748G that is connected to the
   USB port not capable of triggering a DMA transfer on buffer empty. We control the speed
   of the data transmission by a timer based trigger condition. This technique is
   restricted to the first two DMA channels of each group. Here, we select the related
   timer. */
#if DMA_CHN_FOR_SERIAL_OUTPUT >= 0  &&  DMA_CHN_FOR_SERIAL_OUTPUT <= 1
# define PIT_TIMER_CHN_IDX (DMA_CHN_FOR_SERIAL_OUTPUT)
#elif DMA_CHN_FOR_SERIAL_OUTPUT >= DMAMUX_CHCFG_COUNT \
      &&  DMA_CHN_FOR_SERIAL_OUTPUT <= DMAMUX_CHCFG_COUNT+1
# define PIT_TIMER_CHN_IDX ((DMA_CHN_FOR_SERIAL_OUTPUT)-(DMAMUX_CHCFG_COUNT)+4u)
#else
# error Configuration error: The chosen DMA channel does not permit timer triggering
#endif


/*
 * Local type definitions
 */
 
 
/*
 * Local prototypes
 */
 
 
/*
 * Data definitions
 */
 
/** This development support variable counts the number of DMA transfers intiated since
    power-up, to do the serial output */
volatile unsigned long SBSS_OS(sio_serialOutNoDMATransfers) = 0;

/** The ring buffer for serial output can be momentarily full. In such a case a sent
    message can be truncated (from a few bytes shortend up to entirely lost). This
    development support variable counts the number of messages since power-up, which
    underwent trunction.
      @remark Because of the race conditions between serial I/O interrupt and application
    software can not clearly relate a change of \a sio_serialOutNoTruncatedMsgs to a
    particular character or message it sends with sio_osWriteSerial(). In particular, it must
    not try to reset the counter prior to a read operation in order to establish such a
    relation. The application will just know that there are garbled messages. */
volatile unsigned long SBSS_OS(sio_serialOutNoTruncatedMsgs) = 0;

/** The ring buffer for serial output can be momentarily full. In such a case a sent
    message can be truncated (from a few bytes shortend up to entirely lost). This
    development support variable counts the number of truncated, lost message characters
    since power-up.
      @remark See \a sio_serialOutNoTruncatedMsgs for race conditions with the output
    functions of this module's API. Just the same holds for \a
    sio_serialOutNoLostMsgBytes. */
volatile unsigned long SBSS_OS(sio_serialOutNoLostMsgBytes) = 0;

/** The ring buffer used for the DMA based serial output.
      @remark The size of the buffer is defined here in the C source code but there is a
    strong dependency on the linker control file, too. The log2(sizeOfBuffer) least
    significant bits of the buffer address need to be zero. The buffer address (and thus
    its alignment) is specified in the linker file, which therefore limits the maximum size
    of the buffer. */
static uint8_t _serialOutRingBuf[SERIAL_OUTPUT_RING_BUFFER_SIZE]
                                                        SECTION(.sio_bss._serialOutRingBuf);

/** The write index into the ring buffer used for serial output. Since we use bytes and
    since the log2(sizeOfBuffer) least significant bits of the buffer address are zero
    the address of the index element is \a _serialOutRingBuf | \a _serialOutRingBufIdxWrM,
    which is equal to \a _serialOutRingBuf + \a _serialOutRingBufIdxWrM.
      @remark The variable is only used modulo SERIAL_OUTPUT_RING_BUFFER_SIZE, i.e. the more
    significant bits don't care (but aren't necessarily zero). This is indicated by the M
    at the end of the name. */
static volatile unsigned int SBSS_OS(_serialOutRingBufIdxWrM) = 0;

/** The ring buffer used for the interrupt based serial input. No particular section is
    required. Due to the low performance requirements we can use any location and do normal
    address arithmetics. */
static volatile uint8_t BSS_OS(_serialInRingBuf)[SERIAL_INPUT_RING_BUFFER_SIZE];

/** A pointer to the end of the ring buffer used for serial input. This pointer facilitates
    the cyclic pointer update.
      @remark Note, the pointer points to the last byte in the buffer, not to the first
    address beyond as usually done. */
static volatile const uint8_t * _pEndSerialInRingBuf =
                                    &_serialInRingBuf[SERIAL_INPUT_RING_BUFFER_SIZE-1];

/** The pointer to the next write position in the ring buffer used for serial input. */
static volatile uint8_t * volatile SDATA_OS(_pWrSerialInRingBuf) = &_serialInRingBuf[0];

/** The pointer to the next read position from the ring buffer used for serial input. The
    buffer is considered empty if \a _pWrSerialInRingBuf equals \a _pRdSerialInRingBuf,
    i.e. the buffer can contain up to SERIAL_INPUT_RING_BUFFER_SIZE-1 characters. */
static volatile uint8_t * volatile SDATA_OS(_pRdSerialInRingBuf) = &_serialInRingBuf[0];

/** The number of received but not yet consumed end of line characters. Required for read
    line API function. */
static volatile unsigned int SBSS_OS(_serialInNoEOL) = 0;

/** The number of lost characters due to overfull input ring buffer. */
volatile unsigned long SBSS_OS(sio_serialInLostBytes) = 0; 

#ifdef DEBUG
/** Count all characters received since last reset. This variable is supported in DEBUG
    compilation only. */
volatile unsigned long SBSS_OS(sio_serialInNoRxBytes) = 0;
#endif

 
/*
 * Function implementation
 */

/**
 * After reset, the peripheral bridges are closed for DMA. We set the master privileges in
 * bridge A for DMA such that it has read and write access in user and supervisor mode. The
 * default settings for the I/O device related slots (including the required LINFlex 2) are
 * such that now all devices behind bridge A. Bridge B is not touched.
 */
static void configPeripheralBridgeForDMA(void)
{
    /* Extend master priviledges of bridge A such that DMA gets full access.
         Note, read access is granted for generality (safety is not a design goal of this
       sample application), we would only require write access to the device. */
    AIPS_A->MPRA |= AIPS_MPRA_MTR4(1)   /* Allow read access to DMA. */
                    | AIPS_MPRA_MTW4(1) /* Allow write access to DMA. */
                    | AIPS_MPRA_MPL4(1);/* Allow supervisor access to DMA. */

} /* End of configPeripheralBridgeForDMA */


/**
 * Initialize the external pin mapping such that the device LINFlexD_2 can be used without
 * additional hardware or wiring for the serial communication with the openSDA chip on the
 * DEVKIT-MPC5748G evaluation board.\n
 *   Other pin mappings are not supported. Each LINFlexD device has its own pins and
 * usually there are even more than one choices per device. If the code is run with another
 * device or on another board it depends which pins to be used. This cannot be anticipated
 * by the code offered here.
 */
static void configSIULForUseWithOpenSDA(void)
{
    /* This pin configuration is only useful if LINFlexD_2 is configured. */
    assert(IDX_LINFLEX_D == 2);
    
    /* The configuration of in- and output pins is documented in the Excel workbook
       IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx; which is embedded into the
       MCU reference manual PDF file. In Acrobat Reader, click View/Show/Hide/Navigation
       Panes/Attachments to find the Excel workbook.
         In the Excel workbook, on worksheet "IO Signal Table", each line refers to one of
       the possible functions of a port. The port is found in column A and most relevant
       are the settings "SIUL MSCR#" in column B, first line in the area of the given port,
       and "MSCR SSS" in column C. They designate the index of the MSCR register to use and
       the source selection, which is a major field of this register.
         The port has a fixed, hardwired, however chip-housing dependent one-by-one
       relation with a pin. This relation is found in columns O, P and Q.
         The source selection relates to the connection from an I/O device to the output
       buffer of the port. To connect an input of an I/O device with a port, a second
       source selection needs to be made, usually a port/pin but in a few cases is an
       alternate, internal device a possible source, too. (See RM 15.2.11, p. 388 and
       figure 15-2 on next page.) This requires the setting of field "IMCR SSS" in the
       other register array IMCR[]. The index into IMCR[] is found by search in the other
       worksheet "Input Muxing". Look for the port in question in column H or for the
       device to connect in column C. Column D holds the appropriate index into IMCR[].
         Note, the reference from worksheet "IO Signal Table" to worksheet "Input Muxing"
       is made by index of IMCR, too. In worksheet "IO Signal Table", in the sub-ordinated
       lines inside the area of the given port, column C, there is a second index stated
       for the input functions of a port. This index can be found in worksheet "Input
       Muxing" in column E in the line, we are looking for. For unclear reasons, this index
       plus 512 seems to be the index into the IMCR[] register array, too. For inputs, if
       we take worksheet "IO Signal Table", columns C and D, we could program IMCR.SSS
       without refering to the other worksheet. */
    SIUL2->MSCR[40 /* PC8 */] =
                SIUL2_MSCR_SSS(1)   /* Source signal is LIN2TX */
                | SIUL2_MSCR_SRC(3) /* Slew rate: Full drive without SR control */
                | SIUL2_MSCR_OBE(1) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(0) /* Disable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;
    SIUL2->MSCR[41 /* PC9 */] =
                SIUL2_MSCR_SSS(0)   /* Source signal for (disabled) ouput is default */
                | SIUL2_MSCR_SRC(0) /* Slew rate: Irrelevant for input */
                | SIUL2_MSCR_OBE(0) /* Enable output buffer */
                | SIUL2_MSCR_ODE(0) /* Disable open drain, drive both edges */
                | SIUL2_MSCR_SMC(1) /* Safe mode as after reset */
                | SIUL2_MSCR_APC(0) /* No analog I/O */
                | SIUL2_MSCR_IBE(1) /* Enable input buffer */
                | SIUL2_MSCR_HYS(1) /* Hysteresis as after reset */
                | SIUL2_MSCR_PUE(0) /* Pull up/down is disabled */
                | SIUL2_MSCR_PUS(0) /* Pull up/down doesn't care, is disabled */
                ;
   /* Conenct the LINFlexD_2 device with the input buffer of port PC9. */
   SIUL2->IMCR[202 /* LIN2RX */] = SIUL2_IMCR_SSS(2);/* 2: IO_PAD PC9 */

} /* End of configSIULForUseWithOpenSDA */



/**
 * Most of the LINFlexD devices can't themselves request DMA transfers on TX buffer not full
 * or RX buffer not empty. Instead, we use a regular timer tick to trigger the DMA. This is
 * possible since the timing of the UART is strictly regular. The character transmission
 * time is fixed and known and we can trigger the DMA quite accurate. However, we need of
 * course a small safety margin and can't exploit the serial bandwidth as much as it is
 * possible with the few DMA capable UART devices.
 *   @param baudRate
 * The Baud rate in Hz. Allow values range from 10 .. 1000000, proven values range from 300
 * till 115200 Hz.
 *   @remark
 * To match the correct Baud rates the code assumes a peripheral clock rate of 40 MHz for
 * the PIT timers.
 */
static void configPITAsDMATrigger(unsigned int baudRate)
{
    /* Disable timers during configuration. RM, 51.4.1, p. 2731. */
    PIT->MCR |= PIT_MCR_MDIS(1);

    /* The timer's cycle time is the rate of requesting a minor loop at the DMA. A minor
       loop is configured to be a single character. We need to match the character send
       time but need to consider a small margin - there's no handshake between DMA and
       LINFlexD and only by waiting long enough we can be sure that the UART is capable of
       taking the next character.
         The peripheral clock has been initialized to 40 MHz. The timer counts at this
       rate. 
         T_char = (8 payload bits + 1 start bit + 1 stop bit + 1 margin bit) / baudRate
         Counts/cycle = T_char / (1/f_clk) = f_clk / baudRate * 11
         We round the counts upwards in order to not endanger our margin.
         -1: See RM, 51.6 */
    const uint32_t PIT_clk = 40000000u
                 , countsPerCycle = (11*PIT_clk + baudRate-1) / baudRate;
    PIT->TIMER[PIT_TIMER_CHN_IDX].LDVAL = countsPerCycle-1;
    
    /* Enable timer operation again */
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    
    /* Clear possibly pending interrupt flags. */
    PIT->TIMER[PIT_TIMER_CHN_IDX].TFLG = PIT_TFLG_TIF(1);
    
    /* Don't enable interrupts by the timer and keep it still stopped. CHN: No chaining.
       See RM 51.4.10. */
    PIT->TIMER[PIT_TIMER_CHN_IDX].TCTRL = PIT_TCTRL_CHN(0)
                                          | PIT_TCTRL_TIE(0)
                                          | PIT_TCTRL_TEN(0);
} /* End of configPITAsDMATrigger */



/**
 * Halt the PIT timer, which triggers each DMA transfer of a single character from memory
 * to UART. Use startDMATrigger() the re-start the timer again.
 */
static inline void stopDMATrigger(void)
{
    /* See RM 51.4.10. */
    PIT->TIMER[PIT_TIMER_CHN_IDX].TCTRL = PIT_TCTRL_CHN(0)   /* No chaining of timers. */
                                          | PIT_TCTRL_TIE(0) /* No interrupts needed. */
                                          | PIT_TCTRL_TEN(0);/* Disable the timer channel. */

} /* End of stopDMATrigger */



/**
 * (Re-)start the PIT timer, which triggers each DMA transfer of a single character from
 * memory to UART. May be used after initialization with configPITAsDMATrigger() or after
 * the use of stopDMATrigger().
 */
static inline void startDMATrigger(void)
{
    /* See RM 51.4.10. */
    PIT->TIMER[PIT_TIMER_CHN_IDX].TCTRL = PIT_TCTRL_CHN(0)   /* No chaining of timers. */
                                          | PIT_TCTRL_TIE(0) /* No interrupts needed. */
                                          | PIT_TCTRL_TEN(1);/* Enable the timer channel. */

} /* End of startDMATrigger */




/**
 * Initialize the DMA device. The chosen channel is set up to write the contents of a
 * cyclic buffer of fixed address and size into the UART.
 *   @remark
 * The DMA initialization is mostly related to the DMA channel in use (which is considered
 * globally reserved for this purpose). However, this function accesses some DMA registers,
 * too, that affect all channels (e.g. channel arbitration). This function will require
 * changes, when the module is integrated into an environment, where different DMA channels
 * are applied for different, unrelated purposes.
 */
static void configDMA(void)
{
    /* Check preconditions for use of DMA with modulo source addressing. If this assertion
       fires it may point to a inconsistency between the C source code and the linker
       control file, which provides the address of the buffer. */
    assert(((uintptr_t)_serialOutRingBuf & SERIAL_OUTPUT_RING_BUFFER_IDX_MASK) == 0);
    
    /* The linker script is required to provide a properly aligned buffer without risking
       to loose lots of RAM because of the alignment. Therefore, the linker script itself
       has a constant for the size of the buffer. We need to double check the consistency
       of linker configuration with C code. */
    extern uint8_t ld_noBitsDmaRingBuffer[0] ATTRIB_DBG_ONLY;
    assert((uintptr_t)ld_noBitsDmaRingBuffer == SERIAL_OUTPUT_RING_BUFFER_SIZE_PWR_OF_TWO);

    /* Initialize write to ring buffer. */
    _serialOutRingBufIdxWrM = 0;
    
/// @todo Double check reset status and disable this code with same objective as for DCHPRI
    /* GRP1PRI, GRP0PRI: Group priorities, needs to be 1 and 0 in choseable order. We don't
       change the default after reset.
         EMLM: We don't use address offsets after minor and between two major loops, 0 means
       off.
         ERGA: 1: Round robin for group arbitration, 0: Priority controlled
         ERCA: 1: Round robin for channel arbitration, 0: Priority controlled
         EDBG: 1: Halt DMA when entering the debugger. By experience, for debugging of this
       multi-core this is rather counterproductive since mostly two cores are running while
       only one is being debugged.
         The other fields are zero after reset and we do neiter require nor change these
       values.
         Note, these settings affects all channels! */
    DMA->CR = DMA_CR_GRP1PRI(1)
              | DMA_CR_GRP0PRI(0)
              | DMA_CR_EMLM(0)
              | DMA_CR_ERGA(0)
              | DMA_CR_ERCA(0)
              | DMA_CR_EDBG(0);

    /// @todo We chose a low-priority channel for DMA. We need to enable preemptability, too, in order to let this become effective
#if 0
    /* Channel n Priority Register (DMA_DCHPRIn), RM 70.3.20: We use priority controlled
       channel arbitration. All active channels need to have different priorities. The
       standard configuration is to set the priority to the channel number. This is the
       reset default of the hardware and - in order to touch the global settings as little
       as possible - we are not going to change it. The reset default disables
       preemptability of all channels.
         Note, this configuration affects all channels! */
    unsigned int idxChn;
    for(idxChn=0; idxChn<DMA_DCHPRI_COUNT; ++idxChn)
    {
        /* ECP, 0x80: 1: Channel can be preempted, 0: cannot be preempted.
             DPA, 0x40: 0: Channel can preempt, 1: cannot preempt others.
             CHHPRI: Channel priority from 0..15. The macro DMA_DCHPRI_CHPRI filters the
           MSB of the loop counter so that we get two groups with priority identical to
           channel index in group. */
        DMA->DCHPRI[idxChn] = DMA_DCHPRI_ECP(0) 
                              | DMA_DCHPRI_DPA(0)
                              | DMA_DCHPRI_CHPRI(idxChn);
    }
#endif

#if 0
    /* Channel n Master ID Register (DMA_DCHMIDn), RM 70.3.21: Not touched. Default value
       after reset is to let the DMA engine use its own identity when accessing the buses.
         EMI: By setting this bit in this register, we can make the DMA engine pretend
       being the core that writes here into the register.
         All other bits are read only. */
    DMA->DCHMID[DMA_CHN_FOR_SERIAL_OUTPUT] = DMA_DCHMID_EMI(1);
#endif

    /* Initial load address of source data is the beginning of the ring buffer. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].SADDR = 
            DMA_TCD_SADDR_SADDR((__IO uint32_t)&_serialOutRingBuf[_serialOutRingBufIdxWrM]);

    /* SMOD: Source modulo feature is applied to implement the ring buffer.
       SSIZE: Read 1 byte per transfer.
       DMOD: Destination modulo feature is not used.
       DSIZE: Write 1 byte per transfer. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].ATTR =
                            DMA_TCD_ATTR_SMOD(SERIAL_OUTPUT_RING_BUFFER_SIZE_PWR_OF_TWO)
                            | DMA_TCD_ATTR_SSIZE(0 /* 2^n Byte */)
                            | DMA_TCD_ATTR_DMOD(0)
                            | DMA_TCD_ATTR_DSIZE(0 /* 2^n Byte */);
    
    /* After transfer, add 1 to the source address. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].SOFF = DMA_TCD_SOFF_SOFF(1);
    
    /* Transfer 1 byte per minor loop */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].NBYTES.MLNO = DMA_TCD_NBYTES_MLNO_NBYTES(1);
    
    /* After major loop, do not move the source pointer. Next transfer will read from next
       cyclic address. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].SLAST = DMA_TCD_SLAST_SLAST(0);

    /* Load address of destination is fixed. It is the byte input of the UART's FIFO. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].DADDR =
                                    DMA_TCD_DADDR_DADDR((__IO uint32_t)&LINFLEX->BDRL + 3);
                                        
    /* Initialize the beginning and current major loop iteration counts to zero. We will set
       it in the next call of sio_osWriteSerial. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].CITER.ELINKNO = DMA_TCD_CITER_ELINKNO_CITER(0)
                                                        | DMA_TCD_CITER_ELINKNO_ELINK(0);

    /* After transfer, do not alter the destination address. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].DOFF = DMA_TCD_DOFF_DOFF(0);

    /* After major loop, do not alter the destination address. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].DLASTSGA = DMA_TCD_DLASTSGA_DLASTSGA(0);
    
    /* The counter reload value for the major loops needs to be initialized identical to
       CITER to avoid a configuration error. See RM 70.3.35. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].BITER.ELINKNO =
                                            DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].CITER.ELINKNO;

    /* TCD Control and Status (DMA_TCDn_CSR), see RM 70.3.36, p. 3538.
         BWC: No stalling, 3: Stall for 8 cycles after each major cycle (i.e. after each
       character); fast enough for serial com.
         MAJORLINKCH: Index of other channel to start after major loop if channel linking
       is enabled.
         DONE: Will be set on completion and should be zero but we better clear it.
         MAJORELINK: Enable channel linking.
         ESG: Enable scatter/gather mode, i.e. dynamic linkage of TCDs through memory
       pointers.
         DREQ: Do a single transfer; don't repeat, don't link to other channels. 1: Do
       once, 0: Continue by repeating all.
         INTHALF: Generate interrrupt when major loop is half way done.
         INTMAJOR: Generate interrrupt when major loop has completed.
         Start: Initiate the DMA transfer specified by this TCD by SW. The flag is reset by
       HW as soon as the trigger command has been accepted. */
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].CSR = DMA_TCD_CSR_BWC(3)
                                              | DMA_TCD_CSR_MAJORLINKCH(0)
                                              | DMA_TCD_CSR_DONE(0)
                                              | DMA_TCD_CSR_MAJORELINK(0)
                                              | DMA_TCD_CSR_ESG(0)
                                              | DMA_TCD_CSR_DREQ(1)
                                              | DMA_TCD_CSR_INTHALF(0)
                                              | DMA_TCD_CSR_INTMAJOR(0)
                                              | DMA_TCD_CSR_START(0);

    /* Direct Memory Access Multiplexer (DMAMUX), RM, section 71, p. 3563: The DMA is
       triggered to do a minor loop cycle by the data request of some I/O device.
       Unfortunately is the LINFlex device on the DEVKIT-MPC5748G that is connected to the
       USB port not capable of triggering a DMA transfer on buffer empty. We use a dummy
       device instead, "Always on", and control the speed of the data transmission by a
       timer based trigger condition. This technique is restricted to the first two DMA
       channels of each group.
         ENBL: Enable the path from I/O device to DMA channel. RM, 71.4.1, NOTE: The DMA
       channel should first be disabled, then configured.
         TRIG: Enable the gating of the I/O data request with the timer trigger.
         SOURCE: Select the I/O device, "Always on" in our case. The devices are hardwired
       to the DMAMUX and the index of a specific device can be found in table 71-1, RM
       71.1, p. 3563. */
#if DMA_CHN_FOR_SERIAL_OUTPUT >= 0  &&  DMA_CHN_FOR_SERIAL_OUTPUT <= 1
    DMAMUX_0->CHCFG[DMA_CHN_FOR_SERIAL_OUTPUT] =
#elif DMA_CHN_FOR_SERIAL_OUTPUT >= DMAMUX_CHCFG_COUNT \
      &&  DMA_CHN_FOR_SERIAL_OUTPUT <= DMAMUX_CHCFG_COUNT+1
    DMAMUX_1->CHCFG[DMA_CHN_FOR_SERIAL_OUTPUT-DMAMUX_CHCFG_COUNT] =
#else
# error Configuration error: The chosen DMA channel does not permit timer triggering
#endif
    /* DMAMUX_n->CHCFG[] = */   DMAMUX_CHCFG_ENBL(1)
                                | DMAMUX_CHCFG_TRIG(1)
                                | DMAMUX_CHCFG_SOURCE(63);

    /* Reset all possibly pending error bits. */
    DMA->CERR = DMA_CERR_CAEI(1);
   
    /* Enable Request Register (DMA_ERQ), RM 70.3.7: Not touched yet, we don't enable the
       channel yet. This will be done in the next use of sio_osWriteSerial. */
    //DMA->SERQ = DMA_SERQ_SERQ(DMA_CHN_FOR_SERIAL_OUTPUT);

} /* End of configDMA */




/**
 * Initialization of the MPC5748G's I/O device LINFlexDn. The device is put into UART mode
 * for serial in-/output.
 *   @param baudRate
 * The Baud rate in Hz. Allow values range from 10 .. 1000000, proven values range from 300
 * till 256000 Hz. ("Proven" relates to the DEVKIT-MPC5748G connected to a Windows host
 * through openSDA and USB.)
 *   @remark
 * To match the correct Baud rates the code assumes a peripheral clock rate for the LINFlex
 * devices of 80 MHz.
 */
static void configLINFlex(unsigned int baudRate)
{
    /* Avoid over-/underflow down below. */
    if(baudRate < 10)
        baudRate = 10;
    else if(baudRate > 1000000)
        baudRate = 1000000;
    
    /* Please find the UART register description in the MCU ref. manual, section 45.5, p.
       1947ff. */

    /* Enter INIT mode. This is a prerequisite to access the other registers.
       INIT, 0x1: 1 init mode, 0 normal operation or sleep
       SLEEP, 0x2: 1 sleep mode, 0: normal operation */
    LINFLEX->LINCR1 = LINFLEX->LINCR1
                      & ~LINFlexD_LINCR1_SLEEP_MASK
                      | LINFlexD_LINCR1_INIT(0x1);

    /* Wait for acknowledge of the INIT mode. */
    while((LINFLEX->LINSR & LINFlexD_LINSR_LINS_MASK) != LINFlexD_LINSR_LINS(1))
    {}

    /* Configure the LINFlex to operate in UART mode
         The UART bit is set prior to other bits in the same register in
       order to become able to write the other configuration bits. See MCU manual, section
       45.5.5, p. 1988. */
    LINFLEX->UARTCR = LINFlexD_UARTCR_UART(1); /* 0 for UART, 1 for LIN */
    LINFLEX->UARTCR = LINFlexD_UARTCR_RFBM(0) /* RX: 0: Buffer mode, 1: FIFO mode */
                      | LINFlexD_UARTCR_TFBM(0) /* TX: 0: Buffer mode, 1: FIFO mode */
                      | LINFlexD_UARTCR_TDFL_TFC(0) /* Buffer takes n+1 chars per write */
                      | LINFlexD_UARTCR_RDFL_RFC(0) /* Interrupt after n+1 received chars */
                      | LINFlexD_UARTCR_PCE(0) /* 0: Parity off, 1: Parity on */
                      | LINFlexD_UARTCR_WL1(0) /* WL=01b: 8 Bit data */
                      | LINFlexD_UARTCR_WL0(1)
                      | LINFlexD_UARTCR_SBUR(0) /* RX: n+1 stop bits */
                      | LINFlexD_UARTCR_RxEn(1) /* Enable RX */
                      | LINFlexD_UARTCR_TxEn(1) /* Enable TX */
                      | LINFlexD_UARTCR_UART(1); /* Don't loose UART mode bit */
                         
    /* Configure baudrate:
       LIN_clk is 80 MHz (peripheral clock).
       LFDIV = LIN_clk / (16 * desired baudrate)
       LINIBRR.IBR = integer part of LFDIV
       LINFBRR.FBR = 16 * fractional part of LFDIV (after decimal point)

       Example:
       LFDIV = 80e6/(16*9600) = 520.83
       LINIBRR.IBR = 520
       LINFBRR.FBR = 16*0.83 = 13

       Up to 256000 bd worked well with terminal.exe and putty. 384000 bd failed with
       terminal.exe and putty, which is likely due to the openSDA/USB/COM gateways than
       because of the LINFlex/DMA device of the MCU. */
/// @todo Make use of constants in ccl.h
    const unsigned long LIN_clk = 80000000ul /* Hz */
                      , IBR = (LIN_clk/16u) / baudRate
                      , FBR = ((LIN_clk/16u) - IBR*baudRate)*16 / baudRate;
    assert((IBR & ~0xffffful) == 0  &&  (FBR & ~0xful) == 0);
    LINFLEX->LINIBRR = LINFlexD_LINIBRR_IBR(IBR);
    LINFLEX->LINFBRR = LINFlexD_LINFBRR_FBR(FBR);

    /* Clear all possibly pending status bits by w2c access. RM 45.5.6.
         The documentation is ambiguous how to reset bits DRFRFE and DTFTFF. The figure
       says write the value, the explanation text says write to clear. We assume the
       latter. */
    LINFLEX->UARTSR = 0x0000ffefu;

    /* LINIER: Interrupt enable, RM 45.5.2. The bits relate to the bits of same name in
       LINESR (error bits), LINSR and UARTSR (both status).
         BOIE: Buffer overrun could be read in handling of DBFIE
         DBFIE: should report FIFO full in reception mode
         DBEIETOIE: Should request new data for TX, UARTSR[TO] needs to be set
         DRIE: Interrupt on byte received, DRF set in UARTSR
         DTIE: Interrupt on byte sent, DTF set in UARTSR */
    LINFLEX->LINIER = LINFlexD_LINIER_DRIE(1);
    
    /* Global Control Register (GCR) RM 45.5.21.
         Note: Here, we need to select the same number of stop bits as for RX in
       UARTCR.SBUR.
         @todo For unclear reasons this register cannot be written although LINSR indicates
       that we are in init mode. The CPU runs into a machine check exception and manually
       trying it in the debugger yields a "can't write to memory" error. This problem stays
       unsolved; we anyway need to see the reset default value of the register, which is
       zero. */
#if 0
    LINFLEX->GCR = LINFlexD_GCR_TDFBM(0)   /* TX: 0: normal bit order, 1: MSB first */
                   | LINFlexD_GCR_RDFBM(0) /* RX: 0: normal bit order, 1: MSB first */
                   | LINFlexD_GCR_TDLIS(0) /* TX: 1: Invert all bits */
                   | LINFlexD_GCR_RDLIS(0) /* RX: 1: Invert all bits */
                   | LINFlexD_GCR_STOP(0); /* TX: n+1 stop bits */
#endif

    /* Enter normal mode again. */
    LINFLEX->LINCR1 &= ~LINFlexD_LINCR1_INIT_MASK;
    while((LINFLEX->LINSR & LINFlexD_LINSR_LINS_MASK) != LINFlexD_LINSR_LINS(2))
    {}
    
} /* End of configLINFlex */




/**
 * Interrupt handler for UART RX event. A received character is read from the UART hardware
 * and put into our ring buffer if there's space left. Otherwise the character is counted
 * as lost without further remedial action.
 */
static void linFlexRxInterrupt(void)
{
    /* Get the received byte. */
    /// @todo Record a buffer overrun bit in case the IRQ handler comes too slow
    const unsigned char c = (LINFLEX->BDRM & LINFlexD_BDRM_DATA4_MASK)
                            >> LINFlexD_BDRM_DATA4_SHIFT;
#ifdef DEBUG
    ++ sio_serialInNoRxBytes;
#endif

    /* To support different terminal characteristics, one character can be configured to
       be silently ignored in the input stream. This shall normally be the linefeed
       character. */
#if SERIAL_INPUT_FILTERED_CHAR != 0
    if(c != SERIAL_INPUT_FILTERED_CHAR)
#endif
    {
        /* Check for buffer full. Compute next write position at the same time. */
        volatile uint8_t * const pWrTmp = _pWrSerialInRingBuf
                       , * const pWrNext = pWrTmp < _pEndSerialInRingBuf? pWrTmp+1
                                                                        : &_serialInRingBuf[0];

        /* Put the byte into our buffer if there's enough room. */
        if(pWrNext != _pRdSerialInRingBuf)
        {
            *pWrTmp = c;
        
            /* Count the received end of line characters. (The variable is decremented on
               consumption of such a character.) */
            if(c == SERIAL_INPUT_EOL)
                ++ _serialInNoEOL;

            /* Update write position into ring buffer. This is at the same time the indication
               of the availability of the new character to the application API functions. */
            _pWrSerialInRingBuf = pWrNext;
        }
        else    
        {
            /* Buffer overrun, count lost character. */
            ++ sio_serialInLostBytes;
        }
    
        /* Ensure that all relevant memory changes are visible before we leave the
           interrupt. */
        std_fullMemoryBarrier();
        
    } /* End if(Character discarded?) */

    /* Acknowlege the interrupt by w2c and enable the next one at the same time. */
    assert((LINFLEX->UARTSR & LINFlexD_UARTSR_DRFRFE_MASK) != 0);
    LINFLEX->UARTSR = LINFlexD_UARTSR_DRFRFE_MASK;
    
} /* End of linFlexRxInterrupt */



/**
 * Our locally implemented interrupt handlers are registered at the operating system for
 * serving the required I/O devices (LINFlex).
 */
static void registerInterrupts(void)
{
    /* Interrupt offsets taken from MCU reference manual, see 23.1.2 INTC interrupt
       sources, p. 523ff, Table 23-1. */
#define IDX_LINFLEX_RX_IRQ  (376+3*(IDX_LINFLEX_D))

    /* Register our IRQ handler. */
    rtos_osRegisterInterruptHandler( &linFlexRxInterrupt
                                   , /* processorID */ INTC_IRQ_TARGET_CORE
                                   , /* vectorNum */ IDX_LINFLEX_RX_IRQ
                                   , /* psrPriority */ INTC_PRIO_IRQ_UART_FOR_SERIAL_INPUT
                                   , /* isPreemptable */ true
                                   );
#undef IDX_LINFLEX_RX_IRQ
} /* End of registerInterrupts */



/**
 * Initialize the I/O devices for serial output, in particular, these are the LINFlex
 * device plus a DMA channel to serve it. However, to regularly trigger the DMA we still
 * need a PIT timer and to commiunicate with the real world we need two ports from the
 * SIUL2. Finally, the peripheral bridge needs to be configured for granting access rights
 * to the DMA.
 *   @param baudRate
 * The Baud rate of in- and output in Hz. Allow values range from 10 .. 1000000, proven
 * values range from 300 till 115200 Hz.
 *   @remark
 * This function needs to be called at system initialization phase, when all External
 * Interrupts are still suspended.
 */
void sio_osInitSerialInterface(unsigned int baudRate)
{
    /* Grant access to the DMA controller to read from RAM and write to LINFlexD. */
    configPeripheralBridgeForDMA();
    
    /* Connect the LINFlexD_2 device with the external MCU pins so that on the evaluation
       board DEVKIT-MPC5748G communication with the host computer via the openSDA chip and
       the USB connection becomes possible. This step is device dependent and won't work
       with any other LINFlex than 2. */
    configSIULForUseWithOpenSDA();
    
    /* Configure the LINFlex device for serial in- and output. */
    configLINFlex(baudRate);

    /* Register the interrupt handler serial RX. */
    registerInterrupts();
    
    /* Initialize the PIT timer so that it triggers the DMA at maximum speed for given baud
       rate. */
    configPITAsDMATrigger(baudRate);

    /* Initialize DMA for writing into the UART. */
    configDMA();

    /* Empty receive buffer. */
    _pWrSerialInRingBuf =
    _pRdSerialInRingBuf = &_serialInRingBuf[0];
    
} /* End of sio_osInitSerialInterface */



/** 
 * System call handler for entry into data output. A byte string is sent through the serial
 * interface. Actually, the bytes are queued for sending and the function is non-blocking. 
 *   @return
 * The number of queued bytes is returned. Normally, this is the same value as argument \a
 * noBytes. However, the byte sequence can be longer than the currently available space in
 * the send buffer. (Its size is fixed and no reallocation strategy is implemented.) The
 * tranmitted message will be truncated if the return value is less than function argument
 * \a noBytes.
 *   @param PID
 * The process ID of the calling task.
 *   @param msg
 * The byte sequence to send. Note, this may be but is not necessarily a C string with zero
 * terminations. Zero bytes can be sent, too.
 *   @param noBytes
 * The number of bytes to send. For a C string, this will mostly be \a strlen(msg).
 *   @remark
 * This function must never be called directly. The function is only made for placing it in
 * the global system call table.
 */
unsigned int sio_scFlHdlr_writeSerial( uint32_t PID ATTRIB_UNUSED
                                     , const char *msg
                                     , unsigned int noBytes
                                     )
{
    /* The system call handler gets a pointer to the message to print. We need to validate
       that this pointer, coming from the untrusted user code doesn't break our safety
       concept. A user process may read only from all used ROM and all used RAM. */
    if(!rtos_checkUserCodeReadPtr(msg, noBytes))
    {
        /* The user specified memory region is not entirely inside the permitted,
           accessible range. This is a severe user code error, which is handeld with an
           exception, task abort and counted error. */
        rtos_osSystemCallBadArgument();
    }
    
    /* After checking the potentially bad user input we may delegate it to the "normal"
       function implementation. */
    return sio_osWriteSerial(msg, noBytes);

} /* End of sio_scFlHdlr_writeSerial */
        
        

        
/** 
 * Principal API function for data output. A byte string is sent through the serial
 * interface. Actually, the bytes are queued for sending and the function is
 * non-blocking.\n
 *   The function can be called from any context on any core. However, it must not be
 * called untill function sio_osInitSerialInterface() has completed.
 *   @return
 * The number of queued bytes is returned. Normally, this is the same value as argument \a
 * noBytes. However, the byte sequence can be longer than the currently available space in
 * the send buffer. (Its size is fixed and no reallocation strategy is implemented.) The
 * tranmitted message will be truncated if the return value is less than function argument
 * \a noBytes.
 *   @param msg
 * The byte sequence to send. Note, this may be but is not necessarily a C string with zero
 * terminations. Zero bytes can be send, too.
 *   @param noBytes
 * The number of bytes to send. For a C string, this will mostly be \a strlen(msg).
 *   @remark
 * This function must be called by trusted code in supervisor mode only. It belongs to the
 * sphere of trusted code itself.
 *   @remark
 * The mutual exclusion of different contexts from entering this function is implemented
 * using a locally defined critical section object of type \a
 * mtx_intercoreCriticalSection_t. Such a critical will likely cause a deadlock if
 * intermingled with other critical sections. Therefore, this function must not be called
 * from inside of another intercore critical section. Call from a local critical section
 * implemented by suspension of interrupts is however permitted.
 *   @remark
 * The duration of the execution of the critical section is of order O(noBytes); a memcpy()
 * is applied to copy the message bytes into the output buffer. This can mean a significant
 * long time of suspension of interrupts on the invoking and the other cores. Moreover,
 * there's no fair arbitration and if one core makes frequent use of this function then
 * others may suffer from starvation.
 */
unsigned int sio_osWriteSerial(const char *msg, unsigned int noBytes)
{
    /* Do not interfere with a (possibly) running DMA transfer if we don't really need to
       do anything. */
    if(noBytes == 0)
        return 0;

    /* The manipulation if the output buffer and the DMA registers is done inside a
       critical section, which implements mutual exclusion of all contexts on all cores. So
       any context on any core can safely apply this function. */
    static mtx_intercoreCriticalSection_t DATA_OS(critSec) = MTX_INTERCORE_CRITICAL_SECTION;
    mtx_osEnterIntercoreCriticalSection(&critSec);
    
    /* Stop the (possibly) running DMA channel.
         RM 70.5.8.1: Coherently stop a DMA channel with the ability of resuming it later. */
    stopDMATrigger();
    while((DMA->HRS & (0x1<<DMA_CHN_FOR_SERIAL_OUTPUT)) != 0)
    {}
    DMA->CERQ = DMA_CERQ_CERQ(DMA_CHN_FOR_SERIAL_OUTPUT);

    /* Note, most buffer addresses or indexes in this section of the code are
       understood as cyclic, i.e. modulo the buffer size. This is indicated by an M as
       last character of the affected symbols but not mentioned again in the code
       comments. */
#define MODULO(bufIdx)    ((bufIdx) & SERIAL_OUTPUT_RING_BUFFER_IDX_MASK)

    /* The current, i.e. next, transfer address of the DMA is the first (cyclic)
       address, which we must not touch when filling the buffer. This is the (current)
       end of the free buffer area. */
    const uint32_t idxEndOfFreeSpaceM = DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].SADDR;

    /* The cyclic character of the buffer can require one or two copy operations to
       place the message. We compute the concrete index ranges to copy.
         Note the -1: Same index values are used as empty-buffer-indication. Therefore
       it is not possible to entirely fill the buffer. */
    const unsigned int noBytesFree =
                            MODULO(idxEndOfFreeSpaceM - _serialOutRingBufIdxWrM - 1);

    /* Avoid buffer overrun by saturation of the user demand and report the number of
       overrun events and the number of lost message characters. */
    if(noBytes > noBytesFree)
    {
        ++ sio_serialOutNoTruncatedMsgs;
        sio_serialOutNoLostMsgBytes += noBytes - noBytesFree;
        noBytes = noBytesFree;
    }

    /* How many bytes would fit until we have to wrap? This limits the first copy
       operation. */
    const unsigned int noBytesTillEnd = MODULO(- _serialOutRingBufIdxWrM);
    unsigned int noBytesAtEnd;
    if(noBytes <= noBytesTillEnd)
    {
        /* The message fits into the rest of the linear buffer, no wrapping required. */
        noBytesAtEnd = noBytes;
    }
    else
    {
        /* A portion of the message is placed at the end of the linear buffer and the
           rest of the message at its beginning. */
        noBytesAtEnd = noBytesTillEnd;
    }

    /* Always copy the first part of the message to the current end of the linear
       buffer. The serial buffer, shared between all accessing cores and DMA, is located in
       uncached memory so that the writes go into main memory, where it can be accessed by
       DMA. */
    uint8_t * const pDest = &_serialOutRingBuf[MODULO(_serialOutRingBufIdxWrM)];
    assert(pDest + noBytesAtEnd <= &_serialOutRingBuf[SERIAL_OUTPUT_RING_BUFFER_SIZE]);
    memcpy(pDest, msg, noBytesAtEnd);

    /* Copy the second part of the message at the beginning of the linear buffer if
       there is a remainder. */
    if(noBytes > noBytesAtEnd)
    {
        assert(noBytes - noBytesAtEnd < sizeof(_serialOutRingBuf));
        memcpy(&_serialOutRingBuf[0], msg+noBytesAtEnd, noBytes-noBytesAtEnd);
    }           

    /* Apply a memory barrier to ensure that all data is in memory before we start the DMA
       transfer. */
    std_fullMemoryBarrier();

    _serialOutRingBufIdxWrM = _serialOutRingBufIdxWrM + noBytes;

    /* Start DMA. We can do this unconditionally because we have filtered the special
       situation of not writing any new character. */
   
    const uint32_t noBytesPending = MODULO(_serialOutRingBufIdxWrM - idxEndOfFreeSpaceM);
    assert(noBytesPending > 0);
    
    /* Set the number of bytes to transfer to the UART by DMA. */
    assert((unsigned)noBytesPending <= SERIAL_OUTPUT_RING_BUFFER_SIZE-1);
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].CITER.ELINKNO =
    DMA->TCD[DMA_CHN_FOR_SERIAL_OUTPUT].BITER.ELINKNO =
                                            DMA_TCD_CITER_ELINKNO_CITER(noBytesPending)
                                            | DMA_TCD_CITER_ELINKNO_ELINK(0);

    /* Resume the DMA channel. Re-enabling the PIT timer, which requests the bytes from the
       DMA, ensures that we again see a full timer period before it triggers the DMA for the
       next character: The LINFlex may easily be still busy serializing the last character
       from the previous DMA transfer.
         RM 70.5.8.2: Resume a previously stopped DMA channel. */
    DMA->SERQ = DMA_SERQ_SERQ(DMA_CHN_FOR_SERIAL_OUTPUT);
    startDMATrigger();
    ++ sio_serialOutNoDMATransfers;

    mtx_osLeaveIntercoreCriticalSection(&critSec);

    /* noBytes is saturated to buffer size-1 and can't overflow in conversion to signed. */
    return noBytes;
    
} /* End of sio_osWriteSerial */




/**
 * Application API function to read a single character from serial input or EOF if there's
 * no such character received meanwhile.\n
 *   The function is not inter-core safe and must be called solely from execution contexts
 * running on core #INTC_IRQ_TARGET_CORE. It must not be called untill function
 * sio_initSerialInterface() has completed.
 *   @return
 * The function is non-blocking. If the receive buffer currently contains no character it
 * returns EOF (-1). Otherwise it returns the earliest received character, which is still
 * in the buffer.
 *   @remark
 * The return of EOF does not mean that the stream has been closed. It's just a matter of
 * having no input data temporarily. On reception of the more characters the function will
 * continue to return them.
 *   @remark
 * This function must be called by trusted code in supervisor mode only. It belongs to the
 * sphere of trusted code itself.
 */
signed int sio_osGetChar(void)
{
    signed int c;
    
    /* Reading the ring buffer is done in a critical section to ensure mutual exclusion
       with the it filling interrupt. */
    uint32_t msr = rtos_osEnterCriticalSection();
    {
        /* Check for buffer empty. */
        if(_pRdSerialInRingBuf != _pWrSerialInRingBuf)
        {
            c = *_pRdSerialInRingBuf;

            /* Keep track of the received but not yet consumed end of line characters. (The
               variable is incremented on reception of such a character.) */
            if(c == SERIAL_INPUT_EOL)
            {
                assert(_serialInNoEOL > 0);
                -- _serialInNoEOL;
            }

            /* Update read position in the ring buffer. This is at the same time the indication
               towards the interrupt of having the character consumed. */
            volatile uint8_t * const pRdTmp = _pRdSerialInRingBuf;
            _pRdSerialInRingBuf = pRdTmp < _pEndSerialInRingBuf ? pRdTmp+1 
                                                                : &_serialInRingBuf[0];
        }
        else    
        {
            /* Nothing in buffer, return EOF. */
            c = -1;
        }
    }
    rtos_osLeaveCriticalSection(msr);

    return c;

} /* End of sio_osGetChar */




/**
 * The function reads a line of text from serial in and stores it into the string pointed
 * to by \a str. It stops when the end of line character is read and returns an
 * empty string if no such character has been received since system start or the previous
 * call of this function.\n
 *   Note, the latter condition means that the function is non-blocking - it doesn't wait
 * for further serial input.\n
 *   The end of line character, if found, is not copied into \a str. A terminating zero
 * character is automatically appended after the characters copied to \a str.\n
 *   The end of line character is a part of this module's compile time configuration, see
 * #SERIAL_INPUT_EOL. Standard for terminals is '\r', not '\n'. The other character out of
 * these two can or cannot be part of the copied line of text, see
 * #SERIAL_INPUT_FILTERED_CHAR. This, too, is a matter of compile time configuration.\n
 *   The function is not inter-core safe and must be called solely from execution contexts
 * running on core #INTC_IRQ_TARGET_CORE. It must not be called untill function
 * sio_osInitSerialInterface() has completed.
 *   @return
 * This function returns \a str on success, and NULL on error or if not enough characters
 * have been received meanwhile to form a complete line of text.\n
 *   Note the special situation of a full receive buffer without having received any end of
 * line character. The system would be stuck - later received end of line characters would
 * be discarded because of the full buffer and this function could never again return a
 * line of text. Therefore the function will return the complete buffer contents at once as
 * a line of input.
 *   @param str
 * This is the pointer to an array of chars where the C string is stored. \a str is the
 * empty string if the function returns NULL.
 *   @param sizeOfStr
 * The capacity of \a str in Byte. The maximum message length is one less since a
 * terminating zero character is always appended. A value of zero is caught by assertion.\n
 *   Note, if \a sizeOfStr is less than the line of text to be returned then the complete
 * line of text will nonetheless be removed from the receive buffer. Some characters from
 * the input stream would be lost.
 *   @remark
 * The serial interface is not restricted to text characters. If the source sends a zero
 * byte then this byte will be placed into the client's buffer \a str and it'll truncate
 * the message that is interpreted as C string.
 *   @remark
 * This function is a mixture of C lib's \a gets and \a fgets: Similar to \a gets it
 * doesn't put the end of line character into the result and similar to \a fgets it
 * respects the size of the receiving buffer.
 *   @remark 
 * Both, no data available yet and an empty input line of text return the same, empty C
 * string in \a str, but they differ in function return code, which is NULL or \a str,
 * respectively.
 *   @remark
 * On buffer overrun, i.e. if the client code didn't invoke this function fast enough, an
 * end of line won't be written into the internal receive buffer and the truncated line
 * will be silently concatenated with its successor. You may consider observing the global
 * variable \a sio_serialInLostBytes to recognize this situation. Note, because of the race
 * conditions between serial I/O interrupt and application software you can not clearly
 * relate a change of these variables to a particular message you get from this function.
 * In particular, you must not try to reset the counter prior to a read operation in order
 * to establish such a relation. Your application will just know that there is some garbled
 * input.
 *   @remark
 * This function must be called by trusted code in supervisor mode only. It belongs to the
 * sphere of trusted code itself.
 */
char *sio_osGetLine(char str[], unsigned int sizeOfStr)
{
    if(sizeOfStr == 0)
    {
        assert(false);
        return NULL;
    }
    else
    {
        /* Reserve space for a terminating zero byte. */
        -- sizeOfStr;
    }
        
    char *result = &str[0]
       , *pWrApp = result;

    /* Reading the ring buffer is done in a critical section to ensure mutual exclusion
       with the it filling interrupt. */
    uint32_t msr = rtos_osEnterCriticalSection();
    {
        volatile uint8_t * pRd = _pRdSerialInRingBuf;

        /* If no line has been received then we need to double-check that the buffer is not
           entirely full; if so we were stuck: No new characters (i.e. no newline) could
           ever be received and the application would never again get a line of input.
             If we find a full buffer then we consider the entire buffer as a single line
           of input. */
        if(_serialInNoEOL == 0)
        {
            volatile uint8_t * const pWr = _pWrSerialInRingBuf
                           , * const pWrNext = pWr == _pEndSerialInRingBuf
                                               ? &_serialInRingBuf[0]
                                               : pWr + 1;
            if(pWrNext == pRd)
            {

                /* pWr points immediately before pRd: Buffer is currently full. Copy
                   complete contents as a (pseudo-) line of text. */
                unsigned int noBytesToCopy = SERIAL_INPUT_RING_BUFFER_SIZE-1;
                /// @todo Count and report lost characters at least in DEBUG compilation
                if(noBytesToCopy > sizeOfStr)
                    noBytesToCopy = sizeOfStr;

                /* Copy the ring buffer (limited to the requested number of characters).
                   Consider wrapping at the end of the linear area. */
                const unsigned int noBytesTillEnd = (unsigned int)(_pEndSerialInRingBuf - pRd)
                                                    + 1;
                unsigned int noBytesAtEnd;
                if(noBytesTillEnd >= noBytesToCopy)
                {
                    /* The requested number of characters is still found at the end of the
                       ring buffer. */
                    noBytesAtEnd = noBytesToCopy;
                }
                else
                {
                    /* We need to copy a second character sequence from the beginning of
                       the ring buffer into the destination. */
                    noBytesAtEnd = noBytesTillEnd;
                }
                
                assert(noBytesAtEnd <= sizeOfStr);
                memcpy(str, (const uint8_t*)pRd, noBytesAtEnd);
                if(noBytesAtEnd < noBytesToCopy)
                {
                    memcpy( str+noBytesAtEnd
                          , (const uint8_t*)&_serialInRingBuf[0]
                          , noBytesToCopy-noBytesAtEnd
                          );
                }
                
                /* The client code expects a zero terminated C string. */
                str[sizeOfStr] = '\0';

                /* Adjust read pointer such that it represents the empty buffer. */
                _pRdSerialInRingBuf = pWr;
            }
            else
            {
                /* No complete line of text has been read so far. */
                str[0] = '\0';
                result = NULL;
            }
        }
        else
        {
            /* A line of text is available in the buffer. We copy the bytes in naive
               loop instead of using memcpy, since we anyway need such a loop to find the
               next EOL character. */
            while(true)
            {
                /* We can have an empty buffer here, there's at minimum the EOL left. */
                assert(pRd != _pWrSerialInRingBuf);
                
                /* Get next input character. */
                char c = (char)*pRd;
                
                /* Loop termination is the first matching EOL character. */
                if(c == SERIAL_INPUT_EOL)
                {
                    /* Acknowldge consumption of EOL character but do not return the
                       (redundant) EOL character to the application. */
                    -- _serialInNoEOL;
                    
                    /* Advance read pointer: The EOL is consumed by this call of the
                       function. */
                    _pRdSerialInRingBuf = pRd == _pEndSerialInRingBuf? &_serialInRingBuf[0]
                                                                     : pRd + 1;
                    
                    /* End the copy loop. */
                    break;
                }
                
                /* Copy next character only if destination buffer still has room left. We
                   continue to consume the rest of the line if this is not the case. */
                if(sizeOfStr > 0)
                {
                    * pWrApp++ = *pRd;
                    -- sizeOfStr;
                }
                /// @todo else Count and report lost characters at least in DEBUG compilation
                
                /* Cyclically advance read pointer. */
                pRd = pRd == _pEndSerialInRingBuf? &_serialInRingBuf[0]: pRd + 1;
                
            } /* End while(All characters to consume from ring buffer) */
            
            /* Write the terminating zero byte to make the text line a C string. */
            *pWrApp = '\0';
        }
    }
    rtos_osLeaveCriticalSection(msr);

    return result;

} /* End of sio_osGetLine */


