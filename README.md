# Pico Spelunking

Some of the code is based off of examples provided from SunFounder [here](https://docs.sunfounder.com/projects/thales-kit/en/latest/Hello,%20Breadboard!.html)
but converted to a C equivalant.

## Building

```sh
git submodule update --init
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
mkdir build
cd build
cmake ..

make ... (button, breadboard-hello, blink, etc...)
```
