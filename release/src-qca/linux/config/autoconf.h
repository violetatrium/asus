/*
 * Automatically generated C config: don't edit
 */
#define AUTOCONF_INCLUDED

/*
 * Library Configuration
 */

/*
 * Force build (Normally built when required)
 */
#define CONFIG_LIB_LIBPTHREAD_FORCE 1
#undef  CONFIG_LIB_LIBNVRAM_FORCE
#undef  CONFIG_LIB_LIBNTFS3G_FORCE
#undef  CONFIG_LIB_LIBBT_FORCE
#undef  CONFIG_LIB_READLINE_FORCE
#undef  CONFIG_LIB_LIBPCAP_FORCE
#undef  CONFIG_LIB_NCURSE_FORCE
#undef  CONFIG_LIB_FLEX_FORCE
#define CONFIG_LIB_LIBUPNP_FORCE 1
#undef  CONFIG_LIB_LIBDLNA_FORCE
#undef  CONFIG_LIB_LIBFFMPEG_FORCE
#undef  CONFIG_LIB_LIBGDBM_FORCE
#undef  CONFIG_LIB_LIBID3TAG_FORCE
#undef  CONFIG_LIB_PCRE_FORCE
#undef  CONFIG_LIB_ZLIB_FORCE
#define CONFIG_LIB_LIBSTDC_PLUS_FORCE 1
#undef  CONFIG_USER_HELLO_WORLD

/*
 * Force build extra libraries in uClibc
 */
#define CONFIG_LIB_CRYPT_FORCE 1
#define CONFIG_LIB_LIBM_FORCE 1
#undef  CONFIG_LIB_NSL_FORCE
#define CONFIG_LIB_UTIL_FORCE 1
#define CONFIG_LIB_RESOLV_FORCE 1
#undef  CONFIG_LIB_RT_FORCE
#define CONFIG_LIB_USB0112_FORCE 1
#undef  CONFIG_LIB_USB100_FORCE
#define CONFIG_LIB_LIBSTDC_PLUS_FORCE 1

/*
 * MTD utils
 */
#undef  CONFIG_USER_MTDUTILS
#undef  CONFIG_USER_MTDUTILS_ERASE
#undef  CONFIG_USER_MTDUTILS_ERASEALL
#undef  CONFIG_USER_MTDUTILS_FTL_CHECK
#undef  CONFIG_USER_MTDUTILS_FTL_FORMAT
#undef  CONFIG_USER_MTDUTILS_MKFSJFFS
#undef  CONFIG_USER_MTDUTILS_MKFSJFFS2
#undef  CONFIG_USER_MTDUTILS_NFTLDUMP
#undef  CONFIG_USER_MTDUTILS_NFTL_FORMAT
#undef  CONFIG_USER_MTDUTILS_NANDDUMP
#undef  CONFIG_USER_MTDUTILS_NANDTEST
#undef  CONFIG_USER_MTDUTILS_NANDWRITE
#undef  CONFIG_USER_MTDUTILS_DOC_LOADBIOS
#undef  CONFIG_USER_MTDUTILS_DOC_LOADIPL

/*
 * Network Applications
 */
#undef  CONFIG_USER_3G
#define CONFIG_USER_BRCTL_BRCTL 1
#undef  CONFIG_USER_BIGPOND
#undef  CONFIG_USER_BT_UTILS
#undef  CONFIG_USER_BT_AVINFO
#undef  CONFIG_USER_BT_BCCMD
#undef  CONFIG_USER_BT_CIPTOOL
#undef  CONFIG_USER_BT_HCICONFIG
#undef  CONFIG_USER_BT_HCIATTACH
#undef  CONFIG_USER_BT_HCISECFILTER
#undef  CONFIG_USER_BT_HCITOOL
#undef  CONFIG_USER_BT_L2PING
#undef  CONFIG_USER_BT_PPPORC
#undef  CONFIG_USER_BT_SDPTOOL
#undef  CONFIG_USER_CTORRENT
#undef  CONFIG_USER_DHCP6
#undef  CONFIG_USER_DHCP6_SERVER
#undef  CONFIG_USER_DHCP6_CLIENT
#undef  CONFIG_USER_DNSMASQ
#undef  CONFIG_USER_DISKTYPE
#undef  CONFIG_USER_ECHO_SERVER
#undef  CONFIG_USER_STORAGE
#undef  CONFIG_USER_PROFTPD
#undef  CONFIG_USER_SAMBA
#undef  CONFIG_USER_GOAHEAD_HOSTNAME
#undef  CONFIG_USER_MTDAAPD
#undef  CONFIG_LIB_LIBGDBM_FORCE
#undef  CONFIG_LIB_LIBID3TAG_FORCE
#undef  CONFIG_USER_DNS_RESPONDER
#undef  CONFIG_USER_GOAHEAD_HTTPD
#undef  CONFIG_USER_GOAHEAD_IPV6
#undef  CONFIG_USER_GOAHEAD_SSL
#undef  CONFIG_USER_GOAHEAD_HOSTNAME
#undef  CONFIG_USER_GOAHEAD_GreenAP
#undef  CONFIG_USER_WIZARD
#undef  CONFIG_USER_GOAHEAD_LANG_EN
#undef  CONFIG_USER_GOAHEAD_LANG_ZHTW
#undef  CONFIG_USER_GOAHEAD_LANG_ZHCN
#define CONFIG_USER_GOAHEAD_LANG_EN 1
#undef  CONFIG_USER_RALINKIAPPD
#define CONFIG_USER_IGMP_PROXY 1
#undef  CONFIG_USER_INADYN
#define CONFIG_USER_IPTABLES_IPTABLES 1
#undef  CONFIG_USER_IPTABLES_IP6TABLES
#undef  CONFIG_USER_IPSEC_TOOLS
#define CONFIG_USER_IPROUTE2 1
#undef  CONFIG_USER_IPROUTE2_SS
#undef  CONFIG_USER_IPROUTE2_NSTAT
#undef  CONFIG_USER_IPROUTE2_IFSTAT
#undef  CONFIG_USER_IPROUTE2_RTACCT
#undef  CONFIG_USER_IPROUTE2_LNSTAT
#undef  CONFIG_USER_IPROUTE2_IP
#undef  CONFIG_USER_IPROUTE2_RTMON
#define CONFIG_USER_IPROUTE2_TC 1
#define CONFIG_LIB_LIBM_FORCE 1
#undef  CONFIG_USER_MATRIXSSL
#undef  CONFIG_USER_MINIUPNPD
#undef  CONFIG_USER_MKDOSFS
#undef  CONFIG_USER_NTPCLIENT_NTPCLIENT
#undef  CONFIG_USER_NTPCLIENT_ADJTIMEX
#undef  CONFIG_USER_OPENSSL
#undef  CONFIG_USER_OPENSWAN
#undef  CONFIG_USER_P910ND
#undef  CONFIG_USER_PORTMAP
#undef  CONFIG_USER_PPPD
#undef  CONFIG_USER_PPPD_WITH_PPPOE
#undef  CONFIG_USER_PPPD_PPPSTATS
#undef  CONFIG_USER_PPPD_PPPDUMP
#undef  CONFIG_USER_PPPD_PPPCHAT
#undef  CONFIG_USER_RPPPPOE_RELAY
#undef  CONFIG_USER_RPPPPOE_SNIFF
#undef  CONFIG_USER_PPPOECD
#define CONFIG_USER_PPTP_CLIENT 1
#undef  CONFIG_USER_ZEBRA
#undef  CONFIG_LIB_LIBZEBRA_FORCE
#define CONFIG_USER_RP_L2TP 1
#undef  CONFIG_USER_RADVD
#undef  CONFIG_USER_RADVD_DUMP
#define CONFIG_USER_802_1X 1
#undef  CONFIG_USER_RT2561_802_1X
#undef  CONFIG_USER_SNORT
#undef  CONFIG_USER_SNMPD
#undef  CONFIG_USER_TOTD
#undef  CONFIG_USER_UVC_STREAM
#define CONFIG_USER_UPNP_IGD 1
#undef  CONFIG_USER_WPA_SUPPLICANT
#define CONFIG_USER_WSC 1
#define CONFIG_LIB_LIBPTHREAD_FORCE 1
#define CONFIG_LIB_LIBUPNP_FORCE 1

/*
 * Wireless-tools
 */
#define CONFIG_USER_WIRELESS_TOOLS 1
#define CONFIG_USER_WIRELESS_TOOLS_IWCONFIG 1
#undef  CONFIG_USER_WIRELESS_TOOLS_IWGETID
#undef  CONFIG_USER_WIRELESS_TOOLS_IWLIST
#define CONFIG_USER_WIRELESS_TOOLS_IWPRIV 1
#undef  CONFIG_USER_WIRELESS_TOOLS_IWSPY
#undef  CONFIG_USER_WIRELESS_TOOLS_IWEVENT

/*
 * Miscellaneous Applications
 */
#define CONFIG_USER_BUSYBOX_BUSYBOX 1
#undef  CONFIG_USER_BONNIE
#undef  CONFIG_USER_ETHTOOL
#undef  CONFIG_DHRYSTONE
#undef  CONFIG_DHCPFWD
#undef  CONFIG_USER_GDB_GDBREPLAY
#undef  CONFIG_USER_GDB_GDBSERVER
#undef  CONFIG_USER_IXIA_ENDPOINT
#undef  CONFIG_USER_LMBENCH3
#define CONFIG_USER_MTD_WRITE 1
#undef  CONFIG_USER_MPSTAT
#undef  CONFIG_USER_NETCAT
#undef  CONFIG_USER_NETSTAT_NAT
#undef  CONFIG_USER_NTFS3G
#undef  CONFIG_USER_NTFSPROGS
#undef  CONFIG_LIB_LIBNTFS3G_FORCE
#undef  CONFIG_USER_STRACE_STRACE
#undef  CONFIG_USER_TCPDUMP
#undef  CONFIG_USER_PCIUTIL_LSPCI
#undef  CONFIG_USER_PCIUTIL_SETPCI
#undef  CONFIG_USER_LSUSB
#define CONFIG_USER_USBMODESWITCH 1
#define CONFIG_LIB_USB0112_FORCE 1
#define CONFIG_USER_COMGT 1
#define CONFIG_USER_SDPARM 1
#undef  CONFIG_USER_WATCHDOG

/*
 * Ralink Proprietary Application
 */
#define CONFIG_RALINKAPP 1
#define CONFIG_RALINKAPP_ATED 1
#define CONFIG_RALINKAPP_REG_RW 1
#undef  CONFIG_RALINKAPP_CSR
#define CONFIG_RALINKAPP_FLASH 1
#define CONFIG_RALINKAPP_HWNAT 1
#undef  CONFIG_RALINKAPP_MII_MGR
#undef  CONFIG_RALINKAPP_NVRAM
#undef  CONFIG_RALINKAPP_L2_MANAGE
#define CONFIG_RALINKAPP_GPIO 1
#undef  CONFIG_RALINKAPP_SPI
#undef  CONFIG_RALINKAPP_I2C
#undef  CONFIG_RALINKAPP_MEMORY_USAGE
#undef  CONFIG_RALINKAPP_SWQOS
#undef  CONFIG_RALINKAPP_I2S
#undef  CONFIG_RALINKAPP_PCM
#undef  CONFIG_RALINKAPP_CLS
#undef  CONFIG_RALINKAPP_WAPI
#define CONFIG_RALINKAPP_SCRIPTS 1

/*
 * Windows Rally Program
 */
#define CONFIG_USER_LLTD 1

/*
 * ASUS Applications
 */
#define CONFIG_ASUS_SHARED 1
#define CONFIG_ASUS_NVRAM_UTIL 1
#define CONFIG_ASUS_LIBDISK 1
#define CONFIG_ASUS_NETCONF 1
#define CONFIG_ASUS_RC 1
#define CONFIG_DPROXY 1
#define CONFIG_ASUS_INFOSVR 1
#define CONFIG_ASUS_DETECTWAN 1
#define CONFIG_ASUS_HTTPD 1
#define CONFIG_ASUS_WWW 1
#define CONFIG_PPPD 1
#define CONFIG_PPPOE_RELAY 1
#define CONFIG_BPALOGIN 1
#define CONFIG_TC 1
#define CONFIG_UDHCPD 1
#define CONFIG_ASUS_NTPCLIENT 1
#define CONFIG_EZ_IPUPDATE 1
#define CONFIG_VSFTPD 1
#define CONFIG_ASUS_SAMBA 1
#define CONFIG_ASUS_LPRNG 1
#define CONFIG_ASUS_U2EC 1
#define CONFIG_ASUS_WANDUCK 1
#define CONFIG_ASUS_NETWORK_MAP 1
#define CONFIG_ASUS_NTFS3G 1
#define CONFIG_USB_TEST 1
#define CONFIG_VENDOR "Ralink"
#define CONFIG_PRODUCT "RT3883"
#define CONFIG_LINUXDIR "linux-2.6.21.x"
#define CONFIG_LIBCDIR ""
#define CONFIG_LANGUAGE ""
#define VENDORS_AUTOCONF_INCLUDED
#undef AUTOCONF_INCLUDED
