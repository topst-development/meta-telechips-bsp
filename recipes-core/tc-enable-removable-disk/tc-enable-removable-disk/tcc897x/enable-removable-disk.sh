#!/bin/sh
### BEGIN INIT INFO
# Provides:             Telechips Enable Removable Disk
# Required-Start:
# Required-Stop:
# Default-Start:        5
# Default-Stop:         0
# Short-Description:    Script to enable removable disk
# Description:          Script to enable removable disk after application ready.
### END INIT INFO
#
# -*- coding: utf-8 -*-
# Debian init.d script for Telechips Launcher
# Copyright © 2014 Wily Taekhyun Shin <thshin@telechips.com>

case "$1" in
  start)
	. /etc/profile
	if [ -f /sys/devices/platform/tcc-ehci/ehci_vbus ]; then
		echo 1 > /sys/module/ehci_tcc/parameters/ehci_vbus_control_enable
		echo on > /sys/devices/platform/tcc-ehci/ehci_vbus
	fi

	if [ -f /sys/devices/platform/71b00000.usb_dwc2/dwc2_vbus ]; then
		echo 1 > /sys/module/dwc2/parameters/dwc2_vbus_control_enable
		echo on > /sys/devices/platform/71b00000.usb_dwc2/dwc2_vbus
	fi

	udevadm trigger --action=add --subsystem-match=block --sysname-match=mmcblk1*
	;;
  *)
	echo "Usage: /usr/bin/enable-removable-disk.sh {start}"
	exit 1
esac

exit 0
