#include "DigiPotX9C.h"

bool X9C_BASE::_validatePins(uint8_t udPin, uint8_t incPin, uint8_t csPin) {
    #ifdef ESP32
        if (!GPIO_IS_VALID_OUTPUT_GPIO(udPin)) {
            Serial.println("Invalid U/D pin! Use output-capable GPIO");
            return false;
        }
        if (!GPIO_IS_VALID_OUTPUT_GPIO(incPin)) {
            Serial.println("Invalid INC pin! Use output-capable GPIO");
            return false;
        }
        if (!GPIO_IS_VALID_OUTPUT_GPIO(csPin)) {
            Serial.println("Invalid CS pin! Use output-capable GPIO");
            return false;
        }
    #endif
    return true;
}

void X9C_BASE::resetAtStart(bool reset) {
    _resetAtStart = reset;
}

void X9C_BASE::init(uint8_t udPin, uint8_t incPin, uint8_t csPin) {
    
    bool initialised = _initialise(udPin, incPin, csPin);    
    if (!initialised) {
        Serial.println("Failed to initialise digital potentiometer");
        while(1)
            delay(1000);
    }
    else
        Serial.println("Digital potentiometer initialised");
}

bool X9C_BASE::_initialise(uint8_t udPin, uint8_t incPin, uint8_t csPin) {
    
    if (!_validatePins(udPin, incPin, csPin)) return false;
    else {
        _ud = udPin;
        _cmd = incPin;
        _cs = csPin;

        pinMode(_cs, OUTPUT);
        pinMode(_ud, OUTPUT);
        pinMode(_cmd, OUTPUT);

        delay(2);

        digitalWrite(_cs, HIGH);
        digitalWrite(_ud, HIGH);
        digitalWrite(_cmd, HIGH);

        delay(2);
        // do not change the order of initialisation

        if (_resetAtStart)
            _firstReset();
        else {
            wiperPos = EEPROM.read(POT_ADDR);
            wiperPos = constrain(wiperPos, 0, 99);
        }
    }
    return true;
}

uint8_t X9C_BASE::getPosition() {
    return wiperPos; 
}

float X9C_BASE::getApproxResistance() {
    // returns the approximate expected resistance (in ohms) within 5% of the actual resistance
    if (wiperPos <= 0) return 40.0;

    return (resistanceStep * wiperPos) + wiperResistance;
}

void X9C_BASE::incr(uint8_t steps) {
    if (steps <= 0) return; // blank input
    
    if (steps > 99 - wiperPos) {
        steps = 99 - wiperPos;
        if (steps == 0) return; // Already at maximum
    }
    
    _move(steps, true); // true = increment
}
void X9C_BASE::decr(uint8_t steps) {

    if (steps <= 0) return; // blank input
    
    if (steps > wiperPos) {
        steps = wiperPos;
        if (steps == 0) return; // Already at minimum
    }
    
    _move(steps, false); // false = decrement
}

void X9C_BASE::_firstReset() {
    _move(99, false);
    wiperPos = 0;
}

void X9C_BASE::setPosition(uint8_t pos_cmd) {
    // Limit to valid range
    pos_cmd = constrain(pos_cmd, 0, 99);

    // Calculate steps and direction to move
    if (pos_cmd > wiperPos) 
        incr(pos_cmd - wiperPos);

    else if (pos_cmd < wiperPos) 
        decr(wiperPos - pos_cmd);

}


void X9C_BASE::setResistance(float R_set) {

    // Limit to valid range
    if (R_set < 0) R_set = 0;
    if (R_set > maxResistance) R_set = maxResistance;
    
    Serial.println("type:  ");
    Serial.println(_type);
    // Calculate required position
    uint8_t pos = resistanceToPosition(R_set);
     
    if (pos > 99) 
        pos = 99;
    
    // Move to position
    setPosition(pos);
    
    // Store new position in non-volatile memory
    _store();
}

uint8_t X9C_BASE::resistanceToPosition(float resistance) {
    return floor((pow(10, (_type-100))/maxResistance) * ((resistance-wiperResistance) / 10.0));
}

float X9C_BASE::positionToResistance(uint8_t position) {
    if (position <= 0) return 40.0;
    return (maxResistance / 99.0) * position + wiperResistance; 
}

void X9C_BASE::_store() {
    /* 
        INC - HIGH
        CS - LOW TO HIGH (with 20ms delay)
    */
    
    digitalWrite(_cs, LOW);
    digitalWrite(_cmd, HIGH);
    delayMicroseconds(5);
    digitalWrite(_cs, HIGH);
    delayMicroseconds(_T_CPH_S);
    delayMicroseconds(5); // just to be safe

}
void X9C_BASE::_move(uint8_t steps, bool _up_down_flag) {
    if (steps <= 0) return;

    digitalWrite(_ud, _up_down_flag);  // up_down_flag = true, increment; else decrement
    delayMicroseconds(_T_DI+1);  // t_DI

  
    digitalWrite(_cs, LOW);
    while (steps--) {

        digitalWrite(_cmd, HIGH);
        delayMicroseconds(_T_IH+1);   // t_IH
        digitalWrite(_cmd, LOW);
        delayMicroseconds(_T_IL+1);   // t_IL
        
        wiperPos = _up_down_flag ? wiperPos + 1 : wiperPos - 1;
        wiperPos = constrain(wiperPos, 0, 99);
    }
    digitalWrite(_cmd, LOW);
    delayMicroseconds(_T_IL+1);   // t_IC
    digitalWrite(_cs, HIGH);    
    delayMicroseconds(_T_CPH_NS); // t_CPH_NS
    
    digitalWrite(_cmd, HIGH);
    delayMicroseconds(_T_IH+1);   // t_IH
}