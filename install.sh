#!/bin/bash

# Define paths
BUILD_DIR="./build"
SERVICE_FILE_DIR="./"
BIN_DIR="/usr/local/bin"
SERVICE_DIR="/etc/systemd/system"

# Check if run as root
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

# Rename and copy the executable
cp "${BUILD_DIR}/main" "${BIN_DIR}/pi-summoner"
chmod +x "${BIN_DIR}/pi-summoner"

# Step 2: Copy the service file and set permissions
cp "${SERVICE_FILE_DIR}/pi-summoner.service" "${SERVICE_DIR}"
chmod 644 "${SERVICE_DIR}/pi-summoner.service"

# Step 3: Reload systemd and enable/start the service
systemctl daemon-reload
systemctl enable pi-summoner.service
systemctl start pi-summoner.service

echo "Pi-Summoner installed and started successfully."
