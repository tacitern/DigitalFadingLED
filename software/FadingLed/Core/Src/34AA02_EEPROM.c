/*
 * 34AA02_EEPROM.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Kenneth
 */

#include "34AA02_EEPROM.h"

#include <stdint.h>

static uint8_t eepromStatusLogLen = 0;

/**
 * @brief Gets EEPROM data at a provided EEPROM memory address
 *
 * @param address location in memory of desired EEPROM data
 * @param dev_address unsigned integer address of the current EEPROM device
 * @return uint8_t Returns the collected EEPROM data
 */
uint8_t eepromRead(EEPROM_MemTypeDef address, uint8_t dev_address)
{
  uint16_t dev = (10 << 4) + (dev_address << 1);
  uint8_t data = 0;

  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, dev, address, I2C_MEMADD_SIZE_8BIT, &data, 1U, HAL_MAX_DELAY);

  // Log eeprom issues
  if (status != HAL_OK)
  {
    saveStatus(status);
  }

  return data;
}

/**
 * @brief Sets EEPROM data at a provided EEPROM memory address
 *
 * @param address location in memory to modify
 * @param data value to set in EEPROM memory
 * @param dev_address unsigned integer address of the current EEPROM device
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef eepromWrite(EEPROM_MemTypeDef address, uint8_t data, uint8_t dev_address)
{
  uint16_t dev = (10 << 4) + (dev_address << 1);

  uint8_t buf[2] = {address, data};

  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c1, dev, buf, 2, HAL_MAX_DELAY);

  // Log eeprom issues
  if (status != HAL_OK)
  {
    saveStatus(status);
  }

  return status;
}

/**
 * @brief Places EEPROM specific translated data into provided buffer
 *
 * @param buf Container for EEPROM saved data
 * @param dev_address I2C Address for the EEPROM device
 * 
 * @details The current makeup of the EEPROM memory allocation is as follows:
 * 0x00:    ID
 * 0x01:    Red Color Value
 * 0x02:    Green Color Value
 * 0x03:    Blue Color Value
 * 0x04:    Upper 2 bits of Luminance Word
 * 0x05:    Lower byte of the Luminance Word
 * 0x06:    Rate data for fade transition rate
 * 
 * The Buffer array provided is filled as such:
 * buf[0]:  ID
 * buf[1]:  Red Value
 * buf[2]:  Green Value
 * buf[3]:  Blue Value
 * buf[4]:  Luminance Value
 * buf[5]:  Rate Value
 */
void readSavedData(uint16_t *buf, uint8_t dev_address)
{
  uint16_t data;

  // ID
  buf[0] = eepromRead(ID, dev_address);
  eepromReady(dev_address);
  // R
  buf[1] = eepromRead(RED, dev_address);
  eepromReady(dev_address);
  // G
  buf[2] = eepromRead(GREEN, dev_address);
  eepromReady(dev_address);
  // B
  buf[3] = eepromRead(BLUE, dev_address);
  eepromReady(dev_address);
  // L1 upper 2 bits
  data = eepromRead(LUM_UP, dev_address) << 8;
  eepromReady(dev_address);
  // L2 lower 8 bits
  buf[4] = data + eepromRead(LUM_LOW, dev_address);
  eepromReady(dev_address);
  // Rate
  buf[5] = eepromRead(RATE, dev_address);
  eepromReady(dev_address);
}

/**
 * @brief Saves contents of the data pointer/array to specific EEPROM
 * memory locations
 *
 * @param dev_address I2C Device Address
 * @param data Array of data to update the EEPROM with
 * 
 * @details This function overwrites the current EEPROM data with new content.
 * The provided data array is used to set data as follows:
 * data[0]: 0x01 - Rad Value
 * data[1]: 0x02 - Green Value
 * data[2]: 0x03 - Blue Value
 * data[3]: 0x04 - Upper 2 bits of Luminance Value
 * data[4]: 0x05 - Lower byte of Luminance data
 * data[5]: 0x06 - Rate Value
 */
void setSavedData(uint8_t dev_address, uint8_t *data)
{

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

/**
 * @brief Checks State of the I2C Device at the provided address.
 * Polls status until the I2C device is ready for opperation
 *
 * @param dev_address I2C Device Address
 */
void eepromReady(uint8_t dev_address)
{
  uint16_t dev = (10 << 4) + (dev_address << 1);
  while (HAL_I2C_IsDeviceReady(&hi2c1, dev, 1, HAL_MAX_DELAY) == HAL_BUSY)
  {
    HAL_Delay(1);
  }
}

/**
 * @brief saveStatus is a logging function which catalogs EEPROM 
 * communication errors
 *
 * @param status Error status generated for the EEPROM Device
 */
void saveStatus(HAL_StatusTypeDef status)
{

  // if status log overflows move to beginning of status log
  if (eepromStatusLogLen == 1024)
  {
    eepromStatusLogLen = 0;
  }

  eepromStatusLog[eepromStatusLogLen];
  eepromStatusLogLen++;
}

/**
 * @brief Get the Status Log Length value
 *
 * @return uint16_t EEPROM status log length
 */
uint16_t getStatusLogLen(void)
{
  return eepromStatusLogLen;
}

/**
 * @brief Set the Status Log Length value
 *
 * @param len Desired Status log length
 */
void setStatusLogLen(uint16_t len)
{
  eepromStatusLogLen = len;
}
