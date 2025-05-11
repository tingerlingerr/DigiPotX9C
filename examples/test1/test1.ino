#include "DigiPotX9C_Pro.h"

#define udpin 35
#define incpin 32
#define cspin 33

X9C103 pot; // Using the default 10k resistance

void setup() {
  Serial.begin(57600);
  Serial.println(F("Digital Potentiometer X9C10x Example"));
  
  // Initialize the digital potentiometer with pin connections
  pot.init(udpin, incpin, cspin);
  
  // The init function will automatically load the last saved position from EEPROM
  
  Serial.print(F("Current wiper position: "));
  Serial.println(pot.getPosition());
  
  Serial.print(F("Current resistance: "));
  Serial.print(pot.getResistance());
  Serial.println(F(" ohms"));
}

void loop();
