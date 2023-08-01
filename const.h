// ** These are the constants **

#ifndef H_CONSTS_H
#define H_CONSTS_H

const char version[] = "build "  __DATE__ " " __TIME__;

// pinout for ARDUINO_SAMD_MKRZERO with MKR Connector Carrier > pin 4, 5, 8, 9, 10 are RESERVED
const byte NET_SS_PIN = 5;  // reserved for CS
// SPI 8, 9, 10 not on Carrier
// TWI 12, 11 used for I2C communication with Oled and ADC https://wiki.seeedstudio.com/Grove-I2C_ADC/
const byte BUTTON_PIN = A2; // Pushbutton initiating count reset
const byte SD_SS_PIN = SDCARD_SS_PIN; // internal pin of MKR ZERO

const byte LEDMATRIX_DATA_PIN = 13; // connector labeled Serial (it is Serial1 RX)
const byte LEDMATRIX_CLOCK_PIN = LEDMATRIX_DATA_PIN + 1; //on one Grove connector (it is Serial1 TX)

#endif