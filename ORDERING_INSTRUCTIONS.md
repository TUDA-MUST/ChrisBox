# Ordering Instructions

In this document information about the ordering process of various components can be found. This is segmented in the core PCB, required components for the PCB and additional material for a full ChrisBox setup.
It is recommended to read the other documents in this repository before ordering, as provided explanations about the different components ensure understanding of the ChrisBox and help avoiding mistakes in the ordering process.

- [README](/README.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

## PCB

The PCB is designed for ordering at JLCPCB. Files are prepared for a populated PCB. These files are made with the JLCPCB Tool in kiCad. Keep in mind that not all components on the PCB can be placed by JLCPCB, so they have to be ordered seperatly (Feedback resistors and shield).

The files are found in `./PCB/jlcpcb`. The gerber-files contain information about the raw PCB, the production-files contain the information about components and their positions on the PCB. The ordering process should look similar to the following screenshots:

> [!NOTE]
> The voltage generation for VRef (U1) is planned to be 1.6V in the schematic. In the JLCPCB tool and therefore in the exported data a 1.8V model is used due to production capability (at the time of data export). A reference voltage apart from 1.65V is no problem due to the differential measurement, but is shifts the measurement range so that "zero" is not in the middle and more positive or negative values can be measured.

<p align="center">
      <img src="/data/ChrisBox_JLC_1.png" width="49%">
      <img src="/data/ChrisBox_JLC_2.png" width="49%">
</p>

In the ordering process, select the option "Order Number(Specify Position)" if you want to specify the position of the order number on your PCB. The silkscreen contains a text "JLCJLCJLCJLC" for this purpose under the shield. More information about this topic can be found here: [JLCPCB article](https://jlcpcb.com/help/article/How-to-remove-order-number-from-your-PCB).

<p align="center">
      <img src="/data/ChrisBox_JLC_3.png" width="49%">
      <img src="/data/ChrisBox_JLC_4.png" width="49%">
</p>

<p align="center">
      <img src="/data/ChrisBox_JLC_5.png" width="49%">
      <img src="/data/ChrisBox_JLC_6.png" width="49%">
</p>

<p align="center">
      <img src="/data/ChrisBox_JLC_7.png" width="49%">
      <img src="/data/ChrisBox_JLC_8.png" width="49%">
</p>

## Additional Required Parts

### Parts for PCB

- [**4x Resistor 5G&Omega;**](https://www.mouser.de/ProductDetail/TE-Connectivity-Holsworthy/RH73W2A5GNTN?qs=sGAEpiMZZMtlubZbdhIBIFho3SHfDXSt2iO61eRuWOU%3D);, Footprint 0805 (the value of the feedback resistor decides about the low cutoff frequency of the charge amplifier. Feel free to choose different values here if other frequencies are required) (Part-Nr.: RH73W2A5GNTN, TE Connectivity / Holsworthy).
- Shield Laird Technologies: [**1x BMI-S-205-F**](https://www.mouser.de/ProductDetail/Laird-Performance-Materials/BMI-S-205-F?qs=5UmOb8GQ3yJF%252BC0nviEu1Q%3D%3D
) and [**1x BMI-S-205-C**](https://www.mouser.de/ProductDetail/Laird-Performance-Materials/BMI-S-205-C?qs=5UmOb8GQ3yK2YqcYqxMNeQ%3D%3D
) (F for frame, C for cover. These are two different pieces, one to be soldered on the PCB, the other to be stacked above.)

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
