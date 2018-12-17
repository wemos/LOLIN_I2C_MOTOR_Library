/*
    Restore I2C address to DEFAULT_I2C_MOTOR_ADDRESS (0x30)
*/

#include <Wire.h>
#include <LOLIN_I2C_MOTOR.h>

void setup()
{

    Wire.begin();

    Serial.begin(115200);
    // delay(1000);
}

void loop()
{
    byte error, address;
    Serial.println("Scanning...");
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
                    Serial.print("I2C motor found at address 0x");
                    if (address < 16)
                        Serial.print("0");
                    Serial.println(address, HEX);

                    Serial.print("Firmware Version: ");
                    Serial.println(motor.VERSION);

                    if (address == DEFAULT_I2C_MOTOR_ADDRESS)
                    {
                        Serial.println("Already default address");
                    }
                    else
                    {
                        Serial.print("Try to restore default address 0x");
                        Serial.println(DEFAULT_I2C_MOTOR_ADDRESS, HEX);

                        motor.changeAddress(DEFAULT_I2C_MOTOR_ADDRESS);
                    }
                }
            }
        }
    }
}
