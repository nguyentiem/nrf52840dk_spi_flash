/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <string.h>


#define SPI_FLASH_TEST_REGION_OFFSET 0x00000
#define SPI_FLASH_READ_OFFSET 0x0f000
#define SPI_FLASH_SECTOR_SIZE        0x200000


uint8_t buf[1000];

void read(const struct device *flash_dev)
{
  int rc;
		memset(buf, 0, 1000);
	rc = flash_read(flash_dev, SPI_FLASH_READ_OFFSET, buf, 1000);
	if (rc != 0) {
		printf("Flash read failed! %d\n", rc);
		return;
	}

	for(int i =0 ; i<1000 ; i++)
	{
		printf("%x ",buf[i]); 
	}
}

// void write(const struct device *flash_dev)
// {
  
// }

void erase(const struct device *flash_dev)
{
      printf("\nTest 1: Flash erase\n");
   int rc; 
	/* Full flash erase if SPI_FLASH_TEST_REGION_OFFSET = 0 and
	 * SPI_FLASH_SECTOR_SIZE = flash size
	 */
	rc = flash_erase(flash_dev, SPI_FLASH_TEST_REGION_OFFSET,
			 SPI_FLASH_SECTOR_SIZE);
	if (rc != 0) {
		printf("Flash erase failed! %d\n", rc);
	} else {
		printf("Flash erase succeeded!\n");
	}
}


void single_sector_test(const struct device *flash_dev)
{
	// const uint8_t expected[] = { 0x55, 0xaa, 0x66, 0x99 };
	// const size_t len = sizeof(expected);
	
	int rc;

	// printf("\nPerform test on single sector");
	/* Write protection needs to be disabled before each write or
	 * erase, since the flash component turns on write protection
	 * automatically after completion of write and erase
	 * operations.
	 */
	

	// printf("\nTest 2: Flash write\n");

	// printf("Attempting to write %zu bytes\n", len);
	// rc = flash_write(flash_dev, SPI_FLASH_TEST_REGION_OFFSET, expected, len);
	// if (rc != 0) {
	// 	printf("Flash write failed! %d\n", rc);
	// 	return;
	// }



	// if (memcmp(expected, buf, len) == 0) {
	// 	printf("Data read matches data written. Good!!\n");
	// } else {
	// 	const uint8_t *wp = expected;
	// 	const uint8_t *rp = buf;
	// 	const uint8_t *rpe = rp + len;

	// 	printf("Data read does not match data written!!\n");
	// 	while (rp < rpe) {
	// 		printf("%08x wrote %02x read %02x %s\n",
	// 		       (uint32_t)(SPI_FLASH_TEST_REGION_OFFSET + (rp - buf)),
	// 		       *wp, *rp, (*rp == *wp) ? "match" : "MISMATCH");
	// 		++rp;
	// 		++wp;
	// 	}
	// }
}


int main(void)
{
	const struct device *flash_dev = DEVICE_DT_GET(DT_ALIAS(spi_flash0));

	if (!device_is_ready(flash_dev)) {
		printk("%s: device not ready.\n", flash_dev->name);
		return 0;
	}

	printf("\n%s SPI flash testing\n", flash_dev->name);
	printf("==========================\n");

	// single_sector_test(flash_dev);
	erase(flash_dev);
    // read(flash_dev); 
	return 0;
}
