# JARViE_DAC_Demo_Board
 The heart of the demo board are two LTC2642 16-bit DACs. They enable the DAC Demo Board to generate -5 to +5V signals on either of two output channels. Output channels may be updated asynchronously or synchronously. When updating synchronously, the same voltage will be produced on each output channel at the same time instance.
 
![Demo_Board_Annotated_IMG](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Board_Annotate.png)

## Features
* Board size = 2.6" x 2.8"
* Two +/- 5V @ 25 mA max rail-to-rail buffered voltage output channels
* DACs may be updated asynchronously or synchronously
* DAC +5V reference with trimming to adjust reference between 0 to +5V in 40mV increments   
* External DAC voltage reference input (+6V max)
* External supply inputs for DAC output buffers (+V = 18V, -V = -18V max)   
* 2Kbit I2C EEPROM (e.g. store board S/N, calibration constants to adjust DAC non-linearities, etc.)
* Supports 3.3V and 5V SPI and I2C buses

##  Quick Start Procedure
1. Connect the Arduino or Linduino controller to the DAC Demo Board per the illustration below.
2. Upload the controller MCU with the firmware (.ino file) in the *src* directory.
3. Set DAC VREF, unipolar/bipolar mode and output voltage using the CMD listed in the *Software* section below.

## Hardware Architecture 
### Block Diagram
![Demo_Board_Block_Diagram](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Block_Diagram.png)
### Jumper Selections
| Jumper Reference| Description |
|:---:|:---|
| JP1 | Selects the reference voltage for both DACs.  Use JP1 pin 2 to supply a +6V max external voltage.  Populate U2 and place a jumper between JP1 pins 2 and 3 to select +2.5V.  Place jumper between JP1 pins 1 and 2 to select +5V |
| JP2 |  Sets DAC0 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 18V to +V-EXT and -V_EXT  |
| JP3 | Sets DAC1 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 18V to +V-EXT and -V_EXT |
| JP4 | Sets DAC output buffers and digital potentiometer +V supply to *+V_EXT* or onboard *+5V_REG* |
| JP5 | Sets DAC output buffers and digital potentiometer -V supply to *-V_EXT* or onboard GND |
| JP8 | Sets the asynchronous or synchronous control of DAC0 and DAC1.  Asynchronous mode allows the DAC outputs to be set to different values at different times.  Synchronous mode sets the DAC outputs to the same value at the same time. |


## Software 
### Usage
1. Pull/download src repo  
2. Download the latest Arduino IDE if it doesn't exist on computer PC already
3. Copy all files onto your local machine. into a parent directory named after the .ino file
4. Connect the Arduino UNO or Linduino to your PC
5. Open the .ino file and upload the firmware to the UNO or Linduino 

### Commands

#### **DAC0** <*dac_code = unsigned int*> 

|Parameters: |**dac_code** - 16-bit DAC output voltage code|
|:---:|:---|
|Usage Example| **DAC0 65534**, sets DAC0 output voltage to full-scale or DAC0 VREF voltage|

#### **DAC1** <*dac_code = unsigned int*> 

|Parameters: |**dac_code** - 16-bit DAC output voltage code|
|:---:|:---|
|Usage Example| **DAC1 65534**, sets DAC1 output voltage to full-scale or DAC1 VREF voltage|

#### **DAC0_MODE** <*mode_setting = byte*> 

|Parameters: |**mode_setting** - DAC unipolar or bipolar mode|
|:---:|:---|
|Usage Example| **DAC0_MODE 0**, sets DAC0 output mode to unipoloar (output voltages range from 0 to +VREF)|

#### **DAC1_MODE** <*mode_setting = byte*> 

|Parameters: |**mode_setting** - DAC unipolar or bipolar mode|
|:---:|:---|
|Usage Example| **DAC1_MODE 1**, sets DAC1 output mode to bipoloar (output voltages range from -VREF to +VREF)|

#### **VREF** <*VREF_setting = float*> 

|Parameters: |**VREF_setting** - DAC VREF voltage|
|:---:|:---|
|Usage Example| **VREF 2.5**, tells firmware that dac VREF is set to 2.5V on the demo board|

This command is required in order for the board to generae accurate DAC output voltage 
