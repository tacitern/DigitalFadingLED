#include <math.h>
#include <stdio.h>
#include "serial_shell.h"
#include "usart.h"
#include "tim.h"
#include "34AA02_EEPROM.h"

uint8_t serial_out[255] = {0};			// Serial ascii output character buffer
uint8_t serial_in[255] = {0};			// Serial ascii input character buffer

uint8_t len_in = 0;				// Serial in length
uint8_t i_in = 0;				// Serial in index

uint8_t command_term = 0;			// termination char flag

void SendSerial(uint8_t* buf, uint16_t len){
  HAL_UART_Transmit(&huart3, buf, len, 1000);
}

void SerialCommands(uint8_t* input, uint8_t in_len){
  uint8_t i = 0;

  uint8_t error_flag = 0; // Indicates Value errors

  if(strncmp((char*)input, "COLOR?", 6U) == 0){
	  uint8_t colors[3] = {0, 0, 0};

	  uint8_t len_out = 0;

	  GetColorValues(colors);

    sprintf((char*)serial_out, "Red %i; Green %i; Blue %i;\n\r",
        colors[0], colors[1], colors[2]);

    len_out += 22;

    for(uint8_t i = 0; i < 3; i++){
      
      len_out += NumberLen(colors[i]);
    }

    SendSerial(serial_out, len_out);
}

  else if(strncmp((char*)input, "COLOR", 5U) == 0){
    i = 6;

    uint8_t colors[3] = {0, 0, 0};

    for(uint8_t j = 0; j < sizeof(colors); j++){

    	colors[j] = (uint8_t)ParseNumber(input, &i, &error_flag);

    	// limit colors to 8 bit
    	if(colors[j] > 255){
    		colors[j] = 255;
    	}

    	if(input[i] == '\r' || input[i] == '\n'){
    		break;
    	}

    	i++;

    }
    if(error_flag){
	    ValueError();
    }
    else{
	    SetColorValues(colors);
    }
  }

  else if(strncmp((char*)input, "LUM?", 4U) == 0){
      uint8_t len_out = 0;

      uint16_t val = GetLuminanceValue();

      len_out += NumberLen(val);

      sprintf((char*)serial_out, "%i\n\r", val);
      SendSerial(serial_out, len_out + 2);
  }

  else if(strncmp((char*)input, "LUM", 3U) == 0){
    i = 4;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit luminance to 1000
    if(val > 1000){
    	val = 1000;
    }

    if(error_flag){
    	ValueError();
    }
    else{
	    SetLuminanceValue(val);
    }
  }

  else if(strncmp((char*)input, "RATE?", 5U) == 0){
      uint8_t len_out = 0;

      uint16_t val = GetRateValue();

      len_out += NumberLen(val);

      sprintf((char*)serial_out, "%i\n\r", val);
      SendSerial(serial_out, len_out + 2);
  }
  
  else if(strncmp((char*)input, "RATE", 4U) == 0){
    i = 5;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit rate to 8 bits
    if(val > 255){
    	val = 255;
    }

    if(error_flag){
	    ValueError();
    }
    else{
	    SetRateValue(val);
    }
  }

 else if(strncmp((char*)input, "SAVE?", 5U) == 0){
    uint8_t len_out = 0;

    uint16_t buf[6] = {0};
    readSavedData(buf, EEPROMADDRESS);

    for(uint8_t i = 0; i < sizeof(buf); i++){
      len_out += NumberLen(buf[i]);
    }

    len_out += 40;
    // len_out += 12;

    sprintf((char*)serial_out, "ID: %i\nRED: %i\nGREEN: %i\nBLUE: %i\nLUM: %i\nRATE: %i\n\r",
                                buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    SendSerial(serial_out, len_out);
 }

 else if(strncmp((char*)input, "SAVE", 4U) == 0){
    uint8_t data[6] = {0};

    GetColorValues(data);

    uint16_t lum = GetLuminanceValue();
    data[3] = (uint8_t)((lum & 0x0300) >> 8);
    data[4] = (uint8_t)(lum & 0x00FF);

    data[5] = (uint8_t)GetRateValue();

    setSavedData(EEPROMADDRESS, data);
 }

  else if(strncmp((char*)input, "ID?", 3U) == 0){
    uint8_t len_out = 0;

    uint8_t val = eepromRead(ID, EEPROMADDRESS);

    len_out += NumberLen(val);

    sprintf((char*)serial_out, "%i\n\r", val);
    SendSerial(serial_out, len_out + 2);
  }

  else if(strncmp((char*)input, "ID", 2U) == 0){
    i = 3;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit ID to 8 bits
    if(val > 255){
    	val = 255;
    }

    if(error_flag){
	    ValueError();
    }
    else{
	    eepromWrite(ID, (uint8_t)val, EEPROMADDRESS);
      HAL_Delay(5);
    }
  }

  else{
      sprintf((char*)serial_out, "Error: No Command\n\r");
      SendSerial(serial_out, 19);
  }
}

uint16_t ParseNumber(uint8_t* input, uint8_t* i, uint8_t* error){

  uint8_t col = 0; // largest decimal place column number

  while(input[*i + col] != '\r' && input[*i + col] != '\n' && input[*i + col] != ',' && *i < 20){
      col++;
  }

  uint16_t val = 0;
  while(col != 0){

      if((uint8_t)(input[*i] - 0x30) > 9){
	  *error = 1;
      }

      val += (input[*i] - 0x30) * pow(10, col - 1);
      *i += 1;
      col--;
  }

  return val;
}

/**
  *NumberLen
  */
uint16_t NumberLen(uint16_t num){
    uint16_t len = 0;
    if(num >= 10000){
        len += 5;
    }
    else if(num >= 1000){
        len += 4;
    }
    else if(num >= 100){
        len += 3;
    }
    else if(num >= 10){
        len += 2;
    }
    else if(num < 10){
        len += 1;
    }

    return len;
}

void ValueError(void){
  sprintf((char*)serial_out, "Value Error\n\r");	//TODO: Stuttering Error message when error occurs after second comma
  SendSerial(serial_out, 13);
}

void ProcessSerial(uint8_t* Buf){
  serial_in[len_in] = *Buf;
  len_in++;

  if(*Buf == '\n' || *Buf == '\r'){
    command_term = 1;
    len_in = 0;
  }
}

void CheckCommand(void){
  if(command_term == 1){
    command_term = 0;
    SerialCommands(serial_in, i_in);
  }
}

