/*
          JARVIE_DAC_DEMO_BOARD.ino v1.2
Author: Jarvis Hill (hilljarvis@gmail.com)
Date: 23-MAY-2019
Purpose: Reference code for controlling the 16-bit LTC2642 DAC on the JARVIE DAC DEMO BOARD
Usage:
         1. Download this firmware onto the Arduino 
		     2. Open a serial link between a host and the controller at the baud rate specified by
            the "baud" definition below.
         3. Send an ASCII command to identify the controller or set a DAC.  All commands must be terminated with a newline "\n" character. 
            --COMMANDS
              -IDN?: Queries the device ID
              -DAC0 <DAC 16-bit code>:  Sets DAC0 output voltage (refer to datasheet to understand how the dac code relates to the 
              analog output voltage.
              -DAC1 <DAC 16-bit code>:  Sets DAC1 output voltage 
References: LTC2642ACDD-16 16-bit DAC datasheet, DAC Demo Board schematic
*/


/*INCLUDES*/
#include <Wire.h>                       //Required for I2C  
#include "EEPROM_24LC025.h"             //Demo boar EEPROM 
#include "JARVIE_SPI.h"                 //SPI 


/*GLOBALS*/
#define baud 115200


/*LTC2642ACDD-16 DAC chip select signals (diff than SS in Arduino SPI lib)*/
#define DAC1_nCS              PIN5     //Linduino or UNO D5     
#define DAC1_nCS_ddr          DDD5  
#define DAC0_nCS              PIN7     //Linduino or UNO D7  
#define DAC0_nCS_ddr          DDD7  


/*DAC definitions*/
enum DAC : byte{DAC1 = 1, DAC0 = 2};
byte selected_DAC; 


/*System ID string*/
char id_string[]="JARVIE DAC Demo Board rev A---\n\0"; // id string


/*PROTOTYPES*/
char get_char();
char *Read_cmd();
int Host_Command();
void init_DAC_io();
void LTC_DAC_Load(byte DAC, uint16_t dac_code);
void read_EEPROM(uint8_t dev_addr, uint8_t mem_addr, uint8_t bytes);
void write_EEPROM(uint8_t dev_addr, uint8_t mem_addr, char* buf);


/*******************************************************************************
 * get_char
 * Purpose: Reads a single ASCII character received from through the serial port
 *******************************************************************************/
char get_char()
{

  char thisChar;

  //Read ASCII character from serial port
  while(1)
  {
    if (Serial.available() > 0)
    {
       thisChar = (char)Serial.read();
       return thisChar;
    }
    
    delay(10);
  }
}


/*******************************************************************************
 * Read_cmd
 * Purpose: Reads serial data sent from Host to Device
 *******************************************************************************/
char *Read_cmd()
{
  //Get and return received data from buffer
  char *ret;
  
  //creating temp array
  char temp[80];
  int i=0;
  for (i = 0; i< 80; i++)
    temp[i]=0;

  Serial.print("Ready...\n");                             //Print statement for debugging

  //Retrieve serial port ASCII string
  i =0;
  while(1)
  {
    temp[i++] = get_char();                               //Add each character received to the string buffer
            
    if(temp[i-1] == '\n')                                 //New-line terminator signals end of string 
      break;
  }

  temp[i]=0;
  ret = (char *)malloc(sizeof(char)*(strlen(temp)+1));    //Allocate memory for received string pointer
  strcpy(ret,temp);                                       //Copy string buffer to string pointer
  return ret;                                             //Return string pointer
}


/*******************************************************************************
 * Host_Command
 * Purpose: Parses cmd received from host and determines how to handle it.
 *******************************************************************************/
int Host_Command()
{
  //Local variables
  char *temp;
  uint16_t dac_code = -1;
  char DAC_type[100];
  char buf[200];

  //Read command string from host API
  temp = Read_cmd();
 
  //IDN? cmd
  if(strncmp(temp,"IDN?",strlen("IDN?"))==0)                    //IF host cmd is "IDN?"
  {
    Serial.print(id_string);
    Serial.print('\0');
    Serial.flush();
  }

  //Set DAC cmds
  if(strncmp(temp,"DAC",strlen("DAC"))==0){                    
    if(strncmp(temp,"DAC0",strlen("DAC0"))==0)                 //IF host cmd is "DAC0"
    {
      selected_DAC = DAC0;
    }
    else if(strncmp(temp,"DAC1",strlen("DAC1"))==0){           //IF host cmd is "DAC1"
      selected_DAC = DAC1;
    }
    else{ 
      free(temp);
      return dac_code;
    }
  
    sscanf(temp,"%s %u", DAC_type, &dac_code);                                    
    sprintf(buf, "%s %u\n", DAC_type, dac_code);
    Serial.print(buf);
    Serial.flush();
  }
  
  free(temp);
  return dac_code;
}
 

/**********************************************************************
 * init_DAC_io
 * Purpose: Configure I/O for ADC AD4020 and DAC AD5791 communications
 **********************************************************************/
void init_DAC_io(void){
  
  //intialize DAC control signals
  DDRD |= (1 << DAC1_nCS_ddr)| (1 << DAC0_nCS_ddr);                   //Set signals to output 

  PORTD |= (1 << DAC1_nCS)| (1 << DAC0_nCS);                          //Init pin logic levels 

}



/************************************************************************************************************************************
 * LTC_DAC_Load
 * Purpose: Write data to DC1096B DAC. DAC out = Vref x (DAC code/2^16)
 * Note: 2 bytes (16-bits) is required to write DAC. Data is shifted into DAC on CLK rising edge.  
*************************************************************************************************************************************/
void LTC_DAC_Load(byte DAC, uint16_t dac_code){

    //Serial.println(dac_code);                         //Print dac_code to serial terminal for debugging

    //Init MSB and LSB dac bytes
    uint8_t MSB_dac_byte = 0;
    uint8_t LSB_dac_byte = 0;

    //Organize dac_code into high (MSB) and low (LSB) bytes
    MSB_dac_byte = (dac_code & 0xFF00) >> 8;            //DAC code MSB    
    LSB_dac_byte = (dac_code & 0xFF);                   //DAC code LSB 

    //Write data to DAC
    switch (DAC){
      case DAC1:
        PORTD &= ~(1 << DAC1_nCS);                      //DAC DAC1_nCS signal LOW to enable loading  
        break;

      case DAC0:
        PORTD &= ~(1 << DAC0_nCS);                      //DAC DAC1_nCS signal LOW to enable loading  
        break;
    }
    
    SPI_MasterTransmit(MSB_dac_byte);
    SPI_MasterTransmit(LSB_dac_byte);
    
    //End data load
    switch (DAC){
      case DAC1:
        PORTD |= (1 << DAC1_nCS);                      //Idle DAC DAC1_nCS signal HIGH to disable loading
        break;

      case DAC0:
        PORTD |= (1 << DAC0_nCS);                      //Idle DAC DAC1_nCS signal HIGH to disable loading
        break;
    }

}



/*SETUP*/
void setup() {

  //Init SPI
  SPI_MasterInit();

  //Init DC1096B I/O
  init_DAC_io();

  //Start I2C
  Wire.begin();                                 //Init I2C 
  Wire.setClock(10000L);                        //set clk freq, 400kHz max (400000L)
  delay(100);
  
  //Open Serial connection 
  Serial.begin(baud);
  while (!Serial) {
    ;                                          // wait for serial port to connect. Needed for native USB
  }
  
  //Read demo board id_string
  Serial.print("Board ID: ");
  read_EEPROM(80,0,strlen(id_string));
  delay(100);

  //Init DAC output voltages to 0V
  uint16_t dac_code;
  dac_code = 0;                               //Sets DAC output to 0V. If DAC is in bipolar mode, dac_code = 32768                        
  LTC_DAC_Load(DAC0, dac_code);
  delay(10);                            
  LTC_DAC_Load(DAC1, dac_code);
  delay(10);                            

  Serial.flush();

}



/*MAIN PROGRAM*/
void loop() {

  //Local variable declarations
  uint16_t dac_code;
  dac_code = 0;
  
  //Wait for cmd from host 
  dac_code = Host_Command();

  if (dac_code == -1) return;               //Do not set a DAC if the appropriate command is not received from host

  //Update specified DAC output voltage
  LTC_DAC_Load(selected_DAC, dac_code);
  Serial.flush();
    
}
