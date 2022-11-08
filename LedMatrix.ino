// ** The 4 segment LedMatrix display **

// https://github.com/avishorp/TM1637

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 14
#define DIO 13

TM1637Display matrix(CLK, DIO);

void matrixSetup() {
matrix.setBrightness(5);
}

void matrixLoop() {

  int displayValue = insolPower; // display inverter AC Power
  
matrix.showNumberDec(displayValue, true); //
}
