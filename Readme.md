# STM32F0 Bare Metal Blinky (libopencm3)

A lightweight, bare-metal LED blinky project for the **NUCLEO-F072RB** (STM32F072RB). This project bypasses heavy IDEs like STM32CubeIDE in favor of a manual **Makefile** build system and the **libopencm3** firmware library.

Developing in this "No-IDE" environment provides a deep understanding of linker scripts, memory mapping, and the ARM GCC compilation pipeline.

---

## 🛠 Hardware & Environment

### Hardware

- **MCU:** STM32F072RBT6 (ARM Cortex-M0)
- **Board:** NUCLEO-F072RB
- **Debugger:** On-board ST-LINK/V2-1

### Software Stack

This project uses a "Linux-on-Windows" workflow to utilize professional CLI tools:

- **OS:** Windows 11 with **WSL2 (Ubuntu)**
- **Compiler:** `arm-none-eabi-gcc` (GNU Arm Embedded Toolchain)
- **Build System:** GNU Make
- **Flashing Tool:** OpenOCD
- **Hardware Bridge:** `usbipd-win` (Connects Windows USB ports to the WSL2 kernel)

---

## 🔌 Connecting Hardware to WSL2 (Required for Flashing)

WSL2 does not see USB devices by default. You must bridge your ST-LINK debugger from Windows to Ubuntu using `usbipd-win`.

### 1. In Windows PowerShell (Administrator)

Run these commands to share the device with WSL:

```powershell
# 1. List connected devices to find the Bus ID of the ST-LINK (e.g., 2-3)
usbipd list

# 2. Bind the device (Only required once per USB port)
usbipd bind --busid <BUSID>

# 3. Attach the device to WSL (Required every time you plug the board in)
usbipd attach --wsl --busid <BUSID>
```

### 2. In WSL2 (Ubuntu Terminal)

lsusb

# You should see: Bus XXX Device XXX: ID 0483:374b STMicroelectronics ST-LINK/V2.1

## Prerequisites

Within your WSL/Ubuntu terminal, install the necessary tools:

```bash
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi make openocd
```

## Key Features

- **Manual Vector Table:** Custom Reset_Handler and ISR## Key Features vector definition in C(Previously).
- **Defined Vector Table:** Vector table is already defined in libopencm3 using C(Current).
- **Custom Linker Script:** Uses a memory-mapped linker script for precise flash/RAM control.
- **Makefile Workflow:** Full control over compilation, linking, and flashing via OpenOCD.
- **Library:** Powered by the open-source `libopencm3`.

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

# 🧪 Learning Log

## 📅 Day 1 – Bare-Metal Bring-Up

### What was implemented and learned:

- Built and flashed a bare-metal application without STM32CubeIDE

- Understood:

  - Linker script memory layout

  - Startup flow: Reset → Vector Table → main()

- Verified GPIO output by blinking the onboard LED using a busy-wait delay

- Set up:

  - OpenOCD flashing

  - ST-LINK access via WSL2

# Outcome:

Confirmed that the toolchain, linker script, and startup code were correct.

## 📅 Day 2 – SysTick, Vector Table, and Real Debugging

**Focus:** Timekeeping, interrupts, and low-level debugging using VS Code + GDB.

# What was implemented

- SysTick timer configuration (1 kHz)

- Tick counter implementation (initially uint64_t)

- Custom sys_tick_handler() ISR

- Explicit vector table placement at 0x08000000

- Manual SysTick register setup to avoid unsafe helpers

# Bugs encountered and fixed

- Vector table misplacement

  - Reset handler not executing

  - Fixed by forcing .vectors to ORIGIN(FLASH)

- HardFault entering blocking_handler()

  - Caused by incorrect SysTick helper usage on Cortex-M0

  - Fixed by configuring SysTick registers manually

- 64-bit tick counter issues

  - Learned that uint64_t is unsafe on Cortex-M0 without atomic protection

  - Migrated to uint32_t ticks

- Debugger misconceptions

  - Learned that halting the CPU stops time

  - Timing logic must be validated outside breakpoints

# Debugging skills gained

- Attaching GDB to OpenOCD

- Inspecting memory and registers:

  - Vector table at 0x08000000

  - SysTick registers (CTRL, LOAD, VAL)

- Identifying HardFaults via blocking_handler

- Understanding weak symbols and ISR overrides in libopencm3

- Debugging without IDE automation

# Outcome:

A stable SysTick-based LED blink and a deeper understanding of Cortex-M0 startup, interrupts, and debugging.
