CROSS_COMPILE ?= arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE = $(CROSS_COMPILE)size

PROJECT_DIR = $(shell pwd)
BUILD_DIR = $(PROJECT_DIR)/build
CMSIS_CORE = $(PROJECT_DIR)/CMSIS/core
CMSIS_DEVICE = $(PROJECT_DIR)/CMSIS/device
INC = $(PROJECT_DIR)/inc
SRC = $(PROJECT_DIR)/src
STARTUP = $(PROJECT_DIR)/startup
STD_INC = $(PROJECT_DIR)/StdPeriph_Driver/inc
STD_SRC = $(PROJECT_DIR)/StdPeriph_Driver/src

PROJECT_TREE = $(CMSIS_CORE) $(SRC) $(STD_SRC)

INCLUDES = -I $(CMSIS_CORE) \
	-I $(CMSIS_DEVICE) \
	-I $(INC) \
	-I $(SRC) \
	-I $(STARTUP) \
	-I $(STD_INC) \
	-I $(STD_SRC)

HEADERS = $(wildcard $(CMSIS_CORE)/*.h) \
	$(wildcard $(CMSIS_DEVICE)/*.h) \
	$(wildcard $(STD_INC)/*.h) \
	$(wildcard $(INC)/*.h) \
	$(wildcard $(STARTUP)/*.s) \
	$(wildcard $(SRC)/*.h)

SOURCES = $(wildcard $(CMSIS_CORE)/*.c) \
	$(wildcard $(STD_SRC)*/.c) \
	$(wildcard $(SRC)/*.c) \
	$(wildcard $(STARTUP)/*.s)

DEPS = $(SOURCES) $(HEADERS)

OBJECTS = system_stm32f10x.o \
	core_cm3.o \
	syscalls.o \
	stm32f10x_rcc.o \
	stm32f10x_adc.o \
	stm32f10x_usart.o \
	stm32f10x_gpio.o \
	misc.o \
	utils.o  \
	kalman.o \
	adccontroller.o  \
	gui.o \
	settings.o \
	input.o \
	lcd16x2.o \
	protocol.o \
	midicontroller.o \
	stmdrum.o \
	main.o

all: dir $(OBJECTS) binaries 

binaries: stmdrum.elf stmdrum.hex stmdrum.bin stmdrum.lst size

CFLAGS  = -g -Wall --specs=nosys.specs -Wno-missing-braces -O3
CFLAGS += -ffunction-sections -fdata-sections -ffast-math -fsingle-precision-constant 
CFLAGS += -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -Wl,-M=main.map -Wl,-TLinkerScript.ld -DSTM32F10X_MD_VL -DUSE_STDPERIPH_DRIVER
CFLAGS += $(INCLUDES) $(STARTUP)/startup_stm32.s

dir:
	mkdir -p $(BUILD_DIR)

system_stm32f10x.o: $(SRC)/system_stm32f10x.c
	$(CC) $(CFLAGS) -c $(SRC)/system_stm32f10x.c

core_cm3.o: $(CMSIS_CORE)/core_cm3.c
	$(CC) $(CFLAGS) -c $(CMSIS_CORE)/core_cm3.c

syscalls.o: $(SRC)/syscalls.c
	$(CC) $(CFLAGS) -c $(SRC)/syscalls.c

stm32f10x_rcc.o: $(STD_SRC)/stm32f10x_rcc.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/stm32f10x_rcc.c

stm32f10x_adc.o: $(STD_SRC)/stm32f10x_adc.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/stm32f10x_adc.c

stm32f10x_usart.o: $(STD_SRC)/stm32f10x_usart.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/stm32f10x_usart.c

stm32f10x_gpio.o: $(STD_SRC)/stm32f10x_gpio.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/stm32f10x_gpio.c

stm32f10x_flash.o: $(STD_SRC)/stm32f10x_flash.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/stm32f10x_flash.c

eeprom.o: $(SRC)/eeprom.c
	$(CC) $(CFLAGS) -c $(SRC)/eeprom.c

misc.o: $(STD_SRC)/misc.c
	$(CC) $(CFLAGS) -c $(STD_SRC)/misc.c

utils.o: $(SRC)/utils.c
	$(CC) $(CFLAGS) -c $(SRC)/utils.c

kalman.o: $(SRC)/kalman.c
	$(CC) $(CFLAGS) -c $(SRC)/kalman.c

adccontroller.o: $(SRC)/adccontroller.c
	$(CC) $(CFLAGS) -c $(SRC)/adccontroller.c

gui.o: $(SRC)/gui.c
	$(CC) $(CFLAGS) -c $(SRC)/gui.c

settings.o: $(SRC)/settings.c
	$(CC) $(CFLAGS) -c $(SRC)/settings.c

input.o: $(SRC)/input.c
	$(CC) $(CFLAGS) -c $(SRC)/input.c

lcd16x2.o: $(SRC)/lcd16x2.c
	$(CC) $(CFLAGS) -c $(SRC)/lcd16x2.c

protocol.o: $(SRC)/protocol.c
	$(CC) $(CFLAGS) -c $(SRC)/protocol.c

midicontroller.o: $(SRC)/midicontroller.c
	$(CC) $(CFLAGS) -c $(SRC)/midicontroller.c

stmdrum.o: $(SRC)/stmdrum.c
	$(CC) $(CFLAGS) -c $(SRC)/stmdrum.c

main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) -c $(SRC)/main.c

stmdrum.elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o stmdrum.elf $(OBJECTS)

stmdrum.hex: stmdrum.elf
	$(OBJCOPY) -O ihex stmdrum.elf stmdrum.hex

stmdrum.bin: stmdrum.elf
	$(OBJCOPY) -O binary stmdrum.elf stmdrum.bin

stmdrum.lst: stmdrum.elf
	$(OBJDUMP) -x -S stmdrum.elf > stmdrum.lst

size: stmdrum.elf
	$(SIZE) stmdrum.elf


clean: 
	rm -rf $(BUILD_DIR) $(SRC)/*.gch $(INC)/*.gch $(CMSIS_CORE)/*.gch $(CMSIS_DEVICE)/*.gch $(STD_INC)/*.gch $(STD_SRC)/*.gch *.elf *.bin *.o *.map *.gch *.hex *.lst *~

install: all
	st-flash write stmdrum.bin 0x08000000
