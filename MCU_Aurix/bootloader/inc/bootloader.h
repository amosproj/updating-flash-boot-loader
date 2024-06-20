// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>
// SPDX-FileCopyrightText: 2024 Michael Bauer <mike.bauer@fau.de>
// SPDX-FileCopyrightText: 2024 Sebastian Rodriguez <r99@melao.de>

//============================================================================
// Name        : loader.h
// Author      : Dorothea Ehrl, Michael Bauer, Sebastian Rodriguez
// Version     : 0.2
// Copyright   : MIT
// Description : Loader initial file
//============================================================================

#ifndef BOOTLOADER_INC_LOADER_H_
#define BOOTLOADER_INC_LOADER_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/

extern int jumpToASW;

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

void init_bootloader(void);
void cyclicProcessing(void);
void deinit_bootloader(void);

void bootloaderJumpToASW(void);
void show_flash(void);

#endif /* BOOTLOADER_INC_LOADER_H_ */
