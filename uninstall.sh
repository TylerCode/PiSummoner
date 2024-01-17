#!/bin/bash

# Define paths
BIN_DIR="/usr/local/bin"
SERVICE_DIR="/etc/systemd/system"
SERVICE_NAME="pi-summoner"

# Check if run as root
if [ "$(id -u)" != "0" ]; then
   echo "This script must be run as root" 1>&2
   exit 1
fi

# Stop and disable the service
systemctl stop ${SERVICE_NAME}.service
systemctl disable ${SERVICE_NAME}.service

# Remove the service file
rm -f "${SERVICE_DIR}/${SERVICE_NAME}.service"

# Reload systemd
systemctl daemon-reload

# Remove the executable
rm -f "${BIN_DIR}/${SERVICE_NAME}"

echo "Pi-Summoner uninstalled successfully."
