// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>

//============================================================================
// Name        : flash.h
// Author      : Dorothea Ehrl
// Version     : 0.1
// Copyright   : MIT
// Description : Flash wrapper for Bootloader
//============================================================================

#ifndef FLASH_H_
#define FLASH_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxFlash.h"

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

int writeProgramFlash(IfxFlash_FlashType flashModule, uint32 flashStartAddr, uint32 data[], size_t dataSize);
uint32 verifyProgramFlash(uint32 flashStartAddr, uint32 data[], size_t dataSize);

int writeDataFlash(IfxFlash_FlashType flashModule, uint32 address, uint32 data[], size_t data_size);
uint32 verifyDataFlash(uint32 flashStartAddress, uint32 data[], size_t dataSize);

#endif /* FLASH_H_ */
