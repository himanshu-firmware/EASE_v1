#pragma once 


// include the flash partitions 
#include "esp_flash_partitions.h"


/// define the meta data sectors
#define OTA_META_DATA_SECTOR0     0
#define OTA_META_DATA_SECTOR1     1
#define OTA_META_DATA_MAX_SECTORS 2

// define the max partitions for applications
#define MAX_OTA_PARTITIONS 2
#define MAX_DFU_PARTITIONS 2

// define the extra partition subtype
#define PART_SUBTYPE_DATA_BOOT_DUMP     0x25UL
#define PART_SUBTYPE_DATA_OTA_META_DATA 0x35UL


#define PART_SUBTYPE_APP_DFU_0 0x40UL
#define PART_SUBTYPE_APP_DFU_1 0x45UL
#define PART_SUBTYPE_APP_APP_0 0x50UL
#define PART_SUBTYPE_APP_APP_1 0x55UL

#define CUSTOM_PARTITION_TABLE_OFFSET 0x13000UL
#define CUSTOM_PARTITION_TABLE_MAX_LEN 0xc00UL

///=============== flash sector size 
#define FLASH_SECTOR_SIZE 0x1000
#define FLASH_BLOCK_SIZE 	0x10000
#define MMAP_ALIGNED_MASK 	(SPI_FLASH_MMU_PAGE_SIZE - 1)
#define MMU_FLASH_MASK    (~(SPI_FLASH_MMU_PAGE_SIZE - 1))

#define MAX_OTA_PARTITIONS 2 
#define MAX_APP_PARTITIONS 2

typedef struct __ESP_FLASH_PARTITIONS__
{
    esp_partition_pos_t  ota_meta_partition[MAX_OTA_PARTITIONS];
    esp_partition_pos_t  boot_dump_partition;
    esp_partition_pos_t  app_partition[MAX_APP_PARTITIONS];

}esp_flash_partition_struct_t;



/// @brief map the free pages 
/// @param  void 
/// @return free pages in the flash 
uint32_t esp_mmap_get_free_pages(void);


/// @brief map the flash addr to cache for cpu to read 
/// @param src_addr 
/// @param size 
/// @return succ/err
const void * esp_flash_mmap(uint32_t src_addr, uint16_t size);


/// @brief unmap the mapped flash address 
/// @param map_addr 
void esp_flash_unmap(const void * map_addr);


/// @brief this func read the partition table and init the 
/// @param  partition position structure
void esp_read_partition_table(esp_flash_partition_struct_t *part_struct);



/// @brief erase a given sector from flash 
/// @param sector 
/// @return succ/failure
esp_err_t esp_erase_flash_sector(uint32_t sector);


/// @brief just a wrapper function to wrap esp_flash api to specify null by default
/// @param addr 
/// @param buffer 
/// @param len 
/// @param encrypted 
/// @return succ/failure
esp_err_t esp_write_flash(size_t addr,const void *buffer, uint32_t len, bool encrypted);

/// @brief just a wrapper function to wrap esp_flash api to specify null by default
/// @param addr 
/// @param buffer 
/// @param len 
/// @param encrypted 
/// @return 
esp_err_t esp_read_flash(size_t addr,void * buffer, size_t len, bool encrypted);


/// @brief this method you can write the data at protected region , note only write non encrypted data
/// @param address 
/// @param buffer 
/// @param length 
/// @return succ/failure
esp_err_t esp_write_flash_dangerous(uint32_t address,const void *buffer, uint32_t length);
