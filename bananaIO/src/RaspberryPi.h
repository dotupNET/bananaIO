/* 
 * File:   BCM2835.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 09:18
 */

#include <stdint.h>
#include "SocConfiguration.h"

#ifndef BANANE

#ifndef RASPBERRYPI_H
#define	RASPBERRYPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#define GPIO_PIN_CLEAR_MASK							0xFFFFFFFF
#define GPIO_PIN_CLEAR_VALUE							1
	
#define GPIO_PIN_SET_MASK								0xFFFFFFFF
#define GPIO_PIN_SET_VALUE								1

#define SOC_REGISTER_PAGE_SIZE						4096

#define SOC_REGISTER_PHYSICAL_BASEADDRESS			0x20000000
#define SOC_REGISTER_BUS_BASEADDRESS				0x7E000000
#define SOC_REGISTER_BUS_OFFSET						(SOC_REGISTER_BUS_BASEADDRESS - SOC_REGISTER_PHYSICAL_BASEADDRESS) // 0x5E000000

	// GPIO

#define SOC_REGISTER_GPIO_COUNT						54
#define SOC_REGISTER_GPIO_BASEADDRESS				(0x7E200000 - (SOC_REGISTER_BUS_OFFSET)) // /* GPIO register base */

#define SOC_REGISTER_BYTE_PER_REGISTER				4						// All register are 32 Bit
#define SOC_REGISTER_PORT_SIZE						44						// Number of rows per port to calculate with uint32_t pointer

#define SOC_REGISTER_PINS_PER_PORT					54

	enum PinPullMode {
		PinPullModeNone = 0b00,
		PinPullModeUp = 0b01,
		PinPullModeDown = 0b10
	};

	enum PinFunction {
		PinFunctionInput = 0b000, // 000 = GPIO Pin n is an input 
		PinFunctionOutput = 0b001, // 001 = GPIO Pin n is an output 
		PinFunctionAlternate0 = 0b100, // 100 = GPIO Pin n takes alternate function 0 
		PinFunctionAlternate1 = 0b101, // 101 = GPIO Pin n takes alternate function 1 
		PinFunctionAlternate2 = 0b110, // 110 = GPIO Pin n takes alternate function 2 
		PinFunctionAlternate3 = 0b111, // 111 = GPIO Pin n takes alternate function 3 
		PinFunctionAlternate4 = 0b011, // 011 = GPIO Pin n takes alternate function 4 
		PinFunctionAlternate5 = 0b011 // 010 = GPIO Pin n takes alternate function 5 

	};

	enum PortRegister {
		PortRegisterFunction = 0,
		PortRegisterGpioSet = 7,
		PortRegisterGpioClear = 10,
		PortRegisterGpioValue = 13,
		PinEventDetectStatus0 = 16,
		PinRisingEdgeDetectEnable0 = 19,
		PinFallingEdgeDetectEnable0 = 22,
		PinHighDetectEnable0 = 25,
		PinLowDetectEnable0 = 28,
		PinAsyncRisingEdgeDetect0 = 31,
		PinAsyncFallingEdgeDetect0 = 34,
		PinPullUpDownMode = 37,
		PortRegisterPullMode = 38 //PinPullUpDownEnablePins = 38

	};

	enum Pins {
		// Connected to S5-14
		GPIO0 = 0,
		// Connected to S5-13
		GPIO1 = 1,


		// Connected to P1-03
		GPIO2 = 2, PIN03 = 2, SDA1 = 2,
		// Connected to P1-05
		GPIO3 = 3, PIN05 = 3, SCL1 = 3,
		// Connected to P1-07
		GPIO4 = 4, PIN07 = 4, GPIO_GCLK = 4,


		// Connected to S5-12
		GPIO5 = 5,


		// Connected to P1-26
		GPIO7 = 7, PIN26 = 7, SPI_CE1_N = 7,
		// Connected to P1-24
		GPIO8 = 8, PIN24 = 8, SPI_CE0_N = 8,
		// Connected to P1-21
		GPIO9 = 9, PIN21 = 9, SPI_MISO = 9,
		// Connected to P1-19
		GPIO10 = 10, PIN19 = 10, SPI_MOSI = 10,
		// Connected to P1-23
		GPIO11 = 11, PIN23 = 11, SPI_SCLK = 11,
		// Connected to P1-08
		GPIO14 = 14, PIN08 = 14, TXD0 = 14,
		// Connected to P1-10

		GPIO15 = 15, PIN10 = 15, RXD0 = 15,
		// Connected to D5 (ACT LED)

		GPIO16 = 16,
		// Connected to P1-11
		GPIO17 = 17, PIN11 = 17, GPIO_GEN0 = 17,
		// Connected to P1-12
		GPIO18 = 18, PIN12 = 18, GPIO_GEN1 = 18,


		// Connected to S5-11
		GPIO21 = 21,


		// Connected to P1-15
		GPIO22 = 22, PIN15 = 22, GPIO_GEN3 = 22,
		// Connected to P1-16
		GPIO23 = 23, PIN16 = 23, GPIO_GEN4 = 23,
		// Connected to P1-18
		GPIO24 = 24, PIN18 = 24, GPIO_GEN5 = 24,
		// Connected to P1-22
		GPIO25 = 25, PIN22 = 25, GPIO_GEN6 = 25,


		// Connected to P1-13
		GPIO27 = 27, PIN13 = 27, GPIO_GEN2 = 27,


		// Connected to P5-03
		GPIO28 = 28,
		// Connected to P5-04
		GPIO29 = 29,
		// Connected to P5-05
		GPIO30 = 30,
		// Connected to P5-06
		GPIO31 = 31

	};

	volatile uint32_t *openRaspberryPiMemory(uint32_t baseAddress);
	void InitializeRaspberryPi();

#ifdef	__cplusplus
}
#endif

#endif	/* BCM2835_H */

#endif // BANANE