#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "SocConfiguration.h"
#include "SocFramework.h"
#include "BananaPi.h"

#ifdef BANANE
#define TESTPIN	PH24
#else
#define TESTPIN	0
#endif

volatile uint32_t *openBananaPiMemory(uint32_t baseAddress) {
	int fileDescriptor;
	
	if (!(fileDescriptor = open("/dev/mem", O_RDWR))) {
		return NULL;
	}

	uint32_t *map = mmap(0, SOC_REGISTER_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, baseAddress);

	close(fileDescriptor);
			  
	return (volatile uint32_t *)map + 512;

}

void InitializeBananaPi() {

	CurrentSoc.MappedMemory.GpioMemory = openBananaPiMemory(SOC_REGISTER_GPIO_BASEADDRESS);

	CurrentSoc.Register.GpioFunction = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterFunction, 4, 4);
	CurrentSoc.Register.GpioPullMode = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterPullMode, 2, 2);

	// On A20 this points to the same register
	CurrentSoc.Register.GpioSet = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioSet, 1, 1);
	CurrentSoc.Register.GpioClear = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioClear, 1, 1);
	CurrentSoc.Register.GpioValue = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioValue, 1, 1);

}

void TestBananaPi() {
	int value;

//	ConfigurePinDirection(8, PinFunctionOutput);
	
	ConfigurePinDirection(TESTPIN, PinFunctionOutput);
	WritePinValue(TESTPIN, 1);

	WritePinValue(TESTPIN, 0);
	value = ReadPinValue(TESTPIN);
	WritePinValue(TESTPIN, 1);
	value = ReadPinValue(TESTPIN);
	WritePinValue(TESTPIN, 0);
	value = ReadPinValue(TESTPIN);

}
