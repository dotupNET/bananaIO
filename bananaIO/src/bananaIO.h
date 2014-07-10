///* 
// * File:   bananaIO.h
// * Author: pullrich
// *
// * Created on 8. Juli 2014, 12:30
// */
//
//#include "TypeDefinitions.h"
//
//#ifndef BANANAIO_H
//#define	BANANAIO_H
//
//#ifdef	__cplusplus
//extern "C" {
//#endif
//
//
//
//
//
//
//
//volatile uint32_t *openMemory();
//
//struct Register *newRegister(enum PortRegister portRegister, int bitsPerRegister, int bitsPerPin, int size);
//void WriteRegister(struct Register *reg, enum Pins pin, int resetMask, int value);
//int ReadRegister(struct Register *reg, enum Pins pin);
//
//int ReadPinValue(enum Pins pin);
//void WritePinValue(enum Pins pin, int value);
//
//void digitalWrite(enum Pins pin, int value);
//int digitalRead(enum Pins pin);
//
//void ConfigurePinDirection(enum Pins pin, enum PinFunction pinDirection);
//void ConfigurePinPullMode(enum Pins pin, enum PinPullMode pullMode);
//
//struct InOut *newInputOutput(enum Pins pin, enum PinFunction pinDirection, enum PinPullMode pullMode);
//struct InOut *newInput(enum Pins pin, enum PinPullMode pullMode);
//struct InOut *newOutput(enum Pins pin);
//
//void Initialize();
//
//
//#ifdef	__cplusplus
//}
//#endif
//
//#endif	/* BANANAIO_H */
//
