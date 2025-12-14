#!/bin/bash

git clone https://github.com/libsdl-org/SDL.git vendored/SDL
git clone https://github.com/libsdl-org/SDL_ttf.git vendored/SDL_ttf

cd vendored/SDL_ttf/external
./download.sh

cd ../../..
