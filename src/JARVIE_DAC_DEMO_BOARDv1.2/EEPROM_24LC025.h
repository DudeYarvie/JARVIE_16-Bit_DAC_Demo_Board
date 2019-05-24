
#ifndef EEPROM_24LC025_H
#define EEPROM_24LC025_H

#include <Wire.h>

//Writes a character buffer to the EEPROM
//@return void
void write_EEPROM(uint8_t dev_addr,				//I2C slave address
				  uint8_t mem_addr,				        //Starting memory location
				  char* buf						            //character data buffer, all contents will be written to EEPROM
				  );

//Reads EEPROM Data
//@return void
void read_EEPROM(uint8_t dev_addr,				//I2C slave address
				 uint8_t mem_addr, 				        //Starting memory location
				 uint8_t bytes				            //# of bytes to read from slave
				);

#endif	//EEPROM_24LC025_H
