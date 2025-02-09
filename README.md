# Mostek MK23XX Character Generator Readout

![Mostek MK23XX Character Generator Readout device under opertion showing an A character](https://github.com/MattisLind/MK23xxCharGenReadout/blob/main/MK23XX_Character_Generator_Readout.jpg?raw=true)


This device is used to read out the contents of early character generator MK23XX ROMs from Mostek. These devices is a bit special since they include a column counter so that the each column cannot be
accessed directly through external addressing pins.

[![Mostek MK23XX Datasheet](https://github.com/MattisLind/MK23xxCharGenReadout/blob/main/Mostek_MK23XX_Datasheet.png?type=raw)](https://github.com/MattisLind/MK23xxCharGenReadout/blob/main/MK23XX_Datasheet.pdf?type=raw)

The device has to be connected over USB (unless this section is commented out in the source code) and then it provide a dump of the contents of the ROM as hex as it cycles through all 64 characters.

```
CHAR0 COLUMN 0 VALUE 0
CHAR0 COLUMN 1 VALUE 0
CHAR0 COLUMN 2 VALUE 0
CHAR0 COLUMN 3 VALUE 0
CHAR0 COLUMN 4 VALUE 0
CHAR1 COLUMN 0 VALUE 7
CHAR1 COLUMN 1 VALUE 7
CHAR1 COLUMN 2 VALUE 7
CHAR1 COLUMN 3 VALUE 7
CHAR1 COLUMN 4 VALUE 7
CHAR2 COLUMN 0 VALUE 70
CHAR2 COLUMN 1 VALUE 70
CHAR2 COLUMN 2 VALUE 70
CHAR2 COLUMN 3 VALUE 70
CHAR2 COLUMN 4 VALUE 70
```

Please note that the contents of this example ROM is active low so that a binary 0 indicate a lit pixel. Depending if the outputs are active low or high the output driver can be 7407 or 7406 respectively.

## PCB

The first PCB had too small holes for the 24 pin ROM socket so it was not possible to fit a ZIF socket. I revised the PCB so that the new PCB have 1.0 mm holes rather than 0.8 mm. I think that this should work better but have not ordered any PCB to check. 

## Software

The software is an Arduino sketch. I have been using [Arduino Core STM32](https://github.com/stm32duino/Arduino_Core_STM32) library. The Bluepill is a STM32F103C6 and it is set to have USB enabled with serial support 

There is a #define SCROLL which can be set to either 0 or 1 if one want the fancier soft scroll rather than just showing each character.

