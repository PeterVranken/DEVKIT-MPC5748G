#ifndef SIU_SIUPORTCONFIGURATION_INCLUDED
#define SIU_SIUPORTCONFIGURATION_INCLUDED
/**
 * @file siu_siuPortConfiguration.h
 * Definition of global interface of the I/O port driver siu_siuPortConfiguration.c.\n
 *   Note, the port driver supports the two MCUs MPC5748G and MPC5775B/E. Two similar but
 * not identical header files are provided with the driver and your application code will
 * only include the suiting one: This one, siu_siuPortConfiguration.h, if the MCU
 * MPC5775B/E is used and the other one, siu_siul2PortConfiguration.h, for the MPC5748G.\n
 *   The configuration of in- and output pins is documented in the Excel workbook
 * MPC5775B_MPC5775E_System_IO_Definition.xlsx; which is embedded into the MCU
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
 * is found either in the description of the registers (RM75, sections 8.2.66ff,
 * pp.374ff) or by name of the signal in the Excel workbook
 * MPC5775B_MPC5775E_System_IO_Definition.xlsx, worksheet "Input Muxing". In the Excel
 * worksheet look for the wanted device (column B, "Instance") and/or for the wanted
 * signal (column H, "Source Signal"). Columns D, E and F provide the needed three
 * pieces of information for the multiplexer configuration.
 *
 * @note References "RM75" in this module refer to "MPC5775E/MPC5775B Reference Manual",
 * document number: MPC5775E, Rev. 1, 05/2018.
 *
 * @note References "PM75" in this module refer to file
 * "MPC5775B_E-ReferenceManual.System_IO_Definition.xlsx", which is an attachment of RM75.
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
#define SIU_INPUT_MULTIPLEXER_UNUSED    (UINT_T_MAX(uint8_t))


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


/** Settings of a port, which is configured as output. Most of the settings relate to RM,
    8.2.13 Pad Configuration Register (SIU_PCRn), pp.241ff. */
typedef struct siu_portOutCfg_t
{
    /** Source selection as used in MPC5775B_MPC5775E_System_IO_Definition.xlsx,
        worksheet "IO Signal Table", column C. */
    uint8_t idxPortSource_PA;
    
    /** An output can be input at the same time: The SW can read back the driven output
        value. This is particularly useful with open drain outputs. */
    bool enableReadBack;
    
    /** A port uses either open drain (\a true) or it actively drives both logical states
        (\a false). */
    bool enableOpenDrain_ODE;
    
    /** A pull up or pull down resistor can be enabled for the output. Principal use case
        is a pull-up in combination with an open drain output. */
    siu_portInPullResistor_t pullUpDownCfg;
    
    /** Drive strength from min to max. Range is 0..3. */
    uint8_t driveStrength_DSC;
    
    /** The maximum slew rate can be limited. This is a 2 Bit value:\n
          b00: Half drive strength with slew control enabled\n
          b01: Full drive strength with slew control enabled\n
          b10: Half drive strength with slew control disabled\n
          b11: Full drive strength with slew control disabled */
    uint8_t maxSlewRate_SRC;
    
} siu_portOutCfg_t;


/** Settings of a port, which is configured as input. Most of the settings relate to RM,
    8.2.13 Pad Configuration Register (SIU_PCRn), pp.241ff and the multiplxer
    configuration, RM, sections 8.2.66ff Input Multiplexing RegisterN (SIU_IMUXN),
    pp.373ff. */ 
typedef struct siu_portInCfg_t
{
    /** Source selection as used in MPC5775B_MPC5775E_System_IO_Definition.xlsx,
        worksheet "IO Signal Table", column C. */
    uint8_t idxPortSource_PA;
    
    /** The input can be used with hysteresis for better stability of input values. */
    bool enableHysteresis_HYS;
    
    /** A pull up or pull down resistor can be enabled for the input. */
    siu_portInPullResistor_t pullUpDownCfg;

    /** Zero based index of the related input multiplexer register. The index is at the same
        time the number N in its name. See RM, sections 8.2.66ff Input Multiplexing RegisterN
        (SIU_IMUXN), pp.373ff. Range is [0..5, 7, 10, 12].\n
          Note, some inputs are hardwired with a specific port. In which case no related
        multiplexer can be configured. You need to specify the invalid index
        #SIU_INPUT_MULTIPLEXER_UNUSED for such a signal. */
    uint8_t idxMultiplexerRegister;
    
    /** Each multiplexer register contains up to 16 2-Bit multiplexers. This is the zero
        based index of the multiplxer inside the selected register. The index is at the same
        time the number N in the name of the multiplexer.\n
          The range is basically 0..15 but depends on the selected multiplexer register.
        Most of the registers do not support all 16 multiplexers. Please consult RM,
        sections 8.2.66ff, pp.373ff.\n
          The value doesn't care, if \a idxMultiplexerRegister is set to
        #SIU_INPUT_MULTIPLEXER_UNUSED. */
    uint8_t idxMultiplexer;
    
    /** The signal selection for the selected multiplexer. The required value is found in
        MPC5775B_MPC5775E_System_IO_Definition.xlsx, worksheet "Input Muxing", column F.
        Moreover, the possible choices are documented in the description of the selected
        multiplexer register, RM, sections 8.2.66ff, pp.373ff.\n 
          Range is basically 0..3 but not all of the values are supported by all of the
        inputs.\n
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
