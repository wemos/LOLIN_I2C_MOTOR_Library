/*
    Change the I2C Address
*/

#include <Wire.h>
#include <LOLIN_I2C_MOTOR.h>

byte new_address = 1;

void setup()
{
    Wire.begin();

    Serial.begin(115200);
}

void loop()
{
    byte error, address;

    Serial.println("Scanning...");
    for (address = 1; address < 127; address++) //find the I2C motor device
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
                    Serial.print("I2C motor found at address 0x");
                    if (address < 16)
                        Serial.print("0");
                    Serial.println(address, HEX);

                    Serial.print("Firmware Version: ");
                    Serial.println(motor.VERSION);

                    Serial.print("Try to change Address to 0x");
                    if (new_address < 16)
                        Serial.print("0");
                    Serial.println(new_address, HEX);
                    Serial.println("");

                    motor.changeAddress(new_address); //change I2C address
                    new_address++;
                    if (new_address > 126)
                        new_address = 1;
                }
            }
        }
    }

    delay(2000);
}
