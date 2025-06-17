# Building Instructions

This are the building instructions for a complete ChrisBox setup. A complete setup includes not only the main PCB and its software, but also a Nextion display and a casing. The display and casing are optional for functionality.

## PCB Hardware

![Unsoldered version of ChrisBox](/data/ChrisBox_PCB_1_unsoldered.JPG)

![ChrisBox components for soldering](/data/ChrisBox_PCB_2_components.JPG)

![ChrisBox places of soldering](/data/ChrisBox_PCB_1.1_unsoldered_marked.JPG)

![Soldered version of ChrisBox](/data/ChrisBox_PCB_3_soldered.JPG)

## PCB Software

![Arduino IDE select device](/data/ChrisBox_Software_1_select_device.JPG)

![Arduino IDE upload options](/data/ChrisBox_Software_2_upload_options.JPG)

## Nextion Software

The used Nextion display is a NX3224K024 display. The `.HMI` file with the code for the Nextion Editor is in the `./CODE` folder, as well a the `.tft` file. This `Chrisbox Nextion.tft` file can be flashed on a NX3224K024 display via micro SD card.
Either you open the `.HMI` file in Nextion Editor and execute a TFT file output, or you just take the given `.tft` file:
1. Save the `.tft` file to a fresh micro SD card.
2. Insert this micro SD card into the Nextion display.
3. turn on power for the display (by connection GND and 5V, either to the USB adapter or to the ChrisBox PCB.)
4. Software update starts automatically, wait for finish.
5. Turn off the power.
6. Remove SD card.
7. The update is complete. By turning power on again the loaded program should be active, without SD card!

## Casing

![ChrisBox Assembly parts overview](/data/ChrisBox_Assembly_1_overview.JPG)

Cable + Shield!
Cable: UART, JST XH or do something sketchy, RX to TX and otherwise round, GND to GND and 5V to 5V

![ChrisBox Assembly connected cable](/data/ChrisBox_Assembly_2_cable.JPG)

![ChrisBox Assembly inserted display](/data/ChrisBox_Assembly_3_display.JPG)

![ChrisBox Assembly screws](/data/ChrisBox_Assembly_4_screws.JPG)

![ChrisBox Assembly finished](/data/ChrisBox_Assembly_5_finished.JPG)
