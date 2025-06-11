# PCB

Welcome to the PCB folder of ChrisBox!
The ChrisBox PCB is designed with KiCad. The Project files and generated Exports are found here.

![Screenshot of a ChrisBox Assembly](/PCB/data/PCB_screenshot.png)

## Content of the PCB folder

- `./data` - pictures of the PCB and some for the schematic and silkscreen.
- `./exports` - The `.step`-export of the ChrisBox PCB.
- `./interactive bom` - The interactive HTML BOM (made with Interactive Html Bom). It is useful for handsoldering or just looking up which component has to go where.
- `./jlcpcb` - Output data from the KiCAD JLCPCB tools. This data can be used for ordering a PCB with components. Always re-check the data yourself!
- `./models` - Additional footprints and models, which are not included in KiCad and its plugins itself.

## Details on KiCad settings

The design was made with KiCad 8.0. Installed plugins are the Alternate KiCad Library (by Dawid Cislo), the Interactive Html Bom (by qu1ck) and the KiCAD JLCPCB tools (by Bouni).
Additional Footprints or 3D models are found in the `./models` folder.\
Always check the JLCPCB options yourself! The tools seemed to "forget" some data from time to time.

## Ordering and building the PCB

For ordering instructions refer to [ORDERING INSTRUCTIONS](/ORDERING_INSTRUCTIONS.md).
For building instructions refer to [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md).
