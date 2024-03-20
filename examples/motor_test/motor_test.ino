#include <Wire.h>
#include <LOLIN_I2C_MOTOR.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  LOLIN_I2C_MOTOR motor; 
  motor.changeFreq(MOTOR_CH_BOTH, 1000); //Change A & B 's Frequency to 1000Hz.

  motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_CCW);
  motor.changeStatus(MOTOR_CH_B, MOTOR_STATUS_CW);
  motor.changeDuty(MOTOR_CH_A, 80);
  motor.changeDuty(MOTOR_CH_B, 80);
  delay(1000);
  
  motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_STOP);
  delay(500);

  motor.changeStatus(MOTOR_CH_A, MOTOR_STATUS_CW);
  motor.changeStatus(MOTOR_CH_B, MOTOR_STATUS_CCW);
  motor.changeDuty(MOTOR_CH_A, 80);
  motor.changeDuty(MOTOR_CH_B, 80);
  delay(1000);
  
  motor.changeStatus(MOTOR_CH_BOTH, MOTOR_STATUS_STOP);
  delay(500);


}
