/* 
 * File:   Register.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 11:04
 */

#include <stdint.h>

#include "SocConfiguration.h"
#include "SocFramework.h"
#include "RegisterStruct.h"
#include "GpioStruct.h"

#ifndef REGISTER_H
#define	REGISTER_H

#ifdef	__cplusplus
extern "C" {
#endif


struct Register *NewRegister(volatile uint32_t *mappedMemory, int portRegister, int portCount, int bitsPerPin);

//struct Register *NewRegister(volatile uint32_t *mappedMemory, int portRegister, int portOffset, int bytePerRegister, int bitsPerPin, int size);
void WriteRegister(struct Register *reg, int, int resetMask, int value);
int ReadRegister(struct Register *reg, int pin);

int GetPinRegisterShift(struct Register *reg, int pin);
int GetPinRegisterOffset(struct Register *reg, int pin);

#ifdef	__cplusplus
}
#endif

#endif	/* REGISTER_H */

