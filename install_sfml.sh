#!/bin/sh

sudo apt-get update
sudo apt-get install -y build-essential gcc g++ make cmake git pkg-config libx11-dev libxrandr-dev libxcursor-dev libxi-dev libxext-dev libudev-dev libgl1-mesa-dev libegl1-mesa-dev libfreetype6-dev libharfbuzz-dev libopenal-dev libflac-dev libogg-dev libvorbis-dev libsndfile1-dev libmbedtls-dev libssh2-1-dev
git clone https://github.com/sfml/sfml
cd sfml
mkdir build
cd build
cmake ..
make
sudo make install
