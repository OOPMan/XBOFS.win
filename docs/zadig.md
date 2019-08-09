# ZaDig WinUSB Driver Installation Guide

01. Check Device Manager and confirm your supported controller is being detected by Windows. It should appear as a 
    *Xbox Gaming Device* under the *Xbox Peripherals* node. If it does not appear here you may still continue with 
    the process but there is a chance it may not work...

    ![Device Manager](images/zadig/01.jpg)
02. The latest version of **ZaDig** should be downloaded to your system and placed in the location you extracted the **XBOFS.win.zip** bundle to

    ![Device Manager](images/zadig/02.jpg)
03. Run **ZaDig**. You will probably get a pop-up as it wants to run as **Administrator**. Allow it. Once start it should look like this

    ![Device Manager](images/zadig/03.jpg)
04. Click *Device*. Click *Load Preset Device*

    ![Device Manager](images/zadig/04.jpg)
05. Navigate to the *zadig_presets* folder and select the appropriate preset for your device

    ![Device Manager](images/zadig/05.jpg)
06. **ZaDig** should now appear as follows (Device name should match that of your controller)

    ![Device Manager](images/zadig/06.jpg)
07. Ensure the highlighted box is showing **WinUSB**. If it shows something else then click on the little arrows next to it until it displays WinUSB

    ![Device Manager](images/zadig/07.jpg)
08. Click the small arrow next to the *Install Driver* button. **DO NOT** click the *Install Driver* button!

    ![Device Manager](images/zadig/08.jpg)
09. Click the *Extract Files (Don't Install)* option

    ![Device Manager](images/zadig/09.jpg)
10. ZaDig should now appear as follows. **DO NOT** click the *Extract Files* button yet!

    ![Device Manager](images/zadig/10.jpg)
11. Click *Options*. Click *Advanced Mode*

    ![Device Manager](images/zadig/11.jpg)
12. Click the highlighted icon next to the *Extract Files* button

    ![Device Manager](images/zadig/12.jpg)
13. Navigate to the *zadig_driver*, click the folder for your controller and click *Select Folder*

    ![Device Manager](images/zadig/13.jpg)
14. Confirm in the log area that **ZaDig** is going to use the selected folder as the extraction directory

    ![Device Manager](images/zadig/14.jpg)
15. Now, finally, click the *Extract Files* button

    ![Device Manager](images/zadig/15.jpg)
16. Wait and when it's done the log output should appear as follows along with a message at the bottom of the window stating that the files 
    were successfully extracted. You can now close **ZaDig**

    ![Device Manager](images/zadig/16.jpg)
17. Open the correct folder within the *zadig_driver* folder

    ![Device Manager](images/zadig/17.jpg)
18. Right-click on the *Setup information* file (The icon is a white page with a grey gear)

    ![Device Manager](images/zadig/18.jpg)
19. Click *Install*

    ![Device Manager](images/zadig/19.jpg)
20. The driver should install correctly

    ![Device Manager](images/zadig/20.jpg)
21. If it does not, you will need to follow the instructions at 
    http://jbcomp.com/disable-device-driver-signing-in-windows-10/ to disable the requirement for signed device drivers and retry this from step 18
