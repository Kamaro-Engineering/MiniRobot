/*
 * Copyright 2017 <Lennart Nachtigall, Friedolin Gröger> <firesurfer127@gmail.com, gfrodo@gmx.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include <avr/io.h>
#include "adc.h"

void adc_init()
{
    // die Versorgungsspannung AVcc als Referenz wählen:
    ADMUX = (1<<REFS0);    
    // Enable und Prescaler 128 -> 156kHz bei 20Mhz
    ADCSRA = _BV(ADEN) | _BV(ADPS2)| _BV(ADPS0)| _BV(ADPS1);
    // Dummy readout
    adc_value(0);
}

uint16_t adc_value(uint8_t channel)
{
    uint16_t value = 0;
    for (uint8_t i = 0; i < 4; ++i) {
        ADMUX = (1<<REFS0) | (channel & 0xF);

        //Start conversion
        ADCSRA |= _BV(ADSC);

        // wait until converstion completed
        while (ADCSRA & _BV(ADSC)) {}

        // get converted value
        value += ADCW;
        //return ADCW;
    }
    return value / 4;
}

