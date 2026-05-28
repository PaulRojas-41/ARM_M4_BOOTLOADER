/*
 * bl_ota_handler.c
 *
 *  Created on: May 16, 2026
 *      Author: Paul Rojas
 */

#include "bl_flash_ops.h"
#include "drv_ll_flash.h"
#include "stm32f4xx_hal_flash.h"
#include "bl_ota_handler.h"

uint32_t appl_header_updated[4];

uint8_t bl_check_ota_request(void)
{
	/* Check OTA flag during bootloader execution */
	appl_read_flash(0x08008000, appl_header_updated);

	if(appl_header_updated[0] == OTA_FLAG_EN)
		return 1;
	else
		return 0;
}

void bl_clear_ota_request(void)
{
	/* Bootloader sequence to clear OTA flag request */
	drv_unlock_flash();

	appl_read_flash(0x08008000, appl_header_updated);

	appl_header_updated[0] = OTA_FLAG_DIS;

	drv_erase_flash();

	appl_write_flash(0x8008000, appl_header_updated, 1);

	drv_lock_flash();
}
