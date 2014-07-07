
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


#define		PAGESIZE					4096
#define		GPIO_BASE				0x01C20800			// A20 User Manual 2013-03-22.pdf

#define		BYTE_PER_REGISTER		4						// All register are 32 Bit
#define		PORT_SIZE				36						// Number of rows per port to calculate with uint32_t pointer

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
	CON3_P03 = 149, PB21 = 149,
	CON3_P05 = 148, PB20 = 148,
	CON3_P07 = 1027, PI03 = 1027,
	CON3_P08 = 896, PH00 = 896,
	CON3_P10 = 897, PH01 = 897,
	CON3_P11 = 1043, PI19 = 1043,
	CON3_P12 = 898, PH02 = 898,
	CON3_P13 = 1042, PI18 = 1042,
	CON3_P15 = 1041, PI17 = 1041,
	CON3_P16 = 916, PH20 = 916,
	CON3_P18 = 917, PH21 = 917,
	CON3_P19 = 1036, PI12 = 1036,
	CON3_P21 = 1037, PI13 = 1037,
	CON3_P22 = 1040, PI16 = 1040,
	CON3_P23 = 1035, PI11 = 1035,
	CON3_P24 = 1034, PI10 = 1034,
	CON3_P26 = 1038, PI14 = 1038
};

struct Register {
	// global settings
	enum PortRegister PortRegister;
	int PinsPerPort;
	//int BitsPerRegister;
	int PinsPerRegister;
	int BitsPerPin;
};

volatile uint32_t *mappedMemory;

volatile uint32_t *openMemory() {
	int fileDescriptor;

	if (!(fileDescriptor = open("/dev/mem", O_RDWR))) {
		return NULL;
	}

	uint32_t mask = (~(PAGESIZE - 1));
	uint32_t offset = GPIO_BASE & mask;
	uint32_t *map = mmap(0, PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, offset);

	close(fileDescriptor);

	return (volatile uint32_t *)map + ((GPIO_BASE & ~mask) / 4); // /4 = uint32_t pointer

}

struct Register *newRegister(enum PortRegister portRegister, int bitsPerRegister, int bitsPerPin, int size) {

	struct Register *result;

	if ((result = malloc(sizeof (struct Register))) == NULL) {
		return NULL;
	}

	result->PortRegister = portRegister;
	result->BitsPerPin = bitsPerPin;
	//result->BitsPerRegister = bitsPerRegister;
	result->PinsPerRegister = (BYTE_PER_REGISTER * 8) / result->BitsPerPin;
	result->PinsPerPort = BYTE_PER_REGISTER * size * result->PinsPerRegister;

	return result;

}

void WriteRegister(struct Register *reg, enum Pins pin, int resetMask, int value) {
	int shift = (pin % reg->PinsPerRegister) * reg->BitsPerPin;
	int port = pin / reg->PinsPerPort; // debug
	int portOffset = port * (PORT_SIZE / BYTE_PER_REGISTER); // debug
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
	int portOffset = port * (PORT_SIZE / BYTE_PER_REGISTER); // debug
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

void ConfigurePinDirection(enum Pins pin, enum PinDirection pinDirection) {
	struct Register *configurationRegister = newRegister(PortRegisterConfiguration, 32, 4, 4);
	WriteRegister(configurationRegister, pin, 0b111, pinDirection);
	free(configurationRegister);
}

void ConfigurePinPullMode(enum Pins pin, enum PinPullMode pullMode) {
	struct Register *configurationRegister = newRegister(PortRegisterPullMode, 32, 2, 2);
	WriteRegister(configurationRegister, pin, 0b11, pullMode);
	free(configurationRegister);
}

void RegisterTest() {

	mappedMemory = openMemory();
	if (mappedMemory == NULL)
		return;


	ConfigurePinDirection(PH02, PinDirectionInput);
	ConfigurePinPullMode(PH02, PinPullModeUp);

	ConfigurePinDirection(PH20, PinDirectionInput);
	ConfigurePinPullMode(PH20, PinPullModeUp);

	int value;

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


