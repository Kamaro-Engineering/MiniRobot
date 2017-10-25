/*
 * Copyright 2016 <Lennart Nachtigall, Friedolin Gröger> <firesurfer127@gmail.com, gfrodo@gmx.de>
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
#include <avr/interrupt.h>
#include "motor.h"

#define PIN_R_ENABLE 2
#define PIN_R_CLOCK  3
#define PIN_R_DIR    4
#define PIN_L_ENABLE 5
#define PIN_L_CLOCK  6
#define PIN_L_DIR    7

#define PORTMOT PORTD
#define PINMOT  PIND
#define DDRMOT  DDRD

// To invert direction if one motor is going backwards
#define DIR_INV_R 0
#define DIR_INV_L 0


uint16_t count_r = 0;
uint16_t count_l = 0;

int16_t speed_r = 0;
int16_t speed_l = 0;

volatile int16_t odom_r = 0;
volatile int16_t odom_l = 0;

void set_motor_enable(uint8_t enable)
{
    if (enable)
        PORTMOT |= (1 << PIN_R_ENABLE) | (1 << PIN_L_ENABLE);
    else
        PORTMOT &= ~(1 << PIN_R_ENABLE) & ~(1 << PIN_L_ENABLE);
}
void set_motor_enable_r(uint8_t enable)
{
    if (enable)
        PORTMOT |= (1 << PIN_R_ENABLE) ;
    else
        PORTMOT &= ~(1 << PIN_R_ENABLE) ;
}
void set_motor_enable_l(uint8_t enable)
{
    if (enable)
        PORTMOT |= (1 << PIN_L_ENABLE);
    else
        PORTMOT &= ~(1 << PIN_L_ENABLE);
}

void motor_init()
{
    TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64
    TIMSK0 = (1 << TOIE0);            // Overflow interrupt enable
    //TCCR2B = (1<<CS22);               // Prescaler 64
    //TIMSK2 = (1<<TOIE2);              // Overflow interrupt enable
    DDRMOT |= (1 << PIN_R_ENABLE) | (1 << PIN_R_CLOCK) | (1 << PIN_R_DIR)
              | (1 << PIN_L_ENABLE) | (1 << PIN_L_CLOCK) | (1 << PIN_L_DIR);
    //PORTMOT |= (1 << PIN_R_ENABLE) | (1 << PIN_L_ENABLE);
}

void motor_speed_l(int16_t speed)
{
    speed_l = speed;
}
void motor_speed_r(int16_t speed)
{
    speed_r = speed;
}
int16_t get_odom_r()
{
    return odom_r;
}
int16_t get_odom_l()
{
    return odom_l;
}

ISR(TIMER0_OVF_vect)
{
    count_r += abs(speed_r);
    if (count_r & 0x8000) { //on "overflow"
        count_r &= 0x7FFF; //do the overflow
        if (speed_r > 0) {
            odom_r += 1; //count ticks
            if (DIR_INV_R) PORTMOT &= ~(1 << PIN_R_DIR); //set direction pin
            else PORTMOT |= (1 << PIN_R_DIR);
        } else {
            odom_r -= 1;
            if (DIR_INV_R) PORTMOT |= (1 << PIN_R_DIR);
            else PORTMOT &= ~(1 << PIN_R_DIR);
        }
        PINMOT = (1 << PIN_R_CLOCK); //toggle frequency pin
    }
    count_l += abs(speed_l);
    if (count_l & 0x8000) { //on "overflow"
        count_l &= 0x7FFF; //do the overflow
        if (speed_l > 0) {
            odom_l += 1; //count ticks
            if (DIR_INV_L) PORTMOT &= ~(1 << PIN_L_DIR); //set direction pin
            else PORTMOT |= (1 << PIN_L_DIR);
        } else {
            odom_l -= 1;
            if (DIR_INV_L) PORTMOT |= (1 << PIN_L_DIR);
            else PORTMOT &= ~(1 << PIN_L_DIR);
        }
        PINMOT = (1 << PIN_L_CLOCK); //toggle frequency pin
    }
}

