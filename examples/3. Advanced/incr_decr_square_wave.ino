#include "DigiPotX9C.h"

#define udpin 35
#define incpin 32
#define cspin 33
// use output compatible pins in your MCU

// X9C103 pot; // Using the default 10k resistance
X9C103 pot(9190); // Using user measured resistance

int wave_amplitude = 25;

void setup() {
  Serial.begin(57600);
  Serial.print("\n\nLibrary version: ");
  Serial.println(DIGIPOTX9C_PRO_LIB_VERSION);
  Serial.println();
  
  // Initialize the digital potentiometer with pin connections
  pot.init(udpin, incpin, cspin);
  
  // The init function will automatically load the last saved position from EEPROM
  
  delay(20);  // optional delay

  pot.incr(); // A minimum increment is done beforehand to understand the rise and fall
  
}

void loop() {

    Serial.printf("Attempting to increase resistance by %d ohms", wave_amplitude*pow(10, (pot.type-100)));
    pot.incr(wave_amplitude);

    Serial.print("\nApprox resistance after increment: ");
    Serial.printf("%d ohms\n", pot.getApproxResistance());

    delay(2000);

    Serial.printf("Attempting to decrease resistance by %d ohms", wave_amplitude*pow(10, (pot.type-100)));
    pot.decr(wave_amplitude);

    Serial.print("\nApprox resistance after decrement: ");
    Serial.printf("%d ohms\n", pot.getApproxResistance());
    
    Serial.println();
    delay(2000);

}
