# README #
A project with STM32F103RB is called air pencil.
Using FreeRTOS, SPL, auto build with make and require arm-none-eabi-gcc-4.8.4 or newer.
Hardware requirements:

  - STM32F103RB ARM Cortex-M3 MCU (ST Microelectronics)
  - ADXL345 Digital Accelerometer (Analog Devices)
  - ITG3200 Digital Gyroscope     (InvenSense)
  - J-Link BASE hardware v9.x     (Segger - older versions not support for Linux)

### Tree ###
```
.
├── FreeRTOS      => RTOS core
├── Libraries     => Standard peripheral libraries
├── Sensors       => Sensors libraries
├── Inc           => user header files
└── Src           => user source files
```

### Flash Programming with J-Link ###
So, let's go with J-Link Software Pack installation:

  * Download J-Link Software Pack installation at https://www.segger.com/downloads/jlink/
  * In download folder, run: ```sudo dpkg --install <name-of-jlink-installer>```

Connect MCU board to debugger. Run J-Link commander:

  * In terminal, run ```JLinkExe```
  * With prompt displayed as ```J-Link```, type ```connect``` (you can see like ```J-Link>connect```)
  * With prompt displayed as ```Device```, type name of MCU line (you can see like ```Device>STM32F103RB```)
  * With prompt displayed as ```TIF```, type representing symbol of interface you wanna use (I choose SWD, like ```TIF>S```)
  * With prompt displayed as ```Speed```, type operation frequency of interface (e.g. ```TIF>1000```, unit as kHz). If you complete all step above, you'll be received a message as ```Cortex-M3 identified.``` and prompt will be displayed as ```J-Link```

To load data file into target memory, you can use syntax:

  * ```loadfile <filename>, [<addr>]```, supported extensions: *.bin, *.mot, *.hex, *.srec and <addr> is needed for bin files only
  or simple
  * ```loadbin  <filename>, <addr>``` with only *.bin files.
  In there, <addr> is the first memory address of the flash area (see more in linker file)
  * E.g.: ```loadbin demo.bin, 0x0800000```
