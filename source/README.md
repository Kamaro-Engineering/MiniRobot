# MiniRobot - Embeddedcode

This code is written for an Atmega48 (or 88) in C. It can be compiled with avr-gcc.
On Linux you need the following packages:

```
sudo apt install gcc-avr avr-libc  avrdude make
```
In order to build the code, open a terminal, step into the src folder and type `make`.
Via `make program` you can program the controller with a avr-isp mk II programmer. For other programmers have a look at the makefile.

## Communicationprotocol

The robot supports the following commands via a virtual comport. (500000 BAUD)

Format:
STARTBYTE | Command | Highbyte-Data | Lowbyte-Data |

The STARTBYTE matches the ASCII '#'

Commands that can be sent to the robot.

| Command   | Data          | Description     |
| --------- | ------------- | --------------- |
| 0x01      | enable        | Enables/Disables motors  |
| 0x02      | speed left    | Set velocity or speed for the left side  (signed integer!)|
| 0x03      | speed right   | Set velocity or speed for the right side (signed integer!) |
| 0x04      | led number    | Enable LED x |
| 0x05      | led number    | Disable LED x |
| 0x06      | PWM           | Set pwm freq of fan  |
| 0x07      | PWM           | Set pwm freq of external pin | 
| 0x08      | enable        | Enable/Disables sending of ultrasonic sensor  data |
| 0x09      | enable        | Enable/Disables sending of battery voltage |
| 0x0A      | enable        | Enable/Disables sending of motor currents |
| 0x0B      | enable        | Enable/Disables sending of Encoder right and left | 
| 0x0C      | enable        | Enable/Disables sending of Odometry x,y and phi | 

Data that will be sent back from the robot.

| Command      | Data          | Description     |
| ------------ | ------------- | --------------- |
| 0x80         | ultra sonic sensor distance in cm | ultra sonic sensor |
| 0x81         | Battery voltage in mV |  |
| 0x82         | Motor current left in mA | |
| 0x83         | Motor current right in mA |  |
| 0x84         | Taster pressed |  |
| 0x85         | Encoder right |  |
| 0x86         | Encoder left |  |
| 0x87         | Odometry x |  |
| 0x88         | Odometry y |  |
| 0x89         | Odometry phi |  |

