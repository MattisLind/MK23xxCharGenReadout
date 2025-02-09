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

Please note that the contents of this example ROM is active low so that a binary 0 indicate a lit pixel.

