/*
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Configuration settings for the Echo Ridge ER300
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_ER300_H
#define __CONFIG_ZYNQ_ER300_H

#define CONFIG_EXTRA_ENV_SETTINGS       \
	"bootcmd=run sdboot\0" \
	"fit_image=/boot/fit.itb\0"           \
	"load_addr=0x2000000\0"         \
	"fit_size=0x800000\0"           \
	"flash_off=0x100000\0"          \
	"fdt_high=0x20000000\0"         \
	"initrd_high=0x20000000\0"      \
	"loadbootenv_addr=0x2000000\0" \
	"bootenv=uEnv.txt\0" \
	"bootenv_dev=mmc\0" \
	"serverip=192.168.2.65\0" \
	"ipaddr=192.168.2.46\0" \
	"kernel_test=tftpboot $load_addr fit.itb; bootm $load_addr\0" \
	"loadbootenv=load ${bootenv_dev} 0 ${loadbootenv_addr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from ${bootenv_dev} ...; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"bootenv_existence_test=test -e ${bootenv_dev} 0 /${bootenv}\0" \
	"setbootenv=if env run bootenv_existence_test; then " \
			"if env run loadbootenv; then " \
				"env run importbootenv; " \
			"fi; " \
		"fi; \0" \
	"sd_loadbootenv=set bootenv_dev mmc && " \
			"run setbootenv \0" \
	"preboot=if test $modeboot = sdboot; then " \
			"run sd_loadbootenv; " \
			"echo Checking if uenvcmd is set ...; " \
			"if test -n $uenvcmd; then " \
				"echo Running uenvcmd ...; " \
				"run uenvcmd; " \
			"fi; " \
		"fi; \0" \
	"sdboot=echo Copying FIT from SD to RAM... && " \
		"load mmc 0 ${load_addr} ${fit_image} && " \
		"bootm ${load_addr}\0" \
	"jtagboot=echo TFTPing FIT to RAM... && " \
		"tftpboot ${load_addr} ${fit_image} && " \
		"bootm ${load_addr}\0" \
	"usbboot=if usb start; then " \
			"echo Copying FIT from USB to RAM... && " \
			"load usb 0 ${load_addr} ${fit_image} && " \
			"bootm ${load_addr}; fi\0" \
		DFU_ALT_INFO

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_ER300_H */
