FAMILY := nrf52
SOURCES := main.c

BUILD_DIR := build
BUILD_SYS := .build_system
LINKER_SCRIPT := $(BUILD_SYS)/linker_script_nrf52.ld

GNU_PREFIX	:= arm-none-eabi
CC			:= $(GNU_PREFIX)-gcc
OBJCOPY		:= $(GNU_PREFIX)-objcopy
OBJDUMP		:= $(GNU_PREFIX)-objdump

QUIET := @

## Compiler flags
# CPU specific
CFLAGS += -mcpu=cortex-m4 -mthumb -mabi=aapcs -mfloat-abi=soft
# Get linker optimization for free
CFLAGS += -ffunction-sections -fdata-sections --short-enums
CFLAGS += -fno-strict-aliasing -fno-builtin
# Throw errors for warnings and set GNU dialect to ISO C99
CFLAGS += -Wall -Werror -std=gnu99
# CFLAGS += -ggdb -Og / -O0 / -O3 etc
# Chip specific
CFLAGS += -DNRF52832_XXAA

## Linker flags
CFLAGS += --specs=nosys.specs -Wl,--gc-sections -T $(LINKER_SCRIPT)
# or --specs=nano.specs -lc -lnosys

SOURCES += $(BUILD_SYS)/system_nrf52.c
SOURCES += $(BUILD_SYS)/gcc_startup_nrf52.S

.PHONY: default flash debug erase recover clean

default: $(BUILD_DIR)
	@echo Compiling project
	$(QUIET)$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD_DIR)/main.elf
	@echo Creating hex file
	$(QUIET)$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

flash:
	nrfjprog -f $(FAMILY) --sectorerase --program $(BUILD_DIR)/main.hex --verify --reset
	
debug: $(BUILD_DIR)
	@echo Compiling project with debug
	$(CC) $(CFLAGS) -ggdb -Og $(SOURCES) -o $(BUILD_DIR)/main.elf
	@echo Creating hex file
	$(OBJCOPY) -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex

erase: $(BUILD_DIR)
	nrfjprog -f $(FAMILY) --eraseall

clean: $(BUILD_DIR)
	$(QUIET) rm $(BUILD_DIR)/main.elf
	$(QUIET) rm $(BUILD_DIR)/main.hex

recover: $(BUILD_DIR)
	nrfjprog --recover

$(BUILD_DIR):
	$(QUIET)mkdir -p $(BUILD_DIR)
