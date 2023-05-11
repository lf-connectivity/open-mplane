/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Zcu111BootEnv.cpp
 * \brief     Manages access to the u-boot environment
 *
 *
 * \details   The u-boot environment is stored in 2 NOR flash partitions (access in Linux as 2 devices). One is marked
 *            as the active bank, the other the inactive bank. Every time a change is made, it is written to the inactive
 *            bank and the banks swapped
 *
 */


//=============================================================================================================
// INCLUDE
//=============================================================================================================
#include <iostream>
#include <fstream>

//#include "stringfunc.hpp"
#include "Zcu111BootEnv.h"


using namespace Mplane;


//=============================================================================================================
// SINGLETON
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
class Zcu111BootEnvInst : public Zcu111BootEnv
{
public:
	Zcu111BootEnvInst() : Zcu111BootEnv() {}
	virtual ~Zcu111BootEnvInst() {}
};

std::shared_ptr<Zcu111BootEnv> Zcu111BootEnv::getInstance()
{
	static std::shared_ptr<Zcu111BootEnv> instance(std::make_shared<Zcu111BootEnvInst>()) ;
	return instance ;
}

std::shared_ptr<IBootEnv> IBootEnv::getInstance()
{
	return Zcu111BootEnv::getInstance() ;
}


//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111BootEnv::~Zcu111BootEnv()
{
}

#ifdef OFF_TARGET
//=============================================================================================================
// TEST INTERFACE
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
void Zcu111BootEnv::reset(const std::map<std::string, std::string>& env)
{
	std::map<std::string, std::string> vars(env) ;
	if (vars.empty())
	{
		vars["baudrate"] = "115200" ;
		vars["bootcmd"] = "run $modeboot" ;
		vars["bootdelay"] = "2" ;
		vars["bootimage_image"] = "boot.bin" ;
		vars["bootimage_image_full"] = "boot_full.bin" ;
		vars["bootimage_loadaddr"] = "0x4000000" ;
		vars["bootimage_size"] = "0x700000" ;
		vars["bootscript_image"] = "uboot.scr" ;
		vars["bootscript_loadaddr"] = "0x1000000" ;
		vars["bootscript_size"] = "0x80000" ;
		vars["def_args=console"] = "ttyPS0,115200 rw earlyprintk" ;
		vars["devicetree_image"] = "devicetree.dtb" ;
		vars["devicetree_loadaddr"] = "0x6600000" ;
		vars["devicetree_size"] = "0x80000" ;
		vars["emmcboot"] = "setenv mmcdev 1;run mmcboot" ;
		vars["ethaddr"] = "20:B0:F7:03:CD:62" ;
		vars["fdt_high"] = "0x20000000" ;
		vars["fdtcontroladdr"] = "0x3ff956f0" ;
		vars["fullboot_size"] = "0x4000000" ;
		vars["initrd_high"] = "0x20000000" ;
		vars["ipaddr"] = "192.168.1.113" ;
		vars["jffs2_image"] = "rootfs.jffs2" ;
		vars["jffs2_loadaddr"] = "0x2000000" ;
		vars["jffs2_size"] = "0x3280000" ;
		vars["jtagboot"] = "echo Booting on TFTP ...; tftpboot ${bootscript_loadaddr} ${bootscript_image} && source ${bootscript_loadaddr}" ;
		vars["kernel_image"] = "uImage" ;
		vars["kernel_loadaddr"] = "0x6000000" ;
		vars["kernel_size"] = "0x500000" ;
		vars["loadaddr"] = "0x200000" ;
		vars["mmc_args=setenv bootargs ${def_args} rootwait root"] = "/dev/mmcblk${mmcdev}p2" ;
		vars["mmcboot"] = "mmc rescan ; load mmc ${mmcdev} ${bootscript_loadaddr} ${bootscript_image} && source ${bootscript_loadaddr}" ;
		vars["mmcdev"] = "0" ;
		vars["modeboot"] = "qspiboot" ;
		vars["mtdids=nand0"] = "nand" ;
		vars["mtdparts=mtdparts"] = "nand:5M(nand-linux),1M(nand-device-tree),1M(nand-bootscript),-(nand-rootfs)" ;
		vars["nand_args=setenv bootargs ${def_args} rootwait=1 ubi.mtd=3 rootfstype=ubifs root"] = "ubi0:rootfs" ;
		vars["nand_devicetree_size"] = "0x10000" ;
		vars["nand_kernel_size"] = "0x500000" ;
		vars["nandboot"] = "echo Booting on NAND ...; zx_set_storage NAND && nand read ${bootscript_loadaddr} nand-bootscript ${bootscript_size} && source ${bootscript_loadaddr} " ;
		vars["net_args=setenv bootargs ${def_args} rootwait root=/dev/nfs nfsroot=${serverip}:${serverpath},v3 ip"] = "dhcp" ;
		vars["netboot"] = "echo Booting from TFTP/NFS ...; tftpboot ${bootscript_loadaddr} ${bootscript_image} && source ${bootscript_loadaddr}" ;
		vars["netmask"] = "255.255.255.0" ;
		vars["qspi_args=setenv bootargs ${def_args} root=/dev/mtdblock5 rootfstype"] = "jffs2 rootwait" ;
		vars["qspi_bootimage_offset"] = "0x0" ;
		vars["qspi_bootscript_offset"] = "0xc80000" ;
		vars["qspi_devicetree_offset"] = "0xc00000" ;
		vars["qspi_env_offset"] = "0x3f80000" ;
		vars["qspi_env_size"] = "0x80000" ;
		vars["qspi_kernel_offset"] = "0x700000" ;
		vars["qspi_ramdisk_offset"] = "0xd00000" ;
		vars["qspi_rootfs_offset"] = "0xd00000" ;
		vars["qspiboot"] = "echo Bootinq on QSPI Flash ...; zx_set_storage QSPI && sf probe && sf read ${bootscript_loadaddr} ${qspi_bootscript_offset} ${bootscript_size} && source ${bootscript_loadaddr}" ;
		vars["ramdisk_args=setenv bootargs ${def_args} root"] = "/dev/ram" ;
		vars["ramdisk_image"] = "uramdisk" ;
		vars["ramdisk_loadaddr"] = "0x2000000" ;
		vars["ramdisk_size"] = "0x3280000" ;
		vars["sdboot"] = "setenv mmcdev 0;run mmcboot" ;
		vars["serverip"] = "192.168.1.103" ;
		vars["serverpath"] = "/srv/nfs/rootfs" ;
		vars["setupqspi"] = "echo Setting up QSPI partitions...; fdt addr ${devicetree_loadaddr}; fdt set /amba/spi@e000d000/flash@0/partition@qspi-bootimage reg <0x00000000 ${bootimage_size}>; fdt set /amba/spi@e000d000/flash@0/partition@qspi-kernel reg <${qspi_kernel_offset} ${kernel_size}>; fdt set /amba/spi@e000d000/flash@0/partition@qspi-device-tree reg <${qspi_devicetree_offset} ${devicetree_size}>; fdt set /amba/spi@e000d000/flash@0/partition@qspi-bootargs reg <${qspi_env_offset} ${qspi_env_size}>; fdt set /amba/spi@e000d000/flash@0/partition@qspi-bootscript reg <${qspi_bootscript_offset} ${bootscript_size}>; fdt set /amba/spi@e000d000/flash@0/partition@qspi-rootfs reg <${qspi_rootfs_offset} ${jffs2_size}>;" ;
		vars["setuptest"] = "mmc rescan && load mmc 0 0x1000000 setup_script.img && source 0x1000000" ;
		vars["stderr"] = "serial@e0000000" ;
		vars["stdin"] = "serial@e0000000" ;
		vars["stdout"] = "serial@e0000000" ;
		vars["ubifs_image"] = "rootfs.ubi" ;
		vars["ubifs_loadaddr"] = "0x2000000" ;
		vars["ubifs_size"] = "0x3280000" ;
		vars["usbboot"] = "echo Booting on USB ...; usb start && load usb 0 ${bootscript_loadaddr} ${bootscript_image} && source ${bootscript_loadaddr} " ;
	}

	SingleBootEnv::reset(vars) ;
}


#endif

//=============================================================================================================
// PROTECTED CONSTRUCTOR
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
Zcu111BootEnv::Zcu111BootEnv() :
	SingleBootEnv(true)
{
	// call init in this constructor - passing 'true' to SinlgeBootEnv causes that parent to defer calling init()
	// to this class
	init() ;
}

//=============================================================================================================
// PROTECTED HOOKS
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
bool Mplane::Zcu111BootEnv::processDeviceLine(const std::string& line, unsigned & index)
{
    /*
     * Read /proc/mtd, which should be of the form:
     *
     * dev:    size   erasesize  name
     * mtd0: 01e00000 00001000 "boot"
		mtd1: 00040000 00001000 "bootenv"
		mtd2: 02400000 00001000 "kernel"
     *
     * qspi-bootargs is the env vars partition
     */

	// Simply look for any string with "bootenv" and get the index
	std::size_t spos(line.find("bootenv")) ;
	if (spos == std::string::npos)
		return false ;

	index = 1 ;
	return true ;
}

#ifdef OFF_TARGET
//-------------------------------------------------------------------------------------------------------------
std::map<unsigned, BootEnv::PartitionInfo> Zcu111BootEnv::getSimDeviceList()
{
	std::map<unsigned, BootEnv::PartitionInfo> devices ;
	devices[1] = { "/dev/mtd1", 0x40000, 0x1000 } ;
	return devices ;
}
#endif

