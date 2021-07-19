# Device Contributor Guide

This document aims to provide users of unsupported XBO fight sticks with the tools and knowledge they need to assist in the 
process of adding support for new devices


## Contents
1. [Requirements](#requirements)
2. [Tools](#tools)
3. [Preparation](#preparation)
4. [Data Capture](#data-capture)
5. [Delivery](#delivery)


## Requirements
* Access to a XBO fight stick controller that is not supported by the **XBOFS.win**
* Some patience


## Tools
* A text editor (I recommend [Notepad++](https://notepad-plus-plus.org))
* [Device Monitoring Studio](https://www.hhdsoftware.com/device-monitoring-studio). Don't worry about the crazy prices, the shareware 
  version of this application works fine for our needs. Just download the installer and run it. To complete the installation you will need
  to reboot.


## Preparation
Before you can start capturing data for your device it is necessary to ensure it is not configured to use the XBO Controller beta drivers
from 2014. If these drivers are active for your device then Device Monitoring Studio will be unable to see the controller.

##### In order to determine whether you are using the beta drivers
01. Press *Win* + *R* to open the *Run* dialog

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/01.jpg)   
02. Enter *devmgmt.msc* and press *Enter*

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/02.jpg)
03. In the *Device Manager* window, locate the *Xbox Peripherals* item and expand it

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/03.jpg)
04. Locate the *Xbox Gaming Device* item

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/04.jpg)
05. Right-click on the item and click *Properties*

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/05.jpg)
06. Click on the *Driver* tab

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/06.jpg)
07. Check the *Driver Date* and *Driver version* items. If the driver date is **5/26/2014** and the driver version is **6.2.11059.0**
    then you are using the beta drivers and will need to temporarily switch to a newer version while you collect the data

    ![](images/device_contributor_guide/check_xbo_controller_driver_version/07.jpg)

##### In order to update to the latest drivers
01. Navigate to the *Driver* tab as described above

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/01.jpg)
02. Click the *Update* button

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/02.jpg)
03. Click the *Search automatically for updated driver software* option

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/03.jpg)
04. Wait for the driver to be updated

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/04.jpg)
05. Check the *Driver Date* and *Driver version* items. They should reflect a newer version of the driver that the one described above.
    You may be instructed to reboot. If so, reboot as instructed before proceeding to capture data. If for some reason the driver is not
    updated to a newer version using this process then it is recommended to run *Windows Update* and retry this process from step 1

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/05.jpg)

##### To rollback to the beta drivers
01. Navigate to the *Driver* tab as described above

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/01.jpg)
  
02. Click the *Update* button

    ![](images/device_contributor_guide/update_xbo_controller_driver_version/02.jpg)
03. Click the *Browse my computer for driver software* option

    ![](images/device_contributor_guide/rollback_xbo_controller_driver_version/01.jpg)
04. Click the *Let me pick from a list of available drivers on this computer* option

    ![](images/device_contributor_guide/rollback_xbo_controller_driver_version/02.jpg)
05. Select the *Xbox Gaming Device Version 6.2.11059.0 [5/26/2014]* item and click *Next*

    ![](images/device_contributor_guide/rollback_xbo_controller_driver_version/03.jpg)
06. Wait for the driver to be rolled back

    ![](images/device_contributor_guide/rollback_xbo_controller_driver_version/04.jpg)
07. You should get a success message. You may also see a *Microsoft Visual C++ Runtime Library* error dialog. This can be ignored, it's a
    side-effect of using ancient, beta drivers.  You may be instructed to reboot. If instructed, do so

    ![](images/device_contributor_guide/rollback_xbo_controller_driver_version/05.jpg)

## Data Capture

01. Plug in your **XBO Fight Stick**. It is also recommended to unplug any other controllers
02. Confirm the controller is detected correctly using *Device Manager*

    ![](images/device_contributor_guide/data_capture/01.jpg)
03. Use the *Start Menu* to locate and run your text editor

    ![](images/device_contributor_guide/data_capture/02.jpg)
04. Use the *Start Menu* to locate and run *Device Monitoring Studio*

    ![](images/device_contributor_guide/data_capture/03.jpg)
05. Locate your controller in the *Devices* pane and select it

    ![](images/device_contributor_guide/data_capture/04.jpg)
06. Click the *Device Descriptor* tab in the bottom pane

    ![](images/device_contributor_guide/data_capture/05.jpg)
07. Drag-select all of the text, right-click and click *Copy*

    ![](images/device_contributor_guide/data_capture/06.jpg)
08. Switch to your text editor and paste the copied text

    ![](images/device_contributor_guide/data_capture/07.jpg)
09. Switch back to *Device Monitoring Studio* and click the *Configuration Descriptor* tab in the bottom pane

    ![](images/device_contributor_guide/data_capture/08.jpg)
10. Drag-select all of the text, right-click and clik *Copy*

   ![](images/device_contributor_guide/data_capture/09.jpg)
11. Switch to your text editor and paste the copied text

   ![](images/device_contributor_guide/data_capture/10.jpg)
12. Save the text file

   ![](images/device_contributor_guide/data_capture/11.jpg)

   ![](images/device_contributor_guide/data_capture/12.jpg)
13. Switch back to *Device Monitoring Studio*, locate your controlled in the *Devices* pane, right-click on it and click *Start Monitoring*

   ![](images/device_contributor_guide/data_capture/13.jpg)
14. Double-click the *Packet View* item in the left-hand pane

   ![](images/device_contributor_guide/data_capture/14.jpg)
15. Confirm the *Packet View* item appears in the right-hand pane

   ![](images/device_contributor_guide/data_capture/15.jpg)
16. Click the *Start* button

   ![](images/device_contributor_guide/data_capture/16.jpg)
17. Click in the *Packet View* tab to focus the window and press a button on your controller until you start to see items appear in the list view. Items
   labelled *DOWN* are sent by the PC to the controller while items labelled *UP* represent data sent from the controller

   ![](images/device_contributor_guide/data_capture/17.jpg)
18. Select the first *DOWN* item in the list view

   ![](images/device_contributor_guide/data_capture/18.jpg)
19. This data represents the INIT packet sent by the PC to the controller

   ![](images/device_contributor_guide/data_capture/19.jpg)
20. Right-click in the *Complete* tab and click *Copy*

   ![](images/device_contributor_guide/data_capture/20.jpg)
21. Switch to your text editor and paste the copied text and save

   ![](images/device_contributor_guide/data_capture/21.jpg)
22. Switch back to *Device Monitoring Studio*, click in the *Packet View* tab and press and release the *X* button on your controller. Two new *UP* items should
   appear the list view. The first item represents the button press, the second the release. Select the first item

   ![](images/device_contributor_guide/data_capture/22.jpg)
23. This data represents the button/stick action sent by the controller to the PC

   ![](images/device_contributor_guide/data_capture/23.jpg)
24. Right-click in the *Complete* tab and click *Copy*

   ![](images/device_contributor_guide/data_capture/24.jpg)
25. Switch to your text editor and line a noting the button/stick direction that was pressed (E.g. *Button X*)

   ![](images/device_contributor_guide/data_capture/25.jpg)
26. Paste the copied text and save

   ![](images/device_contributor_guide/data_capture/26.jpg)   
27. Repeat steps 22 through 26 for each button, including the *Start*, *View* and *XBox Guide* buttons
   
28. Repeat steps 22 through 26 for each single stick direction (I.e. *Up*, *Left*, *Down*, *Right*). Be careful not to press the stick diagonally. If you
    are not sure whether you pressed diagonally, try again and check the data in the *Complete* tab

29. Once you have collected data on all the buttons and stick directions you can close *Device Monitoring Studio* and make sure your data capture text file is 
    saved. Not that you **DO NOT** need to capture diagonal directions on the stick or any button press combinations (E.g. *X* and *Y* together). All that is
    required are the single button/direction values
   

## Delivery

The data capture text file needs to be submitted so that support can be implemented. The recommended means of doing this is to 
[create a new issue on GitHub](https://github.com/OOPMan/XBOFS.win/issues/new). You will need to sign-up for a GitHub account (Don't worry, it's free) before
you can submit an issue. 

For the *Title* field, fill in a value adjusted for your controller like so: *Device support request: Razer Atrox XBO*.

Drag-and-drop your data capture text file into the *Write* text area and then click the *Submit new issue* button.

If you have any questions, check the [index](index.md) document for support details

