// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>
// SPDX-FileCopyrightText: 2024 Michael Bauer <mike.bauer@fau.de>


//============================================================================
// Name        : flash_driver.h
// Author      : Dorothea Ehrl, Michael Bauer, Paul Roy
// Version     : 0.3
// Copyright   : MIT
// Description : Flash wrapper for Bootloader
//============================================================================

#ifndef FLASH_H_
#define FLASH_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "Ifx_types.h"

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
void flashDriverInit(void);
void flashResetErasedSectionsCtr(void);

bool flashWrite(uint32_t flashStartAddr, uint32_t data[], size_t dataSize);
bool flashVerify(uint32_t flashStartAddr, uint32_t data[], size_t dataSize);
uint8_t *flashRead(uint32_t flashStartAddr, size_t dataBytesToRead);
uint32_t flashCalculateChecksum(uint32_t flashStartAddr, uint32_t lengthInBytes);

#endif /* FLASH_H_ */
