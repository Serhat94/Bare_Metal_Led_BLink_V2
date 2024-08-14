/*
 * PinMode.h
 *
 *  Created on: 13 Aðu 2024
 *      Author: SERHAT
 */

#ifndef PINMODE_H_
#define PINMODE_H_
#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions
#include "F2806x_Device.h"      // F2806x Headerfile Include File
#include "F2806x_Examples.h"    // F2806x Examples Include File

typedef enum {
    PIN_LOW = 0,
    PIN_HIGH = 1
} PinState;
extern void PinMode(Uint32 pinNumber, PinState state);

#endif /* PINMODE_H_ */
