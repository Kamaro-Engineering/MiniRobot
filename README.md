# MiniRobot
All construction files for a mini robot platform.

This mini robot platform was developed as an entry project for the [KAMARO](https://kamaro-engineering.de/) student group. 

![robot](https://github.com/firesurfer/MiniRobot/blob/master/doc/DSC_0270.JPG)
(The display is not part of this project but by chance the drill holes fitted)



# CAD / Mechanics

At the moment we only provide the stl file of the robot base. On request I can provide the Free Cad file too. 

For assembly you need to 3D print the base. We did this on an ultimaker 2+.
The stepper motors we used are standard NEMA12 steppers in combination with standard rc car wheels. (Diameter will be added after I measured it)

# Circuit / Layout

The circuit schematics and layouts were done in the EAGLE layout software. The layout is partly in THT and SMD. All ICs apart from the FTDI (which is only available in SMD) are in THT, the resistors and capacitors are mostly in SMD (0805). As they are in 0805 also beginners will be able to solder them with a bit of training. (It sounds hardware that it is ;) 

The only part you have to adjust are the resistor values for the current limit of the L297. Adapt them to your maximum allowed motor current. (R7,R8 and R3,R4)

The four drill holes in the middle can be used in order to mount a raspberry pi 2 (or 3).

# Software

We provide a fully functional firmware for the Atmega48 (or 88). See the readme in the source subfolder for the serial communication protocol. (It's really simple, just 4 bytes). In most case the only thing you might have to adapt are the constants of the odomotry which is calculated with the amount of steps done by the steppers. For example in case you use a stepper with smaller steps or larger wheels you will have to adapt these constants.

See the [software readme](source/README.md)!

![robot1](https://github.com/firesurfer/MiniRobot/blob/master/doc/DSC_0271.JPG)

