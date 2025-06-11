# PCB

Welcome to the PCB folder of ChrisBox!
The ChrisBox PCB is designed with KiCad. The Project files and generated Exports are found here.

![Screenshot of a ChrisBox Assembly](/PCB/data/PCB_screenshot.png)

## Content of the PCB folder

- `./exports` - Siemens NX part files for the casing.
- `./interactive bom` - Electric components of the assembly (PCB with most components, a standard Battery and the NX3224K024 display). 
- `./jlcpcb` - STL data of the casing, e.g. for 3D printing
- `./models` - pictures of the assembly
- `./support_pictures` - pictures of the PCB and some for the schematic and silkscreen

## Details on KiCad settings

The design was made with KiCad 8.0. Installed plugins are the Alternate KiCad Library (by Dawid Cislo), the Interactive Html Bom (by qu1ck) and the KiCAD JLCPCB tools (by Bouni).
Additional Footprints or 3D models are found in the `./models` folder.

## Ordering and building the PCB

For ordering instructions refer to [ORDERING INSTRUCTIONS](/ORDERING_INSTRUCTIONS.md).
For building instructions refer to [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md).
