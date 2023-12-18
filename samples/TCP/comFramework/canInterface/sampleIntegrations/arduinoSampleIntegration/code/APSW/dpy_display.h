#ifndef DPY_DISPLAY_INCLUDED
#define DPY_DISPLAY_INCLUDED
/**
 * @file dpy_display.h
 * Definition of global interface of module dpy_display.cpp
 *
 * Copyright (C) 2013 Peter Vranken (mailto:Peter_Vranken@Yahoo.de)
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

#include <Arduino.h>

#ifdef __cplusplus
# include <LiquidCrystal.h>
#endif

/*
 * Defines
 */

/** An application may use the display from a single or several tasks. A mutex is applied
    for access serialization in the latter case but not needed in the former case. Set the
    macro to either 0 (display is used by a single task only) or 1 (display is used by two
    or more tasks). */
#define DPY_MULTI_TASKING_SUPPORT   0 
    
/** This module has an interface and a header file, which can be used from either plain C
    or C++ modules. The C API uses this type decoration. */
#ifdef __cplusplus
# define DPY_C_API extern "C"
#else
# define DPY_C_API
#endif

    
/*
 * Global type definitions
 */

#ifdef __cplusplus
/** A single object of this class exists. It encapsulates the functionality of the Arduino
    standard library LiquidCrystal and reduces it to the printf functions needed for this
    application of the display. Furthermore the print functions implement all needed task
    synchronization: The display is shared by several tasks, which will all write their
    specific information into the display. */
class dpy_display_t: private LiquidCrystal
{
public:
    /** The constructor. It is not accessible from outside as there is only one instance of
        this class. This single object is public, not the constructor to make it. */
    dpy_display_t(void);

    /** Print a greeting after reset. */
    void printGreeting();
    
    /** To be called once first and typically only once at all: The invariant background
        parts of the layout are printed. This print may overwrite any of the others. */
    void printBackground(void);

    /** Pseudo-analog display of a numeric value as bar of variable length. */
    void printValueAsBar(uint8_t value, uint8_t fullScale);
    
    /** Formatted printing of the current values of torque and power. */
    void printTqAndPwr(int16_t torque, int16_t power);

    /** Print a short status string. */
    void printStatus(const char *statusText);
    
    /** Formatted printing of current time. */
    void printTime(uint8_t hour, uint8_t min, uint8_t sec);

    /** Formatted printing of voltage. */
    void printVoltage(float voltage);

    /** Formatted printing of current CPU load. Scaling: 0.5% */
    void printCpuLoad(uint8_t cpuLoad);

private:
    inline boolean acquireMutex(void);
    inline void releaseMutex(void);

}; /* End of class dpy_display_t */
#endif


/*
 * Global data declarations
 */

#ifdef __cplusplus
/** The one and only display object. */
extern dpy_display_t dpy_display;
#endif


/*
 * Global prototypes
 */


/** Print a greeting after reset.
      @remark C++ clients should not use this API but access the global object \a
    dpy_display instead. */
DPY_C_API void dpy_printGreeting();
    
/** To be called once first and typically only once at all: The invariant background
    parts of the layout are printed. This print may overwrite any of the others.
      @remark C++ clients should not use this API but access the global object \a
    dpy_display instead. */
DPY_C_API void dpy_printBackground(void);

/** Pseudo-analog display of value as bar of variable length.
      @remark C++ clients should not use this API but access the global object \a
    dpy_display instead. */
DPY_C_API void dpy_printValueAsBar(uint8_t value, uint8_t fullScale);

/** Formatted printing of the current values of torque and power.
      @remark C++ clients should not use this API but access the global object \a
    dpy_display instead. */
DPY_C_API void dpy_printTqAndPwr(int16_t torque, int16_t power);

/** Print a short status string. */
DPY_C_API void dpy_printStatus(const char *statusText);

#endif  /* DPY_DISPLAY_INCLUDED */
