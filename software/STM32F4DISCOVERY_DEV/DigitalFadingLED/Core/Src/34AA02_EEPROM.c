/*
 * 34AA02_EEPROM.c
 *
 *  Created on: Aug 18, 2021
 *      Author: Kenneth
 */


#include "34AA02_EEPROM.h"

static uint8_t eepromStatusLogLen = 0;

uint8_t eepromRead(EEPROM_MemTypeDef address, uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);
  uint8_t data = 0;
  
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, dev, address, I2C_MEMADD_SIZE_8BIT, &data, 1U, HAL_MAX_DELAY);
  
  // Log eeprom issues
  if(status != HAL_OK){
    saveStatus(status);
  }

  return data;
}

HAL_StatusTypeDef eepromWrite(EEPROM_MemTypeDef address, uint8_t data, uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);

  uint8_t buf[2] = {address, data};

  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev, buf, 2, HAL_MAX_DELAY);

  // Log eeprom issues
  if(status != HAL_OK){
    saveStatus(status);
  }

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

void setSavedData(uint8_t dev_address, uint8_t* data){
  
  eepromWrite(RED, data[0], dev_address);
  HAL_Delay(5);
  eepromWrite(GREEN, data[1], dev_address);
  HAL_Delay(5);
  eepromWrite(BLUE, data[2], dev_address);
  HAL_Delay(5);
  eepromWrite(LUM_UP, data[3], dev_address);
  HAL_Delay(5);
  eepromWrite(LUM_LOW, data[4], dev_address);
  HAL_Delay(5);
  eepromWrite(RATE, data[5], 0);
  HAL_Delay(5);
}

void eepromReady(uint8_t dev_address){
  uint16_t dev = (10 << 4) + (dev_address << 1);
  while(HAL_I2C_IsDeviceReady(&hi2c1, dev, 1, HAL_MAX_DELAY) == HAL_BUSY){
      HAL_Delay(1);
  }
}

void saveStatus(HAL_StatusTypeDef status){

  //if status log overflows move to beginning of status log
  if(eepromStatusLogLen == 1024){
    eepromStatusLogLen = 0;
  }
  
  eepromStatusLog[eepromStatusLogLen];
  eepromStatusLogLen++;
}

uint16_t getStatusLogLen(void){
  return eepromStatusLogLen;
}

void setStatusLogLen(uint16_t len){
  eepromStatusLogLen = len;
}

