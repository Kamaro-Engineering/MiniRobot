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


#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define UART_BAUD_RATE 500000

#include "uart_parser.h"
#include "motor.h"
#include "odom.h"
#include "i2cmaster.h"
#include "adc.h"
#include "pwm.h"
#include "pins.h"

struct {
    uint8_t send_battery_voltage : 1;
    uint8_t send_ultra_sonic_data : 1;
    uint8_t send_motor_currents : 1;
    uint8_t send_encoders : 1;
    uint8_t send_odometry : 1;
} flags;


void handle_commands(uint8_t command, uint16_t data)
{
    switch (command) {
    case 0x01:
        set_motor_enable(data);
        break;
    case 0x02:
        motor_speed_l(data);
        set_motor_enable_l(data?1:0);
        break;
    case 0x03:
        motor_speed_r(data);
        set_motor_enable_r(data?1:0);
        break;
    case 0x04://set LED x
        if (data == 0)
            LED_ON(LED1_bm);
        if (data == 1)
            LED_ON(LED2_bm);
        if (data == 2)
            LED_ON(LED3_bm);
        break;
    case 0x05://clear LED x
        if (data == 0)
            LED_OFF(LED1_bm);
        if (data == 1)
            LED_OFF(LED2_bm);
        if (data == 2)
            LED_OFF(LED3_bm);
        break;
    case 0x06://Set fan PWM
        set_PWM(data);
        break;
    case 0x07://Set external PWM
        set_servo(data);
        break;
    case 0x08:
        flags.send_ultra_sonic_data = data;
        break;
    case 0x09:
        flags.send_battery_voltage = data;
        break;
    case 0x0A:
        flags.send_motor_currents = data;
        break;
    case 0x0B:
        flags.send_encoders = data;
        break;
    case 0x0C:
        flags.send_odometry = data;
        break;

    }
}

int main(void)
{
    //enable UART
    uart_init(UART_BAUD_SELECT_DOUBLE_SPEED(UART_BAUD_RATE, F_CPU));
    //Init parser for uart commands
    init_parser();
    //register functions ptr for command handler
    set_command_handler(handle_commands);

    motor_init();
    adc_init();
    reset_odom();
    //i2c_init();
    PORTI2C = SCL_bm | SDA_bm; //Enable Pullups for I2C

    DDRIO = LED1_bm | LED2_bm | LED3_bm | PWM_bm | SERVO_bm; //Configure LEDs and PWM as outputs
    PORTIO = TASTER_bm; //activate pullup

    pwm_init();

    //enable interrupts
    sei();

    uart_puts("Hello world");

    int16_t encoder_r = 0;
    int16_t encoder_l = 0;
    uint8_t taster_pressed = 0;
    while (1) {
        encoder_r = get_odom_r();
        encoder_l = get_odom_l();
        update_odom(encoder_r, encoder_l);
        if (taster_pressed && !PRESSED(TASTER_bm)) {
            taster_pressed = 0;
            send_command(0x84, 1);
        }
        if (!taster_pressed && PRESSED(TASTER_bm)) {
            taster_pressed = 1;
            send_command(0x84, 0);
        }
        if (flags.send_battery_voltage) {
            uint16_t bat = adc_value(2);
            send_command(0x81,  bat);
        }
        if (flags.send_motor_currents) {
            uint16_t left = adc_value(0);
            uint16_t right = adc_value(1);

            send_command(0x82, left);
            send_command(0x83, right);
        }
        if (flags.send_ultra_sonic_data) {
            uint16_t ultra_sonic = adc_value(3);
            send_command(0x80, ultra_sonic);
        }
        if (flags.send_encoders) {
            send_command(0x85, encoder_r);
            send_command(0x86, encoder_l);
        }
        if (flags.send_odometry) {
            send_command(0x87, get_odom_x());
            send_command(0x88, get_odom_y());
            send_command(0x89, get_odom_phi());
        }
        _delay_ms(100);
        //LED_TGL(LED2_bm);
    }
    return 0;
}
