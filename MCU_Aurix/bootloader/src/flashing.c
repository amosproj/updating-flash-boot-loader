// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Dorothea Ehrl <dorothea.ehrl@fau.de>
// SPDX-FileCopyrightText: 2024 Michael Bauer <mike.bauer@fau.de>
// SPDX-FileCopyrightText: 2024 Wiktor Pilarczyk <wiktorpilar99@gmail.com>

//============================================================================
// Name        : flashing.c
// Author      : Dorothea Ehrl, Michael Bauer, Wiktor Pilarczyk
// Version     : 0.1
// Copyright   : MIT
// Description : Manages flash data
//============================================================================

#define MEM(address)                *((uint32_t *)(address))      /* Macro to simplify the access to a memory address */

#include "flashing.h"
#include "uds_comm_spec.h"
#include "memory.h"
#include "flash_driver.h"
#include "flash_driver_TC375_LK.h"

enum FLASHING_STATE {DOWNLOAD, UPLOAD, TRANSFER_DATA, IDLE};
uint32_t flashBuffer[MAX_ISOTP_MESSAGE_LEN/4];
uint32_t flashTransferDataCtr;

typedef struct {
    uint32_t buffer;
    uint32_t startAddr;
    uint32_t endAddr;
    enum FLASHING_STATE state;
    uint32_t checksum;
} Flashing_Internal;

Flashing_Internal flashing_int_data;

//============================================================================
// Internal helper function
//============================================================================

uint32_t flashingGetDIDData(uint16_t DID){
    uint32_t data = 0;

    uint8_t len, nrc;
    uint8_t *read = readData(DID, &len, &nrc);
    if(!nrc){
        if(len == 4){ // uint32_t
            data |= (read[0] << 24);
            data |= (read[1] << 16);
            data |= (read[2] << 8);
            data |= read[3];
        }
    }
    free(read);
    return data;
}

static inline bool addrInCoreRangeCheck(uint32_t addr, uint32_t data_len, uint16_t start_addr_ID, uint16_t end_addr_ID) {
    uint32_t core_start_add = flashingGetDIDData(start_addr_ID);
    uint32_t core_end_add = flashingGetDIDData(end_addr_ID);
    if((core_start_add > 0 && core_end_add > 0) && (addr >= core_start_add && addr < core_end_add)){
        // address belongs to core
        if(addr + (data_len-1) <= core_end_add)
            return true;
    }
    return false;
}

static inline size_t insertDataForFlashing(uint8_t* data, uint32_t data_len){

    uint32_t data_ctr = 0;
    size_t flash_ctr = 0;

    uint32 temp = 0;
    uint32 shifted = 0;

    for(int idx = 0; idx < sizeof(flashBuffer) && data_ctr < data_len ; idx++){
        temp = 0;
        shifted = 0;

        for(int i = 0; i < sizeof(uint32); i++){

            if(FLASHING_FLASHING_ENDIANNESS){
                shifted = (uint32)data[data_ctr] << 8*(sizeof(uint32)-1-i);
            } else{
                shifted = (uint32)data[data_ctr] << 8*i;
            }
            temp |= shifted;
            data_ctr++;

            if(data_ctr >= data_len)
                break;
        }

        flashBuffer[idx] = temp;
        flash_ctr++;
    }
    return flash_ctr;
}

//============================================================================
// Public
//============================================================================
void flashingInit(void){
    flashing_int_data.buffer = 0;
    flashing_int_data.startAddr = 0;
    flashing_int_data.endAddr = 0;
    flashing_int_data.state = IDLE;
}

uint8_t flashingRequestDownload(uint32_t address, uint32_t data_len){

    // Not used since request download should always be able to reset
    //if (flashing_int_data.state != IDLE)
    //    return FBL_RC_UPLOAD_DOWNLOAD_NOT_ACCEPTED;

    // Check on Flash Memory to accept download
    if(!addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE0, FBL_DID_BL_WRITE_END_ADD_CORE0) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE1, FBL_DID_BL_WRITE_END_ADD_CORE1) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE2, FBL_DID_BL_WRITE_END_ADD_CORE2) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_ASW_KEY, FBL_DID_BL_WRITE_END_ADD_ASW_KEY) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CAL_DATA, FBL_DID_BL_WRITE_END_ADD_CAL_DATA))
    {
        flashing_int_data.state = IDLE;
        return FBL_RC_REQUEST_OUT_OF_RANGE;
    }

    // Store base address for flashing
    flashing_int_data.startAddr = address;
    flashing_int_data.endAddr = flashing_int_data.startAddr + data_len - 1; // Idx 0 also counts

    // Identify the max package size
    flashing_int_data.buffer = MAX_ISOTP_MESSAGE_LEN - PFLASH_PAGE_LENGTH; // Excluding: SID + address (5 bytes), keep some buffer, try to keep pages

    // Setup Flashing Mode
    flashing_int_data.state = TRANSFER_DATA;

    // Reset the TransferData counter
    flashTransferDataCtr = 0;

    return 0;
}

uint8_t flashingRequestUpload(uint32_t address, uint32_t data_len){
    
    if(!addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE0, FBL_DID_BL_WRITE_END_ADD_CORE0) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE1, FBL_DID_BL_WRITE_END_ADD_CORE1) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CORE2, FBL_DID_BL_WRITE_END_ADD_CORE2) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_ASW_KEY, FBL_DID_BL_WRITE_END_ADD_ASW_KEY) &&
       !addrInCoreRangeCheck(address, data_len, FBL_DID_BL_WRITE_START_ADD_CAL_DATA, FBL_DID_BL_WRITE_END_ADD_CAL_DATA))
    {
        return FBL_RC_REQUEST_OUT_OF_RANGE;
    }
    
    flashing_int_data.checksum = flashCalculateChecksum(address, data_len);
    
    return 0;
}

uint8_t flashingTransferData(uint32_t address, uint8_t* data, uint32_t data_len){
    if (flashing_int_data.state != TRANSFER_DATA || flashing_int_data.startAddr == 0 || flashing_int_data.endAddr == 0)
        return FBL_RC_REQUEST_SEQUENCE_ERROR;

    if(address < flashing_int_data.startAddr || address+(data_len-1) > flashing_int_data.endAddr){ // Idx 0 also counts
        return FBL_RC_REQUEST_OUT_OF_RANGE;
    }

    // Debugging
    if(flashTransferDataCtr == 4){
         __nop();
    }

    // Store flash data to temp flash buffer
    size_t flashLen = insertDataForFlashing(data, data_len);
    bool flashed = flashWrite(address, flashBuffer, flashLen);

    if(!flashed){
        return FBL_RC_FAILURE_PREVENTS_EXEC_OF_REQUESTED_ACTION;
    }

    flashTransferDataCtr++;
    return 0;
}

uint8_t flashingTransferExit(uint32_t address){
    if(address != 0 && flashing_int_data.startAddr != address)
        return FBL_RC_REQUEST_OUT_OF_RANGE;

    flashing_int_data.startAddr = 0;
    flashing_int_data.endAddr = 0;
    flashing_int_data.buffer = 0;
    flashTransferDataCtr = 0;

    flashing_int_data.state = IDLE;
    return 0;
}

uint32_t flashingGetFlashBufferSize(void){
    return flashing_int_data.buffer;
}

uint32_t flashingGetChecksum(void) {
    return flashing_int_data.checksum;
}

uint32_t flashingGetGoodKey(void){
    return flashingGetDIDData(FBL_DID_BL_KEY_GOOD_VALUE);
}

uint32_t flashingGetGoodKeyStored(void){
    uint32_t goodKeyAddr = flashingGetDIDData(FBL_DID_BL_KEY_ADDRESS);

    uint32_t goodKeyStored = MEM(goodKeyAddr);
    if(FLASHING_GOOD_KEY_STORED_ENDIANNESS){
        goodKeyStored = ((goodKeyStored>>24)  & 0x000000ff) |  // move byte 3 to byte 0
                        ((goodKeyStored<<8)   & 0x00ff0000) |  // move byte 1 to byte 2
                        ((goodKeyStored>>8)   & 0x0000ff00) |  // move byte 2 to byte 1
                        ((goodKeyStored<<24)  & 0xff000000);   // byte 0 to byte 3
    }
    return goodKeyStored;
}
