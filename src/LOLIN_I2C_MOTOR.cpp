#include "LOLIN_I2C_MOTOR.h"

/* 
	Init
*/
LOLIN_I2C_MOTOR::LOLIN_I2C_MOTOR(uint8_t address)
{
	Wire.begin();
	_address = address;
}

/*
	Change Motor Status.

		ch： Motor Channel
				MOTOR_CH_A
  				MOTOR_CH_B
				MOTOR_CH_BOTH
		
		sta: Motor Status
				MOTOR_STATUS_STOP
  				MOTOR_STATUS_CCW
				MOTOR_STATUS_CW
				MOTOR_STATUS_SHORT_BRAKE
				MOTOR_STATUS_STANDBY

*/
unsigned char LOLIN_I2C_MOTOR::changeStatus(unsigned char ch, unsigned char sta)
{
	send_data[0] = CHANGE_STATUS;
	send_data[1] = ch;
	send_data[2] = sta;
	unsigned char result = sendData(send_data, 3);

	return result;
}

/*
	Change Motor Frequency

		ch： Motor Channel
				MOTOR_CH_A
				MOTOR_CH_B
				MOTOR_CH_BOTH
		
		freq: PWM frequency (Hz)
				1 - 80,000 Hz
*/
unsigned char LOLIN_I2C_MOTOR::changeFreq(unsigned char ch, uint32_t freq)
{
	send_data[0] = CHANGE_FREQ;
	send_data[1] = ch;

	send_data[2] = (uint8_t)(freq & 0xff);
	send_data[3] = (uint8_t)((freq >> 8) & 0xff);
	send_data[4] = (uint8_t)((freq >> 16) & 0xff);
	unsigned char result = sendData(send_data, 5);

	return result;
}

/*
	Change Motor Duty.

		ch： Motor Channel
				MOTOR_CH_A
				MOTOR_CH_B
				MOTOR_CH_BOTH
		
		duty: PWM Duty (%)
				0.01 - 100.00 (%)

*/
unsigned char LOLIN_I2C_MOTOR::changeDuty(unsigned char ch, float duty)
{
	uint16_t _duty;
	_duty = (uint16_t)(duty * 100);

	send_data[0] = CHANGE_DUTY;
	send_data[1] = ch;

	send_data[2] = (uint8_t)(_duty & 0xff);
	send_data[3] = (uint8_t)((_duty >> 8) & 0xff);
	unsigned char result = sendData(send_data, 4);

	return result;
}

/*
	Reset Device.
*/
unsigned char LOLIN_I2C_MOTOR::reset()
{
	send_data[0] = RESET_SLAVE;
	unsigned char result = sendData(send_data, 1);

	return result;
}

/*
	Change Device I2C address
	address: when address=0, address>=127, will change address to default I2C address 0x31
*/
unsigned char LOLIN_I2C_MOTOR::changeAddress(unsigned char address)
{
	send_data[0] = CHANGE_I2C_ADDRESS;
	send_data[1] = address;
	unsigned char result = sendData(send_data, 2);

	return result;
}

/*
	Get PRODUCT_ID and Firmwave VERSION
*/
unsigned char LOLIN_I2C_MOTOR::getInfo(void)
{
	send_data[0] = GET_SLAVE_STATUS;
	unsigned char result = sendData(send_data, 1);
	if (result == 0)
	{
		PRODUCT_ID = get_data[0];
		VERSION = get_data[1];
	}
	else
	{
		PRODUCT_ID = 0;
		VERSION = 0;
	}

	return result;
}

/*
	Send and Get I2C Data
*/
unsigned char LOLIN_I2C_MOTOR::sendData(unsigned char *data, unsigned char len)
{
	unsigned char i;

	if ((_address == 0) || (_address >= 127))
	{
		return 1;
	}
	else
	{

		Wire.beginTransmission(_address);
		for (i = 0; i < len; i++)
			Wire.write(data[i]);
		Wire.endTransmission();
		delay(50);

		if (data[0] == GET_SLAVE_STATUS)
			Wire.requestFrom(_address, 2);
		else
			Wire.requestFrom(_address, 1);

		i = 0;

		while (Wire.available())
		{
			get_data[i] = Wire.read();
			i++;
		}

		return 0;
	}
}
