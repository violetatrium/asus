#!/bin/bash

echo "$1"
echo "$2"


if [ "$1" == "" ] || [ "$2" == "" ]; then
  echo "Usage: $0 <AP_IP_ADDRESS> <AP_SSH_PASSWORD> [FIRMWARE_FILE]"
  echo "Make sure you have ssh and sshpass..."
  echo "sudo apt-get install sshpass"
  exit 1
fi

MY_DIR=$(dirname "$0")
cd "$MY_DIR"

IP="$1"
PASSWD="$2"
FIRMWARE_FILE_DEF="$PWD/firmware/firmware_sysupgrade.bin"
if [ "$3" != "" ]; then
  FIRMWARE_FILE="$3"
else
  FIRMWARE_FILE="$FIRMWARE_FILE_DEF"
fi
SSHOPT="-q -o UserKnownHostsFile=/dev/null -o StrictHostKeyChecking=no"

if [ ! -f "$FIRMWARE_FILE" ]; then
  echo "Error: firmware file not found:"
  echo "       $FIRMWARE_FILE"
  exit 1
fi

echo "Uploading the firmware..."
echo "sshpass -p \"$PASSWD\" /usr/bin/scp $SSHOPT \"$FIRMWARE_FILE\" admin@$IP:/tmp/linux.trx"
sshpass -p "$PASSWD" /usr/bin/scp $SSHOPT "$FIRMWARE_FILE" admin@$IP:/tmp/linux.trx
if [ $? -ne 0 ]; then
  echo "Error: failed to upload the test firmware file to AP!"
  exit 5
fi
echo "Sending commands to flash the new firmware... It may take upto 10 minutes."
echo "sshpass -p \"$PASSWD\" ssh $SSHOPT admin@$IP -C  \"/sbin/rc rc_service restart_upgrade\""
sshpass -p "$PASSWD" ssh $SSHOPT admin@$IP -C  /sbin/rc rc_service restart_upgrade
