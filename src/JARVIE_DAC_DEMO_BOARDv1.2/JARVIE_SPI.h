#ifndef JARVIE_SPI_H
#define JARVIE_SPI_H

//#include <SPI.h>
#define _SCK                PIN5     //UNO D13 
#define _MISO               PIN4     //UNO D12
#define _MOSI               PIN3     //UNO D11
#define _SS                 PIN2     //UNO D10
#define DD_SCK              DDB5
#define DD_MOSI             DDB3
#define DD_MISO             DDB4
#define DD_SS               DDB2


//! Inits SPI
//! @return void
void SPI_MasterInit();

//! Transmit data byte to slave
//! @return void
void SPI_MasterTransmit(char cData					//Data byte to transmit to slave
					   );
					   

#endif  // JARVIE_SPI_H
