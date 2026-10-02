# Ordering Instructions

In this document information about the ordering process of various components can be found. This is segmented in the core PCB, required components for the PCB and additional material for a full ChrisBox setup.
It is recommended to read the other documents in this repository before ordering, as provided explanations about the different components ensure understanding of the ChrisBox and help avoiding mistakes in the ordering process.

- [README](/README.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

## PCB

The PCB is designed for ordering at JLCPCB.
Files are prepared for a populated PCB.
These files are made with the [JLCPCB Tool](https://github.com/bouni/kicad-jlcpcb-tools) in KiCad.
Keep in mind that not all components on the PCB are in stock at JLCPCB, so they have to be ordered separately (feedback resistors and shield).
Those parts can either be shipped by you to JLCPCB in advance using their [Global Sourcing Parts Service](https://jlcpcb.com/help/article/how-to-use-jlcpcb-global-sourcing-parts-service) or be manually assembled afterward, as described in the [building instructions](/BUILDING_INSTRUCTIONS.md).

The files are found in `./PCB/jlcpcb`. The gerber-files contain information about the raw PCB, the production-files contain the information about components and their positions on the PCB. The ordering process should look similar to the following screenshots:

> [!NOTE]
> The voltage generation for VRef (U1) is planned to be 1.6V in the schematic. In the JLCPCB tool and therefore in the exported data a 1.8V model is used due to production capability (at the time of data export). A reference voltage apart from 1.65V is no problem due to the differential measurement, but is shifts the measurement range so that "zero" is not in the middle and more positive or negative values can be measured.

<p align="center">
      <img src="/data/ChrisBox_JLCPCB_1.png" width="49%">
      <img src="/data/ChrisBox_JLCPCB_2.png" width="49%">
</p>

In the ordering process, select the option "Mark on PCB", "2D Barcode (Serial Number)", "Number Only", and "Specify Position" if you want to place a serial number on your PCB.
The silkscreen contains a 2x10mm square for this purpose.
The older order number setting has been superseded.
More information about this topic can be found in the [JLCPCB instructions on PCB marks](https://jlcpcb.com/help/article/How-to-mark-on-PCB).

<p align="center">
      <img src="/data/ChrisBox_JLCPCB_3.png" width="49%">
      <img src="/data/ChrisBox_JLCPCB_4.png" width="49%">
</p>

You can also choose Economic PCBA Type here.
However, it may be possible that you are required to upgrade in the next steps.

A few optional solder headers (J1, J2, J5) and test points (TP1-TP5) purposely create an error during BOM/CPL processing, as they are part of the BOM but not in the CPL file.
Furthermore, a few lines in the BOM create warnings.
You will want to manually select all components in the list.
At the time of ordering, placement of the ESP32 module requires an upgrade from Economic to Standard Assembly.
You will need to confirm this message as well.
> [!NOTE]
> Please note that all parts have been pre-ordered through JLCPCBs [Global Sourcing Parts Service](https://jlcpcb.com/help/article/how-to-use-jlcpcb-global-sourcing-parts-service) in the screenshots.
> If you did not do so, the G&Omega; feedback resistors and shield will most likely not be available and cannot be placed.

<p align="center">
      <img src="/data/ChrisBox_JLCPCB_5.png" width="49%">
      <img src="/data/ChrisBox_JLCPCB_6.png" width="49%">
</p>

<p align="center">
      <img src="/data/ChrisBox_JLCPCB_7.png" width="49%">
      <img src="/data/ChrisBox_JLCPCB_8.png" width="49%">
</p>

## Additional Required Parts

### Parts for PCB

- [**4x Resistor 5G&Omega;**](https://www.digikey.com/en/products/detail/te-connectivity-passive-product/RH73W2A5GNTN/2366071), footprint 0805 (RH73W2A5GNTN, TE Connectivity).
The value of the feedback resistor decides about the low cutoff frequency of the charge amplifier.
Feel free to choose different values here if other frequencies are required.
- [**1x BMI-S-205-F**](https://www.digikey.com/en/products/detail/laird-technologies-emi/bmi-s-205-f/2175892
) and [**1x BMI-S-205-C**](https://www.digikey.com/en/products/detail/laird-technologies-emi/bmi-s-205-c/2175918
) (Shield Laird Technologies, F for frame, C for cover).
These are two different pieces, one to be soldered on the PCB, the other to be stacked above.

### Parts for Basic Measurement Setup

- [**4x USB-C cable**](https://www.amazon.de/Amazon-Basics-USB-Type-Cable-White/dp/B01GGKZ0V6/) to connect up to four sensors to the PCB
- [**USB-C female connectors/adapters**](https://www.amazon.de/PENGLIN-Stecker-Adapter-Dr%C3%A4hten-Support-Modul/dp/B09YLVSPQX/) for sensors (number depending on the amount of sensors you work with). Important is USB 2.0 functionality, which means that there are D+ and D- connections to solder the ferroelectret to. A shield around the sensor can be soldered to the housing of the adapter.
- [**Micro USB cable**](https://www.amazon.de/Amazon-Basics-%C3%9Cbertragungsgeschwindigkeit-vergoldeten-Steckern/dp/B0711PVX6Z/) to connect the PCB to a PC

## Full ChrisBox Setup

- [**1x Nextion NX3224K024**](https://nextion.tech/datasheets/nx3224k024/) Display
- A 720mAh 3.7V Lithium Polymer battery with JST PH Plug
- 3D prints for the casing (these are probably no parts to be ordered, but to be printed in lab/at home)
- [**4x threaded insert**](https://cnckitchen.store/de/products/heat-set-insert-m3-x-3-short-version-100-pieces) M3 x 3,0 (the CAD has a blind hole of 4mm, and a diameter of 4mm)
- [**4x screw**](https://www.amazon.de/Sechskopf-Knopf-Zylinderschrauben-Gewindeschrauben-Sechskantschrauben-Maschinenschrauben/dp/B0B3MGZ7T2/) M3x25 (the specific choice of screw head is not relevant, but the CAD was theoretically designed for countersunk heads)
