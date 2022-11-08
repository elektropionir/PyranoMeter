// https://www.hackster.io/Arduino_Genuino/mkr-zero-read-battery-voltage-4853ac

// https://blog.ampow.com/lipo-voltage-chart/

// averaging parameters

float lipoMAvg; // value for moving average to flatten out fluctuations
long lipoReport; // delay in updating insolPowerAv
unsigned long nLipo; // number of samples
  
void lipoLoop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(ADC_BATTERY);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 4.2V):
  float lipoVoltage = sensorValue * (4.2 / 1023.0);
  lipoLevel = (lipoVoltage-3.7) / 0.5 * 100;
  if (lipoLevel > 100) {
    lipoLevel = 100;
  }

// floating average
  nLipo++; // update sample count
  lipoMAvg += (lipoLevel - lipoMAvg) / nLipo; // calculate moving average
    
  if (loopStartMillis - lipoReport > 10 * 1000) { // 10 secs polling
  lipoLevelAvg = lipoMAvg; // retreive result after polling time
  if (lipoLevelAvg < 0) {
    lipoLevelAvg = 0;
  }
  lipoReport = loopStartMillis;
  nLipo = 0; // to start a new averaging period, set number of samples (n) to zero
  } 
}
