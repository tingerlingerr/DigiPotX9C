#pragma once
/*  Library Details:
    FILE - DigiPotX9C.h
    AUTHOR - tingerlinger
    VERSION - 1.0.0
    URL - 
    PURPOSE - Arduino library for X9C10x digital potentiometers (102, 103, 105)
    ORIGINAL DEVICE DATASHEET - https://www.renesas.com/en/document/dst/x9c102-x9c103-x9c104-x9c503-datasheet?r=502671
*/

#ifndef DIGIPOTX9C_H
#define DIGIPOTX9C_H

#define SENSOR_LIB_H

#include "Arduino.h"
#include <EEPROM.h>

/* Relevant notes from datasheet: 
1. 99 wiper positions
2. 1 MI (Minimum Increment) = R_tot / 99
3. Wiper has 40ohm line resistance (typical)
4. Non-volatile recall happens automatically on power
5. For storing wiperPos, requires 20ms minimum
6. MINIMUM Timing requirements:
   - t_CS: CS to INC setup time = 1μs
   - t_IH: INC high time = 1μs
   - t_IL: INC low time = 1μs
   - t_DI: U/D to INC setup time = 3μs
   - t_CPH_S: CS high time for store = 20ms
   - t_CPH_NS: CS high time for recall = 100ns
*/

// Device type constants
#define X9C102_TYPE    102
#define X9C103_TYPE    103
#define X9C104_TYPE    104

// Nominal resistance values
#define X9C102_RESISTANCE    1000    // 1 kΩ
#define X9C103_RESISTANCE    10000   // 10 kΩ
#define X9C104_RESISTANCE    100000  // 100 kΩ


#define DIGIPOTX9C_LIB_VERSION     (F("0.0.3"))    // F stores library version in flash memory (PROGMEM) instead of RAM

class X9C_BASE {
    public:
        uint8_t wiperPos;
        uint32_t maxResistance; // user measured total resistance
        float resistanceStep;
        float wiperResistance = 40.0;

        
        void init(uint8_t udPin, uint8_t incPin, uint8_t csPin);    // udPin and incPin can be same for multiple POTs, csPin needs to be unique - however then, only one POT can be controlled at a time
        void resetAtStart(bool reset);
        void incr(uint8_t step = 1);    // default increment is 1
        void decr(uint8_t step = 1);    // default decrement is 1
        uint8_t getPosition();         // Get current wiper position
        void setPosition(uint8_t pos_cmd); // Set position directly (0-99)
        float getApproxResistance();  // gets current resistance in ohms
        void setResistance(float R_set);    // accepts in ohms
        
        
        // Utility functions
        uint8_t resistanceToPosition(float resistance);
        float positionToResistance(uint8_t position);
    
    protected:
        X9C_BASE(uint32_t measuredOhm, uint8_t type = 0) {
            maxResistance = measuredOhm - wiperResistance;
            wiperPos = 0;
            resistanceStep = maxResistance / 99.0;
            _type = type;
        }

    private:
        const uint8_t POT_ADDR = 0x10;   // EEPROM address

        uint8_t _ud;   // u/d GPIO pin no.
        uint8_t _cmd;  // inc GPIO pin no., command to increment / decrement
        uint8_t _cs;   // cs GPIO pin no.
        bool _resetAtStart = true; // default is reset at start
        uint8_t _type; // 102, 103, 104
        
        // Timing constants (in microseconds)
        const uint8_t _T_IC = 1;    // CS to INC setup time
        const uint8_t _T_IH = 1;    // INC high time
        const uint8_t _T_IL = 1;    // INC low time
        const uint8_t _T_DI = 3;    // U/D to INC setup time
        const uint16_t _T_CPH_S = 20000; // CS high time for store
        const uint16_t _T_CPH_NS = 100; // CS high time for no-store, return to standby 
        
        bool _initialise(uint8_t udPin, uint8_t incPin, uint8_t csPin); 
        bool _validatePins(uint8_t udPin, uint8_t incPin, uint8_t csPin);
        void _store();   // store to EEPROM
        void _move(uint8_t steps, bool _up_down_flag);
        void _firstReset();
        
        
}; // Base class for X9C10x digital potentiometers

// Device-specific classes
class X9C102 : public X9C_BASE {
    public:
        X9C102(uint32_t measuredOhm = 1000, uint8_t type = X9C102_TYPE) : X9C_BASE(measuredOhm, type) {}  // 1 kΩ nominal
};
    
class X9C103 : public X9C_BASE {
    public:
        X9C103(uint32_t measuredOhm = 10000, uint8_t type = X9C103_TYPE) : X9C_BASE(measuredOhm, type) {} // 10 kΩ nominal
};
    
class X9C104 : public X9C_BASE {
    public:
        X9C104(uint32_t measuredOhm = 100000, uint8_t type = X9C104_TYPE) : X9C_BASE(measuredOhm, type) {} // 100 kΩ nominal
};
    
    
#endif