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


#ifndef MOTOR_H
#define MOTOR_H
#include <inttypes.h>

void motor_init();

void set_motor_enable(uint8_t enable);
void set_motor_enable_r(uint8_t enable);
void set_motor_enable_l(uint8_t enable);
void motor_speed_l(int16_t speed);
void motor_speed_r(int16_t speed);
int16_t get_odom_r();
int16_t get_odom_l();




#endif

