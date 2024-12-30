/*
 * smarthome.h
 *
 *  Created on: Nov 14, 2024
 *      Author: Mohamed
 */

#ifndef APP_SMARTHOME_SMARTHOME_H_
#define APP_SMARTHOME_SMARTHOME_H_

typedef enum {
	False = 0,
	True,
} bool;



u8 u8CalculateTemperature();
void vCheckTemp();
void vSetLedDirections();
u16 u16password(u16 address, u16 pass);
bool vcheckpass();
#endif /* APP_SMARTHOME_SMARTHOME_H_ */
