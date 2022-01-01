
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setupOled()
{
    Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C (for the 128x32)(initializing the display)
  Serial.begin(9600);
}
void Display()
{
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Humidity: "); 
  display.print(" %\t");
  display.setCursor(0,10);
  display.print("Temperature: "); 
  display.print(" C"); 
  display.setCursor(0,20);
  display.print("Temperature: "); 
  display.print(" F"); 
}
void oled_loop()
{
  Display();
  display.display();
}
