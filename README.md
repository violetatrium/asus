et Up Environment(Tested in Fedora 8/9 and Ubuntu)

    1. prepare environment

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
                git (or git-core)
                gitk
                zlib1g-dev
                autoconf
                autopoint (or gettext)
                libtool
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
2. For Asus LYRA Trio (MAP AC1750):
         
         - Extract tools/openwrt-gcc463.mips.mesh.tar.bz2 directory to /opt
           (sudo tar -xvf openwrt-gcc463.mips.mesh.tar.bz2 -C /opt/)
           
         - Goto the directory release
         
         - Issue the command "./build.sh asus_map_ac1750"
         
         - It may take an hour to complete the build
         
         - Firmware is copied at, firmware/firmware_sysupgrade.bin
         
         - If the build process fails for some dependencies, install the dependencies and build
           from scratch on a fresh codebase

