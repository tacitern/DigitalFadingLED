/*
 * serial_shell.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Kenneth
 */

#ifndef INC_SERIAL_SHELL_H_
#define INC_SERIAL_SHELL_H_

#ifdef __cplusplus
 extern "C" {
#endif


#include "main.h"

void SendSerial(uint8_t* buf, uint16_t len);

void ProcessSerial(uint8_t* Buf);

void SerialCommands(uint8_t* input, uint8_t in_len);

uint16_t ParseNumber(uint8_t* input, uint8_t* i, uint8_t* error);

uint16_t NumberLen(uint16_t num);

void ValueError(void);

void EEPROMError(void);

void CheckCommand(void);


#ifdef __cplusplus
}
#endif

#endif /* INC_SERIAL_SHELL_H_ */
