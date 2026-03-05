# flight-controls-systems
Repository will host the Flight Controls System for the SFSU Fog Rocketry Club


# Prerequisites

> [!NOTE]
> Only do the step for installing Python and Pip/Pipx on your specific system
> Required for installing platformIO.

Refer to the getting started page [link](https://engine3d-dev.github.io/0.1/getting_started/) for installing pipx (or pip).

## Installing PlatformIO

If your not using pipx, but pip:

```
pip install platformio
```

If your using pipx:
```
pipx install platformio
```

# Project Structure

* `drivers/` will contain different implementations of drivers. OR implementation for sensors that use those driver implementations.
* `drivers/esp32/` is the hal abstraction for the `esp32-wroom-32` devices. This contains a modern C++ abstraction to interact with the esp32 devices. Including wrappers for serial communication, GPIO pins, and other forms of wrappers around the `espidf`.
* `application/` represents where the application-side code will reside. This will be where any of the device interactive code will be contained.
* `demos/` contains example code to communicate over various serial communication protocols. These demos are demonstrations in using the API's for communicating sending/receiving data.

# Building the Demos with PlatformIO

To build a specific demo, run the following command:

```
pio run -e <demo>
```

Here is an example for output_pin. To run the output_pin demo.

Use the following command:

```
pio run -e output_pin
```

# Flashing Specific Demo

The flash command will be in this format:

```
pio run -e <demo> -t upload
```

Example for flashing output pin code:

```
pio run -e output_pin -t upload
```

### Flashing Specific Port

To flash to a specific serial device port, do the following:

```
pio run -e output_pin -t upload --upload-port <port>
```

If your device is, lets say `/dev/ttyS0`. This is how the port is specified:

```
pio run -e output_pin -t upload --upload-port /dev/ttyS0
```

# Brief Context

> [!NOTE]
> Plans in having this to be moved to a WIKI or some documentation page.

## Serial Communication Protocols

Here is a brief context summary of the various serial communication protocols.

| `UART` | `SPI` | `I2C` | CAN |
| :--- | :---- | :--- | :---
| Universe-Asynchronous-Receiver-Transceiver. <br> Does not need a shared clock for synchronizing <br> sending and receiving bytes of data. | Temp | Temp | Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
| Temp | Temp | Temp | Temp |
