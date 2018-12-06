MODEL=$1
rm -f release/src/router/unum/unum.tgz
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
  echo "Build the Readynet based firmware with UNUM additons (--add option)"
  echo "or without them (--no-changes) option."
  exit 2
fi

if [ "$MODEL" == "asus_map_ac1750" ]; then
	MODEL="map-ac1750"
	fw="release/src-qca/image/MAP-AC1750.trx"
else
	echo "This model is not supported yet"
	exit 1
fi
mydir=`pwd`

export PATH=/opt/openwrt-gcc463.mips.mesh/bin:$PATH
export STAGING_DIR=/opt/openwrt-gcc463.mips
cd release/src-qca
make $MODEL
cd $mydir
mkdir -p firmware
cp $fw firmware/firmware_sysupgrade.bin
