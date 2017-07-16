#include "eeprom.h"


void eeprom_write_page(uint16_t addr, uint8_t *src, uint8_t count)
{
    uint8_t i = 0;
    uint8_t *EEAddress;
    //  Check if the EEPROM is write-protected.  If it is then unlock the EEPROM.
    if ((FLASH->IAPSR & FLASH_IAPSR_DUL) == 0) {
        FLASH->DUKR = FLASH_RASS_KEY2;
        FLASH->DUKR = FLASH_RASS_KEY1;
    }

    //  Write the data to the EEPROM.
    EEAddress = (uint8_t *) (FLASH_DATA_START_PHYSICAL_ADDRESS + addr);
    for (; i < count; i++) {
        *EEAddress = src[i];
        EEAddress++;
    }

    // Write protect the EEPROM.
    FLASH->IAPSR &= ~FLASH_IAPSR_DUL;
}

void eeprom_read_page(uint16_t addr, uint8_t * dest, uint8_t count) {
    uint8_t i = 0;
    //  Write the data to the EEPROM.
    uint8_t *EEAddress  = (uint8_t *) (FLASH_DATA_START_PHYSICAL_ADDRESS + addr);
    for (; i < count; i++) {
        dest[i] = *EEAddress;
        EEAddress++;
    }
}

// uint8_t eeprom_read_byte(uint16_t addr) {
//     return (*(uint8_t *) (FLASH_DATA_START_PHYSICAL_ADDRESS + addr));
// }