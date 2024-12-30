/*
 * smarthome.c

 *
 *  Created on: Nov 14, 2024
 *      Author: Mohamed
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/KEYBAD/KEYBAD_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/EEPROM/EEPROM_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"
#include "../../HAL/Sensor/Sensor_Interface.h"
#include <avr/delay.h>
#include "smarthome.h"
#include "smarthomeConfig.h"


#define MAX_ATTEMPTS 3
volatile u8 temp = 0;
u16 thepass = 0;
u8 u8CalculateTemperature(){
	temp = u16ADCTempRead(Channel_A1);
	_delay_ms(500);
	return temp;
}
void vCheckTemp(){
	if(temp > 28 || temp >= 21 ){
		DCMotorON();
	}else if(temp < 21){
		DCMotorOFF();
	}else{
		DCMotorOFF();
	}
}
void vSetLedDirections(){
	vSetPinDirection(PORT_D , PIN_3 , output);
	vPinValue(PORT_D , PIN_3 , HIGH);
	vSetPinDirection(PORT_D , PIN_4 , output);
	vPinValue(PORT_D , PIN_4 , HIGH);
	vSetPinDirection(PORT_B , PIN_0 , output);
	vPinValue(PORT_B , PIN_0 , HIGH);
	vSetPinDirection(PORT_D , PIN_6 , output);
	vPinValue(PORT_D , PIN_6 , HIGH);
	vSetPinDirection(PORT_D , PIN_7 , output);
	vPinValue(PORT_D , PIN_7 , HIGH);
	vSetPinDirection(PORT_D , PIN_1 , output);
	vPinValue(PORT_D , PIN_1 , HIGH);
}
u16 u16password(u16 address, u16 pass){
	u8 data1 = 0;
	u8 data2 = 0;
	EEPROM_WriteData(address,(u8)pass);
	EEPROM_WriteData(address+1,(u8)(pass >> 8));

	EEPROM_ReadData(address,&data1);
	EEPROM_ReadData(address+1,&data2);
	u16 combined_pass = ((u16)data2 << 8) | data1;
	thepass= combined_pass;
	return combined_pass;
}
bool vcheckpass() {
	u8 Key = NoKey;
	u16 pass = 0;
	u8 attempts = 0;

	while (attempts < MAX_ATTEMPTS) {
		vClearDisplay();
		vLcdWriteString("Enter password:");
		vSetCursor(2, 1);

		pass = 0;
		while (1) {
			Key = u8KeyPressed();
			if (Key != NoKey) {
				LcdWriteData('*');
			if (Key >= '0' && Key <= '9') {
				pass = (pass * 10) + (Key - '0');
				}
			if (Key == '=') {
				if (pass == thepass) {
					vLcdWriteString("Access Granted");
					return True;
					} else {
					attempts++;
					vClearDisplay();
					vLcdWriteString("Wrong password");
					_delay_ms(1000);
					break;
					}
				}
			if (Key == 'c') {
				vClearDisplay();
				vLcdWriteString("Password cleared");
				_delay_ms(1000);
				vClearDisplay();
				pass = 0;
				vLcdWriteString("Enter password:");
				vSetCursor(2, 1);
				}
			}
		}
	}

	vClearDisplay();
	vSetCursor(1, 1);
	vLcdWriteString("System locked!");
	vSetCursor(2, 1);
	vLcdWriteString("Require Restart");
	_delay_ms(1000);
	return False;
}
