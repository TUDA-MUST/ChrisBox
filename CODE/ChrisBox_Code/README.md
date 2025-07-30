# ChrisBox Code

In this section the main features of the ChrisBox code are explained. The code was written in Arduino IDE 2.x.x.

> [!NOTE]
> In the code the [Protocentral library for the ADS1220](https://github.com/Protocentral/Protocentral_ADS1220) is used, which also is under the MIT license. Some minor changes are made in the library to adapt the pins to the wiring of the ChrisBox PCB.

## Code structure

There are the following sections in the code:

- include for the used libraries
- definitions for pins
- some settings and constants. Settings regarding ESP NOW, UART, BAUDRate etc. are made here.
- variables, which are used at runtime
- setup for ESP NOW
- setup for UART
- void setup(). The different parts (e.g. UART) are started here, if the part is wished (see settings and constants).
- void loop(). This is repeated after the setup until the power is switched of or reset is pressed. The ADCs are read and the measured values published on the Serial port, ESP NOW and/or UART
- support functionality
