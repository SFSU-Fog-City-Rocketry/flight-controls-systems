## Flights Control Systems


## Setting up Conan Profiles

```
conan config install https://github.com/SFSU-Fog-City-Rocketry/conan-config.git
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
