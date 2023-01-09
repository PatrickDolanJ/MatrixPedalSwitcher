# The Heighliner 

Full Stereo Pedal Switcher Matrix with recallable phase and volumes.  

  

![Mother_3D_v142](https://user-images.githubusercontent.com/87340915/200351416-46ea5be7-2c23-44e3-af4f-a50014fb4ffa.png) 

  

## What is it? 

  

Imagine if you could switch your pedals in any order, save that order as presets, assign it to a foot switch, and effortlessly and quickly rock n roll. Traditionally pedals are arranged in a sequential order.  However, what if you wanted to rearrange that sequential order to achieve a certain sound. For instance, reverb then distortion sounds very different from distortion then reverb. On most pedal boards this is not something that can be quickly configured.  Even with pedal switching boards you are often limited to just adding in the pedals in an fx loop via a button press.  what if you wanted to use two delay pedals in parallel so that the delay from the first pedal does not affect the delay of the other.  Perhaps you'd like to be able to turn on and off 3 fx simultaneously via one foot switch for a crucial moment in a song.  

  

This is the job of a pedal switcher, but the Heighliner offers a few more features worth noting.  

  

1.) The slim profile(approx. 16" by 4") means that it takes up significantly less real estate than other pedal switchers.   

  

2.) The UI is quick, responsive, and intuitive.   

  

3.) It is entirely stereo but supports mono as well.   

  

4.) Input volume, left and right output volume, and the phase of each channel (both left and right) are savable in the presets, requiring even less knob turning.   

  

  

## How to Run 

  

The Heighliner's core is an Arduino Mega 2560 Pro (Mega) and thus requires the Arduino framework. This project, however, uses the PlatformIO (VSCode extension) platform to compile, upload, and communicate with the Mega.

To compile the project click the small "checkmark" in the blue band on the bottom of VSCode. To upload, make sure that the Arduino is connected via USB and click the small right facing arrow. To open the Serial Monitor, used to communicate over the Arduino's USB port serial line, click the small electrical plug symbol.  

The serial Baud rate is set to 115200 and can be set via the platformio.ini file as such:

monitor_speed = 115200


## How it Works
    
The core of the project is two AGD2188 Unbuffered Analog Switch Arrays over I2C, one for right and one for left channels at 0x70 and 0x74 addresses respectively. The chip is an 8x8 matrix that allows any permutation of x and y connections. The basic principle is to connect an x(input) to y(output) when a pedal (loop) should be incorporated into the signal chain. This is handled by the "Matrix" library through the AGD2188 class.

Each input and both left and right outputs volumes are controlled by digital pots (AD5206) over SPI.  

The return(Mono or Stereo) relays (OMRON G6K-F2  5VDC DPDT Relays) are addressed through IO Expanders  (PCF8574) and found at I2C address 0x24.   

The left phase invert relays (OMRON G6K-F2  5VDC DPDT Relays)  are addressed through IO Expanders (PCF8574) and found at I2C address 0x26.  

The right phase invert relays (OMRON G6K-F2  5VDC DPDT Relays) are addressed through IO Expanders (PCF8574) and found at I2C address 0x25.  

All PCF8574s utilize  Version: 1.0.3 pcf8574-1.03 library by MSZ98 through the PCF8574 class and can be found at: https://github.com/MSZ98/PCF8574 ;

The primary controls are 8 rotary encoders which are connected to a MPC23017 IO expander which communicates over I2C found at 0x20. These are handled through the "EasyRotary" library which is based on maxgerhardt's "RotaryEncOverMCP" library found at: https://github.com/maxgerhardt/rotary-encoder-over-mcp23017

These control the adjustment of most parameters including volume, phase, loop position etc., depending on the menu state.

Each rotary encoder has a push button which is used to switch between menu states and long pressed to change the return from Mono to Stereo and vice versa. 
These are accessed through an IO Expander (PCF8574) at 0x21. 

Likewise the foot switches, used to change between presets, are run through an IO Expander (PCF8574) at 0x22. 

The foot switches, rotary encoder buttons, and the rotary encoders themselves all use interrupt pins to initialize reading  input data over I2C.

Lastly, the main display is a Nextion NX3224T024_01. These are programmed using Nextions GUI editor and addressed over SPI. The Nextion commands can be found in NextionCommands.h

## Next Steps

1.) Adding SD card read/write to save/load presets.  
2.) Add volume damping back in when changing data
3.) 

## Made by
### Proto Co-op: 
Patrick Dolan  
Ian Edwards
