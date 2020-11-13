

Asus MAP 1300 Router set is a 11AC WiFi Router. Following are the specifications.

cpu model	: ARM Quadcore

RAM Size        : 128MB

Flash Size      : 128MB

Serial Pin Connections:
As marked on the board. There are 4-pins marked VCC, RX, GND and TX 
behind WAN port.

   Asus Router   ----------------------------   CP2102 module

   * VCC ---------------------------------- Leave it. Dont connect anything.
   * Rx  --------------------------------- Tx
   * GND --------------------------------- GND
   * Tx  -------------`*------------------ Rx


Build:

Build involves two steps ie preparing the build system and build instructions.


    1. prepare build system

        a. Ubuntu
                Install these packages (I used synaptic: "sudo synaptic")

                libncurses5
                libncurses5-dev
                m4
                bison
                gawk
                flex
                libstdc++6-4.4-dev
                g++-4.4
                g++
                gengetopt
                lib32z1-dev
                git (or git-core)
                gitk
                zlib1g-dev
                pkg-config
                autoconf
                autopoint (or gettext)
                libtool
                libtool-bin
                shtool
                autogen
                mtd-utils
                intltool
                sharutils
                docbook-xsl-*
                libstdc++5
                texinfo
                dos2unix (or tofrodos)
                xsltproc
                uboot-mkimage
                device-tree-compiler
                python 2.7 or above.
                qemu
                gperf
                liblzo2-dev
                uuid-dev
                build-essential
                lzma-dev
                liblzma-dev
                lzma
                binutils-dev
                patch
                cmake
                intltool
                libglib2.0-dev
                gtk-doc-tools

                If you are using Ubuntu amd64, you may need to install 32-bit packages listed below.
                        libc6-i386
                        lib32stdc++6
                        lib32z1
                        libelf1:i386
                        libncurses5:i386
                        ia32-libs
                        libc6-dev-i386
                        gcc-multilib g++-multilib

        b. Fedora
                python 2.7 or above.
                sudo yum groupinstall "Development Tools"
                sudo yum install gettext-devel libxml2-devel mtd-utils-ubi ncurses-devel \
                        zlib-devel intltool sharutils docbook-dtds docbook-style-xsl \
                        uboot-tools dtc gengetopt qemu gperf cmake glib2-devel gtk-doc

                If you are using Fedora 19 or above, you need to install below packages.
                sudo yum groupinstall "C Development Tools and Libraries"

                If you are using Fedora x86_64, you may need to install 32-bit packages listed below.
                        elfutils-libelf.i686
                        glibc.i686
                        libstdc++.i686
                        zlib.i686

                If you are using Fedora 24+, you may need to install 32-bit packages listed below.
                        ncurses-compat-libs.i686
2. For Asus MAP AC1300
         
         - Extract tools/openwrt-gcc463.arm.tar.bz2 directory to /opt
           (sudo tar -xvf tools/openwrt-gcc463.arm.tar.bz2 -C /opt/)
                    
         - Issue the build command. Syntax is ./build.sh <Asus_HW_MODEL>  <--add <path_to_unum.tgz> |--no-changes> <Asus_HW_MODEL>. 
         For eg: to build for Asus' MAP AC1300, assuming the unum is at ~/unum.tgz, the command "./build.sh asus_map_ac1750 --add ~/unum.tgz  asus_map_ac1300"
         
         - It may take an hour to complete the build
         
         - Firmware is copied at, firmware/firmware_sysupgrade.bin
         
         - If the build process fails for some dependencies, install the dependencies and build
           from scratch on a fresh codebase

