// ** The insolation value read from a 1W "reference" PV panel and translated to available PV power **

// see also: https://solarduino.com/wp-content/uploads/2020/01/2020-1-9_Irradiance_Meter_with_LCD_Display.ino
// see also: https://solarduino.com/wp-content/uploads/2020/01/2020-1-9_Irradiance_Meter_with_LCD_and_Datalogger_Shield.ino

// Voltaic Systems 6V 1,12W Solar Panel (0.20A expected Isc shortcut current), shorted with a 15Ω 5W resister, and connected to ADC

float Isc = 0.20; // shortcut current in Ampere
float Rsc = 15;  // shortcut resistance in Ohm –> at 0,21A max 3 volt on ADC input

// ADC121 Grove I2C ADC
// Working Voltage 5.0 VDC
// Max ADC input: 3.0 VDC

#define I2C_ADDR_ADC121      0x50
#define V_REF 3.111 // measured between VA and GND on ADC121

const byte REG_ADDR_RESULT = 0x00;
const byte REG_ADDR_CONFIG = 0x02;

float ADCcorr = 0.996; // voltage measurement calibration with multimeter

// correction Irradiance value from reference

float IRref = 1.5000; // reference  https://www.hidmet.gov.rs/eng/osmotreni/kosutnjak.php

volatile float Radiation;


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
  return ((adc_sum / n)*V_REF*5/4096*1000)*ADCcorr; // V_REF*2/4096*1000) Divide the ADC value by the ADC maximum value, Multiply by the supply voltage
}
   
void insolSetup()
{
  init_adc();
}
 
void insolLoop()
{

// Grove ADC reading voltage from reference panel
   Vx = read_adc(); // millivolts

// Power calculations

  Ix = (Vx / Rsc); // follows Ohm's law: V = I * R

  Radiation = Ix / Isc; // the factor of measured versus short cut current, max = 1000W per square meter

  insolPower = Radiation * IRref; // correction for Irradiance calibration value
  
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

