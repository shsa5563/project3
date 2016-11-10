/*
 * led.h
 *
 *  Created on: 09-Oct-2016
 *      Author: Satyanarayana
 */
#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_
typedef enum
{
	OFF,
	RED,
	YELLOW,
	GREEN,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
}Colour_LED;
void Initialize_LED();
void Change_LEDColor(uint8_t Value);
void Intensty_Modify(Colour_LED Colour, uint16_t Brightness);

#endif /* SOURCES_LED_H_ */
