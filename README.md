# JARViE_DAC_Demo_Board
 The heart of the demo board are two LTC2642 16-bit DACs. They enable the DAC Demo Board to generate -5 to +5V signals on either of two output channels. Output channels may be updated asynchronously or synchronously. When updating synchronously, the same voltage will be produced on each output channel at the same time instance.
 
![Demo_Board_Annotated_IMG](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Board_Annotate.png)

## Features
* Board size = 2.6" x 2.8"
* Two +/- 5V @ 25 mA max rail-to-rail buffered voltage output channels
* DACs may be updated asynchronously or synchronously
* DAC +5V reference with trimming to adjust reference between 0 to +5V in 40mV increments   
* External DAC voltage reference input (+6V max)
* External supply inputs for DAC output buffers and trim pot (+V = +15V, -V = -15V max)   
* 2Kbit I2C EEPROM (e.g. store board S/N, calibration constants to adjust DAC non-linearities, etc.)
* Supports 3.3V and 5V SPI and I2C buses
* The demo board can generate DC voltages, as well as, arbitrary and AC waveforms.
![SINE_WFM_EX](https://raw.githubusercontent.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/master/Reference%20Docs/pics/SINE_wave.png)
![TRI_WFM_EX](https://raw.githubusercontent.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/master/Reference%20Docs/pics/TRI_wave.png)
![SAW_WFM_EX](https://raw.githubusercontent.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/master/Reference%20Docs/pics/SAW_wave.png)

## Ordering Info
![JARViE_Tindie_store](https://d2ss6ovg47m0r5.cloudfront.net/images/tindie-logo@2x.png)

[Check JARViE out on tindie!](https://www.tindie.com/stores/jarvie/)

##  Quick Start Procedure
1. Connect the Arduino or Linduino controller to the DAC Demo Board per the illustration below.
2. Upload the controller MCU with the firmware (.ino file) in the *src* directory.
3. Set DAC VREF, unipolar/bipolar mode and output voltage using the CMD listed in the *Software* section below.

**Setting VREF, or the output mode via software will not set the hardware VREF or bipolar/unipolar mode. The jumpers need to be placed in their proper positions in order to accomplish this.**

![Quick_Connect_Diagram](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Quick_Connect_Diagram.png)

## Hardware Architecture 
### Block Diagram
![Demo_Board_Block_Diagram](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Block_Diagram.png)
### Jumper Selections
| Jumper Reference| Description |
|:---:|:---|
| JP1 | Selects the reference voltage for both DACs.  Use JP1 pin 2 to supply a +6V max external voltage.  Populate U2 and place a jumper between JP1 pins 2 and 3 to select +2.5V.  Place jumper between JP1 pins 1 and 2 to select +5V |
| JP2 |  Sets DAC0 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 15V to +V-EXT and -V_EXT  |
| JP3 | Sets DAC1 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 15V to +V-EXT and -V_EXT |
| JP4 | Sets DAC output buffers and digital potentiometer +V supply to *+V_EXT* or onboard *+5V_REG* |
| JP5 | Sets DAC output buffers and digital potentiometer -V supply to *-V_EXT* or onboard GND |
| JP8 | Sets the asynchronous or synchronous control of DAC0 and DAC1.  Asynchronous mode allows the DAC outputs to be set to different values at different times.  Synchronous mode sets the DAC outputs to the same value at the same time. |

## Using the demo board with Linear Technologies QuikEval Software
1. Follow the Linduino ***Setup*** section on the Analog Devices website [here](https://www.analog.com/en/design-center/evaluation-hardware-and-software/evaluation-development-platforms/linduino.html).  The ***Linduino Sketch*** can be placed on the Arduino UNO as well.
2. Starting at address 0x0000, write the EEPROM on the JARViE demo board with the following ID string: ***LTC2642,Cls,D2642,01,01,DC,DC1096,--------------***
3. Open the QuikEval software and make sure the demo board is identified as a "DC1096" Linear Technologies demo board.

## Software 
### Usage
1. Pull/download src repo  
2. Download the latest Arduino IDE if it doesn't exist on computer PC already
3. Copy all files onto your local machine. into a parent directory named after the .ino file
4. Connect the Arduino UNO or Linduino to your PC
5. Open the .ino file and upload the firmware to the UNO or Linduino 

### Commands
The following commands are supported by the demo board firmware.  The commands are sent to the demo board controller from a PC through a serial conenction.  All commands must be terminated with a newline character (\n).  The command syntax is command <*parameter*>\n. Example, sending *VREF 5.0V\n* to the controller, tells the firmware that the DAC VREF jumper JP1 is set in the 5V configuration.

#### **DAC0** <*dac_code = unsigned int*> 

|Parameters: |**dac_code** - 16-bit DAC output voltage code|
|:---:|:---|
|Usage Example| **DAC0 65534**, sets DAC0 output voltage to full-scale or DAC0 VREF voltage. DAC voltage = (dac_code/2^16) x VREF|

#### **DAC1** <*dac_code = unsigned int*> 

|Parameters: |**dac_code** - 16-bit DAC output voltage code|
|:---:|:---|
|Usage Example| **DAC1 65534**, sets DAC1 output voltage to full-scale or DAC1 VREF voltage. DAC voltage = (dac_code/2^16) x VREF|

#### **WFM** <*dac#*> <*WFM_type*> <*low voltage*> <*high voltage*> 

|Parameters: |**dac#** - selects which DAC, 0 or 1, on the demo board generates the selected waveform. **WFM_type** - selects between sawtooth, sine, triangle and square waveforms. **low voltage** - lowest voltage DAC will output. **high voltage** - highest voltage DAC will output|
|:---:|:---|
|Usage Example| **WFM DAC0 SINE 12000 65000**, outputs a SINE wave on DAC0 output with a low voltage = +0.91V and a high voltage = +4.95V. DAC voltage = (dac_code/2^16) x VREF|


**The following commands will be implemented in the next code version**
#### **DAC0_MODE** <*mode_setting = byte*> 

|Parameters: |**mode_setting** - DAC unipolar or bipolar mode|
|:---:|:---|
|Usage Example| **DAC0_MODE 0**, sets DAC0 output mode to unipoloar (output voltages range from 0 to +VREF). USER MUST SET JUMPER TO CORRECT POSITION ON DEMO BOARD!!!|

#### **DAC1_MODE** <*mode_setting = byte*> 

|Parameters: |**mode_setting** - DAC unipolar or bipolar mode|
|:---:|:---|
|Usage Example| **DAC1_MODE 1**, sets DAC1 output mode to bipoloar (output voltages range from -VREF to +VREF). USER MUST SET JUMPER TO CORRECT POSITION ON DEMO BOARD!!!|

#### **VREF** <*VREF_setting = float*> 

|Parameters: |**VREF_setting** - DAC VREF voltage|
|:---:|:---|
|Usage Example| **VREF 2.5**, tells firmware that dac VREF is set to 2.5V on the demo board. USER MUST SET JUMPER TO CORRECT POSITION ON DEMO BOARD!!!|

This command is required in order for the board to generae accurate DAC output voltage 
