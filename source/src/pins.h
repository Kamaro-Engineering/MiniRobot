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


#ifndef PINS_H
#define PINS_H

#define LED1_bp   3
#define LED2_bp   4
#define LED3_bp   5
#define PWM_bp    2
#define SERVO_bp  1
#define TASTER_bp 0

#define LED1_bm   (1<<LED1_bp)
#define LED2_bm   (1<<LED2_bp)
#define LED3_bm   (1<<LED3_bp)
#define PWM_bm    (1<<PWM_bp)
#define SERVO_bm  (1<<SERVO_bp)
#define TASTER_bm (1<<TASTER_bp)

#define PORTIO PORTB
#define PINIO  PINB
#define DDRIO  DDRB

#define LED_ON(led) (PORTIO|=led)
#define LED_OFF(led) (PORTIO&=~(led))
#define LED_TGL(led) (PINIO=led)

#define PRESSED(t) (PINIO&t)

#define SDA_bp    4
#define SCL_bp    5

#define SDA_bm    (1<<SDA_bp)
#define SCL_bm    (1<<SCL_bp)

#define PORTI2C PORTC


#endif
