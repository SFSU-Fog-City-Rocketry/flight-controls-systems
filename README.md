# flight-controls-systems
Repository will host the Flight Controls System for the SFSU Fog Rocketry Club


# Build Instructions

To build the project. Run the following conan command:


```
conan build . -b missing -s build_type=Debug
```


## Flashing the ESP32

> [!NOTE]
> This needs to be tested for flashing. I am adding this for documenting.
> Hoping to write some testing code to see if this'll work.

### Installing esptool

To install esp tool, do the following:

```
pipx install esptool
```


### Flash
```bash
esptool.py --chip esp32 --port <port_value> --baud 460800 write_flash -z 0x1000 my_app.bin
```
