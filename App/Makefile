# PROJECT = blink
# BUILD_DIR = build
# SRC = src/firmware.c

# LIBOPENCM3_DIR = ../libopencm3
# DEVICE = stm32f0
# OOCD_FILE = interface/stlink.cfg
# OOCD_TARGET = target/stm32f0x.cfg

# CC = arm-none-eabi-gcc

# CFLAGS = -Os -Wall -g
# CFLAGS += -mcpu=cortex-m0 -mthumb
# CFLAGS += -DSTM32F0
# CFLAGS += -I$(LIBOPENCM3_DIR)/include

# LDFLAGS = -T../linkerscript.ld
# LDFLAGS += -nostartfiles -Wl,--gc-sections
# LDFLAGS += -L$(LIBOPENCM3_DIR)/lib
# LDFLAGS += -lopencm3_stm32f0
# # LDFLAGS += ../libopencm3/lib/stm32/f0/stm32f072rb.o


# all: $(BUILD_DIR)/$(PROJECT).elf

# $(BUILD_DIR):
# 	mkdir $(BUILD_DIR)

# $(BUILD_DIR)/$(PROJECT).elf: $(SRC) | $(BUILD_DIR)
# 	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

# flash:
# 	openocd -f $(OOCD_FILE) -f $(OOCD_TARGET) \
# 	-c "program $(BUILD_DIR)/$(PROJECT).elf verify reset exit"

# clean:
# 	rm -rf $(BUILD_DIR)

PROJECT = blink
BUILD_DIR = build
SRC = src/firmware.c
# Convert source paths to object paths in the build directory
OBJ = $(BUILD_DIR)/firmware.o

LIBOPENCM3_DIR = ../libopencm3
DEVICE = stm32f0
OOCD_FILE = interface/stlink.cfg
OOCD_TARGET = target/stm32f0x.cfg

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -Os -Wall -g
CFLAGS += -mcpu=cortex-m0 -mthumb
CFLAGS += -DSTM32F0
# FIX: Added -Iinc to find your local headers
CFLAGS += -Iinc -I$(LIBOPENCM3_DIR)/include

LDFLAGS = -T../linkerscript.ld
LDFLAGS += -nostartfiles -Wl,--gc-sections
LDFLAGS += -L$(LIBOPENCM3_DIR)/lib
LDFLAGS += -lopencm3_stm32f0

# Default target: build the .bin file
all: $(BUILD_DIR)/$(PROJECT).bin

# Rule 1: Create the build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule 2: Compile .c files into .o object files
$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule 3: Link .o files into .elf executable
$(BUILD_DIR)/$(PROJECT).elf: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Rule 4: Convert .elf to .bin (The flashable file)
$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

flash: $(BUILD_DIR)/$(PROJECT).bin
	openocd -f $(OOCD_FILE) -f $(OOCD_TARGET) \
	-c "program $< verify reset exit"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash
