/*
 * appl_flash_operations.c
 *
 *  Created on: May 19, 2026
 *      Author: Paul Rojas
 */

#include "bl_flash_ops.h"
#include "drv_ll_flash.h"
#include "bl_jump2_appl.h"
#include "bl_ota_handler.h"

void bl_fls_clear_ota_flag(uint32_t fls_sector_address)
{
	uint32_t *ptr_to_flash = (uint32_t *)fls_sector_address;

	/* HW initialization flash driver */
	wait_flash_op();
	drv_write_flash();

	/* clear appl_header OTA flag */
	if(!bl_check_ota_request())
	{
		/* OTA indicator is enabled by appl */
		ptr_to_flash[0] = 0x00000000;
	}

	wait_flash_op();
	FLASH->CR &=~(1 << 0);  //deactivates the write to flash operation
}

uint32_t bl_fls_read_ota_flag(void)
{
	uint32_t *ptr_to_flash = (uint32_t *)APPL_HEADER_START_ADDR;

	return ptr_to_flash[0];
}

/* Placeholder method */
void bl_fls_write_ota_fw(uint32_t fls_sector_address, uint32_t *fls_ota_data)
{
	uint32_t *ptr_to_flash = (uint32_t *)fls_sector_address;
	uint32_t pages;
	/* In order to proceed to write we need to evaluate:
	 * 1. Address's sector will gives us the following info:
	 * 	  a) Size of the sector: 16KB, 64, or 128 kb
	 * 2. However appl_header->size: will determine the number of shifts through pages: 22KB = 1024*22 = 22,528 (uint8) / 4 elements of uin32: 5,632 times
	 * 3. For each uint32 byte we should check the integrity before put it on flash */

	/* Page shift: for 22kb, we will do this 5,632 times */
	for(int j = 0; j < pages; j++)
	{
		/* uint32 or uint8 format elements to be written on each page shifted + 4 */
		for(int i = 0; i < 4; i++)
		{
			ptr_to_flash[i]= fls_ota_data[i];
		}

		ptr_to_flash = ptr_to_flash + FLS_SHIFT_PAGE;
	}

	/* Mem bank 2: 11 sectors starting from 0x0810 0000 - 0x0810 3FFFF */
}

void appl_read_flash(uint32_t fls_sector_address, uint32_t *fls_data)
{
	uint32_t *get_header = (uint32_t *)fls_sector_address;

	for(int i = 0; i < sizeof(fls_data); i++)
		fls_data[i] = *(get_header + i);
}

void appl_unlock_flash()
{
	drv_unlock_flash();
}

void appl_lock_flash()
{
	drv_lock_flash();
}
