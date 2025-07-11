# *****************************************************************************
# NEORV32 FreeRTOS Makefile
# *****************************************************************************

# Override the default RISC-V GCC prefix
RISCV_PREFIX ?= riscv-none-elf-

# User's application sources (*.c, *.cpp, *.s, *.S); add additional files here
APP_SRC = $(wildcard ./*.c) $(wildcard ./*.s) $(wildcard ./*.cpp) $(wildcard ./*.S)

# User's application include folders (don't forget the '-I' before each entry)
APP_INC = -I .

# User's application include folders - for assembly files only (don't forget the '-I' before each entry)
ASM_INC = -I .

# User flags for additional configuration (will be added to compiler flags)
USER_FLAGS =

# -----------------------------------------------------------------------------
# FreeRTOS
# -----------------------------------------------------------------------------

# FreeRTOS home folder
FREERTOS_HOME ?= ../FreeRTOS-Kernel

# Kernel
APP_SRC += $(wildcard $(FREERTOS_HOME)/*.c)
APP_INC += -I $(FREERTOS_HOME)/include

# RISC-V specifics
APP_SRC += $(wildcard  $(FREERTOS_HOME)/portable/GCC/RISC-V/*.c)
APP_SRC += $(FREERTOS_HOME)/portable/GCC/RISC-V/portASM.S
APP_INC += -I $(FREERTOS_HOME)/portable/GCC/RISC-V

# Heap management
APP_SRC += $(wildcard  $(FREERTOS_HOME)/portable/MemMang/heap_4.c)

# -----------------------------------------------------------------------------
# NEORV32
# -----------------------------------------------------------------------------

# NEORV32 home folder
NEORV32_HOME ?= ../neorv32

# Chip-specific configuration
APP_INC += -I chip_specific_extensions/neorv32
ASM_INC += -I chip_specific_extensions/neorv32

# Override the default CPU ISA and ABI
MARCH = rv32i_zicsr_zifencei
MABI  = ilp32

# Set RISC-V GCC prefix
RISCV_PREFIX ?= riscv-none-elf-

# Override default optimization goal
EFFORT = -Os

# Adjust processor IMEM size and base address
USER_FLAGS += -Wl,--defsym,__neorv32_rom_size=32k
USER_FLAGS += -Wl,--defsym,__neorv32_rom_base=0x00000000

# Adjust processor DMEM size and base address
USER_FLAGS += -Wl,--defsym,__neorv32_ram_size=16k
USER_FLAGS += -Wl,--defsym,__neorv32_ram_base=0x80000000

# Software framework, HAL, build environment, etc.
include $(NEORV32_HOME)/sw/common/common.mk
