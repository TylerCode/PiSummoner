#!/bin/bash

echo "Build started."

gcc main.c -o main -lpigpio -lmicrohttpd -lrt
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

chmod +x main

rm -rf build
mkdir build
mv main build

echo "Build complete!"
