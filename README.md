# SensESP-blackwater-tank-sensor-array

This code is designed for use with a XKC-Y25-V sensor, or more accurately, 5 of them placed on the outside of the balck water tank at 20% intervals.  
If you connect only to the Power/ground/data wire (leave the 4th wire disconnected), then the sensors will read 0 until the water level covers them, then they will read 1.
The "tanks.blackwater.1.currentlevel" field will give you the current level based on the combination of sensors.  The others are available for Diagnostics at the moment
