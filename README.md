# Razer Atrox WinUSB VigEm Feeder
This tool is a simple console application which processes WinUSB input from the **Razer Atrox XBO** controller through 
to a VigEm Virtual XB360 gamepad. This allows you to use your **Razer Atrox XBO** in any game that supports a XB360 
controller. All 8 face buttons work without any need to install ancient, beta drivers and rewire buttons.


## Requirements

1. Windows 7 or newer
2. **Razer Atrox XBO**


## Installation

1. Head over to https://github.com/ViGEm/ViGEmBus/releases/ and download the latest VigEmBus installer
2. Install **VigEmBus** and reboot
3. Head over to https://zadig.akeo.ie and download **Zadig 2.4**
4. Head over to https://github.com/OOPMan/RazorAtroxWinUSBVigEmFeeder/releases and download the latest versions of 
  
   1. ``RazorAtroxWinUSBVigEmFeeder_x64.exe``
   2. ``razer_atrox_zadig_preset.cfg``

5. Plug in your **Razer Atrox XBO**
6. Head over to the *RazerAtroxWinUSBVigEmFeeder ZaDig guide* at https://imgur.com/a/F8XqFXx and follow the instructions
   there to install a WinUSB driver for your **Razer Atrox XBO**
7. If, for some reason, the ZaDig guide does not work for you, then you will need to do the following:

   1. Head over to https://github.com/OOPMan/RazorAtroxWinUSBVigEmFeeder/releases and download
      the latest ``Razer.Atrox.WinUSB.Driver.zip``
   2. Follow the instructions at http://jbcomp.com/disable-device-driver-signing-in-windows-10/ to disable the 
      requirement for signed device drivers
   3. Extract the contents of the ``Razer.Atrox.WinUSB.Driver.zip`` file somewhere and then open the 
      ``Razer Atrox WinUSB Drivers`` folder that was extracted
   4. Right-click on the file ``Razer\_Atrox\_Arcade\_Stick.inf`` and select *Install* from the menu
   5. You should get a message stating the driver was installed correctly
8. Run ``RazorAtroxWinUSBVigEmFeeder_x64.exe`` and wait for both status lines to state ``CONNECTED``. You may 
   see a pop-up notification about a new XB360 controller being detected. This is created by the tool using VigEmBus 
   and is a virtual controller that all input from the Atrox will be directed to
9. You should now be able to play any of your fighting games in Steam. They will detect the Atrox as a standard XB360 
   controller. Note that the input from the stick is mapped to the D-Pad on the virtual XB360 controller not the analog 
   stick. Additionally, Windows Store games like Killer Instinct will work fine too.
10. When you are done playing, activate the *RazorAtroxWinUSBVigEmFeeder_x64.exe* window, hit *Q* and press a button on the Atrox. The application will exit and the virtual XB360 controller will disappear


## Uninstallation

If you want to revert to either of the MS XBO controller drivers for this device it's quite simple to do so:

1. Hit *Win* \+ *R*
2. Enter *devmgmt.msc* in the Run box and press enter
3. Click *View* and then click *Show hidden devices*
4. Locate the item in the tree labelled *Universal Serial Bus devices*
5. Right-click the *Razer Atrox Arcade Stick* item and click *Uninstall device*
6. In the dialog box, mark the checkbox labelled *Delete the driver software for this device*
7. Click *Uninstall*
8. Replug your Razer Atrox. It will now use whichever MS driver you previously configured for it


## Interface
The application provides a simple text-mode UI. When running the UI appears as follows:

```
WinUSB Status: CONNECTED
VigEm Status: CONNECTED

Press:
* Q and then a button on the controller to exit 
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


## Roadmap

1. Improved GUI (Text-mode first, later a proper Win32 GUI)
2. Advanced Input rebinding and presets system
3. Input modifier system to allow a button on the controller to be used to trigger alternate input mode.
   Similar to the *Shift* key on a keyboard
4. Support up to 8 controllers
5. Integrate ``libwdi`` to integrate WinUSB driver generation and installation into the application
6. Support other XBO Arcade Stick controllers that do not work correctly on Windows


## Credits

I'd like to thank the following people for their assistance on this project:

* *Nefarius*, *!ϻega*, *evilC*, *Snoothy* and *Sylveon* of the [Nefarius Software Solutions](https://discord.vigem.org/) Discord server for their assistance with with VigEm, WinUSB and C++
* [ZaDig](https://zadig.akeo.ie) for the tool used to generate the WinUSB driver for the Razer Atrox
* The developers of the *xpad* driver for Linux which provided some useful information on interacting with XBO controllers
* The developers of *Device Monitoring Studio*, which I used to capture the USB packet data sent and received by the Razer Atrox


## Contact Details

I would love for anyone testing this tool to provide feedback on the following:

* Did you notice any input lag or similar issues?
* Did the tool fail to work in any games you tried?
* Do you have any ideas or suggestion to improve the tool?

You can contact me via the following avenues:

* The [Nefarius Software Solutions](https://discord.vigem.org/) Discord server
* The GitHub issue tracker for the tool is here: https://github.com/OOPMan/RazorAtroxWinUSBVigEmFeeder/issues
* You can also leave a message on the forum thread https://forums.vigem.org/topic/282/xbo-arcade-sticks-vigem-and-a-whole-ton-of-fun/
* The Reddit post for this software is here: https://www.reddit.com/r/Fighters/comments/bjmca9/attention_razer_atrox_xbo_owners_other_xbo_arcade/
