// ** The insolation value read from a 1W "reference" PV panel and translated to available PV power **

// https://solarduino.com/wp-content/uploads/2020/01/2020-1-9_Irradiance_Meter_with_LCD_Display.ino

// Voltaic Systems 1W 6V Solar Panel (0.21A Isc shortcut current), shorted with a 15Ω 5W resister, and connected to ADC
// efficiency 19,5 %, power 1,12W
// size 95 * 70 cm = 0,00665 m2
// 150,0376 panels in m2


// ADC121 Grove I2C ADC
// Working Voltage 5.0 VDC
// Max ADC input: 3.0 VDC

#define PANEL_LENGTH 95 // Length of active part of solar panel in mm
#define PANEL_WIDTH 70 // Width of active part of solar panel in mm
#define eff_pc 19.5 //percent efficiency of solar panel

#define I2C_ADDR_ADC121             0x50
#define V_REF 3.00

const byte REG_ADDR_RESULT = 0x00;
const byte REG_ADDR_CONFIG = 0x02;

// for voltage conversion
float vRef = 3.290; // the accurate value of your reference

// for referencing meteo data

float IRref = 2.5951; // 1.477  reference  https://www.hidmet.gov.rs/eng/osmotreni/kosutnjak.php

// sampling parameters
// int nSamp = 5;   // Number of Samples to take for each reading
// int interval = 7; //milliseconds interval between successive readings

float res = 15;  //resistance in OHMS
volatile float Area;
volatile float Radiation;
float ADCcorr = 0.9424;

// averaging parameters

float insolMAvg; // value for moving average to flatten out fluctuations
long insolReport; // delay in updating insolPowerAv
unsigned long nSol; // number of samples

void init_adc()
{
  Wire.beginTransmission(I2C_ADDR_ADC121);    // transmit to device
  Wire.write(REG_ADDR_CONFIG);                // configuration Register
  Wire.write(REG_ADDR_RESULT);
  Wire.endTransmission();

  Wire.beginTransmission(I2C_ADDR_ADC121);    // transmit to device
  Wire.write(REG_ADDR_RESULT);                // get result
  Wire.endTransmission();
}
 
unsigned short read_adc()     //unsigned int *data
{
  unsigned long long adc_sum = 0;
  int n = 0;
  unsigned long start_adc_time = millis();
  
//  Wire.beginTransmission(I2C_ADDR_ADC121);    // transmit to device
//  Wire.write(REG_ADDR_RESULT);                // get result
//  Wire.endTransmission();

  while (millis() - start_adc_time < 10) { // measures samples within 10 ms
  
  Wire.requestFrom(I2C_ADDR_ADC121, 2);
  byte buff[2];
  Wire.readBytes(buff, 2);
  long v = (buff[0] << 8) | buff[1];
  adc_sum += v;
  n++;
    }
  return (adc_sum / n) *vRef*5/4096*1000*ADCcorr; // 4096 for 12 bit, scaler 1667 for 3 V_REF, 0,75 correction
}
   
void insolSetup()
{
  init_adc();
}
 
void insolLoop()
{

// Grove ADC reading voltage from reference panel
   Vx = read_adc();

// Power calculations
  Area = PANEL_LENGTH * PANEL_WIDTH; //in mm square
  Px = Vx * Vx / res ; // Calculating power v^2 / R in microWatts
  Px /=1000; // mW
  Radiation = Px / Area; //mW/mm^2
  Radiation *=1000; //W/m^2
  Radiation  *= 100/eff_pc; //correct for panel efficiency
  Radiation *= IRref; // correct for Meteo reference value

  insolPower = Radiation;
  
  onePanel = insolPower*1.74*0.2; // calculate output for 1 350Wp panel

 // floating average
  nSol++; // update sample count
  insolMAvg += (insolPower - insolMAvg) / nSol; // calculate moving average
    
  if (loopStartMillis - insolReport > 60 * 1000) { // 60 secs polling
  insolPowerAvg = insolMAvg; // retreive result after polling time
  if (insolPowerAvg < 0) {
    insolPowerAvg = 0;
  }
  insolReport = loopStartMillis;
  nSol = 0; // to start a new averaging period, set number of samples (n) to zero
  }    
}
