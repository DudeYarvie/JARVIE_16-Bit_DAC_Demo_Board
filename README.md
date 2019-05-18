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
| Jumper Reference| Description |
|:---:|:---|
| JP1 | Selects the reference voltage for both DACs.  Use JP1 pin 2 to supply a +6V max external voltage.  Populate U2 and place a jumper between JP1 pins 2 and 3 to select +2.5V.  Place jumper between JP1 pins 1 and 2 to select +5V |
| JP2 |  Sets DAC0 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 18V to +V-EXT and -V_EXT  |
| JP3 | Sets DAC1 to uni (output 0V to +VREF) or bipolar (output +VREF to -VREF) mode.  In bipolar mode, set JP4 and JP5 to EXT supplies and apply up to +/- 18V to +V-EXT and -V_EXT |
| JP4 | Sets DAC output buffers and digital potentiometer +V supply to *+V_EXT* or onboard *+5V_REG* |
| JP5 | Sets DAC output buffers and digital potentiometer -V supply to *-V_EXT* or onboard GND |
| JP8 | Sets the asynchronous or synchronous control of DAC0 and DAC1.  Asynchronous mode allows the DAC outputs to be set to different values at different times.  Synchronous mode sets the DAC outputs to the same value at the same time. |

### DAC
### EEPROM


## SOFTWARE
