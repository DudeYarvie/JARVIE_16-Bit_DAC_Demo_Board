# JARViE_DAC_Demo_Board
 The heart of the demo board are two LTC2642 16-bit DACs. They enable the DAC Demo Board to generate -5 to +5V signals on either of two output channels. Output channels may be updated asynchronously or synchronously. When updating synchronously, the same voltage will be produced on each output channel at the same time instance.

## Features
* Two +/- 5V @ 25 mA max rail-to-rail buffered voltage output channels
* DACs may be updated asynchronously or synchronously
* DAC +5V reference with trimming to adjust reference between 0 to +5V in 40mV increments   
* External DAC voltage reference input (+6V max)
* External supply inputs for DAC output buffers (+V = 18V, -V = -18V max)   
* 2Kbit I2C EEPROM (e.g. store board S/N, calibration constants to adjust DAC non-linearities, etc.)
* Supports 3.3V and 5V SPI and I2C buses

## Hardware Architecture 
### Block Diagram
![Demo_Board_Block_Diagram](https://github.com/DudeYarvie/JARVIE_16-Bit_DAC_Demo_Board/blob/master/Reference%20Docs/JARViE_DAC_DEMO_Block_Diagram.png)
### Jumper Selections
### DAC
### EEPROM


## SOFTWARE
