#ifndef DEL_DELAY_INCLUDED
#define DEL_DELAY_INCLUDED
/**
 * @file del_delay.h
 * Definition of global interface of module del_delay.S
 *
 * Copyright (C) 2017 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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


/*
 * Global type definitions
 */


/*
 * Global data declarations
 */


/*
 * Global prototypes
 */

/** This function does nothing but consumes an exactely determined amount of CPU execution
    time before it returns. "Consumption of CPU time" means that not the elapsed world time
    counts; all interrupts etc. which interrupt the execution of this function won't be
    accounted. The blocking time of this function until return therefore is greater or
    equal to \a tiCpuInUs Microseconds.
      @param tiCpuInUs
    The CPU executes further useless code this number of Microseconds. */
void del_delayMicroseconds(unsigned int tiCpuInUs);

#endif  /* DEL_DELAY_INCLUDED */
