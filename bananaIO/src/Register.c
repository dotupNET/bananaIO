#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "RegisterStruct.h"
#include "Register.h"

struct Register *NewRegister(volatile uint32_t *mappedMemory, int registerNumber, int registerCount, int bitsPerPin) {

	struct Register *result;

	if ((result = malloc(sizeof (struct Register))) == NULL) {
		return NULL;
	}

	result->RegisterNumber = registerNumber;
	result->BitsPerPin = bitsPerPin;
	result->PinsPerRegister = (SOC_REGISTER_BYTE_PER_REGISTER * 8) / result->BitsPerPin;
	result->mappedMemory = mappedMemory;

	return result;

}

void WriteRegister(struct Register *reg, int pin, int resetMask, int value) {

	int shift = GetPinRegisterShift(reg, pin);
	int offset = GetPinRegisterOffset(reg, pin);
	
	if (resetMask == -1)
		*(reg->mappedMemory + offset) = (value << shift); // just set value into address. Raspi Set Register fails on |= !?
	else {
		*(reg->mappedMemory + offset) &= ~(resetMask << shift); // mask
		*(reg->mappedMemory + offset) |= (value << shift); // and set
	}

}

int ReadRegister(struct Register *reg, int pin) {

	int shift = GetPinRegisterShift(reg, pin);
	int offset = GetPinRegisterOffset(reg, pin);

	int pinValue = (*(reg->mappedMemory + offset) & (1 << shift)) > 0;

	return pinValue;
}

int GetPinRegisterShift(struct Register *reg, int pin) {
	return (pin % reg->PinsPerRegister) * reg->BitsPerPin;
}

int GetPinRegisterOffset(struct Register *reg, int pin) {

	int port = pin / SOC_REGISTER_PINS_PER_PORT;
	int portOffset = port * SOC_REGISTER_PORT_SIZE;
	int registerOffset = (pin - (SOC_REGISTER_PINS_PER_PORT * port)) / reg->PinsPerRegister * SOC_REGISTER_BYTE_PER_REGISTER;
	int offset = portOffset + registerOffset + (reg->RegisterNumber*SOC_REGISTER_BYTE_PER_REGISTER);

	return offset / 4; // offset is in byte, we've uint32_t pointer

}
