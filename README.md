<div align="center">

# 🖥️ C Programming & Embedded Systems
### Portfolio of Embedded Projects — Microcontroller Programming, Hardware Interfacing & System Design

![C](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![AVR](https://img.shields.io/badge/MCU-AVR%20%2F%20ATmega-green?style=flat-square)
![Proteus](https://img.shields.io/badge/Simulation-Proteus-purple?style=flat-square)
![Makefile](https://img.shields.io/badge/Build-Makefile-lightgrey?style=flat-square)

*Hands-on embedded systems projects covering real-world applications — from distance sensing to home automation — built in bare-metal C and simulated in Proteus.*

[View on GitHub](https://github.com/AbdullahMohamed221/c-programming-and-embedded-systems-) · [LinkedIn](https://www.linkedin.com/in/abdullah-mohamed-61801931b/)

</div>

---

## 📌 About This Repository

This portfolio documents projects built during my studies in **C programming and embedded systems**. Each project targets a real-world problem and is implemented using **bare-metal C** on an AVR microcontroller, with hardware simulated and validated in **Proteus Design Suite**.

These projects reflect my ability to:
- Write low-level C code that interfaces directly with hardware registers
- Design control logic for sensors, actuators, and output peripherals
- Structure embedded software into modular, maintainable codebases
- Simulate and validate complete embedded systems before hardware deployment

---

## 🚀 Projects

---

### 🎓 Final Project *(Capstone)*
> **Full embedded application integrating multiple subsystems**

The capstone project that brings together all concepts developed throughout the course — sensor interfacing, peripheral drivers, communication protocols, and control logic — into a single, well-structured embedded application.

**Highlights:**
- Multi-peripheral integration (sensors + actuators + display)
- End-to-end system design from input sensing to output control
- Modular codebase with clean separation of drivers and application logic
- Fully simulated and validated in Proteus

`C` `AVR` `Proteus` `GPIO` `Modular Design`

---

### 🚗 Car Parking Sensor
> **Ultrasonic proximity detection with real-time alert feedback**

An embedded parking assistant system that continuously measures the distance between a vehicle and an obstacle using an **HC-SR04 ultrasonic sensor**. As the vehicle gets closer, the buzzer alert frequency increases, providing an intuitive proximity warning — similar to real parking sensors found in modern cars.

**Highlights:**
- HC-SR04 ultrasonic sensor interfacing via GPIO timing pulses
- Distance-to-alert mapping with configurable threshold zones
- PWM-driven buzzer that speeds up as distance decreases
- LED indicators for multi-zone visual feedback

`C` `HC-SR04` `Ultrasonic` `PWM` `GPIO` `Proteus`

---

### 🏠 Smart Home System
> **Sensor-driven appliance automation on a microcontroller**

An embedded smart home controller that monitors environmental sensor inputs and automatically controls household appliances (fans, lights, etc.) based on predefined conditions. The system demonstrates event-driven design and finite state machine logic in a resource-constrained embedded environment.

**Highlights:**
- Interrupt-driven sensor handling for responsive control
- State machine logic for appliance control sequences
- Digital I/O control of relays / output peripherals
- Clean separation of sensing, decision, and actuation layers

`C` `AVR` `Interrupts` `Digital I/O` `State Machine` `Proteus`

---

### 🔌 Interfacing Project
> **Peripheral driver development and communication protocol implementation**

A focused project on interfacing common embedded peripherals with a microcontroller using standard communication protocols. Custom drivers are written from scratch in bare-metal C — no HAL abstraction layers — giving full control over peripheral behavior and timing.

**Peripherals and protocols covered:**
- **LCD Display** — character display via 4-bit parallel interface
- **Keypad** — matrix scanning for user input
- **UART** — serial communication for data transmission
- **I²C / SPI** — bus communication with external devices

`C` `UART` `I²C` `SPI` `LCD` `Keypad` `Bare-metal Drivers`

---

### 💻 C Programming Project
> **Low-level C fundamentals applied in an embedded context**

A set of structured C programming exercises designed to build the foundational skills required for professional embedded development — with a focus on writing efficient, hardware-aware code within the constraints of a microcontroller environment.

**Topics covered:**
- Pointer arithmetic and memory management
- Bitwise operations for register-level hardware control
- Modular code organization with `.h` / `.c` file separation
- Algorithm design under memory and speed constraints

`C` `Pointers` `Bitwise Operations` `Memory Management` `Makefile`

---

## 🛠️ Tech Stack

| Category | Details |
|---|---|
| **Language** | C (Bare-metal / Embedded) |
| **Target MCU** | AVR / ATmega series |
| **Simulation Tool** | Proteus Design Suite |
| **Build System** | AVR-GCC + Makefile |
| **Communication Protocols** | UART, I²C, SPI, GPIO |
| **IDE** | Atmel Studio / VS Code + AVR toolchain |

---

## ⚙️ Getting Started

```bash
# 1. Clone the repository
git clone https://github.com/AbdullahMohamed221/c-programming-and-embedded-systems-.git

# 2. Navigate to a project folder
cd "car parking sensor"

# 3. Compile with AVR-GCC
make all

# 4. Open the .pdsprj file in Proteus
#    Load the compiled .hex onto the MCU component and run the simulation
```

> **Requirements:** AVR-GCC toolchain, GNU Make, Proteus Design Suite

---

## 👤 Author

**Abdullah Mohamed**
Embedded Systems & Industrial Automation Engineer

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Abdullah%20Mohamed-blue?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/abdullah-mohamed-61801931b/)

---

<div align="center">
<sub>Built with bare-metal C · Simulated in Proteus · Validated by doing</sub>
</div>
