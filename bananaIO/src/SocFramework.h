/* 
 * File:   SocFramework.h
 * Author: pullrich
 *
 * Created on 10. Juli 2014, 11:48
 */

#ifndef SOCFRAMEWORK_H
#define	SOCFRAMEWORK_H

#include "Register.h"
#include "SocConfiguration.h"

#ifdef BANANE
	#include "BananaPi.h"
	#define InitializePi		InitializeBananaPi	
	#define TestPi				TestBananaPi	
#else
	#include "RaspberryPi.h"
	#define InitializePi		InitializeRaspberryPi	
	#define TestPi				TestRaspberryPi	
#endif

//#ifdef BANANAPI_H
//	#define GPIO_PIN_CLEAR_VALUE							0
//	#define GPIO_PIN_SET_VALUE								1
//#elif defined(RASPBERRYPI_H)
//	#define GPIO_PIN_CLEAR_VALUE							1
//	#define GPIO_PIN_SET_VALUE								1
//#else
//	#define GPIO_PIN_CLEAR_VALUE							0
//	#define GPIO_PIN_SET_VALUE								0
//#endif

#ifdef	__cplusplus
extern "C" {
#endif
	
	struct SocRegister{
		struct Register *GpioFunction;
		struct Register *GpioPullMode;
		struct Register *GpioSet;
		struct Register *GpioClear;
		struct Register *GpioValue;	
	};
	
	struct MappedMemory{
		volatile uint32_t *GpioMemory;
	};

	struct Soc
	{
		struct MappedMemory MappedMemory;
		struct SocRegister Register;
	} CurrentSoc;


#ifdef	__cplusplus
}
#endif

#endif	/* SOCFRAMEWORK_H */

