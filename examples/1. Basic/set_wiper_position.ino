/*
  Remeber to ground the VW. Most ckt diagrams online are incorrect.
  
    VH
    VW------------
            |    |
            RΩ   |
            |    |
    VL-------  __|__  
                ---   GND
                  -
*/

#include "DigiPotX9C.h"

#define udpin 32
#define incpin 33
#define cspin 25
// use output compatible pins in your MCU

// X9C103 pot; // Using the default 10k resistance
X9C103 pot(9190); // Using user measured resistance

void setup() {
  Serial.begin(57600);
  Serial.print("\n\nLibrary version: ");
  Serial.println(DIGIPOTX9C_LIB_VERSION);
  Serial.println();
  
  // Initialize the digital potentiometer with pin connections
  pot.init(udpin, incpin, cspin);
  
  // The init function will automatically reset the POT
  
  delay(20);  // optional delay

  Serial.print("Set position: ");
  pot.setPosition(50);

  Serial.print("***\nCurrent position: ");
  Serial.println(pot.getPosition());

  Serial.print("Current resistance: ");
  Serial.print(pot.getApproxResistance());
  Serial.println(" ohms");
  
  Serial.print("***\n");
  
}

void loop() {}
