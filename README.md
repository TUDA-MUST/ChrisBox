# ChrisBox
(**CH**arge **R**eading **I**nferface **S**ystem Box)
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

> *IMPORTANT NOTE:* This document describes the features and assembly of ChrisBox and does not contain information about ferroelectret sensors.

## About this Repository

In this repository are the PCB design of ChrisBox, the CAD for the Box, where the PCB can be combined with an battery and a display, as well as general code for the PCB.
- [PCB](/PCB) -> circuit board
- [CAD](/CAD) -> housing for the circuit board and an additional display
- [CODE](/CODE) -> code to be flashes on the microcontroller on the PCB

Ordering and Building instructions are inclued here:
- [ORDERING INSTRUCTIONS](/ORDERING_INSTRUCTIONS.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

Contributing to ChrisBox and this repository: [CONTRIBUTORS](#contributors).\
License: [LICENSE](/LICENSE).

## About ChrisBox

### Development objective and target group

One of the research topics at **Measurement and Sensor Technology Group (MUST)** at **Technical University Darmstadt**, Germany, are ferroelectret sensors. Ferroelectret sensors offer many interesing usecases and many fields of research. All over the world research is done. But many research groups run into similar problems: Ferroelectret sensors require charge amplifiers or electrometers to record measurement data. Most electrometers are very expensive and heavy, and used simple prototype circuits often report strong noise.

To solve these problems a PCB was developed at MUST: ChrisBox.

The main goals of development were:
- **Low noise** with a shielding concept which covers the PCB, but also the cabel to the sensor and depending on the sensor also the sensor itself.
- **Portable**, which is a key aspect compared to electrometers and oscilloscopes. Measurements on the human body while walking, etc., require a portable solution.
- **Simple to use**, as the PCB is intended as a tool for people who are no experts in developing PCBs or code, but want to do measurements with ferroelectret sensors.
- **Affordable** is interesting in comparison to e.g. electrometers, because with this PCB more risky experiments (like electric shocks near the measurement setup) can be conducted with a relatively low financial risk (one assembled PCB costed around 40€-50€ (no guarantee for the price!)).

### Detailed decription of ChrisBox


## Contributors
