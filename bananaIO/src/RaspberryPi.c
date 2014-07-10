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

	
/*
#define SOC_REGISTER_BYTE_PER_REGISTER				4						// All register are 32 Bit
#define SOC_REGISTER_BLOCKSIZE						4						// Each register has 4x 4 byte
#define SOC_REGISTER_PORT_SIZE						36						// Number of rows per port to calculate with uint32_t pointer
*/
/*
_t *mappedMemory, int portRegister, int portOffset, int bytePerRegister, int bitsPerPin, int size) 

		result->PortOffset = portOffset;
	result->PortRegister = portRegister;
	result->BitsPerPin = bitsPerPin;
	//result->BitsPerRegister = bitsPerRegister;
	result->PinsPerRegister = (bytePerRegister * 8) / result->BitsPerPin;
	result->PinsPerPort = bytePerRegister * size * result->PinsPerRegister;
	
	CurrentSoc.Register.GpioFunction = NewRegister(
			  CurrentSoc.MappedMemory.GpioMemory, 
			  PortRegisterFunction, 
			  
			  SOC_REGISTER_BYTE_PER_REGISTER, 
			  3, 
			  4
	);
	CurrentSoc.Register.GpioPullMode = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterPullMode, portOffset, SOC_REGISTER_BYTE_PER_REGISTER, 2, 1);
		
	// On A20 this points to the same register
	CurrentSoc.Register.GpioSet = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioSet, portOffset, SOC_REGISTER_BYTE_PER_REGISTER, 1, 1);
	CurrentSoc.Register.GpioClear = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioClear, portOffset, SOC_REGISTER_BYTE_PER_REGISTER, 1, 1);
	CurrentSoc.Register.GpioValue = NewRegister(CurrentSoc.MappedMemory.GpioMemory, PortRegisterGpioValue, portOffset, SOC_REGISTER_BYTE_PER_REGISTER, 1, 1);
*/

	
/*
		this->functionSelectRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::FunctionSelect0, 6, 32, 3);
	this->setPinRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::PinOutputSet0, 2, 32, 1);
	this->clearPinRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::PinOutputClear0, 2, 32, 1);
	this->valuesRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::PinLevel0, 2, 32, 1);
	this->resistorsModeRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::PinPullUpDownMode, 1, 32, 1);
	this->resistorsPinRegister = new Register1((unsigned int) Bcm2835_Gpio::GpioRegister::PinPullUpDownEnablePins, 2, 32, 1);
*/

	
}

void TestRaspberryPi()
{
	int value;
	
	ConfigurePinDirection(PIN23, PinFunctionOutput);

	SetRegisterBit(CurrentSoc.Register.GpioClear, PIN23);
	SetRegisterBit(CurrentSoc.Register.GpioSet, PIN23);
	SetRegisterBit(CurrentSoc.Register.GpioClear, PIN23);
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 1);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);
	
}
