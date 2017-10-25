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


#ifndef ODOM_H
#define ODOM_H
#include <inttypes.h>

void reset_odom();
void update_odom(int16_t odom_r, int16_t odol_l);
int16_t get_odom_x();
int16_t get_odom_y();
int16_t get_odom_phi();


#endif
