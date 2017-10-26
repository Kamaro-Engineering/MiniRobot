# MiniRobot
All construction files for a mini robot platform.

This mini robot platform was developed entry project for the [KAMARO](https://kamaro-engineering.de/) student group. 

I will provide pictures of the fully assembled robot soon.

# CAD / Mechanics

At the moment we only provide the stl file of the robot base. On request I can provide the Free Cad file too. 

For assembly you need to 3D print the base. We did this on an ultimaker 2+.
The stepper motors we used are standard NEMA12 steppers in combination with standard rc car wheels. (Diameter will be added after I measured it)

# Circuit / Layout

The circuit schematics and layouts were done in the EAGLE layout software. The layout is partly in THT and SMD. All ICs apart from the FTDI (which is only available in SMD) are in THT, the resistors and capacitors are mostly in SMD (0805). As they are in 0805 also beginners will be able to solder them with a bit of training. (It sounds hardware that it is ;) 

The only part you have to adjust are the resistor values for the current limit of the L297. Adapt them to your maximum allowed motor current. (R7,R8 and R3,R4)
