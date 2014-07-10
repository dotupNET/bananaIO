/*

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#include "bananaIO.h"


volatile uint32_t *mappedMemory;

void Initialize() {
	mappedMemory = openMemory();
}

volatile uint32_t *openMemory() {
	int fileDescriptor;

	if (!(fileDescriptor = open("/dev/mem", O_RDWR))) {
		return NULL;
	}

	uint32_t mask = (~(SOC_REGISTER_PAGE_SIZE - 1));
	uint32_t offset = SOC_REGISTER_GPIO_BASEADDRESS & mask;
	uint32_t *map = mmap(0, SOC_REGISTER_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, offset);

	close(fileDescriptor);

	return (volatile uint32_t *)map + ((SOC_REGISTER_GPIO_BASEADDRESS & ~mask) / 4); // /4 = uint32_t pointer

}

struct Register *NewRegister(enum PortRegister portRegister, int bitsPerRegister, int bitsPerPin, int size) {

	struct Register *result;

	if ((result = malloc(sizeof (struct Register))) == NULL) {
		return NULL;
	}

	result->PortRegister = portRegister;
	result->BitsPerPin = bitsPerPin;
	//result->BitsPerRegister = bitsPerRegister;
	result->PinsPerRegister = (SOC_REGISTER_BYTE_PER_REGISTER * 8) / result->BitsPerPin;
	result->PinsPerPort = SOC_REGISTER_BYTE_PER_REGISTER * size * result->PinsPerRegister;

	return result;

}

void WriteRegister(struct Register *reg, enum Pins pin, int resetMask, int value) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / 4) + registerOffset;

	int val;

	val = *(mappedMemory + offset); // debug
	*(mappedMemory + offset) &= ~(resetMask << shift);
	val = *(mappedMemory + offset); // debug
	*(mappedMemory + offset) |= (value << shift);
	val = *(mappedMemory + offset); // debug


}

int ReadRegister(struct Register *reg, enum Pins pin) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / 4) + registerOffset;

	int pinValue;

	pinValue = *(mappedMemory + offset); // debug	
	pinValue = (*(mappedMemory + offset) & (1 << shift)) > 0;

	return pinValue;

}

int ReadPinValue(enum Pins pin) {
	struct Register *configurationRegister = newRegister(PortRegisterData, 32, 1, 1);
	int pinValue = ReadRegister(configurationRegister, pin);
	free(configurationRegister);
	return pinValue;
}

int digitalRead(enum Pins pin)
{
	return ReadPinValue(pin);
}

void digitalWrite(enum Pins pin, int value)
{
	WritePinValue(pin, value);
}

void WritePinValue(enum Pins pin, int value) {
	struct Register *configurationRegister = newRegister(PortRegisterData, 32, 1, 1);
	WriteRegister(configurationRegister, pin, 1, value);
	free(configurationRegister);
}

void ConfigurePinDirection(enum Pins pin, enum PinFunction pinFunction) {
	struct Register *configurationRegister = newRegister(PortRegisterFunction, 32, 4, 4);
	WriteRegister(configurationRegister, pin, 0b111, pinFunction);
	free(configurationRegister);
}

void ConfigurePinPullMode(enum Pins pin, enum PinPullMode pullMode) {
	struct Register *configurationRegister = newRegister(PortRegisterPullMode, 32, 2, 2);
	WriteRegister(configurationRegister, pin, 0b11, pullMode);
	free(configurationRegister);
}

struct InOut *newInputOutput(enum Pins pin, enum PinFunction pinFunction, enum PinPullMode pullMode) {

	struct InOut *result;
	if ((result = malloc(sizeof (struct InOut))) == NULL) {
		return NULL;
	}

	ConfigurePinDirection(pin, pinFunction);
	ConfigurePinPullMode(pin, pullMode);

	result->Function = pinFunction;
	result->Pin = pin;
	result->value = ReadPinValue(pin);

	return result;

}

struct InOut *newInput(enum Pins pin, enum PinPullMode pullMode) {
	return newInputOutput(pin, PinFunctionInput, pullMode);
}

struct InOut *newOutput(enum Pins pin) {
	return newInputOutput(pin, PinFunctionOutput, PinPullModeNone);
}


void RegisterTest() {

	int value;

	mappedMemory = openMemory();
	if (mappedMemory == NULL)
		return;


	ConfigurePinDirection(PH02, PinFunctionInput);
	ConfigurePinPullMode(PH02, PinPullModeUp);

	ConfigurePinDirection(PH20, PinFunctionInput);
	ConfigurePinPullMode(PH20, PinPullModeUp);


	ConfigurePinDirection(PIN23, PinFunctionOutput);
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 1);
	value = ReadPinValue(PIN23);
	WritePinValue(PIN23, 0);
	value = ReadPinValue(PIN23);

	// onboard LED - first echo gpio > /sys/class/leds/green\:ph24\:led1/trigger

	ConfigurePinDirection(PH24, PinFunctionOutput);
	WritePinValue(PH24, 0);
	value = ReadPinValue(PH24);
	WritePinValue(PH24, 1);
	value = ReadPinValue(PH24);
	WritePinValue(PH24, 0);
	value = ReadPinValue(PH24);




	// should be 1
	value = ReadPinValue(PH02);
	value = ReadPinValue(PH20);

	ConfigurePinPullMode(PH02, PinPullModeDown);
	ConfigurePinPullMode(PH20, PinPullModeDown);

	// should be 0
	value = ReadPinValue(PH02);
	value = ReadPinValue(PH20);

	ConfigurePinPullMode(PH02, PinPullModeUp);
	ConfigurePinPullMode(PH20, PinPullModeUp);

	// should be 1
	value = ReadPinValue(PH02);
	value = ReadPinValue(PH20);


}

/*
int main(int argc, char **argv) {

	RegisterTest();
	
}
 */

