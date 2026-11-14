## Flights Control Systems

## Setting up Conan

Follow the [getting started](https://engine3d-dev.github.io/0.1/getting_started/) page that I use for a separate open-source project. The getting started up until you reach the Conan profiles step, and continue the remaining steps from this README.

## Setting up Conan Profiles

```
conan config install https://github.com/SFSU-Fog-City-Rocketry/conan-config.git
```

## Before Building this Repo do the following


Just call these two commandline commands

```
conan remote add engine3d-conan https://libhal.jfrog.io/artifactory/api/conan/engine3d-conan
```


```
conan remote add libhal-trunk https://libhal.jfrog.io/artifactory/api/conan/trunk-conan
```

## How to Build


Using conan to build:


```
conan build . -pr:h hal/tc/arm-gcc-14.2 -pr:h pico/pico -of build -b=missing
```


## How to Flash

Copy this command to enable **picotool**.

Picotool is how you will be able to flash the code that you write for this flight control system repository.

### Sourcing conanbuild.sh

Source the **conanbuild.sh** to be able to use **picotool**:

```
source build/build/rp2040/Release/generators/conanbuild.sh
```

### Using picotool to flash your code

```
picotool load build/build/rp2040/Release/adc_demo.uf2 -f
```
