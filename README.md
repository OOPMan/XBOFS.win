# Razer Atrox WinUSB VigEm Feeder
This tool is a simple console application which processes WinUSB input from the Razer Atrox controller through 
to a VigEm Virtual XB360 gamepad.


## Interface
The application provides a simple PDCurses based text-mode UI. When running the UI appears as follows:

```
WinUSB Status: CONNECTED
VigEm Status: CONNECTED

Press:

* W to reset WinUSB connection to Razer Atrox
* V to reset VigEm XB360 controller
* Q to exit 
```

### WinUSB Status
* **DISCONNECTED**: The Razer Atrox is not connected or has disconnected
* **INIT**: The Razer Atrox is connected and the INIT packet has been sent
* **CONNECTED**: The Razer Atrox is connected and data from it has been received

### VigEm Status:
* **DISCONNECTED**: VigEm Virtual XB360 controller is disconnected
* **CONNECTED**: VigEm Virtual XB360 controller is connected


## Operation
Upon starting the application will attempt to establish a connection with the Razer Atrox via WinUSB. Once a connection
has been established it will create a VigEm XB360 controller and begin processing input through. 