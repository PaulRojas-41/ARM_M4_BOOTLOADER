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
#include "bl_jump2_appl.h"

volatile uint32_t appl_header_updated[4];

uint8_t bl_check_ota_request(void)
{
	/* Check OTA flag during bootloader execution */
	if(bl_fls_read_ota_flag() == OTA_FLAG_EN)
		return 0;
	else
		return 1;
}

void bl_clear_ota_request(void)
{
	/* Bootloader sequence to clear OTA flag request */
	drv_unlock_flash();

	bl_fls_clear_ota_flag(APPL_HEADER_START_ADDR);

	drv_lock_flash();
}
