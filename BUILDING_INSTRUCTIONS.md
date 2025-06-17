# Building Instructions

This are the building instructions for a complete ChrisBox setup. A complete setup includes not only the main PCB and its software, but also a Nextion display and a casing. The display and casing are optional for functionality.

1. [PCB Hardware](#pcb-hardware)
2. [PCB Software](#pcb-software)
3. [Nextion Software](#nextion-software)
4. [Full ChrisBox Assembly](#full-chrisbox-assembly)


## PCB Hardware

When ordering a populated circuit board (e.g. from JLCPCB), the result should look like this:

![Unsoldered version of ChrisBox](/data/ChrisBox_PCB_1_unsoldered.JPG)

This PCB is not finished. The shielding frame cannot be placed at JLCPCB, as well as the very high (G&Omega; range) feedback resistors for the charge amplifiers.
As a result, these components have to be placed by hand:
- Feedback resistors: 4x 0805 (in) or 2012 (mm), >2G&Omega;
- Shield frame: 1x Laird Technologies, BMI-S-205-F
- Shield cover: 1x Laird Technologies, BMI-S-205-C

![ChrisBox components for soldering](/data/ChrisBox_PCB_2_components.JPG)

The places for the feedback resistors and the shielding frame are shown in the picture below. The shielding cover does not have to be soldered, it can be placed on the fence afterwards.
> **Tip:** Things get easier if the resistors are soldered first because of the height of the components.
> Also it can come handy to remove the cross in the middle of the shielding frame before soldering if some components have to be reached afterwards.
Unfortunaly, fhe frame and connected shielding plane (in the PCB) are good in heat distribution. Therefore it takes a while to heat the pads and solder the frame.

![ChrisBox places of soldering](/data/ChrisBox_PCB_1.1_unsoldered_marked.JPG)

The soldered resistors and frame can look like in the picture below. The soldering part of the PCB is finished now!

![Soldered version of ChrisBox](/data/ChrisBox_PCB_3_soldered.JPG)

## PCB Software

On the PCB is an ESP32-S3 microcontroller (ESP32-S3-MINI-1). The connection between PC and microcontroller works with a UART-TO-USB bridge (CP2102N). This is the same bridge chip as on most ESP32 development boards. To enable interaction between a PC and the microcontroller on the ChrisBox PCB, the **Silicon Labs CP210x USB to UART Bridge** driver should be installed on the PC.
After installing the driver, connect the ChrisBox PCB to the PC via micro USB cable and turn it on with the switch on the side. Before turing on one LED should work, after turning on multiple LEDs.
The PC should detect a device called something like "Silicon Labs CP210x USB to UART Bridge" on a COM port. Remeber this COM port!

Programming works with the **Arduino IDE**. Programming and the setting were tested with Arduino IDE 2.3.6, but other versions should work as well.
In the Arduino IDE, select the device as in the picture below. Seelct the COM port accordingly to the one your PCB is connected to.
It may be necessary to install the esp32 by espressif systems via board manager.

![Arduino IDE select device](/data/ChrisBox_Software_1_select_device.png)

Open the downloaded code in the Arduino IDE. It is important that all code files from this repository are in the same folder after downloading, that the Arduino IDE can find libraries while compiling.
Select the upload options as shown below and hit upload. This can take a while. After finishing, the ESP reboots and the uploaded program starts. While a program is running, a LED is blinking on the PCB.
You can see measurement data incoming on the serial monitor (select baud rate 115200). This serial data also can be viewed in the **Better Serial Plotter** or tools like **MATLAB**.

![Arduino IDE upload options](/data/ChrisBox_Software_2_upload_options.png)

## Nextion Software

The used Nextion display is a NX3224K024 display. The `.HMI` file with the code for the Nextion Editor is in the `./CODE` folder, as well a the `.tft` file. This `ChrisBox Nextion.tft` file can be flashed on a NX3224K024 display via micro SD card.
Either you open the `.HMI` file in Nextion Editor and execute a TFT file output, or you just take the given `.tft` file:
1. Save the `.tft` file to a fresh micro SD card.
2. Insert this micro SD card into the Nextion display.
3. turn on power for the display (by connection GND and 5V, either to the USB adapter or to the ChrisBox PCB.)
4. Software update starts automatically, wait for finish.
5. Turn off the power.
6. Remove SD card.
7. The update is complete. By turning power on again the loaded program should be active, without SD card!

## Full ChrisBox Assembly

The full ChrisBox assembly consists of:
- ChrisBox PCB with shielding cover
- Nextion NX3224K024 display
- cable between PCB and display
- 1x Casing Top (3D printing)
- 1x Casing Bottom  (3D printing)
- 4x Spacer (3D printing)
- 4x M3x25 screw
- 4x Threaded insert M3x3,0 (CAD made for: hole diameter 4mm, blind hole depth min. 4mm)

![ChrisBox Assembly parts overview](/data/ChrisBox_Assembly_1_overview.JPG)

First, insert the threaded inserts into the top of the casing with a solder iron or threaded insert heat press.

<p align="center">
      <img src="/data/ChrisBox_Casing_2_inserts.JPG" width="49%">
      <img src="/data/ChrisBox_Casing_3_inserted_inserts.JPG" width="49%">
</p>

Then connect the Nextion display to the ChrisBox PCB. An ordered Nextion display contains a cable with on JST XH connector (the white 4x1 connector) and four Dupont connectors (the black 1x1 connectors).
Connect the JST XH connector to the display. You can connect the Dupont cables on the ChrisBox PCB, or you can shorten the cables and add crimp connectins for another JST XH connector. This is what is used here on the picture. The JST XH connector fits directly onto the ChrisBox PCB.
Anyway, connect GND to GND, 5V to 5V and RX to TX and the other way around.
Place the shielding cover onto the shielding frame on the PCB.

Place the display into the top half of the casing, with the connector in the direction of the bulge.

<p align="center">
      <img src="/data/ChrisBox_Assembly_2_cable.JPG" width="49%">
      <img src="/data/ChrisBox_Assembly_3_display.JPG" width="49%">
</p>

Place the PCB into the bottom half of the casing, with screws and spacers.

Then connect both halfs of the casing and tighten the screws. The ChrisBox is finished!

> **Tip:** Place the top half on top of the lower half with the screws and spacers on a table. Then move the assembly to the edge of the table that one screw can be tightened. Repeat for the other screws.

<p align="center">
      <img src="/data/ChrisBox_Assembly_4_screws.JPG" width="49%">
      <img src="/data/ChrisBox_Assembly_5_finished.JPG" width="49%">
</p>
