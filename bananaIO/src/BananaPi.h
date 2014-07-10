/* 
 * File:   A20.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 09:21
 */

#include <stdint.h>
#include "SocConfiguration.h"

#ifdef BANANE

#ifndef BANANAPI_H
#define	BANANAPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define GPIO_PIN_CLEAR_VALUE							0
#define GPIO_PIN_SET_VALUE								1

#define SOC_REGISTER_PAGE_SIZE						4096

#define SOC_REGISTER_PHYSICAL_BASEADDRESS			0x01C20800
#define SOC_REGISTER_BUS_BASEADDRESS				0x01C20800
#define SOC_REGISTER_BUS_OFFSET						(SOC_REGISTER_BUS_BASEADDRESS - SOC_REGISTER_PHYSICAL_BASEADDRESS) // 0x5E000000

// GPIO	
#define SOC_REGISTER_GPIO_COUNT						88
#define SOC_REGISTER_GPIO_BASEADDRESS				(SOC_REGISTER_BUS_BASEADDRESS - (SOC_REGISTER_BUS_OFFSET)) // /* GPIO register base */

#define SOC_REGISTER_BYTE_PER_REGISTER				4						// All register are 32 Bit
#define SOC_REGISTER_BLOCKSIZE						4						// Each register has 4x 4 byte
#define SOC_REGISTER_PORT_SIZE						36						// Number of rows per port to calculate with uint32_t pointer

enum PinPullMode {
	PinPullModeNone = 0b00,
	PinPullModeUp = 0b01,
	PinPullModeDown = 0b10
};

enum PinFunction {
	PinFunctionInput = 0b000,
	PinFunctionOutput = 0b001
};

enum PortRegister {
	PortRegisterPullMode = 28,
	PortRegisterMultiDriving = 20,
	PortRegisterData = 16,
	PortRegisterGpioSet = 16,
	PortRegisterGpioClear = 16,
	PortRegisterGpioValue = 16,
	PortRegisterFunction = 0
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

volatile uint32_t *openBananaPiMemory(uint32_t baseAddress);
void InitializeBananaPi();

#ifdef	__cplusplus
}
#endif

#endif	/* A20_H */

#endif // BANANE