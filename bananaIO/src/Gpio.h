/* 
 * File:   Gpio.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 11:03
 */

#include <stdlib.h>

#include "SocConfiguration.h"
#include "SocFramework.h"
#include "RegisterStruct.h"
#include "GpioStruct.h"

#ifndef GPIO_H
#define	GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif

#define		HIGH						1
#define		LOW						0

struct GpioPin *NewInputOutput(int pin, int pinDirection, int pullMode);
struct GpioPin *NewInput(int pin, int pullMode);
struct GpioPin *NewOutput(int pin);

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

