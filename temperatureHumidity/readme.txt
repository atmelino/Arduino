
Temperature and Humidity Sensor Network - Arduino
=================================================

Instructions:

Download the PDE sketch from the Arduino folder and upload it to the Arduino.

Connect the hardware components as shown in the wiki pages.

Ethernet version
----------------

You can verify that the hardware works with a telnet session (see wiki).

connect to the Arduino: 

telnet 192.168.1.177

and type t to get temperature, h to get humidity



To test the plotting in a web browser:

Run the script "read_data_sim.sh" and go to the index.html web page in a web browser.
Note: The page has to be loaded from a web server! Just loading it from a file system will not work.

You can install a web server on your PC by installing a LAMP stack and placing the arduinoTempHumid/html folder under your local document root.

Once you have established that the plotting works, you can retrieve actual data from the Arduino. Run the script "telnet_to_file.sh" to read data from the Arduino and to write them to a file. Also, run the script "read_data_loop.sh" to convert the data to JSON format which is used in the pltting web page.



Caution:

If you are going to have this running for many days, the software will write to files over and over. This could cause unnecessary wear on the hard disk. To prevent this, you can copy the folder to a RAM disk and run the software from the RAM disk. Under Ubuntu, a RAM disk already exists at /dev/shm.

The only caution is that you would lose all of your data if the power goes off, Therefore, it is recommended to copy the data file periodically from the RAM disk to the hard disk. 





USB version
-----------

the device /dev/USBtty0 is created when the Arduino is plugged in. The command cat /dev/ttyUSB0 will not work until after the Arduino IDE has been started and the serial monitor window has been opened. 


