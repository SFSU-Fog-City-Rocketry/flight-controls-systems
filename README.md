# flight-controls-systems
Repository will host the Flight Controls System for the SFSU Fog Rocketry Club


# Build Instructions

To build the project. Run the following conan command:


```
conan build . -b missing -s build_type=Debug
```


## To Flash the ESP32

```bash
esptool.py --chip esp32 --port <port_value> --baud 460800 write_flash -z 0x1000 my_app.bin
```


