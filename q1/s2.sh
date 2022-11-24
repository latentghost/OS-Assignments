#!/bin/bash

cd /home/latentghost/
mkdir ker2
cp linux-5.19.8.tar ker2/
cd ker2/
tar -xf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
make nconfig
sudo make -j$(nproc)
