#!/bin/bash

echo "Build started."

gcc main.c -o main -lpigpio -lmicrohttpd -lrt
chmod +x main
rm -r build
mkdir build
mv main build

echo "Build complete!"
