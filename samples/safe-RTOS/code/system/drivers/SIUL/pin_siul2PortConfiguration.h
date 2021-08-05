#ifndef PIN_SIUPORTCONFIGURATION_INCLUDED
#define PIN_SIUPORTCONFIGURATION_INCLUDED
/**
 * @file pin_siuPortConfiguration.h
 * Definition of global interface of the I/O port driver pin_siuPortConfiguration.c.\n
 *   Note, the port driver supports the two MCUs MPC5748G and MPC5775B/E. Two similar but
 * not identical header files are provided with the driver and your application code will
 * only include the suiting one: This one, pin_siul2PortConfiguration.h, if the MCU
 * MPC5748G is used and the other one, pin_siuPortConfiguration.h, for the MPC5775B/E.\n
 *   The configuration of in- and output pins is documented in the Excel workbook
 * IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx, which is embedded into the MCU
 * reference manual PDF file. In Acrobat Reader, click View/Show/Hide/Navigation
 * Panes/Attachments to find the Excel workbook.\n
 *   In the Excel workbook, on worksheet "IO Signal Table", each line refers to one of
 * the possible functions of a port. The port is found in column A and most relevant
 * are the settings "SIU_A PCR#" in column B, and "PCR PA" in column C. They designate
 * the index of the PCR register to use and the source selection, which is a major
 * field of this register.\n
 *   The port has a fixed, hardwired, however chip-housing dependent one-by-one
 * relation with a pin. This relation is found in columns I and J and on tab "416
 * PBGA".\n
 *   The source selection relates to the connection from an I/O device to the output
 * buffer of the port.\n
 *   To connect an input of an I/O device with a port, a selection of one out of
 * different offered input sources needs to be made besides the port configuration
 * itself. Selecting the wanted input means configuring an input multiplexer register.
 * There are nine such registers and they contain a varying number of multiplexers
 * each. You need to know, which multiplexer register to use and which multiplxer
 * inside the register and which value to configure for this multiplexer. All of this
 * is found either in the description of the registers (RM, sections 8.2.66ff,
 * pp.374ff) or by name of the signal in the Excel workbook
 * MPC5775B_MPC5775E_System_IO_Definition.xlsx, worksheet "Input Muxing". In the Excel
 * worksheet look for the wanted device (column B, "Instance") and/or for the wanted
 * signal (column H, "Source Signal"). Columns D, E and F provide the needed three
 * pieces of information for the multiplexer configuration.
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


/*
 * Global type definitions
 */

/** Settings of a port, which is configured as output. Most of the settings relate to RM48,
    15.2.11 SIUL2 Multiplexed Signal Configuration Register (SIUL2_MSCRn), pp.388ff. */
typedef struct pin_portOutCfg_t
{
    /** The index of the port as used in
        IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx worksheet "IO Signal
        Table", column C. */
    uint16_t idxPort_MSCR;
    
    /** Source selection as used in IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx,
        worksheet "IO Signal Table", column D. */
    uint8_t idxPortSource_SSS;
    
    /** A port uses either open drain (\a true) or it actively drives both logical states
        (\a false). */
    bool enableOpenDrain_ODE;
    
    /** The maximum slew rate can be limited. Range is 0..3. 3 means maximum slew rate, or
        no limitation. */
    uint8_t maxSlewRate_SRC;
    
} pin_portOutCfg_t;



/** Settings of a port, which is configured as input. Most of the settings relate to RM48,
    15.2.11 SIUL2 Multiplexed Signal Configuration Register (SIUL2_MSCRn), pp.388ff, and
    the input multiplxer configuration, 15.2.12 SIUL2 Input Multiplexed Signal
    Configuration Register (SIUL2_IMCRn), pp.391f. */
typedef struct pin_portInCfg_t
{
    /** The index of the port as used in
        IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx, worksheet "IO Signal
        Table", column C. */
    uint16_t idxPort_MSCR;
    
    /** Source selection as used in IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx,
        worksheet "IO Signal Table", column D, and at the same time same file, worksheet
        "Input Muxing", column F. */
    uint8_t idxPortSource_SSS;
    
    /** The input can be used with hysteresis for better stability of input values. */
    bool enableHysteresis_HYS;
    
    /** A pull up or pull down resistor can be enabled for the input. */
    enum pin_portInPullResistor_t 
    {
        pin_pullRes_none,
        pin_pullRes_pullUp,
        pin_pullRes_pullDown,
        
    } pullUpDownCfg;
    
    /** Zero based index of the related input multiplexer register IMCR. This index is
        found in worksheet "Input Muxing", column D. It can be identified in worksheet "IO
        Signal Table", column C, too, but careful, then you need to subtract the constant
        512 from the index specified there. */
    uint16_t idxMultiplexerRegister;
    
    /** The signal selection for the selected multiplexer. The required value is found in
        IO_Signal_Description_and_Input_Multiplexing_Tables.xlsx, worksheet "Input Muxing",
        column F. It can be identified in worksheet "IO
        Signal Table", column D, too.
          Range is basically 0..15 but not all of the values are supported by all of the
        inputs and values greater than 7 seem to be not used at all. */
    uint8_t idxInputSource_MUXSELVALUE;

} pin_portInCfg_t;


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** Configure an output port. */
void pin_siuConfigureOutput(const pin_portOutCfg_t *pPortCfg);

/** Configure an input port. */
void pin_siuConfigureInput(const pin_portInCfg_t *pPortCfg);


/*
 * Global inline functions
 */


#endif  /* PIN_SIUPORTCONFIGURATION_INCLUDED */
