#include <SPI.h>
#include "JARVIE_SPI.h"


/*******************************************************************************
 * SPI_MasterInit
 * Purpose: Configures and enables SPI bus
 *******************************************************************************/
void SPI_MasterInit(void)
{
  /* Set MOSI and SCK output, all others input */
  DDRB = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);

  /*Pull SCK and MOSI LOW*/
  PORTB |= (0<<_SCK)|(0<<_MOSI)|(1<<_SS);
  
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(0<<CPOL)|(0<<CPHA)|(0<<DORD);
  
}


/*******************************************************************************
 * SPI_MasterTransmit
 * Purpose: Sends specified data byte over SPI bus
 *******************************************************************************/
void SPI_MasterTransmit(char cData)
{
  /* Start transmission */
  SPDR = cData;
  
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}
