#include <stdint.h>
#include <unistd.h>

#include "Gpio.h"
#include "SocConfiguration.h"
#include "SocFramework.h"

#define		PIN_CLOCK		PIN12 // Serial-Clock
#define		PIN_MOSI			PIN18 // Master-Out-Slave-In
#define		PIN_MISO			PIN16 // Master-In-Slave-Out
#define		PIN_CS			PIN22 // Chip-Select



#define		MCP23S17_CONTROL_FIXED				0b01000000
#define		MCP23S17_CONTROL_WRITE				0
#define		MCP23S17_CONTROL_READ				1

#define		MCP23S17_REGISTER_PORT_A_DIRECTION			0x00
#define		MCP23S17_REGISTER_PORT_B_DIRECTION			0x01

#define		MCP23S17_REGISTER_PORT_A_INTERRUPT			0x04
#define		MCP23S17_REGISTER_PORT_B_INTERRUPT			0x05

#define		MCP23S17_REGISTER_PORT_A_PULLMODE			0x0C
#define		MCP23S17_REGISTER_PORT_B_PULLMODE			0x0D

#define		MCP23S17_REGISTER_PORT_A						0x12
#define		MCP23S17_REGISTER_PORT_B						0x13

#define		MCP23S17_PORT_WRITE								0
#define		MCP23S17_PORT_READ								1

#define		MCP23S17_PORT_PULLNONE							0
#define		MCP23S17_PORT_PULLUP								1

enum PortDirection {
	PortDirectionOutput = 0,
	PortDirectionInput = 1
};

void SpiSendByte(int value) {
	int bitNumber = 0;
	for (bitNumber; bitNumber < 8; bitNumber++) {

		// send bit (high to low)
		uint8_t x = ((value & 0x80) == 0x80);
		digitalWrite(PIN_MOSI, x);

		value <<= 1; // next bit. << because high to low

		// high low on clock
		digitalWrite(PIN_CLOCK, HIGH);
		digitalWrite(PIN_CLOCK, LOW);


	}

}

void SpiWrite(int address, int reg, int value) {

	uint8_t control = MCP23S17_CONTROL_FIXED | address;

	//	start signal
	digitalWrite(PIN_CS, LOW);

	// send data ( control + register + value )
	SpiSendByte(control);
	SpiSendByte(reg);
	SpiSendByte(value);

	// end signal
	digitalWrite(PIN_CS, HIGH);

}

void SpiConfigure(int address, enum PortDirection portDirection) {

	digitalWrite(PIN_CS, HIGH);
	digitalWrite(PIN_CLOCK, LOW);

	SpiWrite(address, MCP23S17_REGISTER_PORT_A_DIRECTION, portDirection);
}

void TestSpi() {
		
	NewOutput(PIN_CLOCK);
	NewOutput(PIN_MOSI);
	NewOutput(PIN_MISO);
	NewOutput(PIN_CS);

	SpiConfigure(0, PortDirectionOutput);

	int loopIndex = 0, value = 1;
	for (loopIndex; loopIndex < 9; loopIndex++) {
		SpiWrite(0, MCP23S17_REGISTER_PORT_A, value);
		value = value << 1;
		sleep(1);
	}

}
