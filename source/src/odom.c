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


#include <math.h>
#include "odom.h"

int16_t odom_r_last = 0;
int16_t odom_l_last = 0;
int16_t odom_x = 0;
int16_t odom_y = 0;
int16_t odom_phi = 0;
#define RADPERTICK (M_PI/400/2)
#define TICKS180 (M_PI/RADPERTICK)

void update_odom(int16_t odom_r, int16_t odom_l)
{
    int16_t diff_r = odom_r - odom_r_last;
    int16_t diff_l = odom_l - odom_l_last;
    odom_r_last = odom_r;
    odom_l_last = odom_l;
    int16_t dist = diff_r + diff_l;
    int16_t angle = diff_r - diff_l;
    odom_x += cos(odom_phi + angle / 2) * 0.5f * dist;
    odom_y += sin(odom_phi + angle / 2) * 0.5f * dist;
    odom_phi += angle;
    if (angle > TICKS180)angle -= 2 * TICKS180;
    if (angle < -TICKS180)angle += 2 * TICKS180;
}

void reset_odom(int16_t odom_r, int16_t odom_l)
{
    odom_x = 0;
    odom_y = 0;
    odom_phi = 0;
    odom_r_last = odom_r;
    odom_l_last = odom_l;
}
int16_t get_odom_x()
{
    return odom_x;
}
int16_t get_odom_y()
{
    return odom_y;
}
int16_t get_odom_phi()
{
    return odom_phi;
}
