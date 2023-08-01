# PyranoMeter

## Intro

A DIY Arduino insolation meter.
 
This device helps to measure the power of the sun – irradiance (W/m2) from the
hemisphere – at a given location. It helps you to understand how much solar PV
energy can be harvested and what is the best orientation of the panels.

The PyronoMeter is based on the [DIY Irradiation Meter with Arduino](https://solarduino.com/diy-irradiation-meter-with-arduino/), while the code has been made modular to easier add functionality (Oled, LED Matrix, etc.)

## CPU

The platform used is ARDUINO_SAMD_MKRZERO. It can easily be made compatible with other platforms.

## Hardware

<img src="https://elektropionir.rs/wp-content/uploads/2022/10/pyranometer-web-768x1024.jpg" width=75% height=75%>
Components used:

* PV Solar panel
* ADC for reference mini PV panel (Grove)
* 15 OHM 5W 'shortcut' resistor for mini PV panel
* Arduino MKR Zero
* I2C hub (Grove)
* OLED display (128 x 128) and LED Matrix display

## Releases

 2023.08.01: updated insolation calculation and using a larger (128x128) Oled screen.
