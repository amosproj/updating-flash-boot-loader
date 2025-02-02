// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Sebastian Rodriguez <r99@melao.de>

//============================================================================
// Name        : can_driver.h
// Author      : Sebastian Rodriguez
// Version     : 0.1
// Copyright   : MIT
// Description : Header for CAN Driver
//============================================================================

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

/**********/
/*INCLUDES*/
/*********/
#include "Ifx_types.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int canTransmitMessage(uint32_t canMessageID, uint8_t* data, size_t size);

#endif /*CAN_DRIVER_H*/


