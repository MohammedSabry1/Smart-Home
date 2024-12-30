/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Mohamed
 */
#include "../LIB/STD_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include"../MCAL/DIO/DIO_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/KEYBAD/KEYBAD_Interface.h"
#include "../MCAL/EXTI/EXTI_Interface.h"
#include "../MCAL/Global_Interrupt/GIE_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../APP/Calculation/Calculation_Interface.h"
#include "../HAL/Sensor/Sensor_Interface.h"
#include "../MCAL/SPI/SPI_init.h"
#include "../MCAL/Timer/Timer_Interface.h"
#include "../APP/Smarthome/smarthome.h"
#include "../HAL/EEPROM/EEPROM_Interface.h"
#include "../MCAL/I2C/I2C_Interface.h"
#include "../HAL/ServoMotor/ServoMotor_Interface.h"
#include <util/delay.h>
#include <avr/interrupt.h>
ISR(INT0_vect){
	if(u8DigitalFlameRead()){
		vPinValue(PORT_C,PIN_7,HIGH);// TURN ON BUZZER
		vPinValue(PORT_C,PIN_6,HIGH);// TURN ON PUMP

	}else{
		vPinValue(PORT_C,PIN_7,LOW);
		vPinValue(PORT_C,PIN_6,LOW);

	}
}

int main(){
	vSetPinDirection(PORT_C,PIN_7,output);
	vSetPinDirection(PORT_C,PIN_6,output);
	EEPROM_Init();
	LcdInit();
	vKeyPadInit();
	u16 pass = 0;
	pass = u16password(10,12121);
	vLcdWriteString("Enter password :");
	vSetCursor(2,1);
	if(vcheckpass()){
		_delay_ms(500);
		vClearDisplay();
		vSetCursor(1,3);
		vLcdWriteString("Welcome to");
		vSetCursor(2,3);
		vLcdWriteString(" your Home");
		vADCInit();
		vEnableADC();
		vEnable_EXTI(EXTI0);
		vMod_EXTI(EXTI0,LOGIC_CHANGE);
		ENABLE_GIE();
		vSetLedDirections();
		_delay_ms(200);
		vSetPinDirection(PORT_D,PIN_5,output);
		SERVO_ANGLE(125); // for 90 degree angle
	}else{
		vLcdWriteString("Access Denied");

	}

	while(1){
		u8CalculateTemperature();
		vCheckTemp();
	}

	return 0;
}













//	vSetPinDirection(PORT_D,PIN_5,output);
//	// SELECR OCR1A NON INVERTING
//	SET_BIT(TCCR1A,COM1A1);
//	CLEAR_BIT(TCCR1A,COM1A0);
//
//	// SELECT TIMEFR1 MODE 14
//	CLEAR_BIT(TCCR1A,WGM10);
//	SET_BIT(TCCR1A , WGM11);
//	SET_BIT(TCCR1B,WGM12);
//	SET_BIT(TCCR1B,WGM13);
//	// SELECT PRESCALLER 256
//	CLEAR_BIT(TCCR1B,CS10);
//	CLEAR_BIT(TCCR1B,CS11);
//	SET_BIT(TCCR1B,CS12);
//
//
//	ICR1 = 1250;
//

