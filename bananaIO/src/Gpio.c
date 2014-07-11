#include "Gpio.h"

struct GpioPin *NewInputOutput(int pin, int pinFunction, int pullMode) {

	struct GpioPin *result;
	if ((result = malloc(sizeof (struct GpioPin))) == NULL) {
		return NULL;
	}

	ConfigurePinDirection(pin, pinFunction);
	ConfigurePinPullMode(pin, pullMode);

	result->Function = pinFunction;
	result->Pin = pin;
	result->value = ReadPinValue(pin);

	return result;

}

struct GpioPin *NewInput(int pin, int pullMode) {
	return NewInputOutput(pin, PinFunctionInput, pullMode);
}

struct GpioPin *NewOutput(int pin) {
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
		WriteRegister(CurrentSoc.Register.GpioClear, pin, GPIO_PIN_CLEAR_MASK, GPIO_PIN_CLEAR_VALUE);
	else
		WriteRegister(CurrentSoc.Register.GpioSet, pin, GPIO_PIN_SET_MASK, GPIO_PIN_SET_VALUE);
}

int digitalRead(int pin)
{
	return ReadPinValue(pin);
}

void digitalWrite(int pin, int value)
{
	WritePinValue(pin, value);
}
