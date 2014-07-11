/* 
 * File:   GpioStruct.h
 * Author: pullrich
 *
 * Created on 11. Juli 2014, 09:51
 */

#ifndef GPIOSTRUCT_H
#define	GPIOSTRUCT_H

#ifdef	__cplusplus
extern "C" {
#endif

struct GpioPin {
	int Pin;
	int Function;
	int value;
};

#ifdef	__cplusplus
}
#endif

#endif	/* GPIOSTRUCT_H */

