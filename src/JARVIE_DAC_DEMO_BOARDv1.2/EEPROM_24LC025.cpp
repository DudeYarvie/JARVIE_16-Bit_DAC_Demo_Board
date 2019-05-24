// EEPROM 24LC025
// by Jarvis Hill <hilljarvis@gmail.com>

// Demonstrates use of the Wire library

// Created 22 May 2019

/*INCLUDES*/
#include <Wire.h>
#include "EEPROM_24LC025.h"
#include <Arduino.h>
#include <stdint.h>


/********************************************************************
* write_EEPROM
* Purpose: Writes EEPROM with data in specified char buffer
*
*********************************************************************/
void write_EEPROM(uint8_t dev_addr, uint8_t mem_addr, char* buf){
  char temp[]= "";
  strcpy(temp,buf);
  uint8_t j;
  
  //Serial.print("Writing EEPROM..\n");

  for (j = mem_addr; j < (strlen(temp)+mem_addr); j++){

    //Make sure we don't access memory location that doesn't exist in 2Kbit EEPROM
    if (j > 0xFA) break;
    
    //Serial.print(temp[i]);
    Wire.beginTransmission(dev_addr);         // Write to device put addr byte, don't inc. R/W bit
    delay(1); 
    Wire.write(j);                            // Point EPPROM to memory addr 0
    delay(1);
    Wire.write(temp[(j-mem_addr)]);           // sends one byte
    delay(10);

    Wire.endTransmission();                   // stop transmitting
    delay(10);
  }
  //Serial.print("Writing complete..\n");
}


/***************************************************************************
* read_EEPROM
* Purpose: Reads a specified amount of EEPROM data bytes starting at 
*		   at a specified memory address with data in specified char buffer
*
****************************************************************************/
void read_EEPROM(uint8_t dev_addr, uint8_t mem_addr, uint8_t bytes){
  
  char c;
  uint8_t i, d;
  
  //Serial.print("Reading EEPROM..\n");
  
   for (i = mem_addr; i < (mem_addr+bytes); i++){
    Wire.beginTransmission(dev_addr); // Read from device
    delay(1); 
    Wire.write(i);              // Point EPPROM to memory addr 0
    Wire.endTransmission(); 
    Wire.requestFrom(dev_addr, 1, true);
    //delay(1);
    while (Wire.available()) {  // slave may send less than requested
      c = Wire.read();          // receive a byte as character
      Serial.print(c);          // print the character
    }
  }

  //Serial.print("Reading complete..\n");
  //Serial.print(buf);
}


/*MISCELLANEOUS*/ 
/*
//Clear EEPROM
char buf[60] = " ";
buf[60]="\0";
uint8_t i = 0;
for (i = 0; i < 59; i++){ 
  write_EEPROM(80,i, buf);
}
delay(200);
*/
