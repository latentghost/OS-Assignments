#!/bin/bash

cd /home/latentghost/
mkdir ker3
cp linux-5.19.8.tar ker3/
cd ker3/
tar -xf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
make nconfig
sudo make -j$(nproc)
