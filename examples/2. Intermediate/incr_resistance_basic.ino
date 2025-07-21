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

  Serial.printf("Initial resistance: %.f ohms\n", pot.getApproxResistance());
  
  Serial.printf("Attempting to increase resistance by %.f ohms", pow(10, (pot.type-101)));
  Serial.println("\nNote that the resistance will not increase above maximum");
  pot.incr();

  Serial.print("\nApprox resistance after increment: ");
  Serial.printf("%.f ohms\n", pot.getApproxResistance());
  Serial.printf("Wiper position: %d", pot.getPosition());
  Serial.println();
  
}

void loop() {}
