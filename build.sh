#!/bin/bash

gcc main.c -o main -lpigpio -lmicrohttpd -lrt
chmod +x main
mkdir build
mv main build