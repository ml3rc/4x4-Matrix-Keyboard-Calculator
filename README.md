# 4x4 Matrix Keyboard Calculator

![AVR](https://img.shields.io/badge/Platform-AVR-blue)
![MCU](https://img.shields.io/badge/MCU-ATmega2560-green)
![Language](https://img.shields.io/badge/Language-C-orange)
![Build](https://img.shields.io/badge/Build-Microchip%20Studio-red)
![Status](https://img.shields.io/badge/Status-Stable-success)

A simple calculator firmware for the ATmega2560 using a 4x4 matrix keyboard and LCD display.

The program provides basic calculator functionality:

* Addition, subtraction, multiplication, division
* Floating-point arithmetic
* Chaining calculations (use previous result)
* Real-time display updates
* Clear function

The implementation uses a finite state machine (FSM) to manage the calculator's operation states, keeping the control logic simple, predictable, and easy to extend.

The firmware was developed and tested using a:

* PICado ATmega2560 development board with HD44780 LCD Display (16x2 characters)
* 4x4 Matrix Keyboard

---

# Table of Contents

* [Overview](#overview)
* [Requirements](#requirements)
* [Project Setup](#project-setup)
* [Building and Flashing](#building-and-flashing)
* [System Architecture](#system-architecture)
* [Hardware Setup](#hardware-setup)
* [Calculator Operation](#calculator-operation)
* [Design Decisions](#design-decisions)
* [Testing](#testing)
* [Sources](#sources)

---

# Overview

This project is a minimal implementation of a calculator firmware using matrix keyboard input and LCD display output.

Features include:

* Basic arithmetic operations (+, -, *, /)
* Floating-point calculations with decimal results
* Chaining operations (use previous result as first operand)
* Real-time key display as you type
* Multi-digit number input
* Clear function
* Error handling for division by zero
* Deterministic control using an FSM

The project focuses on clarity and maintainability, making it suitable for educational use or small embedded projects.

---

# Requirements

## Development Tools

* Microchip Studio

  * AVR toolchain
  * XC8 compiler support

### Documentation Tools (Optional)

For editing diagrams:

* VS Code
* Draw.io plugin
* C and C++ plugin

## Hardware

* PICado ATmega2560 development board with HD44780 LCD Display (16x2 characters)
* 4x4 Matrix Keyboard

---

# Project Setup

Before building the project, a small configuration step is required.

## 1. Install AVRdude

Download the AVRdude tool from:

[https://github.com/ml3rc/4x4-Matrix-Keyboard-Calculator/tree/main/readme/AVRdude](https://github.com/ml3rc/4x4-Matrix-Keyboard-Calculator/tree/main/readme/AVRdude)

Place it in:

```
C:\Program Files (x86)\Atmel\Studio\7.0\tools\
```

Adjust the folder if your Microchip Studio version differs.

---

## 2. Configure the Programming Tool

Open the project properties in Microchip Studio:

```
Project → matrix_keyboard Properties
```

Navigate to:

```
Tool → Custom programming tool → Command
```

Update the following things in the command:

* Repository path
* COM port of the development board

---

# Building and Flashing

Once the setup is complete, the firmware can be built and flashed directly from Microchip Studio.

Use:

```
Start Without Debugging (Green start sign with a hole in the middle)
```

This will:

1. Compile the firmware
2. Upload it to the ATmega2560
3. Start execution immediately

---

# System Architecture

The calculator logic is implemented using a finite state machine (FSM).

Advantages of this approach:

* Clear calculator behavior
* Predictable input handling
* Easy to extend with new operations

The FSM manages four main states: CLEAR, OPERAND_1, OPERAND_2, and OPERATOR. The OPERATOR state enables chaining calculations by using the previous result as the first operand for the next operation.

## State Event Diagram

![State Event Diagram](./readme/State-Event.svg)

---

# Hardware Setup

The firmware was tested using the following hardware:

* PICado ATmega2560 development board with HD44780 LCD Display (16x2 characters)
* 4x4 Matrix Keyboard

## Hardware Connection Diagram

![Hardware Connection](./readme/HW-Connection.svg)

The development board provides 5 V supply voltage for both the keyboard and LCD display.

---

# Calculator Operation

The calculator supports basic arithmetic operations with a 4x4 matrix keyboard input.

## Keyboard Layout

```
1  2  3  +
4  5  6  -
7  8  9  *
C  0  =  /
```

## Operating Parameters

| Parameter         | Value         |
| ----------------- | ------------- |
| Display size      | 16x2 characters |
| Number type       | Floating-point |
| Operations        | +, -, *, /     |
| Input method      | Matrix keyboard |
| Chaining          | Supported      |

---

## Usage Instructions

1. **Number Input**: Press digit keys (0-9) to enter numbers    
    - each digit appears immediately on screen
2. **Operations**: Press operator keys (+, -, *, /) after first number
3. **Equals**: Press '=' to calculate the result
4. **Chaining**: After calculation, you can immediately enter another operator to use the result as the first operand
5. **Clear**: Press 'C' to reset the calculator

---

# Design Decisions

Some design choices differ from the task given, why that is like this is described below.

## Finite State Machine

An FSM was chosen because it provides:

* clear separation of calculator states
* predictable input handling
* simple expansion for future features

The four states (CLEAR, OPERAND_1, OPERAND_2, OPERATOR) provide clean separation between different phases of calculator operation, with the OPERATOR state enabling calculation chaining.

---

## Floating-Point Arithmetic

Floating-point calculations were implemented to provide:

* Decimal results for division operations
* Better precision for mathematical operations
* More complete calculator functionality

---

## Real-Time Display

Each key press is displayed immediately because:

* Provides immediate user feedback
* Shows the complete calculation expression
* Makes the calculator feel more responsive

---

## Calculation Chaining

The ability to chain calculations (using previous result) provides:

* More efficient multi-step calculations
* Familiar calculator behavior
* Reduced need to re-enter numbers

---

## Polling Keyboard

The design choice, that no interrupts were used, was because of simplicity of the project

---

# Testing

All functionality was tested on the hardware setup described above.

| Step |         Action        |              Expected Result             |                 Result                | Pass/Fail |
| :--: | :-------------------: | :--------------------------------------: | :-----------------------------------: | :-------: |
|   0  |        Power on       |         Display shows ready state        |        Display shows ready state       |    Pass   |
|   1  |   Press '5', '+', '3' |         Display shows '5+3'              |        Display shows '5+3'            |    Pass   |
|   2  |      Press '='        |         Display shows '8.000000'         |       Display shows '8.000000'        |    Pass   |
|   3  |       Press '*'       |         Display shows '8.000000*'        |      Display shows '8.000000*'        |    Pass   |
|   4  |   Press '2', '='      |        Display shows '16.000000'         |       Display shows '16.000000'       |    Pass   |
|   5  |       Press 'C'       |           Calculator resets              |          Calculator resets            |    Pass   |

---

# Sources

All images used in this document are referenced via their original URLs inside the README.

## Submodules

* [HD44780 LCD Driver](https://github.com/ml3rc/HD44780-Driver-AT2560.git)
* [4x4 Matrix Keyboard Driver](https://github.com/ml3rc/4x4-Matrix-Keyboard-Driver.git)
