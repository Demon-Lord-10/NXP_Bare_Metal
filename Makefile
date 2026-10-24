TARGET := firmware
CPU    := cortex-m33+nodsp+nofp

OBJ_DIR := obj
BUILD_DIR := build

INC := -I inc/
SRC := $(wildcard src/*.c) src/startup.s
OBJ := $(patsubst src/%,$(OBJ_DIR)/%.o,$(basename $(SRC)))
LDSCRIPT := linker.ld

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size
OBJDUMP := arm-none-eabi-objdump

ELF := $(BUILD_DIR)/$(TARGET).elf
BIN := $(BUILD_DIR)/$(TARGET).bin
MAP := $(BUILD_DIR)/$(TARGET).map
LST := $(BUILD_DIR)/$(TARGET).lst

# Flags
CFLAGS := -mcpu=$(CPU) -mthumb -O0 -g3 \
          -Wall -Wextra -mlittle-endian \
          -nostdlib $(INC) -nostartfiles \
		  -Wshadow

LDFLAGS  := -mcpu=$(CPU) -mthumb \
            -T $(LDSCRIPT) \
            -nostartfiles \
            -Wl,-Map=$(MAP),--cref \
            -Wl,--gc-sections \
            -Wl,--print-memory-usage

# Default rule: asks for both .elf and .bin
all: $(ELF) $(BIN) $(LST)

# create dir if it doesnt exist
$(BUILD_DIR) $(OBJ_DIR):
	@mkdir -p $@

$(OBJ): | $(OBJ_DIR)

# .elf -> .bin
$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

# .elf -> .lst (Disassembly listing with interleaved C source)
$(LST): $(ELF)
	$(OBJDUMP) -h -S -d $< >$@

# .o files -> .elf
$(ELF): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

# .c and .s files -> .o files
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.s
	$(CC) $(CFLAGS) -c $< -o $@

# Delete generated files so you can rebuild from scratch
clean:
	rm -rf $(BUILD_DIR)/* $(OBJ_DIR)/*

# Flash on to the NXP board
flash: $(ELF)
	LinkServer flash MCXA153 load $<

.PHONY: all clean flash
