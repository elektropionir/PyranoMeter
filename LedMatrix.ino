// ** The 4 segment LedMatrix display **

// https://github.com/avishorp/TM1637

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
TM1637Display matrix(LEDMATRIX_CLOCK_PIN, LEDMATRIX_DATA_PIN);

void matrixSetup() {
matrix.setBrightness(5); // range: 0-7; display.setBrightness(7, false);  // Turn off
}

void matrixLoop() {

  int displayValue = insolPower; // display inverter AC Power
  
matrix.showNumberDec(displayValue, true); //
}
