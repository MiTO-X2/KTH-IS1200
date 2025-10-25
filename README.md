# KTH-IS1200 – Computer Hardware Engineering

This repository contains lab assignments and a final project for the **IS1200 Computer Hardware Engineering** course at **KTH Royal Institute of Technology**.  
The course introduces students to **low-level programming**, **computer architecture**, and **embedded systems development** through a series of hands-on labs using **MIPS assembly**, **C programming**, and **Logisim circuits**.

---

## 🧠 Course Overview

The goal of this course is to develop a fundamental understanding of how computers work at the hardware level, from digital circuits to low-level machine code execution.  
Throughout the labs, students learn to:

- Program in **MIPS assembly** and **C** for embedded environments.
- Understand **CPU architecture**, **ALU operations**, **instruction cycles**, and **memory management**.
- Interface with **hardware components** such as timers, I/O ports, and displays.
- Simulate and test **processors and logic circuits** using **Logisim**.
- Integrate assembly and C programs into functioning embedded systems.

Each lab builds upon the previous one, increasing in complexity and depth.

---


Each folder contains:
- Source code in **Assembly (.asm)** or **C (.c)**
- **Makefiles** for compiling on MIPS
- Precompiled outputs (`.elf`, `.hex`)
- Supporting files (`vectors.S`, `mipslab*.c/h`, etc.)
- In some labs, **Logisim circuit files (.circ)** for processor simulation.

---

## 🧩 Labs Breakdown

### 🔹 LAB 1 – Introduction to MIPS Assembly
**Folder:** `LAB1/`

This lab introduces MIPS assembly language programming, focusing on:
- Basic instruction execution
- Registers and the program counter
- Arithmetic and control flow
- Delay loops and timing functions
- Working with templates like `timetemplate.asm` and `hexmain.asm`

The folder also includes the **time4mips** subproject with a working setup for compiling, linking, and running MIPS programs on the lab simulator.

---

### 🔹 LAB 2 – C Programming and Pointers
**Folder:** `LAB2/`

This lab transitions from assembly to **C programming**, emphasizing:
- The relationship between C and assembly
- Memory management and pointer arithmetic
- Prime number generation (`prime.c`, `print-primes.c`)
- Implementing sieve algorithms (`sieves.c`, `sieves-heap.c`)
- Cross-compiling and testing on MIPS architecture

It includes a `uno32tests` subfolder with build files and helper code for the Uno32 platform.

---

### 🔹 LAB 3 – Interrupts, Timers, and I/O
**Folder:** `LAB3/`

This lab dives deeper into embedded systems, focusing on:
- Timer setup and interrupt handling
- Real-time system design
- Hardware I/O management
- Using multiple configurations such as `time4int`, `time4io`, and `time4timer`

Each subfolder is a variation of the same system built with different timing and interrupt mechanisms.

---

### 🔹 LAB 4 – Processor Design in Logisim
**Folder:** `LAB4/`

Students design and simulate a simple processor using **Logisim**, a digital circuit simulator.  
Key learning outcomes:
- CPU datapath and control logic
- Assembly execution pipeline
- Arithmetic Logic Unit (ALU) design
- Handling branching, factorial, and arithmetic operations

Notable files:
- `processor.circ` – the main CPU circuit
- `factorial.asm`, `test.asm` – test programs
- `mips*.txt` – assembly instruction traces
- License and configuration files for Atash/Logisim

---

### 🕹️ Final Project – PONG Game
**Folder:** `ProjectPONG/`

The final project integrates all previous knowledge to build a **fully functional Pong game** on an embedded MIPS simulator.

#### Key Components:
- `game.c`, `display.c`, `timer.c` – handle logic, rendering, and timing
- `labwork.S`, `mipslab*.c/h` – low-level system and hardware interfaces
- `Makefile` – builds the project into `.elf` and `.hex` outputs
- `include/numbers.h` – contains display number mappings

#### Learning Outcomes:
- Real-time event handling with interrupts
- Game loop design and rendering logic
- Display and timer synchronization
- Integration of C and Assembly code

---

## 🧰 Tools and Technologies

- **MIPS Assembly** and **C**
- **Logisim** (for circuit simulation)
- **Uno32 / PIC32 emulator**
- **Makefiles** and **GCC cross-compilation**
- **ELF/HEX binaries** for hardware simulation
