/* 
 * File:   bananaIO.h
 * Author: pullrich
 *
 * Created on 8. Juli 2014, 12:30
 */

#ifndef BANANAIO_H
#define	BANANAIO_H

#ifdef	__cplusplus
extern "C" {
#endif


#define		HIGH						1
#define		LOW						0

enum PinPullMode {
	PinPullModeNone = 0b00,
	PinPullModeUp = 0b01,
	PinPullModeDown = 0b10
};

enum PinDirection {
	PinDirectionInput = 0b000,
	PinDirectionOutput = 0b001
};

enum PortRegister {
	PortRegisterPullMode = 28,
	PortRegisterMultiDriving = 20,
	PortRegisterData = 16,
	PortRegisterConfiguration = 0
};

enum Pins {
	PIN03 = 149,	CON3_P03 = 149,	PB21 = 149,
	PIN05 = 148, CON3_P05 = 148, PB20 = 148,
	PIN07 = 1027, CON3_P07 = 1027, PI03 = 1027,
	PIN08 = 896, CON3_P08 = 896, PH00 = 896,
	PIN10 = 897, CON3_P10 = 897, PH01 = 897,
	PIN11 = 1043, CON3_P11 = 1043, PI19 = 1043,
	PIN12 = 898, CON3_P12 = 898, PH02 = 898,
	PIN13 = 1042, CON3_P13 = 1042, PI18 = 1042,
	PIN15 = 1041, CON3_P15 = 1041, PI17 = 1041,
	PIN16 = 916, CON3_P16 = 916, PH20 = 916,
	PIN18 = 917, CON3_P18 = 917, PH21 = 917,
	PIN19 = 1036, CON3_P19 = 1036, PI12 = 1036,
	PIN21 = 1037, CON3_P21 = 1037, PI13 = 1037,
	PIN22 = 1040, CON3_P22 = 1040, PI16 = 1040,
	PIN23 = 1035, CON3_P23 = 1035, PI11 = 1035,
	PIN24 = 1034, CON3_P24 = 1034, PI10 = 1034,
	PIN26 = 1038, CON3_P26 = 1038, PI14 = 1038,

	PH24 = 920

};

struct Register {
	// global settings
	enum PortRegister PortRegister;
	int PinsPerPort;
	//int BitsPerRegister;
	int PinsPerRegister;
	int BitsPerPin;
};

struct InOut {
	enum Pins Pin;
	enum PinDirection Direction;
	int value;
};

volatile uint32_t *openMemory();

struct Register *newRegister(enum PortRegister portRegister, int bitsPerRegister, int bitsPerPin, int size);
void WriteRegister(struct Register *reg, enum Pins pin, int resetMask, int value);
int ReadRegister(struct Register *reg, enum Pins pin);

int ReadPinValue(enum Pins pin);
void WritePinValue(enum Pins pin, int value);

void digitalWrite(enum Pins pin, int value);
int digitalRead(enum Pins pin);

void ConfigurePinDirection(enum Pins pin, enum PinDirection pinDirection);
void ConfigurePinPullMode(enum Pins pin, enum PinPullMode pullMode);

struct InOut *newInputOutput(enum Pins pin, enum PinDirection pinDirection, enum PinPullMode pullMode);
struct InOut *newInput(enum Pins pin, enum PinPullMode pullMode);
struct InOut *newOutput(enum Pins pin);

void Initialize();


#ifdef	__cplusplus
}
#endif

#endif	/* BANANAIO_H */

