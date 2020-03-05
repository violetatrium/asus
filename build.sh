#!/bin/bash -e
rm -f release/src/router/unum/unum.tgz

# lighttpd is unhappy being rebuilt
git clean -xdf -- release/src/router/lighttpd-1.4.39

if [ "$1" == "--add" ]; then
  UNUM="$2"
  if [ ! -f "$UNUM" ]; then
    echo "Unable to find \"$UNUM\"."
    echo "Please specify full path to the file."
    exit 1
  fi
  MODEL="$3"
  cp $UNUM release/src/router/unum/unum.tgz
  echo "Building firmware with $UNUM..."
elif [ "$1" == "--no-changes" ]; then
  unset UNUM
  echo "Building firmware without changes."
  MODEL="$2"
else
  echo "Usage: $0 <--add <path_to_unum.tgz> <Asus_HW_MODEL> |--no-changes> <Asus_HW_MODEL>"
  echo "Build the Asus based firmware with UNUM additons (--add option)"
  echo "or without them (--no-changes) option."
  exit 2
fi

if [ "$MODEL" == "asus_map_ac1300" ]; then
	MODEL="rt-ac58u"
	fw="release/src-qca-dakota/image/RT-AC58U.trx"
else
	echo "This model is not supported yet"
	exit 1
fi

echo $UNUM
echo $MODEL

export PATH=/opt/openwrt-gcc463.arm/bin:$PATH
export STAGING_DIR=/opt/openwrt-gcc463.arm
# Create a link to provision file
#ln -sf /var/provision_info.htm release/src-qca-dakota/router/www/provision_info.htm

# Dealing with artefacts leftover mess (till normal fix)
touch release/src/router/libdaemon/configure
touch release/src/router/libxml2/configure

mydir=`pwd`
cd release/src-qca-dakota/
make $MODEL
cd $mydir
mkdir -p firmware
cp $fw firmware/firmware_sysupgrade.bin

