# STM32F0 Bare Metal Blinky (libopencm3)

A lightweight, bare-metal LED blinky project for the **NUCLEO-F072RB** (STM32F072RB). This project bypasses heavy IDEs like STM32CubeIDE in favor of a manual **Makefile** build system and the **libopencm3** firmware library.

## Hardware

- **MCU:** STM32F072RBT6 (Cortex-M0)
- **Board:** NUCLEO-F072RB
- **Debugger:** On-board ST-LINK/V2-1

## Key Features

- **Manual Vector Table:** Custom Reset_Handler and ISR vector definition in C.
- **Custom Linker Script:** Uses a memory-mapped linker script for precise flash/RAM control.
- **Makefile Workflow:** Full control over compilation, linking, and flashing via OpenOCD.
- **Library:** Powered by the open-source `libopencm3`.

## Prerequisites

- `arm-none-eabi-gcc`
- `make`
- `openocd`

## Setup & Build

1. **Clone the repo with submodules:**
   ```bash
   git clone --recursive <your-repo-url>
   cd <repo-name>
   Use code with caution.
   ```

Build the library:
bash
cd libopencm3
make TARGETS=stm32/f0
cd ..
Use code with caution.

Compile the application:
bash
cd App
make
Use code with caution.

Flash the board:
bash
make flash
