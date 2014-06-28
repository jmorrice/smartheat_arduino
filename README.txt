Code to use an Arduino Uno as a wireless sensor node with the FigureEnergy database.

1). Add the two WiFly library files to your respective Arduino library folder.
2). Open SmartHeat_Arduino.ino (should open a sketch including all other .ino files).
3). At the top of the file change mySSID and myPassword to match your WiFi network.
4). Change any server settings or POST requests in the wifi.ino file.
5). Set the switch on the Wireless shield to USB and program the device.
6). Once done, set the switch to Micro and press the reset button.
7). The device should configure itself, connect to the network and then enter a sleep mode for 2 minutes before posting for the first time.

Note:
-you may need to change the MAC adress of the wifi module in the POST request to the server
-authentification currently only support WPA2 networks

Jonathan Morrice (jnsm1g10@ecs.soton.ac.uk) 28/12/13
