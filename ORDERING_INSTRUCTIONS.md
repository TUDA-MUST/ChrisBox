# Ordering Instructions

In this document information about the ordering process of various components can be found. This is segmented in the core PCB, required components for the PCB and additional material for a full ChrisBox setup.
It is recommended to read the other documents in this repository before ordering, as provided explainations about the different components ensure understanding of the ChrisBox and help avoiding mistakes in the ordering process.

- [README](/README.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

## PCB

The PCB is designed for ordering at JLCPCB. Files are prepared for a populated PCB. These files are made with the JLCPCB Tool in kiCad. Keep in mind that not all components on the PCB can be placed by JLCPCB (Feedback resistors and shield), so they have to be ordered seperatly.

The files are found in `./PCB/jlcpcb`. The gerber-files contain information about the raw PCB, the production-files contain the information about parts and their positions on the PCB.

In the ordering process, select the option "Order Number(Specify Position)" if you want to specify the position of the order number on your PCB. The silkcreen contains a text "JLCJLCJLCJLC" for this purpose under the shield. More information about this topic can be found here: [JLCPCB article](https://jlcpcb.com/help/article/How-to-remove-order-number-from-your-PCB).

## Additional Required Parts

### Parts for PCB

- **4x Resistor 5G&Omega**;, Footprint 0805 (the value of the feedback resistor decides about the low cutoff frequency of the charge amplifier. Feel free to choose different values here if other frequencies are required).
- Shield Laird Technologies: **1x BMI-S-205-F** and **1x BMI-S-205-C** (F for frame, C for cover. These are two different pieces, one to be soldered on the PCB, the other to be stacked above.)

### Parts for Basic Measurement Setup

- **4x USB-C cable** to connect up to four sensors to the PCB
- **USB-C female connectors/adapters** for sensors (number depending on the amount of sensors you work with). Important is USB 2.0 functionality, which means that there are D+ and D- connections to solder the ferroelectret to. A shield around the sensor can be soldered to the housing of the adapter.
- **Micro USB cable** to connect the PCB to a PC

## Full ChrisBox Setup

- **1x Nextion NX3224K024** Display
- 3D prints for the casing (these are probably no parts to be ordered, but to be printed in lab/at home)
- **4x threaded inserts** M3 x 3,0 (the CAD has a blind hole of 4mm, and a diameter of 4mm)
- **4x screw** M3x25 (the specific choice of screw head is not relevant, but the CAD was theoretically designed for countersunk heads)
