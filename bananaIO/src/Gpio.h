/* 
 * File:   Gpio.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 11:03
 */

#include <stdlib.h>


#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif



struct InOut {
	int Pin;
	int Function;
	int value;
};

#define		HIGH						1
#define		LOW						0

struct InOut *NewInputOutput(int pin, int pinDirection, int pullMode);
struct InOut *NewInput(int pin, int pullMode);
struct InOut *NewOutput(int pin);

void ConfigurePinDirection(int pin, int pinDirection);
void ConfigurePinPullMode(int pin, int pullMode);

int ReadPinValue(int pin);
void WritePinValue(int pin, int value);
void SetPinValue(int pin);
void ClearPinValue(int pin);

void digitalWrite(int pin, int value);
int digitalRead(int pin);

#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_H */

