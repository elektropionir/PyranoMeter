// Arduino IDE: 1.8.16 && SAMD Boards Package 1.8.13 - https://github.com/arduino/ArduinoCore-samd/releases
// important: lcdgfx Version: 1.1.1
// if bricked press reset button twice fast

/******************************************************************************
                               --- EP PyranoMeter ---
 DIY Arduino insolation meter.

******************************************************************************/

#include <MemoryFree.h> // https://github.com/mpflaga/Arduino-MemoryFree
#include <Wire.h>

unsigned long loopStartMillis;

long displayReport = 0; // delay in updating display

// InSol values (PV panel insolation)
int Vx; // raw ADC measurement of Ishortcut from panel in mV
int Px; // raw power measurement from panel in mW
int insolPower; // available measured PV power calculation
int insolPowerAvg; // averaged insolPower

// 1 panel output
int onePanel; // output 1 panel 1,74m2 / 20% eff (350Wp)

// LiPo level
int lipoLevel; // %
int lipoLevelAvg; // % averaged

/******************************************************************************
*                                 --- SETUP ---                               *
******************************************************************************/

void setup() {
  
    Wire.begin();
    Wire.setClock(400000); // 400000

    insolSetup();
    displaySetup();
    matrixSetup();

// setup serial communication
    Serial.begin(115200);  // TX can be used if Serial is not used

//  set DAC resulution to full 1024
    analogWriteResolution(10); // default is 8 bits (0-256)

    
}

/******************************************************************************
*                                 --- LOOP ---                                *
******************************************************************************/


void loop() {
  
    loopStartMillis = millis();

// display control    
    if (loopStartMillis - displayReport > 2000) { // display update timer 2 sec
    displayReport = loopStartMillis;
    displayLoop();
    matrixLoop();
    }

    insolLoop();
    lipoLoop();


}
