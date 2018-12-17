/*
    Scan device and dispaly on OLED Sheild
*/

#include <Wire.h>
#include <LOLIN_I2C_MOTOR.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{

  Wire.begin();

  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
  byte error, address;

  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  display.println("Scanning..");
  for (address = 1; address < 127; address++) //find the I2C MOTOR device
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      LOLIN_I2C_MOTOR motor(address);
      if (motor.getInfo() == 0)
      {

        if (motor.PRODUCT_ID == PRODUCT_ID_I2C_MOTOR)
        {
          display.setTextSize(2);
          display.println("Motor");
        }
      }
    }
  }
  display.display();
  delay(1000);
}
