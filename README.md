# SensESP-blackwater-tank-sensor-array

This code is designed for use with a XKC-Y25-V sensor, or more accurately, 5 of them placed on the outside of the balck water tank at 20% intervals.  
If you connect only to the Power/ground/data wire (leave the 4th -Black- wire disconnected), then the sensors will read 0 until the water level covers them, then they will read 1.
The "tanks.blackwater.1.currentlevel" field will give you the current level based on the combination of sensors.  The others are available for Diagnostics at the moment

the sensors I bought are:
- [XKC-Y25-V](https://www.aliexpress.us/item/2251832778905166.html) also available on [Amazon](https://amzn.to/40CFGIb)

![Cover](https://github.com/Techstyleuk/SensESP-blackwater-tank-sensor-array/blob/main/BW-cover.jpg)

Video is available on YouTube: https://youtu.be/_G8A6kWUJCs

The files should replace the files of the same name in the template. locations are as follows:

src/main.cpp

platformio.ini

Comprehensive documentation for SensESP, including how to get started with your own project, is available at the [SensESP documentation site](https://signalk.org/SensESP/).
