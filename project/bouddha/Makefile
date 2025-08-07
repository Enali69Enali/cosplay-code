# Target MCU and build configuration
MCU=atmega328p         # Target microcontroller (Arduino Uno)
F_CPU=16000000UL       # Clock frequency in Hz (16 MHz for Uno)
PORT=COM3              # Serial port (adjust as needed)
BAUD=115200            # Baud rate for flashing
PROGRAMMER=arduino     # Type of programmer (Arduino bootloader)

# Compiler tools
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

# Compiler flags
CFLAGS=-Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)

# Target binary name (without extension)
TARGET=main

SRC_DIR = .
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)

# Each src files generates its own object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

# Detect platform (Windows or Unix)
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RMDIR = if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
else
    MKDIR = mkdir -p $(BUILD_DIR)
    RMDIR = rm -rf $(BUILD_DIR)
endif



# Default target: generate .hex file
all: $(HEX)

$(BUILD_DIR):
	$(MKDIR)

# Compile .c to .o (object file)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Link .o to .elf (executable)
$(ELF): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ 

# Convert .elf to .hex for flashing
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# Upload .hex to Arduino via avrdude
flash: $(HEX)
	$(AVRDUDE) -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

# Clean up intermediate files
clean:
	$(RMDIR)
