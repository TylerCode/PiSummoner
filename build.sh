#!/bin/bash

echo "Build started."

# Check for an environment variable to determine if we are compiling for a non-Raspberry Pi environment
if [ "$NON_RPI_BUILD" == "1" ]; then
    echo "Compiling for a non-Raspberry Pi environment..."
    gcc main.c -o main -lmicrohttpd -lrt
else
    echo "Compiling for Raspberry Pi..."
    gcc main.c -o main -lpigpio -lmicrohttpd -lrt
fi

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

chmod +x main

rm -rf build
mkdir build
mv main build

echo "Build complete!"
