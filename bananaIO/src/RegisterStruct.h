/* 
 * File:   RegisterStruct.h
 * Author: pullrich
 *
 * Created on 11. Juli 2014, 09:50
 */

#ifndef REGISTERSTRUCT_H
#define	REGISTERSTRUCT_H

#ifdef	__cplusplus
extern "C" {
#endif


struct Register {
	// global settings
	volatile uint32_t *mappedMemory;
	int RegisterNumber;
	int PinsPerRegister;
	int BitsPerPin;
};


#ifdef	__cplusplus
}
#endif

#endif	/* REGISTERSTRUCT_H */

