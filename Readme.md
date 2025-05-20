# X9C Series Digital Potentiometer - Library ![C++](https://img.shields.io/badge/C++-red) ![Arduino](https://img.shields.io/badge/Arduino-teal)
---

## **About**
**Description**</br>
The X9C10C is a digitally controlled potentiometer (digipot) from the X9C series, providing 1 / 10 / 50 / 100 kΩ resistance with 100 tap points (0-99) and ±20% resistance tolerance, that can be adjusted via digital signals. </br>Operated between -5 to 5V logic levels, it features a non-volatile memory with (typical) 1e5 write cycles to store wiper positions. The device uses a 3-wire interface (CS, U/D', INC) for increment/decrement control, with 1µs typical step response time, making it ideal for applications requiring programmable resistance like gain adjustment, calibration, or volume control. 

This repository aims to accurately replicate timing characteristics and resistance taper behaviour of this series of digital potentiometers.

**Pinout diagram**</br>
https://github.com/tingerlingerr/DigiPotX9C/blob/main/wiring/circuit.png

**Advantages**
- Dirt cheap (like most chinese products), and fairly reliable. 
- Unlike mechanical potentiometers, no physical wear; offers repeatable digital control
- Retains last wiper position after power loss (for up to 100 years).
- Compact size; max 16mW (10mW for X9C102) power consumption.
- Suitable for applications requiring auto-calibration of resistive-based sensing / actuating devices, removing undesired manual intervention.

**Disadvantages**
- ±20% high tolerance a detrimental factor in critical systems; can be mitigated via software to some extent.
- Limited to ~3mA current; ±1 LSB wiper position uncertainty. 
- Some have complained that full rresistance often reached in 30–50 steps, not 100.

**Limitations**
- Always 100 steps resolution, irrespective of module; 100kΩ module resolution only 1kΩ, not be very precise.
- Datasheet mentions ONLY minimum timing specs - what if real dalay is more? How much more? We may never know!!

**Reason for building library**
--
- Verifies pin connection for ESP32 (very imp).
- Considers the fact a user may want to increase wiper position by more than 1 position a time.
- Minimally written library balancing speed of operation, and reliability & ease of use.</br>
:grey_exclamation:_FUTURE WORK_ : This library will also house an easy-to-use bluetooth and wifi connectivity option. For wifi, it will also be connected to ROS1 and ROS2.
---

## :clipboard: **Folder Structure**

```
DigiPotX9C/
├── docs/
├── examples/
├── src/
├── wiring/
├ Changelog
├ LICENSE
├ Readme
├ datasheet
├ keywords
└ library.properties
```
---
## 🧞 **Features**

To be updated
---
## Credit

1. Renesas  X9C102, X9C103, X9C104, X9C503 Digitally Controlled Potentiometer (XDCP™) Datasheet
(https://www.renesas.com/en/document/dst/x9c102-x9c103-x9c104-x9c503-datasheet?r=502676)

2. Inspirations:
    - https://github.com/RobTillaart/X9C10X
    - https://github.com/GitMoDu/FastX9CXXX
---