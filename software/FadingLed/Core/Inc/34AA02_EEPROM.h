/*
 * 34AA02_EEPROM.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Kenneth
 */

#ifndef INC_34AA02_EEPROM_H_
#define INC_34AA02_EEPROM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"

#define EEPROMADDRESS  0  // EEPROM I2C Device Address

typedef enum
{
  ID      = 0x00U,
  RED     = 0x01U,
  GREEN   = 0x02U,
  BLUE    = 0x03U,
  LUM_UP  = 0x04U,
  LUM_LOW = 0x05U,
  RATE    = 0x06U
}EEPROM_MemTypeDef;

HAL_StatusTypeDef eepromStatusLog[1024];

uint8_t eepromRead(EEPROM_MemTypeDef address, uint8_t dev_address);

HAL_StatusTypeDef eepromWrite(uint8_t address, uint8_t data, uint8_t dev_address);

void readSavedData(uint16_t *buf, uint8_t dev_address);

void setSavedData(uint8_t dev_address, uint8_t* data);

void eepromReady(uint8_t dev_address);

void saveStatus(HAL_StatusTypeDef status);

uint16_t getStatusLogLen(void);

void setStatusLogLen(uint16_t len);

#ifdef __cplusplus
}
#endif

#endif  /* INC_34AA02_EEPROM_H_ */
