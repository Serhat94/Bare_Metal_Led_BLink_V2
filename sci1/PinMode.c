/*
 * PinMode.c
 *
 *  Created on: 13 A�u 2024
 *      Author: SERHAT
 */

#include "PinMode.h"

void PinMode(Uint32 pinNumber, PinState state) {
    if (pinNumber <= 31)
    {
        // GPIO A i�lemleri
        if (state == PIN_HIGH) {
            GpioDataRegs.GPASET.all = 1 << pinNumber;
        }
        else {
            GpioDataRegs.GPACLEAR.all = 1 << pinNumber;
        }
    }
    else if (pinNumber <= 58) {
        // GPIO B i�lemleri
        Uint32 pin = pinNumber - 32;
        if (state == PIN_HIGH) {
            GpioDataRegs.GPBSET.all = 1 << pin;
        }
        else {
            GpioDataRegs.GPBCLEAR.all = 1 << pin;
        }
    }
    else if (pinNumber >= 64 && pinNumber <= 79) {
        // Analog I/O i�lemleri
        Uint32 pin = pinNumber - 64;
        if (state == PIN_HIGH) {
            GpioDataRegs.AIOSET.all = 1 << pin;
        }
        else {
            GpioDataRegs.AIOCLEAR.all = 1 << pin;
        }
    }
}


