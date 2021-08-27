#include <math.h>
#include <stdio.h>
#include "serial_shell.h"
#include "usart.h"
#include "tim.h"
#include "34AA02_EEPROM.h"

uint8_t serial_out[200] = {0};			// Serial ascii output character buffer
uint8_t serial_in[200] = {0};			// Serial ascii input character buffer

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

      sprintf((char*)serial_out, "Red %i; Green %i; Blue %i\n\r",
				  colors[0], colors[1], colors[2]);

      len_out += 21;

      for(uint8_t i = 0; i < 3; i++){
    	  if(colors[i] >= 100){
    		  len_out += 3;
    	  }
    	  else if(colors[i] >= 10){
    		  len_out += 2;
    	  }
    	  else{
    		  len_out++;
    	  }
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

      if(val >= 1000){
	  len_out += 4;
      }
      else if(val >= 100){
	  len_out += 3;
      }
      else if(val >= 10){
	  len_out += 2;
      }
      else{
	  len_out += 1;
      }

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

      if(val >= 1000){
      	  len_out += 4;
      }
      else if(val >= 100){
      	  len_out += 3;
      }
      else if(val >= 10){
      	  len_out += 2;
      }
      else{
      	  len_out += 1;
      }

      sprintf((char*)serial_out, "%i\n\r", val);
      SendSerial(serial_out, len_out + 2);
  }
  else if(strncmp((char*)input, "RATE", 4U) == 0){
    i = 5;

    uint16_t val = ParseNumber(input, &i, &error_flag);

    // limit rate to 1000
    if(val > 1000){
	val = 1000;
    }

    if(error_flag){
	ValueError();
    }
    else{
	SetRateValue(val);
    }
  }
  //TODO
//  else if(strncmp((char*)input, "SAVE?", 5U) == 0){
////      readSavedValues();
//  }
//  else if(strncmp((char*)input, "SAVE", 4U) == 0){
//
//  }
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

