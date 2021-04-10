# Pico Spelunking

## Building

```sh
git submodule update --init
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi
mkdir build
cd build
cmake ..

make ... (button, breadboard-hello, blink, etc...)
```
