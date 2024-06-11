// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>
// SPDX-FileCopyrightText: 2024 Michael Bauer <mike.bauer@fau.de>


//============================================================================
// Name        : flash_driver.h
// Author      : Dorothea Ehrl, Michael Bauer
// Version     : 0.2
// Copyright   : MIT
// Description : Flash wrapper for Bootloader
//============================================================================

#ifndef FLASH_H_
#define FLASH_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

#include <stdbool.h>
#include <stdint.h>

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Global variables--------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*-------------------------------------------------Data Structures---------------------------------------------------*/
/*********************************************************************************************************************/
 
/*********************************************************************************************************************/
/*--------------------------------------------Private Variables/Constants--------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------Function Prototypes------------------------------------------------*/
/*********************************************************************************************************************/

bool flashWrite(uint32 flashStartAddr, uint32 data[], size_t dataSize);
bool flashVerify(uint32 flashStartAddr, uint32 data[], size_t dataSize);
uint8_t *flashRead(uint32 flashStartAddr, size_t dataBytesToRead);

#endif /* FLASH_H_ */
