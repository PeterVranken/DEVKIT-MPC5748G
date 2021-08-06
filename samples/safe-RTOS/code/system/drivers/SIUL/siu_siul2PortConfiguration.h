#ifndef SIU_SIUPORTCONFIGURATION_INCLUDED
#define SIU_SIUPORTCONFIGURATION_INCLUDED
/**
 * @file siu_siuPortConfiguration.h
 * Definition of global interface of the I/O port driver siu_siuPortConfiguration.c.\n
 *   Note, the port driver supports the two MCUs MPC5748G and MPC5775B/E. Two similar but
 * not identical header files are provided with the driver and your application code will
 * only include the suiting one: This one, siu_siul2PortConfiguration.h, if the MCU
 * MPC5748G is used and the other one, siu_siuPortConfiguration.h, for the MPC5775B/E.\n
 
 * The configuration of in- and output pins is documented in the Excel workbook
 * IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx, which is embedded into the
 * MCU reference manual PDF file. In Acrobat Reader, click View/Show/Hide/Navigation
 * Panes/Attachments to find the Excel workbook.\n
 *   In the Excel workbook, on worksheet "IO Signal Table", each line refers to one of
 * the possible functions of a port. The port is found in column A and most relevant
 * are the settings "SIUL MSCR#" in column B, first line in the area of the given port,
 * and "MSCR SSS" in column C. They designate the index of the MSCR register to use and
 * the source selection, which is a major field of this register.\n
 *   The port has a fixed, hardwired, however chip-housing dependent one-by-one
 * relation with a pin. This relation is found in columns O, P and Q.\n
 *   The source selection relates to the connection from an I/O device to the output
 * buffer of the port. To connect the input of an I/O device with a port, a second
 * source selection needs to be made, usually a port/pin but in a few cases an
 * alternate, internal device is a possible source, too. (See RM48 15.2.11, p. 388 and
 * figure 15-2 on next page.) This requires the setting of field "IMCR SSS" in the
 * other register array IMCR[]. The index into IMCR[] is found by search in the other
 * worksheet "Input Muxing". Look for the port in question in column H or for the
 * device to connect in column C. Column D holds the appropriate index into IMCR[].\n
 *   Note, the reference from worksheet "IO Signal Table" to worksheet "Input Muxing" 
 * is made by index of IMCR, too. In worksheet "IO Signal Table", in the sub-ordinated
 * lines inside the area of the given port, column C, there is a second index stated
 * for the input functions of a port. This index can be found in worksheet "Input
 * Muxing" in column E in the line, we are looking for. This index plus 512 is the
 * index into the IMCR[] register array, too. For inputs, if we take worksheet "IO
 * Signal Table", columns C and D, we could program IMCR.SSS without refering to the
 * other worksheet. (The "512" results from the offsets of the MSCR and the IMCR
 * registers. The two register arrays have an address offset of 2k or 512 32 Bit words.
 * Indexing MSCR with the value found in column C of worksheet "IO Signal Table" is
 * identical to writing to the right IMCR, identified on worksheet "Input Muxing".)
 *
 * @note References "RM48" (reference manual) in this module refer to "MPC5748G Reference
 * Manual", document number: MPC5748GRM, Rev. 6, 10/2017.
 *
 * @note References "PM48" (pin mapping) in this module refer to file
 * "IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx", which is an attachment of
 * RM48.
 *
 * Copyright (C) 2021 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <typ_types.h>


/*
 * Defines
 */

/** The invalid selection of an input multiplexer. To be used for configuration field \a
    idxMultiplexerRegister, if an input is not routed to an I/O device but used as
    simple GPIO. */
#define SIU_INPUT_MULTIPLEXER_UNUSED    (UINT_T_MAX(uint16_t))


/*
 * Global type definitions
 */

/** A pull up or pull down resistor can be enabled for in- and outputs. Principal use case
    is a pull-up in combination with an open drain output. All possible configurations are
    enumerated here. */
typedef enum siu_portInPullResistor_t 
{
    siu_pullRes_none,
    siu_pullRes_pullUp,
    siu_pullRes_pullDown,

} siu_portInPullResistor_t;


/** Settings of a port, which is configured as output. Most of the settings relate to RM48,
    15.2.11 SIUL2 Multiplexed Signal Configuration Register (SIUL2_MSCRn), pp.388ff. */
typedef struct siu_portOutCfg_t
{
    /** Source selection as used in IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx,
        worksheet "IO Signal Table", column D. */
    uint8_t idxPortSource_SSS;
    
    /** An output can be input at the same time: The SW can read back the driven output
        value. This is particularly useful with open drain outputs. */
    bool enableReadBack;
    
    /** A port uses either open drain (\a true) or it actively drives both logical states
        (\a false). */
    bool enableOpenDrain_ODE;
    
    /** A pull up or pull down resistor can be enabled for the output. Principal use case
        is a pull-up in combination with an open drain output. */
    siu_portInPullResistor_t pullUpDownCfg;
    
    /** The maximum slew rate can be limited. Range is 0..3. 3 means maximum slew rate, or
        no limitation. */
    uint8_t maxSlewRate_SRC;
    
} siu_portOutCfg_t;



/** Settings of a port, which is configured as input. Most of the settings relate to RM48,
    15.2.11 SIUL2 Multiplexed Signal Configuration Register (SIUL2_MSCRn), pp.388ff, and
    the input multiplxer configuration, 15.2.12 SIUL2 Input Multiplexed Signal
    Configuration Register (SIUL2_IMCRn), pp.391f. */
typedef struct siu_portInCfg_t
{
    /** The input can be used with hysteresis for better stability of input values. */
    bool enableHysteresis_HYS;
    
    /** A pull up or pull down resistor can be enabled for the input. */
    siu_portInPullResistor_t pullUpDownCfg;
    
    /** Zero based index of the related input multiplexer register IMCR. This index is
        found in worksheet "Input Muxing", column D. It can be identified in worksheet "IO
        Signal Table", column C, too, but careful, then you need to subtract the constant
        512 from the index specified there.\n
          Note, if the port is used as simple GPIO and the input doesn't need to be routed
        to an input of a particular I/O device then no multiplexer should be configured.
        You need to specify the invalid index #SIU_INPUT_MULTIPLEXER_UNUSED for such a
        signal. */
    uint16_t idxMultiplexerRegister;
    
    /** The signal selection for the selected multiplexer. The required value is found in
        IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx, worksheet "Input Muxing",
        column F. It can be identified in worksheet "IO
        Signal Table", column D, too.\n
          Range is basically 0..15 but not all of the values are supported by all of the
        inputs and values greater than 7 seem to be not used at all.\n
          The value doesn't care, if \a idxMultiplexerRegister is set to
        #SIU_INPUT_MULTIPLEXER_UNUSED. */
    uint8_t idxInputSource_MUXSELVALUE;

} siu_portInCfg_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */


/*
 * Global inline functions
 */


#endif  /* SIU_SIUPORTCONFIGURATION_INCLUDED */
