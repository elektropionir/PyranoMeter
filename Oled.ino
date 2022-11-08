// ** The oled data screen **

#include "lcdgfx.h" // https://github.com/lexus2k/lcdgfx

// standard X/Y positions: 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128

DisplaySSD1306_128x64_I2C display(-1); // SSD1306 Oled 128 x 64

String s;
char str[16];

void displaySetup() {
    display.setFixedFont( ssd1306xled_font6x8 );
    display.begin();
    display.clear();

      display.printFixed(28, 16, "ELEKTROPIONIR", STYLE_BOLD);
    lcd_delay(2000);
      display.printFixed(36, 32, "pyranometer", STYLE_NORMAL);
      display.printFixed(36, 56, "version 1.1", STYLE_NORMAL);
     lcd_delay(3000);   
      display.clear();
}

void displayClear() {
display.clear();
}

void displayLoop() {
//  display.setColor(GRAY_COLOR4(200)); // 255 is max level
  
// display Irradiance (W/m2)
  display.printFixed(0, 8, "SolPow", STYLE_NORMAL);
  sprintf(str,"%04d",insolPower); // insol
  display.printFixedN(48, 0, str, STYLE_NORMAL, FONT_SIZE_2X);
  display.printFixed(100, 8, "W/m2", STYLE_NORMAL);

// display solar sensor average (W)
//  display.printFixed(0, 28, "INsol", STYLE_NORMAL);
//  sprintf(str,"%04d",insolPowerAvg); // insol AV
//  display.printFixed(48, 28, str, STYLE_NORMAL);
//  display.printFixed(100, 28, "W/m2", STYLE_NORMAL);

// display 1 panel output
  display.printFixed(0, 28, "1 350Wp", STYLE_NORMAL);
  display.printFixed(0, 36, "  panel", STYLE_NORMAL);
  sprintf(str,"%04d",onePanel); // insol
  display.printFixed(48, 28, str, STYLE_NORMAL);
  display.printFixed(100, 28, "W", STYLE_NORMAL);

// footer

// display solar sensor (Vx raw)
// sprintf(str,"%04d",Vx); // voltage in mV measured by ADC
// display.printFixed(48, 40, str, STYLE_NORMAL);
// display.printFixed(100, 40, "mV", STYLE_NORMAL);

// display solar sensor (P raw)
  sprintf(str,"%04d",Px); // power in mW measured by ADC
  display.printFixed(48, 48, str, STYLE_NORMAL);
  display.printFixed(100, 48, "mW", STYLE_NORMAL);
  
// display Mem
  sprintf(str,"%.2d", freeMemory()/1000);
  display.printFixed(48, 56, str, STYLE_NORMAL);
  display.printFixed(66, 56, "kB", STYLE_NORMAL);

// display LiPo
//   display.printFixed(104, 56, "++++", STYLE_NORMAL);
  sprintf(str,"%03d",lipoLevelAvg); // battery
  display.printFixed(100, 56, str, STYLE_NORMAL);
  display.printFixed(120, 56, "%", STYLE_NORMAL);
  }
