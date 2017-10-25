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


#include "uart_parser.h"

static void (*m_command_handler)(uint8_t, uint16_t);

void init_parser()
{
    set_rx_handler(rx_handler);
}



void send_command(uint8_t command, uint16_t data)
{
    uart_putc('#');
    uart_putc(command);
    uart_putc(data >> 8);
    uart_putc(data);
}

void set_command_handler(void(*func)(uint8_t, uint16_t))
{
    m_command_handler = func;
}

void rx_handler(char c)
{
    static uint8_t buf[4];
    static uint8_t index = 0;

    switch (index) {
    case 0:
        if (c == '#')++index;
        break;
    case 1:
    case 2:
    case 3:
        buf[index] = c;
        ++index;
        if(index==4){
          m_command_handler(buf[1], buf[3] | (uint16_t)buf[2] << 8);
          index = 0;
        }
        break;
    default:
        index = 0;
    }
}
