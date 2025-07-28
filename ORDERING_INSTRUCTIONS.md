# Ordering Instructions

In this document information about the ordering process of various components can be found. This is segmented in the core PCB, required components for the PCB and additional material for a full ChrisBox setup.
It is recommended to read the other documents in this repository before ordering, as provided explainations about the different components ensure understanding of the ChrisBox and help avoiding mistakes in the ordering process.

- [README](/README.md)
- [BUILDING INSTRUCTIONS](/BUILDING_INSTRUCTIONS.md)

## PCB

The PCB is designed for ordering at JLCPCB. Files are prepared for a populated PCB. These files are made with the JLCPCB Tool in kiCad. Keep in mind that not all components on the PCB can be placed by JLCPCB, so they have to be ordered seperatly (Feedback resistors and shield).

The files are found in `./PCB/jlcpcb`. The gerber-files contain information about the raw PCB, the production-files contain the information about components and their positions on the PCB. The ordering process should look similar to the following screenshots:

<p align="center">
      <img src="/data/ChrisBox_JLC_1.png" width="49%">
      <img src="/data/ChrisBox_JLC_2.png" width="49%">
</p>

In the ordering process, select the option "Order Number(Specify Position)" if you want to specify the position of the order number on your PCB. The silkcreen contains a text "JLCJLCJLCJLC" for this purpose under the shield. More information about this topic can be found here: [JLCPCB article](https://jlcpcb.com/help/article/How-to-remove-order-number-from-your-PCB).

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
) and [**1x BMI-S-205-C**](https://www.mouser.de/ProductDetail/Laird-Performance-Materials/BMI-S-205-C?qs=5UmOb8GQ3yK2YqcYqxMNeQ%3D%3D&srsltid=AfmBOorolz6B2jLrK0CN6-kLWo5Zzo08A8Ydt0RMlH1AmU8FWxSRlpGi
) (F for frame, C for cover. These are two different pieces, one to be soldered on the PCB, the other to be stacked above.)

### Parts for Basic Measurement Setup

- [**4x USB-C cable**](https://www.amazon.de/Amazon-Basics-USB-Type-Cable-White/dp/B01GGKZ0V6/ref=sr_1_1_ffob_sspa?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=80VN82ANXT8J&dib=eyJ2IjoiMSJ9.vgjmrp-aDf_bGEG0J0PDTxjd0Qp5fMKhsOm-B0mDXrhbRaYK8NBDM03t5GbRuHV3Rt8b8IN2fhvhON1Xwo2N0tOTRJD2vNE0FyKrH9_0vvxciWoiR_mtRzBAOj6633rsI0j545gj2UuqNfCdq_h3FPnJ0Aw5l1zK1_SrPElwF3q577uXC1i6WSqs4VeIR27R7fAu27XK2MVPb0t3tDcMk0Jye3cpDEduj-q1Zqw_qNY.Opa50E3FN3Dd8NRjDSQqUPbjJRZN-wKM0Mvl5LQuFt0&dib_tag=se&keywords=usb%2Bc%2Bkabel&qid=1753699122&sprefix=usb%2Bc%2Bkabel%2Caps%2C80&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1) to connect up to four sensors to the PCB
- [**USB-C female connectors/adapters**](https://www.amazon.de/PENGLIN-Stecker-Adapter-Dr%C3%A4hten-Support-Modul/dp/B09YLVSPQX/ref=sr_1_2_sspa?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=3T94KPK6QQP81&dib=eyJ2IjoiMSJ9.EqoXHDrlrt2_A0cLlTeGxh6hGppBbbqbKIskqD6gxpyrvy-NtSj1prO1v9BtJ2MJOFxKJ02KDHJo4hF-XAWqVcq9rhuhHl3JHem7T6ZtQa5MzYmlerkeNecnb5LSLppPhLMNJ5M824s_Pdvz2yPA3ujy5lOsmQNyPnBt8on-8fBIwgZkYYIQFAwI-JlRrRbTgkqfj9Hy16AA83MysnQzmjpKQUw-mpsLFktj3oHvDlM.dR9aHifNoiTt5DBjIE_X1pH8ZvCfO85IRelC873oQ_I&dib_tag=se&keywords=usb%2Bc%2Bfemale%2Bsoldering&qid=1753699164&sprefix=usb%2Bc%2Bfemale%2Bsoldering%2Caps%2C76&sr=8-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1) for sensors (number depending on the amount of sensors you work with). Important is USB 2.0 functionality, which means that there are D+ and D- connections to solder the ferroelectret to. A shield around the sensor can be soldered to the housing of the adapter.
- [**Micro USB cable**](https://www.amazon.de/Amazon-Basics-%C3%9Cbertragungsgeschwindigkeit-vergoldeten-Steckern/dp/B0711PVX6Z/ref=sr_1_1_ffob_sspa?crid=P42ZCKRZMITQ&dib=eyJ2IjoiMSJ9.862P6e4T0ro17qzqzqj7ZvPDv5CFpfW7NreERp7BZc43L2qEfKYfaXO7NBIHHNoE9VND49e1tjbIMNlVhRUyH4c0p6e8MvgVeZj9nvwSPcbUA5fnzwebti8KgCyqHZPsaNKvb1Fr8nrsCg3t3wMHm0uIBB0jIhA8m1KGGW68JeOyqVTYmKs5Y2Bynf7TTYOyrTAWB_48l9QlZfaH0sZ8UvaAgZKWzN2jy7j2dX7ljcU.aUsRSGJvwDCuVKMs1TrMqY4e1wHhJZncyf9X3PtXxc4&dib_tag=se&keywords=micro%2Busb%2Bkabel&qid=1753699206&sprefix=micro%2Busb%2B%2Caps%2C84&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1) to connect the PCB to a PC

## Full ChrisBox Setup

- [**1x Nextion NX3224K024**](https://nextion.tech/datasheets/nx3224k024/) Display
- 3D prints for the casing (these are probably no parts to be ordered, but to be printed in lab/at home)
- [**4x threaded insert**}(https://cnckitchen.store/de/products/heat-set-insert-m3-x-3-short-version-100-pieces?srsltid=AfmBOornlfvZyaQYzeZzhRBzZKCRoDfPxM9L4EdxtAn12wZz5er1hIQk) M3 x 3,0 (the CAD has a blind hole of 4mm, and a diameter of 4mm)
- [**4x screw**}(https://www.amazon.de/Sechskopf-Knopf-Zylinderschrauben-Gewindeschrauben-Sechskantschrauben-Maschinenschrauben/dp/B0B3MGZ7T2/ref=sr_1_6?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=FAFPGZ2V0XM1&dib=eyJ2IjoiMSJ9.v1rRW_mBIfRziI334hjc46z12uBmLSZbKBzMMLnH29wag-l4WUZt8dW__fPZG4pG-PhCgUnbvHOA2-hHh9MMFTHHPAMYOrxTkJw6NtRt3AurmrEAIhInxn6k_6bAEnKW72UItmjv7Yld4Y_C7H6KjwbdExwgNt6EWuoRGrTeREoaqaPFFgXJEKvtueAzfyCj1Ovh9nvqkK61WQw8uHM6H6BAQDqbhbLzkaxw95yXvdSq6ZoC4vVQT0VexMTsXbpHnjTd14SXVzO9HTXImlbo8t_xP9XIxdQWKS35ccfRCCQ.DXMdmuSZSZpUR3ooVibcpTV0weTlLRJambx-1QhvLDY&dib_tag=se&keywords=m3%2Bx%2B25&qid=1753699396&sprefix=m3%2Bx%2B25%2Caps%2C99&sr=8-6&th=1) M3x25 (the specific choice of screw head is not relevant, but the CAD was theoretically designed for countersunk heads)
