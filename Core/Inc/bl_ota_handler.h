/*
 * bl_ota_handler.h
 *
 *  Created on: May 16, 2026
 *      Author: Paul Rojas
 */

#ifndef INC_BL_OTA_HANDLER_H_
#define INC_BL_OTA_HANDLER_H_

#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#define OTA_FLAG_EN  0xCE
#define OTA_FLAG_DIS 0x00


#define FLS_ERASE_APPL_HEADER_SECTOR 0x02
#define FLS_ERASE_APPL_SECTOR        0x03

uint8_t bl_check_ota_request(void);
void bl_clear_ota_request(void);

#endif /* INC_BL_OTA_HANDLER_H_ */
