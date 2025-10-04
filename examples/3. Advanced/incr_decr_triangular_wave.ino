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

int wave_amplitude = 30;

void setup() {
  Serial.begin(57600);
  Serial.print("\n\nLibrary version: ");
  Serial.println(DIGIPOTX9C_LIB_VERSION);
  Serial.println();
  
  // Initialize the digital potentiometer with pin connections
  pot.init(udpin, incpin, cspin);
  
  // The init function will automatically reset the POT
  
  delay(20);  // optional delay

  pot.incr(); // A minimum increment is done beforehand to understand the rise and fall
  
}

void loop() {

    Serial.printf("Attempting to increase resistance by %d ohms", wave_amplitude*pow(10, (pot.type-101)));

    for(int i = 0; i<wave_amplitude; i++) {

      pot.incr();

      Serial.print("\nApprox resistance after increment: ");
      Serial.printf("%d ohms\n", pot.getApproxResistance());
      delay(100);
    }

    Serial.printf("Attempting to decrease resistance by %.f ohms", wave_amplitude*pow(10, (pot.type-101)));
    delay(25);

    for(int j = 0; j<wave_amplitude; j++) {

      pot.decr();

      Serial.print("\nApprox resistance after decrement: ");
      Serial.printf("%d ohms\n", pot.getApproxResistance());
      delay(100);
    }

    delay(2000);

}
