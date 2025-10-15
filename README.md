# ChrisBox
(**CH**arge **R**eading **I**nferface **S**ystem Box)\
4 Channel Charge Amplifier PCB

## Introduction

Welcome to ChrisBox!\
ChrisBox is a four channel charge amplifier, mainly developed for the simulatneous charge measurement of four ferroelectret sensors.
The main goals of development were 
- low noise (shielding concept),
- portable,
- simple to use,
- affordable.

More details about ChrisBox are here to find: [About ChrisBox](#about-chrisbox).

> [!IMPORTANT]
> This document describes the features and assembly of ChrisBox and does not contain information on how to build or use ferroelectret sensors.

![Rendering of ChrisBox with display, battery and connected ferroelectret sensors.](/data/ChrisBox_rendering_inscription.png)

## About this Repository

In this repository are the PCB design of ChrisBox, the CAD for the Box, where the PCB can be combined with an battery and a display, as well as general code for the PCB.
- [PCB](/PCB) -> circuit board
- [CAD](/CAD) -> housing for the circuit board and an additional display
- [CODE](/CODE) -> code to be flashed on the microcontroller of the PCB, and code for a Nextion display.

A code description is found in the `./CODE` folder, if you just want to build a ChrisBox, the following instructions should be sufficient.

Ordering and Building instructions are inclued here:
- [ORDERING INSTRUCTIONS](/ORDERING_INSTRUCTIONS.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

Contributing to ChrisBox and this repository: [CONTRIBUTORS](#contributors).\
License: [LICENSE](/LICENSE).

Information about citation is found here: [CITATION](#citation).

## About ChrisBox

### Development objective and target group

One of the research topics at **Measurement and Sensor Technology Group (MUST)** at **Technical University Darmstadt**, Germany, are ferroelectret sensors. Ferroelectret sensors offer many interesing usecases and many fields of research. All over the world research is done. But many research groups run into similar problems: Ferroelectret sensors require charge amplifiers or electrometers to record measurement data. Most electrometers are very expensive and heavy, and used simple prototype circuits often report strong noise.

To solve these problems a PCB was developed at MUST: ChrisBox.

The main goals of development were:
- **Low noise** with a shielding concept which covers the PCB, but also the cabel to the sensor and, depending on the sensor, also the sensor itself.
- **Portable**, which is a key aspect compared to electrometers and oscilloscopes. Measurements on the human body while walking, etc., require a portable solution.
- **Simple to use**, as the PCB is intended as a tool for people who are no experts in developing PCBs or code, but want to do measurements with ferroelectret sensors.
- **Affordable** is interesting in comparison to e.g. electrometers, because with this PCB more risky experiments (like electric shocks near the measurement setup) can be conducted with a relatively low financial risk (one assembled PCB costed around 40€-50€ (no guarantee for the price!)).

### Detailed decription of ChrisBox

**Analog electronics**
A ferroelectret is connected to the PCB through an USB C cable/connector. The signal wires are D+ and D-. The signal from the ferroelectret is a charge. This charge is amplified in a charge amplifier. An exemplary application for the setup is heartrate measurement. This requires measurements in very low frequencies. Therefore a very large feedback resistor is used in the charge amplifier (in the G&Omega; range).
A reference voltage in the middle of the measurement range (around 1.65V) is generated to allow differential measurements in the 0-3.3V setup.
The analog electronics exists four times independent to each other.

**Digital electronics**
The output of each charge amplifier is connected to a ADC (ADS1220). The reference voltage also is connected there to allow differential measurements with the ADC.
All four ADCs are connected to an ESP32 via SPI.

**ESP32**
An ESP32 S3 Mini 1 is the microcontroller for the ChrisBox, together with a Boot and Reset button. A UART-to-USB converter is used for good connectivity with different PCs.

**Support circuits**
On the PCB some other ciruits are included: Four LEDs as status LEDs, which can freely be programmed in the ESP32. A connector for UART is included to connect a Nextion display. Also a connector for five GPIO pins of the ESP32 is included to allow free usage of those pins for other functions is needed.
5V can be generated (enabled by ESP32) for a Nextion display.
A battery can be connected for power supply, and can be charged when also connected to USB.

**Shielding**
The PCB is shielded with a shielding frame and cover, as well as a shielding layer in the PCB. USB C cables are used to connect the ferroelectret sensors. This is chosen because USB C cables are shielded themself and are easy to buy. A ferroelectret needs to be soldered to an USB C connector. An unshielded ferroelectret sensor is a source for noise, so this should be shielded as well for a low-noise measurement setup.

**Data output**
There are different ways as output for the aquired measurement data:
- Serial communication to a PC
- UART to a Nextion display for on-the-fly results
- ESP NOW for wireless measurements. Requires a second ESP32 as receiver for the data, which itself could communicate to a PC.

## Contributors

ChrisBox was developed at the [Measurement and Sensor Technology Group](https://www.etit.tu-darmstadt.de/must/home_must/index.de.jsp) at TU Darmstadt by:
- [Sven Suppelt](https://orcid.org/0000-0002-2338-9333) (Supervision)
- [Dominik Werner](https://orcid.org/0009-0001-8082-5584) (Hardware and Software Design, CAD Design)
- [Alexander Altmann](https://orcid.org/0000-0001-5299-3620) (Supporting Ferroelectret Knowledge)
- [Felix Herbst](https://orcid.org/0000-0003-1480-3691) (Artwork)

## Citation

If you would like to reference the project, please cite the following (yet to publish...) [paper](https://www.etit.tu-darmstadt.de/must/home_must/index.de.jsp):

```
@article{name2025,
  author={},
  booktitle={}, 
  title={}, 
  year={2025},
  pages={},
  doi={}
```
