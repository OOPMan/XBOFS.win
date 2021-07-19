# XBOFS.win v1.0.0
**XBOFS.win** allows you to use your **XBO Fight Stick** on Windows without having to install ancient, beta XBO drivers and 
rewire buttons. 

The application achieves this by communicating directly with your **XBO Fight Stick** using a generic WinUSB driver and 
forwarding the input data from the controls to a **Virtual XBox 360 Controller** provided by **VigEmBus**. 

From the perspective of games and other software, the **Virtual XBox 360 Controller** is identical to a real controller and 
**XBOFS.win** is thus able to achieve maximum compatibility with minimum overhead.

## Supported XBO Fight Sticks
* Razer Atrox XBO
* Madcatz TE2 XBO

## Features
* All buttons on supported fight sticks work, no rewiring or fiddling required!
* Multiple supported fight sticks can be connected
* Supported fight sticks work in Steam, Windows Store games, etc
* A proper Installer and Driver Manager tool to get you up and running fast!
* Comprehensive profile-based control binding system
* Additional debugging features
* QT6 GUI

## Quickstart
1. Download and install the latest version of [VigEmBus](https://github.com/ViGEm/ViGEmBus/releases/latest)
2. Download and install the latest version of [XBOFS.win](https://github.com/OOPMan/XBOFS.win/releases/latest)
3. Run **XBOFS.win** and use the **Driver Manager** to install the necessary WinUSB Driver(s) for your **XBO Fight Stick(s)**
4. **XBOFS.win** should detect your **XBO Fight Stick(s)** and once it does you're good to go! 

#### Don't forget...
The **XBOFS.win** application needs to be running in order for your Controller to work, so it's a good idea to set it to start
automatically with Windows!

#### Need more detail?
For a more comprehensive and in-depth installation and first-run guide, [click here!](/installation_guide.md) If you're an
existing user then you should also read the installation guide as it will inform you as to the upgrade process.

If you would like a guided tour of the application in general, [click here.](/application_guide.md)

## Control Binding
**XBOFS.win** features a very comprehensive control binding system. Named Profiles can be used to easily switch between different configurations
and each configuration supports two sets of bindings that can be switched between using the XBox Guide Button.

Read the [Control Binding](/binding_guide.md) page to learn more about why you might want to use it, what you can do with it and how to configure it.

## Debugging
Another useful feature is the debugging window. When this feature is enabled you can view application performance data and in-depth as well
as a complete summary of the data received from your **XBO Fight Stick** and sent to the **Virtual XBox 360 Controller**.

Read the [Debugging](/debugging_guide.md) page to learn more about this feature.

## Troubleshooting
If you run into issues the [Troubleshooting](/troubleshooting.md) page is the first place to read to see if your question has already been
answered. You'll also find details on how to submit a support ticket.

## FAQ
The [FAQ](/faq.md) page contains answer to some commonly asked questions that don't fall under trouble-shooting, along with a bit of general
information on this project.

## Credits

* **Coding**
  * [OOPMan](https://github.com/OOPMan)
* **VigEmBus** and **VigEmClient**
  * [Nefarius](https://github.com/nefarius) (If you have some cash to spare [go give this man some support](https://forums.vigem.org/topic/291/shameless-beggar-post). Without his work on [VigEmBus](https://github.com/ViGEm) **XBOFS.win** would not exist)
  * [!ϻega](https://github.com/megadrago88)
* **Advice**
  * [Nefarius](https://github.com/nefarius)
  * [!ϻega](https://github.com/megadrago88)
  * [evilC](https://github.com/evilC)
  * [Snoothy](https://github.com/Snoothy)
  * [Sylveon](https://github.com/sylveon)
* **XBO Controller Information**
  * [xpad.c](https://github.com/torvalds/linux/blob/master/drivers/input/joystick/xpad.c)
* **Tools**
  * [Device Monitoring Studio](https://www.hhdsoftware.com/device-monitoring-studio)
  * [Microsoft Visual Studio Community 2019](https://visualstudio.microsoft.com)
  * [ZaDig](https://zadig.akeo.ie)
  * [InkScape](https://inkscape.org)
* **Testing**
  * Multiple Atrox support
    * [Manick74](https://www.reddit.com/user/Manick74)
    * [TheDecn](https://www.reddit.com/user/TheDecn)
  * Madcatz TE2 XBO support
    * [Fodenn](https://www.reddit.com/user/Fodenn)
* **Graphics**
  * Icon made by Freepik from [www.flaticon.com](https://www.flaticon.com) and modified by [OOPMan](https://github.com/OOPMan)