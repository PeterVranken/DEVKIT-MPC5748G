/*
 * This sub-ordinated linker script file builds a ROM table that contains the information
 * about the initialized RAM sections of the processes. The table is read by the startup
 * code in order to fill the RAM sections from their image in ROM.
 *   It has been generated from the information in spreadsheet processes_ld.xlsx, worksheet
 * Processes.
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
LONG(ADDR(.data))
LONG(LOADADDR(.data))
LONG(SIZEOF(.data))

LONG(ADDR(.data.P4))
LONG(LOADADDR(.data.P4))
LONG(SIZEOF(.data.P4))

LONG(ADDR(.data.P3))
LONG(LOADADDR(.data.P3))
LONG(SIZEOF(.data.P3))

LONG(ADDR(.data.P2))
LONG(LOADADDR(.data.P2))
LONG(SIZEOF(.data.P2))

LONG(ADDR(.data.P1))
LONG(LOADADDR(.data.P1))
LONG(SIZEOF(.data.P1))

LONG(ADDR(.sdata))
LONG(LOADADDR(.sdata))
LONG(SIZEOF(.sdata))

LONG(ADDR(.sdata2))
LONG(LOADADDR(.sdata2))
LONG(SIZEOF(.sdata2))

