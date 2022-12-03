#!/bin/bash

cd /home/latentghost/ker1/
cd linux-5.19.8
cp ../../config-rev-9-gold .config
make nconfig
sudo make bzImage
