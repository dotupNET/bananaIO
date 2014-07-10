#include "Gpio.h"
#include "Register.h"
#include "SocFramework.h"

struct InOut *NewInputOutput(int pin, int pinFunction, int pullMode) {

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

struct InOut *NewInput(int pin, int pullMode) {
	return NewInputOutput(pin, PinFunctionInput, pullMode);
}

struct InOut *NewOutput(int pin) {
	return NewInputOutput(pin, PinFunctionOutput, PinPullModeNone);
}

void ConfigurePinDirection(int pin, int pinFunction) {
	WriteRegister(CurrentSoc.Register.GpioFunction, pin, 0b111, pinFunction);
}

void ConfigurePinPullMode(int pin, int pullMode) {
	WriteRegister(CurrentSoc.Register.GpioPullMode,pin,0b11,pullMode);
}

int ReadPinValue(int pin) {
	int pinValue = ReadRegister(CurrentSoc.Register.GpioValue, pin);
	return pinValue;
}

void WritePinValue(int pin, int value) {
	if(value == LOW)
		WriteRegister(CurrentSoc.Register.GpioClear, pin, 1, GPIO_PIN_CLEAR_VALUE);
	else
		WriteRegister(CurrentSoc.Register.GpioSet, pin, 1, GPIO_PIN_SET_VALUE);
}

int digitalRead(int pin)
{
	return ReadPinValue(pin);
}

void digitalWrite(int pin, int value)
{
	WritePinValue(pin, value);
}
