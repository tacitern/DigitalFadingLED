/*
 * 34AA02_EEPROM.c
 *
 *  Created on: Aug 18, 2021
 *      Author: Kenneth
 */


#include "34AA02_EEPROM.h"


uint8_t eepromRead(EEPROM_MemTypeDef address, uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);
  uint8_t data = 0;
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, dev, address, I2C_MEMADD_SIZE_8BIT, &data, 1U, HAL_MAX_DELAY);
  if(status == HAL_OK){
      return data;
  }
  //TODO added other status return handling
  return data;
}

HAL_StatusTypeDef eepromWrite(EEPROM_MemTypeDef address, uint8_t data, uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);

  uint8_t buf[2] = {address, data};

  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev, buf, 2, HAL_MAX_DELAY);
  if(status == HAL_OK){
      return status;
  }
  //TODO added other status return handling
  return status;
}

void readSavedData(uint16_t *buf, uint8_t dev_address){
  uint16_t data;
  //ID
  buf[0] = eepromRead(ID, dev_address);
  eepromReady(dev_address);
  //R
  buf[1] = eepromRead(RED, dev_address);
  eepromReady(dev_address);
  //G
  buf[2] = eepromRead(GREEN, dev_address);
  eepromReady(dev_address);
  //B
  buf[3] = eepromRead(BLUE, dev_address);
  eepromReady(dev_address);
  //L1 upper 2 bits
  data = eepromRead(LUM_UP, dev_address) << 8;
  eepromReady(dev_address);
  //L2 lower 8 bits
  buf[4] = data + eepromRead(LUM_LOW, dev_address);
  eepromReady(dev_address);
  //Rate
  buf[5] = eepromRead(RATE, dev_address);
  eepromReady(dev_address);
}

void setSavedData(uint8_t dev_address){
  eepromWrite(ID, 1, dev_address);
  HAL_Delay(5);
  eepromWrite(RED, 186, dev_address);
  HAL_Delay(5);
  eepromWrite(GREEN, 127, dev_address);
  HAL_Delay(5);
  eepromWrite(BLUE, 24, dev_address);
  HAL_Delay(5);
  eepromWrite(LUM_UP, 2, dev_address);
  HAL_Delay(5);
  eepromWrite(LUM_LOW, 128, dev_address);
  HAL_Delay(5);
  eepromWrite(RATE, 5, 0);
  HAL_Delay(5);
}

void eepromReady(uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);
  while(HAL_I2C_IsDeviceReady(&hi2c1, dev, 1, HAL_MAX_DELAY) == HAL_BUSY){
      HAL_Delay(1);
  }

//  HAL_Delay(5);
}

