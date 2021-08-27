/*
 * 34AA02_EEPROM.h
 *
 *  Created on: Aug 18, 2021
 *      Author: Kenneth
 */


#ifndef __34AA02_EEPROM_H__
#define __34AA02_EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"


typedef enum
{
  ID		= 0x00U,
  RED		= 0x01U,
  GREEN		= 0x02U,
  BLUE		= 0x03U,
  LUM_UP	= 0x04U,
  LUM_LOW	= 0x05U,
  RATE		= 0x06U
}EEPROM_MemTypeDef;


uint8_t eepromRead(EEPROM_MemTypeDef address, uint8_t dev_address);

HAL_StatusTypeDef eepromWrite(uint8_t address, uint8_t data, uint8_t dev_address);

void readSavedData(uint16_t *buf, uint8_t dev_address);

void setSavedData(uint8_t dev_address);

void eepromReady(uint8_t dev_address);

#ifdef __cplusplus
}
#endif

#endif
