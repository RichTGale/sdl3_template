#!/bin/bash

# Uncomment to install on pi
sudo apt install curl wget jq libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev build-essential \
git make pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev \
libpulse-dev libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev \
libxext-dev libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev \
libxtst-dev libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev \
libgles2-mesa-dev libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev \
libthai-dev

#pacaur -S sdl3 sdl3_ttf sdl3_image alsa-lib cmake hidapi ibus jack libdecor libthai fribidi libgl libpulse libusb libx11 libxcursor libxext libxfixes libxi libxinerama libxkbcommon libxrandr libxrender libxss libxtst mesa ninja pipewire sndio vulkan-driver vulkan-headers wayland wayland-protocols

mkdir vendored
cd vendored
# Get SDL3
version=3.2.10
wget $(curl -L https://api.github.com/repos/libsdl-org/SDL/releases/209447334 | jq -r ".assets[].browser_download_url" | grep -m 1 "SDL3-${version}.tar.gz")
tar -xf SDL3-${version}.tar.gz


# et SDL_image
version=3.2.4
wget $(curl -L https://api.github.com/repos/libsdl-org/SDL_image/releases/203451891 | jq -r ".assets[].browser_download_url" | grep -m 1 "SDL3_image-${version}.tar.gz")
tar -xf SDL3_image-${version}.tar.gz

# Get SDL_ttf
version=3.2.2
wget $(curl -L https://api.github.com/repos/libsdl-org/SDL_ttf/releases/209439259 | jq -r ".assets[].browser_download_url" | grep -m 1 "SDL3_ttf-${version}.tar.gz")
tar -xf SDL3_ttf-${version}.tar.gz

#git clone https://github.com/libsdl-org/SDL.git vendored/SDL
#git clone https://github.com/libsdl-org/SDL_ttf.git vendored/SDL_ttf
#git clone https://github.com/libsdl-org/SDL_image.git vendored/SDL_image

cd ./SDL3_ttf-${version}/external
./download.sh

cd ../../..
