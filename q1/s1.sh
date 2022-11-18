#!/bin/bash

cd /home/latentghost/copy1/linux-5.19.8
make -j$(nproc)
sudo make modules_install
