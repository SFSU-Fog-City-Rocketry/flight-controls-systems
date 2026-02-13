# flight-controls-systems
Repository will host the Flight Controls System for the SFSU Fog Rocketry Club


# Prerequisites

> [!NOTE]
> Only do the step for installing Python and Pip/Pipx on your specific system
> Required for installing platformIO.

Refer to the getting started page [link](https://engine3d-dev.github.io/0.1/getting_started/) for installing Pip/Pipx.



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
