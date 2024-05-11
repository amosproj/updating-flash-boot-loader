// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>

//============================================================================
// Name        : loader.c
// Author      : Dorothea Ehrl
// Version     : 0.1
// Copyright   : MIT
// Description : Loader initial file
//============================================================================

#include "loader.h"

#include "can_driver.h"
#include "can_init.h"
#include "flash.h"
#include "led_driver.h"

void show_can(void)
{
    init_led_driver();

    canInitDriver();
    canTransmitMessage(CAN_DEBUG_ID,CAN_DEBUG_DATA, 1);
}

void show_flash(void)
{
    init_led_driver();

    size_t data_size = 64;
    uint32 data[data_size];
    for(size_t i = 0; i < data_size; i++)
    {
        data[i] = i;
    }

    int ret_p = writeProgramFlash(PROGRAM_FLASH_0, PROGRAM_FLASH_0_BASE_ADDR, data, data_size);

    uint32 errors_p = verifyProgramFlash(PROGRAM_FLASH_0_BASE_ADDR, data, data_size);
    if(errors_p == 0 && ret_p == 0)
    {
        led_on(LED2);
    }

    int ret_d = writeDataFlash(DATA_FLASH_0, DATA_FLASH_0_BASE_ADDR, data, data_size);

    uint32 errors_d = verifyDataFlash(DATA_FLASH_0_BASE_ADDR, data, data_size);
    if(errors_d == 0 && ret_d == 0)
    {
        led_on(LED1);
    }
}
