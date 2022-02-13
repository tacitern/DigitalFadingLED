/*
 * serial_shell.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Kenneth
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "serial_shell.h"
#include "usart.h"
#include "tim.h"
#include "34AA02_EEPROM.h"

uint8_t serial_out[255] = {0}; // Serial ascii output character buffer
uint8_t serial_in[255] = {0};  // Serial ascii input character buffer

uint8_t len_in = 0; // Serial in length

uint8_t command_term = 0; // termination char flag

/**
 * @brief Sends serial data via UART
 *
 * @param buf Serial buffer containing data to send
 * @param len Length of the serial buffer
 *
 * TODO(klow): added interface selection for ST-Link VCP
 */
void SendSerial(uint8_t *buf, uint16_t len)
{
  HAL_UART_Transmit(&huart1, buf, len, 1000);
}

/**
 * @brief Takes a '\n' or '\r' terminated serial string and
 * checks for associated commands; preforms valid command actions
 *
 * @param input pointer to recieved serial string
 */
void SerialCommands(uint8_t *input)
{
  uint8_t i = 0;

  uint8_t error_flag = 0; // Indicates Value errors

  // Check for EEPROM Errors
  if (getStatusLogLen())
  {
    EEPROMError();
  }

  /* Gets color information returns serial message with:
   * "Red <0-255>; Green <0-255>; Blue <0-255>;\n\r"
   */
  if (strncmp((char *)input, "COLOR?", 6U) == 0)
  {
    uint8_t colors[3] = {0, 0, 0};

    GetColorValues(colors);

    sprintf((char *)serial_out, "Red %i; Green %i; Blue %i;\n\r", colors[0],
            colors[1], colors[2]);

    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }

  /* Sets color information using the following message format:
   * "<Red: 0-255>,<Green: 0-255>,<Blue: 0-255>\n\r"
   */
  else if (strncmp((char *)input, "COLOR", 5U) == 0)
  {
    i = 6;

    uint8_t colors[3] = {0, 0, 0};

    for (uint8_t j = 0; j < sizeof(colors); j++)
    {

      colors[j] = (uint8_t)ParseNumber(input, &i, &error_flag);

      // limit colors to 8 bit
      if (colors[j] > 255)
      {
        colors[j] = 255;
      }

      if (input[i] == '\r' || input[i] == '\n')
      {
        break;
      }

      i++;
    }
    if (error_flag)
    {
      ValueError();
    }
    else
    {
      SetColorValues(colors);
    }
  }

  /* Gets the current Luminence Value; returns serial string:
   * <lum: 0-1000>
   * Where 0-1000 refer to: '<brightness percentage> * 10'
   */
  else if (strncmp((char *)input, "LUM?", 4U) == 0)
  {
    uint16_t val = GetLuminanceValue();

    sprintf((char *)serial_out, "%i\n\r", val);
    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }

  /* Sets the Luminence value; accepts:
   * <lum: 0-1000>
   * Where 0-1000 refer to: '<brightness percentage> * 10'
   */
  else if (strncmp((char *)input, "LUM", 3U) == 0)
  {
    i = 4;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit luminance to 1000
    if (val > 1000)
    {
      val = 1000;
    }

    if (error_flag)
    {
      ValueError();
    }
    else
    {
      SetLuminanceValue(val);
    }
  }

  /* Gets the current rate of change setting.
   */
  else if (strncmp((char *)input, "RATE?", 5U) == 0)
  {
    uint16_t val = GetRateValue();

    sprintf((char *)serial_out, "%i\n\r", val);
    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }

  /* Sets a desired rate setting
   */
  else if (strncmp((char *)input, "RATE", 4U) == 0)
  {
    i = 5;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit rate to 8 bits
    if (val > 255)
    {
      val = 255;
    }

    if (error_flag)
    {
      ValueError();
    }
    else
    {
      SetRateValue(val);
    }
  }

  /* Gets the current settings saved in the EEPROM
   */
  else if (strncmp((char *)input, "SAVE?", 5U) == 0)
  {
    uint16_t buf[6] = {0};
    readSavedData(buf, EEPROMADDRESS);

    sprintf((char *)serial_out,
            "ID: %i\nRED: %i\nGREEN: %i\nBLUE: %i\nLUM: %i\nRATE: %i\n\r", buf[0],
            buf[1], buf[2], buf[3], buf[4], buf[5]);
    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }

  /* Saves the current settings to the EEPROM
   */
  else if (strncmp((char *)input, "SAVE", 4U) == 0)
  {
    uint8_t data[6] = {0};

    GetColorValues(data);

    uint16_t lum = GetLuminanceValue();
    data[3] = (uint8_t)((lum & 0x0300) >> 8);
    data[4] = (uint8_t)(lum & 0x00FF);

    data[5] = (uint8_t)GetRateValue();

    setSavedData(EEPROMADDRESS, data);
  }

  /* Returns the ID saved in the EEPROM of the Device
   */
  else if (strncmp((char *)input, "ID?", 3U) == 0)
  {
    uint8_t val = eepromRead(ID, EEPROMADDRESS);

    sprintf((char *)serial_out, "%i\n\r", val);
    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }

  /* Sets the current ID of the Deviced; Used to
   * distinush multiple connected devices.
   * <ID: uint8_t>
   */
  else if (strncmp((char *)input, "ID", 2U) == 0)
  {
    i = 3;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit ID to 8 bits
    if (val > 255)
    {
      val = 255;
    }

    if (error_flag)
    {
      ValueError();
    }
    else
    {
      eepromWrite(ID, (uint8_t)val, EEPROMADDRESS);
      HAL_Delay(5);
    }
  }

  else
  {
    sprintf((char *)serial_out, "Error: No Command\n\r");
    SendSerial(serial_out, strlen((char *)serial_out));
    memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
  }
}

/**
 * @brief This function parses strings for integer values
 *
 * @param input Serial String
 * @param i Current string index location
 * @param error Error flag
 * @return uint16_t Parsed integer from string
 *
 * TODO(klow): This function can probably be replaced with
 * strtol or strtof function calls
 */
uint16_t ParseNumber(uint8_t *input, uint8_t *i, uint8_t *error)
{

  uint8_t col = 0; // largest decimal place column number

  while (input[*i + col] != '\r' && input[*i + col] != '\n' && input[*i + col] != ',' && *i < 20)
  {
    col++;
  }

  uint16_t val = 0;
  while (col != 0)
  {
    // Check for non number ascii characters
    if ((uint8_t)(input[*i] - 0x30) > 9)
    {
      *error = 1;
    }

    val += (input[*i] - 0x30) * pow(10, col - 1);
    *i += 1;
    col--;
  }

  return val;
}

/**
 * @brief Error handler for incorrect serial ascii values
 *
 */
void ValueError(void)
{
  sprintf((char *)serial_out, "Value Error\n\r"); // TODO: Stuttering Error message when error occurs after second comma
  SendSerial(serial_out, strlen((char *)serial_out));
  memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
}

/**
 * @brief Error handler function for failed EEPROM access attempts
 *
 */
void EEPROMError(void)
{
  uint16_t eepromStatusLogLen = getStatusLogLen();

  for (eepromStatusLogLen; eepromStatusLogLen > 0; eepromStatusLogLen--)
  {
    if (eepromStatusLog[eepromStatusLogLen - 1] == HAL_BUSY)
    {
      sprintf((char *)serial_out, "EEPROM BUSY\n\r");
      SendSerial(serial_out, strlen((char *)serial_out));
      memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
    }
    else if (eepromStatusLog[eepromStatusLogLen - 1] == HAL_ERROR)
    {
      sprintf((char *)serial_out, "EEPROM ERROR\n\r");
      SendSerial(serial_out, strlen((char *)serial_out));
      memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
    }
    else
    {
      sprintf((char *)serial_out, "EEPROM FAIL\n\r");
      SendSerial(serial_out, strlen((char *)serial_out));
      memset(serial_out, 0, sizeof(serial_out)); // Clear serial_out array
    }
  }

  setStatusLogLen(0);
}

/**
 * @brief Takes in ascii from UART interrupt routine; Saves ascii characters to
 * serial_in
 *
 * @param Buf Most recent ascii character from UART interrupt
 */
void ProcessSerial(uint8_t *Buf)
{
  serial_in[len_in] = *Buf;
  len_in++;

  if (*Buf == '\n' || *Buf == '\r')
  {
    command_term = 1;
    len_in = 0;
  }
}

/**
 * @brief Checks for completed serial command from UART interface, based on
 * termination of serial command being reached; Sends command to
 * serial commands
 *
 */
void CheckCommand(void)
{
  if (command_term == 1)
  {
    command_term = 0;
    SerialCommands(serial_in);
  }
}
