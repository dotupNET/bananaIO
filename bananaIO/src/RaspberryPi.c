#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "SocConfiguration.h"
#include "SocFramework.h"
#include "RaspberryPi.h"
#include "Gpio.h"


volatile uint32_t *openRaspberryPiMemory(uint32_t baseAddress) {
	int fileDescriptor;

	if (!(fileDescriptor = open("/dev/mem", O_RDWR))) {
		return NULL;
	}

	uint32_t *map = mmap(0, SOC_REGISTER_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, baseAddress);

	close(fileDescriptor);

	return (volatile uint32_t *)map;

}

void InitializeRaspberryPi(){
	
	CurrentSoc.MappedMemory.GpioMemory = openRaspberryPiMemory(SOC_REGISTER_GPIO_BASEADDRESS);
	
	CurrentSoc.Register.GpioFunction = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterFunction, 6, 3);
	CurrentSoc.Register.GpioPullMode = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterPullMode, 2, 2);
		
	// On A20 this points to the same register
	CurrentSoc.Register.GpioSet = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioSet,  2, 1);
	CurrentSoc.Register.GpioClear = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioClear, 2, 1);
	CurrentSoc.Register.GpioValue = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioValue, 2, 1);

}

void TestRaspberryPi()
{
	int value;
	
	ConfigurePinDirection(PIN23, PinFunctionOutput);

/*
	SetRegisterBit(CurrentSoc.Register.GpioClear, PIN23);
	SetRegisterBit(CurrentSoc.Register.GpioSet, PIN23);
	SetRegisterBit(CurrentSoc.Register.GpioClear, PIN23);
*/
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 1);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);
	
}
