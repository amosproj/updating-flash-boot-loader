//============================================================================
// Name        : led_driver_TC375_LK.h
// Author      : Paul Roy
// Version     : 0.2
// Copyright   : MIT
// Description : LED-Driver header file for TC375 LK
//============================================================================

#ifndef LED_DRIVER_TC375_LK_H_
#define LED_DRIVER_TC375_LK_H_

/******************************************************************************/
/*---------------------------------Includes-----------------------------------*/
/******************************************************************************/

#include "IfxPort.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#define NUM_LEDS        2
#define LED_PORTS       ((Ifx_P*[]) { &MODULE_P00, &MODULE_P00 })
#define LED_PINS        ((uint8[]) { 5, 6})

/******************************************************************************/
/*----------------------------Function Prototypes-----------------------------*/
/******************************************************************************/

void ledInitDriver(void);

#endif
