#!/bin/bash

# # Uncomment to install on pi
#sudo apt install libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev build-essential \
#git make \ pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev \
#libpulse-dev libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev \
#libxext-dev libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
#libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev \
#libgles2-mesa-dev libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
#libthai-dev

sudo pacaur -S sdl3 sdl3_ttf sdl3_image alsa-lib cmake hidapi ibus jack libdecor libthai fribidi libgl libpulse libusb libx11 libxcursor libxext libxfixes libxi libxinerama libxkbcommon libxrandr libxrender libxss libxtst mesa ninja pipewire sndio vulkan-driver vulkan-headers wayland wayland-protocols

git clone https://github.com/libsdl-org/SDL.git vendored/SDL
git clone https://github.com/libsdl-org/SDL_ttf.git vendored/SDL_ttf
git clone https://github.com/libsdl-org/SDL_image.git vendored/SDL_image

cd vendored/SDL_ttf/external
./download.sh

cd ../../..
