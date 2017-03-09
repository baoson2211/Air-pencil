#
# Simple makefile to compile the example code given for the STM32F10x
# family of ARM processors. This file should be placed in the same
# directory that you wish to compile.
#
# INCLUDEDIRS selects all folders in the package that have header files. Since
#             this is already an inclusive list, it should not need editing.
#
# LIBSOURCES contains all the Driver (SPL/HAL/BSP) files that need to be compiled
#            for this specific project. This should be updated with the help
#            of the dependencies file (main.d) generated on any (including
#            unsucessful) compilation.
#
# Note: The provided code sometimes uses windows backslashes (\) in include
#       paths. Update as needed.
#
# Note: When building the lists for LIBSOURCES, *_ex.c files must come before
#       the generic version of the file. This is necessary for linking to find
#       the extended (board-specific) version of the function.
#

# build environment
CC      = arm-none-eabi-gcc
CPP     = arm-none-eabi-g++
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size
MAKE    = make

# location of OpenOCD Board .cfg files (only used with 'make program')
OPENOCD_BOARD_DIR=/usr/local/share/openocd/scripts/board

# Configuration (cfg) file containing programming directives for OpenOCD
OPENOCD_PROC_FILE=stm32f1-openocd.cfg

# project parameters
PROJ_NAME = air-pencil
CPU_FAMILY = STM32F10x
CPU_MODEL_GENERAL = STM32F103xB
CPU_MODEL_SPECIFIC = STM32F103RB


################################################################################
# Libraries
# Header of all libraries
INCLUDEDIRS  = Inc
INCLUDEDIRS += Sensors/inc
INCLUDEDIRS += Libraries/STM32F10x_StdPeriph_Driver/inc
INCLUDEDIRS += Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
INCLUDEDIRS += Libraries/CMSIS/CM3/CoreSupport
INCLUDEDIRS += AHRS
# include of FreeRTOS
INCLUDEDIRS += FreeRTOS
INCLUDEDIRS += FreeRTOS/include
INCLUDEDIRS += FreeRTOS/portable/GCC/ARM_CM3
INCLUDEDIRS += FreeRTOS/portable/MemMang

# Source of specify libraries
LIBSOURCES  = AHRS/AHRS.c
# system_stm32f10x.c
LIBSOURCES += $(shell find Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -name '*.c')
# full std periph libraries - if you wanna choose specify libraries, comment the line below
# and define specify ones in this LIBSOURCES
LIBSOURCES += $(shell find Libraries/STM32F10x_StdPeriph_Driver/src -name '*.c')
# sensors user define libraries
LIBSOURCES += $(shell find Sensors/src -name '*.c')
#LIBSOURCES += Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
#LIBSOURCES += Libraries/STM32F10x_StdPeriph_Driver/src/

# sources of FreeRTOS
#LIBSOURCES += FreeRTOS/croutine.c \
              FreeRTOS/event_groups.c \
              FreeRTOS/list.c \
              FreeRTOS/queue.c \
              FreeRTOS/tasks.c \
              FreeRTOS/timers.c
#LIBSOURCES += FreeRTOS/portable/GCC/ARM_CM3/port.c
#LIBSOURCES += FreeRTOS/portable/MemMang/heap_1.c

LIBOBJS = $(LIBSOURCES:.c=.o)

################################################################################
# Source files
#
# auto-generated project paths
SOURCES  = $(shell find Src -name '*.c')
SOURCES += Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

# C Object files
OBJC = $(SOURCES:.c=.o)
# add ASM Object files
OBJ = $(OBJC:.s=.o)

# Resources are translated to ASM
TOASSEMBLY  = $(SOURCES:.c=.o)
TOASSEMBLY += $(LIBSOURCES:.c=.o)

# Linked file
# can see it in STM32F10x_StdPeriph_Lib_V3.x.x/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210X-EVAL
# X may be B, C or E depend on your mcu
LDSCRIPT = -Wl,-T stm32_flash.ld

# CFLAGS
CFLAGS  = -Wall -g -Og -D $(CPU_MODEL_GENERAL)
CFLAGS += -std=c99 -mlittle-endian -mcpu=cortex-m3 -march=armv7-m -mthumb
CFLAGS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD -DHSE_VALUE=8000000
CFLAGS += -DGCC_ARMCM3 #-DFREERTOS
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(PROJ_NAME).map
CFLAGS +=  $(addprefix -I ,$(INCLUDEDIRS))

.PHONY: all clean

all: proj

proj: toassembly $(PROJ_NAME).elf

################################################################################
# Compile and assemble sequence C files, but do not link
#
%.o: %.c
# $(eval AUTOINCLUDES = $(addprefix -include ,$(shell find $(dir $<) -name *.h)))
	$(CC) -c -o $@ $< $(CFLAGS)
# Translate all .c files to ASM -masm
	$(CC) -S -o $*.asm $< $(CFLAGS)
# pull in dependency info for *existing* .o files
	$(CC) -MM $(CFLAGS) $< > $*.d

################################################################################
# Translate all .c files to ASM
#
toassembly: $(TOASSEMBLY)

################################################################################
# A brief introduction about the libraries:
#
# -lc      : link to standard C library ( stdio.h and stdlib.h are examples)
# -lg      : a debugging-enabled libc
# -lm      : link to math C library ( math.h )
# -lnosys  : non-semihosting
#            link to libnosys.a - The libnosys.a is used to satisfy all system call references,
#            although with empty calls. In this configuration, the debug output
#            is forwarded to the semihosting debug channel, vis SYS_WRITEC.
#            The application and redefine all syscall implementation functions, like _write(),
#            _read(), etc. When using libnosys.a, the startup files are not needed
#            Since 4.8, recommended -specs=nosys.specs instead
# -lrdimon : semihosting
#            link to librdimon.a - implements all system calls via the semihosting API with all
#            functionality provided by the host. When using librdimon.a, the startup files are
#            required to provide all specific initialisation, and the rdimon.specs
#            must be added to the linker
#            Since 4.8, recommended -specs=rdimon.specs instead
#

################################################################################
# Link all object files
# -l : library search, applies in a special way to libraries used with the linker
#      (GNU Make - page 28 - 4.4.6 Directory Search for Link Libraries)
# -L : Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L.
#      Libraries (-lfoo) should be added to the LDLIBS variable instead.
#      (GNU Make - page 72 - 6.13 Suppressing Inheritance)
# -T : ld script file
#
$(PROJ_NAME).elf: $(OBJ) $(LIBOBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDSCRIPT) --specs=nano.specs --specs=rdimon.specs -lc -lm -lrdimon
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf > $(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf

################################################################################
# Programming with openocd
#program: proj
#	openocd -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE) -c "stm_flash `pwd`/$(PROJ_NAME).bin" -c shutdown
#
#openocd:
#	openocd -f $(OPENOCD_BOARD_DIR)/stm32f0discovery.cfg -f $(OPENOCD_PROC_FILE)

################################################################################
# Programming with stm32flash
#
flash:
	stm32flash -w $(PROJ_NAME).hex -v -g 0x08000000 /dev/ttyUSB0

################################################################################
# Clean
#
clean:
	rm -f $(shell find ./ -name '*.o')
	rm -f $(shell find ./ -name '*.d')
	rm -f $(shell find ./ -name '*.asm')
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst
