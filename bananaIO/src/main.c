/* 
 * File:   main.c
 * Author: pullrich
 *
 * Created on 7. Juli 2014, 11:19
 */

#include <stdio.h>
#include <stdlib.h>

#include "SocConfiguration.h"
#include "SocFramework.h"

#include "Gpio.h"


int main(int argc, char** argv) {

	// Initialize A20 or BCM2835
	InitializePi();
			  
	TestPi();

	TestSpi();
	
	// Initialize GPIO
	//InitializeGpio();


/*
	InOut *io1 = NewInput(Pins.PIN12);
	int x = io1->value;

	Test();
*/
/*
	return (EXIT_SUCCESS);
	RegisterTest();
	return (EXIT_SUCCESS);
*/
}

