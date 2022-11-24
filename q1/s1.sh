#!/bin/bash

cd /home/latentghost/
mkdir ker1
cp linux-5.19.8.tar ker1/
cd ker1/
tar -xf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
make nconfig
sudo make bzImage