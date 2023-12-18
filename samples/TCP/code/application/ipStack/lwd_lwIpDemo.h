#ifndef LWD_LWIP_DEMO_INCLUDED
#define LWD_LWIP_DEMO_INCLUDED
/**
 * @file lwd_lwIpDemo.h
 * Definition of global interface of module lwd_lwIpDemo.c
 *
 * Copyright (C) 2023 FEV.io GmbH, Germany (mailto:vranken@fev.io)
 *
 * All rights reserved. Reproduction in whole or in part is prohibited without the written
 * consent of the copyright owner.
 */

/*
 * Include files
 */

#include "typ_types.h"

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

/** Initialize the IP demo. */
void lwd_lwIpDemo_init(void);

/** Main function of IP protocol stack, which drives lwIP's protocol state machine. */
void lwd_lwIpDemo_main( unsigned int noNotificationsRx
                      , unsigned int noNotificationsTx
                      , unsigned int noNotificationsTimer
                      );

/*
 * Global inline functions
 */

#endif  /* LWD_LWIP_DEMO_INCLUDED */
