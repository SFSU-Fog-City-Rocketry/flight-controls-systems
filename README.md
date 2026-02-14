# flight-controls-systems
Repository will host the Flight Controls System for the SFSU Fog Rocketry Club


# Prerequisites

> [!NOTE]
> Only do the step for installing Python and Pip/Pipx on your specific system
> Required for installing platformIO.

Refer to the getting started page [link](https://engine3d-dev.github.io/0.1/getting_started/) to only install `pipx`

## Installing PlatformIO

If your not using pipx, but pip:

```
pip install platformio
```

If your using pipx:
```
pipx install platformio
```


# Build using PlatformIO

To build the project. Run the following conan command:

```
pio run
```

## Flashing with PlatformIO

To flash using PlatformIO. Do the following command:
```
pio run -t upload
```

# Project Structure

* `drivers/` will contain different implementations of drivers. OR implementation for sensors that use those driver implementations.
* `drivers/esp32/` is the hal abstraction for the `esp32-wroom-32` devices. This contains a modern C++ abstraction to interact with the esp32 devices. Including wrappers for serial communication, GPIO pins, and other forms of wrappers around the `espidf`.
* `application/` represents where the application-side code will reside. This will be where any of the device interactive code will be contained.

# Brief Context

> [!NOTE]
> Plans in having this to be moved to a WIKI or some documentation page.

## Serial Communication Protocols


| `UART` | `SPI` | `I2C` | CAN |
| :--- | :---- | :--- | :---
| Universe-Asynchronous-Receiver-Transceiver. <br> Does not need a shared clock for synchronizing <br> sending and receiving bytes of data. | Temp | Temp | Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
