// ** The oled data screen **

#include "lcdgfx.h" // https://github.com/lexus2k/lcdgfx

// standard X/Y positions (16) : 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128

DisplaySSD1327_128x128_I2C display(-1); // SSD1327 Oled 128 x 128

String s;
char str[16];

void displaySetup() {
    display.setFixedFont( ssd1306xled_font6x8 );
    display.begin();
    display.clear();

      display.printFixed(24, 16, "ELEKTROPIONIR", STYLE_BOLD);
    lcd_delay(2000);
      display.printFixed(28, 48, "PYRANOMETER", STYLE_NORMAL);

      // display firmware version
      display.printFixed(28, 64, "version", STYLE_NORMAL);
      sprintf(str,"%.2f",firmVer);
      display.printFixed(76, 64, str, STYLE_NORMAL);

     lcd_delay(2000);   
      display.clear();
}

void displayClear() {
display.clear();
}

void displayLoop() {
  display.setColor(GRAY_COLOR4(200)); // 255 is max level
  
  display.printFixed(28, 0, "PYRANOMETER", STYLE_BOLD);

// display Irradiance (W/m2)
   display.setFixedFont( ssd1306xled_font8x16 );
  display.printFixed(0, 16, "SUN", STYLE_NORMAL);
  sprintf(str,"%04d",insolPower); // insol
  display.printFixed(48, 16, str, STYLE_BOLD);
  display.setFixedFont( ssd1306xled_font6x8 );
  display.printFixed(96, 24, "W/m2", STYLE_NORMAL);

  display.setFixedFont( ssd1306xled_font8x16 );
  display.printFixed(0, 32, "AVG", STYLE_NORMAL);
  sprintf(str,"%04d",insolPowerAvg); // insol
  display.printFixed(48, 32, str, STYLE_BOLD);
    display.setFixedFont( ssd1306xled_font6x8 );
  display.printFixed(96, 40, "W/m2", STYLE_NORMAL);
 
  display.setFixedFont( ssd1306xled_font6x8 );

// display 1 panel output
  display.printFixed(0, 60, "350Wp", STYLE_NORMAL);
  sprintf(str,"%04d",onePanel); // insol
  display.printFixed(48, 60, str, STYLE_NORMAL);
  display.printFixed(96, 60, "W", STYLE_NORMAL);

  display.setColor(GRAY_COLOR4(75)); // 255 is max level

// display solar sensor (Vx raw)
  display.printFixed(0, 80, "Vsc", STYLE_NORMAL);
  sprintf(str,"%04d",Vx); // voltage in mV measured by ADC
  display.printFixed(48, 80, str, STYLE_NORMAL);
  display.printFixed(96, 80, "mV", STYLE_NORMAL);

// display solar sensor (Ix raw)
    display.printFixed(0, 88, "Isc", STYLE_NORMAL);
    sprintf(str,"%04d",Ix); // power in mW measured by ADC
    display.printFixed(48, 88, str, STYLE_NORMAL);
    display.printFixed(96, 88, "mA", STYLE_NORMAL);

  display.setColor(GRAY_COLOR4(200)); // 255 is max level

}



