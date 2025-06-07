#include "DigiPotX9C.h"

#define udpin 35
#define incpin 32
#define cspin 33
// use output compatible pins in your MCU

// X9C103 pot; // Using the default 10k resistance
X9C103 pot(9190); // Using user measured resistance

void setup() {
  Serial.begin(57600);
  Serial.print("\n\nLibrary version: ");
  Serial.println(DIGIPOTX9C_PRO_LIB_VERSION);
  Serial.println();
  
  // Initialize the digital potentiometer with pin connections
  pot.init(udpin, incpin, cspin);
  
  // The init function will automatically load the last saved position from EEPROM
  
  delay(20);

  Serial.print("Set position: ");
  pot.setPosition(50);

  // The setPosition function will automatically save the position to in-built EEPROM

  Serial.print("***\nCurrent position: ");
  Serial.println(pot.getPosition());

  Serial.print("Current resistance: ");
  Serial.print(pot.getApproxResistance());
  Serial.println(" ohms");
  
  Serial.print("***\n");
  
}

void loop();
