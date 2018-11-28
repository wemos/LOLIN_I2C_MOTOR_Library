/*
  Simple Motor Shield Test.
*/

#include <Wire.h>
#include <LOLIN_I2C_MOTOR.h>

LOLIN_I2C_MOTOR motor; //I2C address 0x30
// LOLIN_I2C_MOTOR motor(DEFAULT_I2C_MOTOR_ADDRESS); //I2C address 0x30
// LOLIN_I2C_MOTOR motor(your_address); //using customize I2C address

void setup()
{
  Serial.begin(115200);
  Serial.println("Motor Shield Testing...");

  while (motor.PRODUCT_ID != PRODUCT_ID_I2C_MOTOR) //wait motor shield ready.
  {
    motor.getInfo();
  }
}

void loop()
{
  Serial.println("Change A to CCW, B to CW, Freq: 1000Hz");
  Serial.println("Duty Tesing...");

  motor.changeFreq(MOTOR_CH_BOTH, 1000); //Change A & B 's Frequency to 1000Hz.
  /*
      motor.changeFreq(MOTOR_CH_A, 1000);//Change A 's Frequency to 1000Hz.
      motor.changeFreq(MOTOR_CH_B, 2000);//Change B 's Frequency to 2000Hz.
  */
  motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_CCW);
  motor.changeStatus(MOTOR_CH_B, MOTOR_STATUS_CW);

  for (float duty = 0; duty <= 100; duty++)
  {
    motor.changeDuty(MOTOR_CH_A, duty);
    motor.changeDuty(MOTOR_CH_B, 100 - duty);

    Serial.print("Change A Duty to ");
    Serial.print(duty);
    Serial.println("%");

    Serial.print("Change B Duty to ");
    Serial.print(100 - duty);
    Serial.println("%");

    delay(100);
  }

  Serial.println("STANDBY Tesing...");
  motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_CCW);
  motor.changeDuty(MOTOR_CH_BOTH, 100);
  for (int i = 0; i < 5; i++)
  {
    Serial.println("MOTOR_STATUS_STANDBY");
    motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_STANDBY);
    delay(500);
    Serial.println("MOTOR_STATUS_CW");
    motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_CW);
    delay(500);
    Serial.println("MOTOR_STATUS_STANDBY");
    motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_STANDBY);
    delay(500);
    Serial.println("MOTOR_STATUS_CCW");
    motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_CCW);
    delay(500);
  }

  Serial.println("MOTOR_STATUS Tesing...");
  for (int i = 0; i < 5; i++)
  {
    Serial.println("MOTOR_STATUS_STOP");
    motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_STOP);
    delay(500);
    Serial.println("MOTOR_STATUS_CCW");
    motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_CCW);
    delay(500);
    Serial.println("MOTOR_SHORT_BRAKE");
    motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_SHORT_BRAKE);
    delay(500);
    Serial.println("MOTOR_STATUS_CW");
    motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_CW);
    delay(500);
  }
}
