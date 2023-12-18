#include <Arduino.h>

#include "rtos.h"

/* This stub is required by the implementation of delay() in
   $(ARDUINO_HOME)/hardware/arduino/avr/cores/arduino/wiring.c. The Arduino installation
   has a file hooks.c, which provides a default implementation of the function (also as
   empty dummy) but hook.c doesn't compile for unclear reasons. So this is a kind of
   substitute. */
void yield(void)
{}

int main(void)
{
	init();

#if defined(USBCON)
	USBDevice.attach();
#endif

    /* The next function will never return. */
    rtos_initRTOS();
    
    /* This code is never reached. */
	return 0;
}
