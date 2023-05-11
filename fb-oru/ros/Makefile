#
# build the os image
#
# builds the 2.6 U-Boot and Kernel for the C2G4 derived boards with the 40EX processor
#
# The kernel uses uses an embedded cpio archive and initramfs (see
# Documentation/filesystems/ramfs-rootfs-initramfs.txt)
#
# building the various bits is very order dependent as the rootfs is compiled into the kernel, but this
# has kernel modules in it
#
# basic order is
#
#    * build crosstool (it needs the kernel headers)
#    * build apps and utils (u-boot mtd-utils)
#    * build kernel modules
#    * make root file system
#    * build kernel
#

GITDIR := $(patsubst %/,%,$(dir $(patsubst %/,%,$(dir $(abspath $(MAKEFILE_LIST))))))

## Create a list of the tools to be added to the package. Variable is filled in by the tools makefiles
## selected by selector.mk
TOOLS_LIST = 

## Create a list of the libraries to be added to the package. Variable is filled in by the libs makefiles
## selected by selector.mk
LIBS_LIST = 

## List of prerequisites that need to be instaleld on this machine before the make will build properly


## Shared functions
include make/functions.mk

## Build Vars
include make/buildvars.mk

# BOARD
#
# Sets:
# BUILD_TARGET
# BUILD_ARCH
# TOOLCHAIN_HOST
# TOOLCHAIN_TARGET
# TOOLCHAIN_SELECTOR
#
include make/boards/$(BUILD_BOARD).mk

## Settings
include make/settings.mk

## Select which parts of the makefile to include based on setting
include make/selector/$(TOOLCHAIN_SELECTOR)/selector.mk

## Include variables from the sub-makefiles
INCMODE := VARS

## Load in the makefile parts
include make/selector/$(TOOLCHAIN_SELECTOR)/selected.mk

BOARDFILES_TARGET := 
ifeq (1,$(REQUIRES_INIT))
  BOARDFILES_TARGET := board-files
endif


INCMODE += TARGETS

ifeq (1,$(REQUIRES_INIT))
all: join-files
	make board=$(BUILD_BOARD) variant=$(BUILD_VARIANT) init
	make board=$(BUILD_BOARD) variant=$(BUILD_VARIANT) build-all

else
all: join-files build-all

endif


## TARGETS
ifeq ($(BUILD_TARGET),x86_64)

$(call INFO,TOOLCHAIN_BUILD_FLAG: $(TOOLCHAIN_BUILD_FLAG))
$(call INFO,TOOLS_LIST: $(TOOLS_LIST))
$(call INFO,LIBS_LIST: $(LIBS_LIST))

build-all: show-settings \
	$(TOOLCHAIN_BUILD_FLAG) \
	gdb \
	$(LIBS_LIST)

else

build-all: show-settings \
	$(BOARDFILES_TARGET) \
	$(TOOLCHAIN_BUILD_FLAG) \
	$(TOOLS_LIST) \
	$(LIBS_LIST) \
	$(ROOTFS_BUILD_FLAG) \
	$(OS.PACKAGE) \
	escrow

install: all

libs: \
	$(BOARDFILES_TARGET) \
	$(TOOLCHAIN_BUILD_FLAG) \
	$(TOOLS_LIST) \
	$(LIBS_LIST)

$(call INFO,BOARD: $(BUILD_BOARD))
$(call INFO,VARIANT: $(BUILD_VARIANT))
$(call INFO,LOCAL_SRC_MIRROR: $(LOCAL_SRC_MIRROR))
$(call INFO,TOOLCHAIN_BUILD_FLAG: $(TOOLCHAIN_BUILD_FLAG))
$(call INFO,TOOLS_LIST: $(TOOLS_LIST))
$(call INFO,LIBS_LIST: $(LIBS_LIST))
$(call INFO,ROOTFS_BUILD_FLAG: $(ROOTFS_BUILD_FLAG))
$(call INFO,OS.PACKAGE: $(OS.PACKAGE))
$(call INFO,TOOLCHAIN_PREFIX: $(TOOLCHAIN_PREFIX))

#    $(info --- VARIABLES ---)
#    $(foreach v,$(SETTINGS_VARS),\
#		$(info $(v) = $($(v)))\
#	) 
#    $(info -------------)



endif

## Create the targets to recreate split files
join-files: $(PART_BASE_FILES)

# Create target for each split file
$(foreach pf,$(PART_BASE_FILES),\
	$(eval $(call ADD_JOIN_TARGET,${pf})))


test:
	mkdir $(BUILDDIR)/packages
	date > $(BUILDDIR)/packages/test-file

.PHONY: test install all build-all

makeTools: $(Make-Tools)
kernel: $(PIMAGE)
os.package: $(OS.PACKAGE)
.PHONY: makeTools kernel os.package

clean-all full-clean: clean-build 
clean: clean-rootfs kernel-clean clean-utils clean-uboot
clean-kernel: kernel-clean
.PHONY: clean clean-all full-clean clean-kernel

clean-utils:
	-@chmod -R a+w $(UTILS_DIR) 2>/dev/null
	-@rm -rf $(UTILS_DIR) 2>/dev/null
	-@chmod -R a+w $(TOOLS_TARGETDIR) 2>/dev/null
	-@rm -rf $(TOOLS_TARGETDIR) 2>/dev/null
.PHONY: clean-build

clean-build:
	-@chmod -R a+w $(BUILDDIR) 2>/dev/null
	-@rm -rf $(BUILDDIR) 2>/dev/null
.PHONY: clean-build

## Package up the build
include make/pkg/$(TOOLCHAIN_SELECTOR).mk

## Load in the makefile parts
include make/selector/$(TOOLCHAIN_SELECTOR)/selected.mk


## Init target - calling this ensures the environment is set up
init: $(BOARDFILES_TARGET)

## Ensure the board files links are up to date
board-files:
	-@if ! $(ROS_MAKETOOLS)/cp-links.bsh $(COMMON_BOARDDIR) $(BOARDDIR) ; then \
		if [ ! "$(MAKECMDGOALS)" == "board-files" ] ; then \
			echo "** Re-run make because board-files links have changed **" ; \
			exit 1; \
		fi \
	fi
.PHONY: board-files

show-env:
	@echo "PATH=$(extraPATH)$(PATH)"
	@echo "CC=$(BU_CC)"
	@echo "AR=$(BU_AR)"
	@echo "RANLIB=$(BU_RANLIB)"
	@echo "LDFLAGS=$(CFG_LDFLAGS)"
	@echo "TOOLS_INSTALLDIR=$(TOOLS_INSTALLDIR)" 
	@echo "TOOLCHAIN_HOST=$(TOOLCHAIN_HOST)"
	@echo "DEVTOOLS_INSTALLDIR=$(DEVTOOLS_INSTALLDIR)"
	

## HELP
help: show-settings
	@echo " "
	@echo "--------------------------------------------------------"
	@echo "TARGETS "
	@echo " "
	@echo "   all             - Build OS package (default target) "
	@echo "   gdb-install     - Cross-compile gdb (only run with board=HOST) "
	@echo "   clean           - Clean out all apart from toolchain"
	@echo "   clean-all       - Clean out everything"
	@echo "   show-boards     - Show one line list of buildable boards (used in scripting)"
	@echo "   display-boards  - Human readable list of buildable boards"
	@echo " "
	@echo "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -  "
	@echo "Crosstool targets (not available for petalinux builds)"
	@echo " "
	@echo "   clean-rootfs    - Clean out root filesystem"
	@echo "   clean-kernel    - Clean out linux kernel build"
	@echo "   clean-utils     - Clean out utils (busybox, tcpdump etc)"
	@echo "   xconfig         - Run Kernel config"
	@echo "   ct-menuconfig   - Run crosstools config"
	@echo "   ct-cp-config    - Copy modified crosstools config back to repository"
	@echo "   bb-menuconfig   - Run busybox config"
	@echo "   bb-cp-config    - Copy modified crosstools config back to repository"
	@echo " "
	@echo "--------------------------------------------------------"
	@echo "EXAMPLE: To build HOST tools run: "
	@echo " "
	@echo "$ make board=HOST "
	@echo " "
	@echo "--------------------------------------------------------"
	@echo "EXAMPLE: To build for ECB board run: "
	@echo " "
	@echo "$ make board=ECB "
	@echo " "
	
.PHONY: help


show-settings:
	@echo " "
	@echo "--------------------------------------------------------"
	@echo "BUILD SETTINGS"
	@echo " "
	@echo "BUILDDIR...........: $(BUILDDIR)"
	@echo "BOARD..............: $(BUILD_BOARD)"
	@echo "VARIANT............: $(BUILD_VARIANT)"
	@echo "TARGET.............: $(BUILD_TARGET)"
	@echo "TOOLCHAIN TARGET...: $(TOOLCHAIN_TARGET)"
	@echo " "
	@echo "TOOLCHAIN..........: $(TOOLCHAIN_VERSION)"
	@echo "Linux..............: $(LINUX_VER)"
	@echo "GCC................: $(GCC_DIR)"
	@echo "GLIBC..............: $(GLIBC_DIR)"
	@echo " "
	
.PHONY: show-settings


ifneq ($(BUILD_TARGET),x86_64)

$(call INFO,ESCROW_PKG_LIST=$(ESCROW_PKG_LIST))
$(call INFO,ESCROW_PATCH_LIST=$(ESCROW_PATCH_LIST))

escrow: $(ESCROW_PKG_LIST) $(ESCROW_PATCH_LIST)
	-@rm -rf $(ESCROW_DIR)
	-@mkdir -p $(ESCROW_DIR)/rootfs
	@cp $(ESCROW_PKG_LIST) $(ESCROW_PATCH_LIST)  $(ESCROW_DIR)/rootfs
	@(cd $(ESCROW_DIR)/rootfs ; tar cvzf ../ros-$(BuildVersion)-escrow.tgz *)

endif

# Just display the boards that can be built - used for build scripts
show-boards:
	@echo $(BOARD_LIST)
.PHONY: boards

# Human readable display of the boards
display-boards:
	@echo List of buildable boards:
	@for b in $(BOARD_LIST); do \
	   echo "  $$b" ; \
	done

