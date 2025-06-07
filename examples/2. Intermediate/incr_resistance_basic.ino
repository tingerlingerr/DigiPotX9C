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
  
  delay(20);  // optional delay

  Serial.printf("Initial resistance: %d ohms\n", pot.getApproxResistance());
  
  Serial.printf("Attempting to increase resistance by %d ohms", pow(10, (pot.type-100)));
  Serial.println("Note that the resistance will not increase above maximum");
  pot.incr();

  Serial.print("\nApprox resistance after increment: ");
  Serial.printf("%d ohms\n", pot.getApproxResistance());
  Serial.printf("Wiper position: %d", pot.getPosition());
  Serial.println();
  
}

void loop();
