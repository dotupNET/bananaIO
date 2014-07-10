#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "Register.h"

struct Register *NewRegister(volatile uint32_t *mappedMemory, int portRegister, int registerCount, int bitsPerPin) {

	struct Register *result;

	if ((result = malloc(sizeof (struct Register))) == NULL) {
		return NULL;
	}

	result->PortRegister = portRegister;
	result->BitsPerPin = bitsPerPin;
	result->PinsPerRegister = (SOC_REGISTER_BYTE_PER_REGISTER * 8) / result->BitsPerPin;
	result->PinsPerPort = SOC_REGISTER_BLOCKSIZE * registerCount * result->PinsPerRegister;

	result->mappedMemory = mappedMemory;
	
	return result;

}

void WriteRegister(struct Register *reg, int pin, int resetMask, int value) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / SOC_REGISTER_BLOCKSIZE) + registerOffset;

	int val;

	val = *(reg->mappedMemory + offset); // debug
	*(reg->mappedMemory + offset) &= ~(resetMask << shift);
	val = *(reg->mappedMemory + offset); // debug
	*(reg->mappedMemory + offset) |= (value << shift);
	val = *(reg->mappedMemory + offset); // debug


}

void SetRegisterBit(struct Register *reg, int pin)
{
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / SOC_REGISTER_BLOCKSIZE) + registerOffset;

	*(reg->mappedMemory + offset) = (1 << shift);
}

int ReadRegister(struct Register *reg, int pin) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / SOC_REGISTER_BLOCKSIZE) + registerOffset;

	int pinValue;

	pinValue = *(reg->mappedMemory + offset); // debug	
	pinValue = (*(reg->mappedMemory + offset) & (1 << shift)) > 0;

	return pinValue;

}


/*

struct Register *NewRegister(volatile uint32_t *mappedMemory, int portRegister, int portOffset, int bytePerRegister, int bitsPerPin, int size) {

	struct Register *result;

	if ((result = malloc(sizeof (struct Register))) == NULL) {
		return NULL;
	}

	result->PortOffset = portOffset;
	result->PortRegister = portRegister;
	result->BitsPerPin = bitsPerPin;
	//result->BitsPerRegister = bitsPerRegister;
	result->PinsPerRegister = (bytePerRegister * 8) / result->BitsPerPin;
	result->PinsPerPort = bytePerRegister * size * result->PinsPerRegister;

	result->mappedMemory = mappedMemory;
	
	return result;

}

void WriteRegister(struct Register *reg, int pin, int resetMask, int value) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * reg->PortOffset; // (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / 4) + registerOffset;

	int val;

	val = *(reg->mappedMemory + offset); // debug
	*(reg->mappedMemory + offset) &= ~(resetMask << shift);
	val = *(reg->mappedMemory + offset); // debug
	*(reg->mappedMemory + offset) |= (value << shift);
	val = *(reg->mappedMemory + offset); // debug


}

int ReadRegister(struct Register *reg, int pin) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * reg->PortOffset; // (SOC_REGISTER_PORT_SIZE / SOC_REGISTER_BYTE_PER_REGISTER); // debug
	int registerOffset = pin % reg->PinsPerPort / reg->PinsPerRegister; // debug
	int offset = portOffset + (reg->PortRegister / 4) + registerOffset;

	int pinValue;

	pinValue = *(reg->mappedMemory + offset); // debug	
	pinValue = (*(reg->mappedMemory + offset) & (1 << shift)) > 0;

	return pinValue;

}
 
 * 
 *  */