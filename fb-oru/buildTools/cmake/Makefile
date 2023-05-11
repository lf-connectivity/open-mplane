##############################################################################################
# ENVIRONMENT
##############################################################################################

# Set top-level where git repositories live (can be overridden by make call)
GITDIR ?= $(shell cd ../.. ; pwd)
export GITDIR
#$(info GITDIR=$(GITDIR))

##############################################################################################
# LOAD VARIABLES
##############################################################################################

## set include mode to VARS
INCMODE := VARS

## BUILD VARS - Variables
include make/buildvars.mk

# Settings
include make/settings.mk

## Utilities
include make/utils.mk

## FEATURES
include make/features.mk

## BUILD CONFIGS
include make/builds.mk

## Find fpga
# Locates possible paths in which an FPGA tar is available
include make/fpgavars_example.mk

## Pull in the feature specific makefiles
include make/features/*.mk

## TARGETS - Variables
include make/targets.mk

## TOOLS - Variables
ifneq ($(special_target),2)
include make/tools.mk
endif

## REPO - Inject any makefile commands specific to each repo
ifneq ($(special_target),2)
ifneq (,$(REPO_MKFS))
include $(REPO_MKFS)
endif
endif

## type-specific
ifeq ($(special_target),0)
include make/types/$(BUILD_TYPE).mk
endif

# Documentation
ifneq (,$(filter $(MAKECMDGOALS),doxygen))
include make/doc.mk
endif

ifneq (,$(filter $(MAKECMDGOALS),show-doxygen))
include make/doc.mk
endif
ifneq (,$(filter $(MAKECMDGOALS),repos.inc))
include make/doc.mk
endif

## RUN
include make/run.mk

## Build ppc
include make/pkg.mk

## set include mode to TARGETS
INCMODE += TARGETS

##############################################################################################
# SETTINGS
##############################################################################################
include make/settings.mk

##############################################################################################
# FUNCTIONS
##############################################################################################
include make/functions.mk


##############################################################################################
# TARGETS
##############################################################################################
HELP = ""
EXTTOOLS :=

## Default target 'all' just invokes the targets.mk all
all: targets-all
.PHONY: all

## Pull in the feature specific makefiles
include make/features/*.mk

# Targets
include make/targets.mk

ifeq ($(special_target),0)

## type-specific
include make/types/$(BUILD_TYPE).mk

endif

# Documentation
ifneq (,$(filter $(MAKECMDGOALS),doxygen))
include make/doc.mk
endif

ifneq (,$(filter $(MAKECMDGOALS),show-doxygen))
include make/doc.mk
endif
ifneq (,$(filter $(MAKECMDGOALS),repos.inc))
include make/doc.mk
endif

# Tools (cppcheck etc)
ifneq ($(special_target),2)
include make/tools.mk
endif

## REPO - Inject any makefile commands specific to each repo
ifneq ($(special_target),2)
ifneq (,$(REPO_MKFS))
include $(REPO_MKFS)
endif
endif

# Run the simulations
include make/run.mk

## Build package
include make/pkg.mk


##############################################################################################
# HELP
##############################################################################################
define HELP_BUILD_SETTINGS

echo " "
echo "-----------------------------------------------------------------"
echo " CURRENT BUILD SETTINGS"
echo " "
echo "    Target.............: $(BUILD_TARGET)"
echo "    Application........: $(BUILD_APPLICATION)"
echo "    Customer...........: $(BUILD_CUSTOMER)"
echo "    Board..............: $(BUILD_BOARD)"
echo "    Product Code.......: $(BUILD_PRODUCT_CODE)"
echo "    Vendor Code........: $(BUILD_VENDOR_CODE)"
echo "    Repos..............: $(BUILD_REPOS)"
echo "    Duplex.............: $(BUILD_DUPLEX)"
echo "    Fibre I/F..........: $(BUILD_FIBRE_INTERFACE)"
echo "    Version............: $(BUILD_VERSION)"
echo "    App Name...........: $(BUILD_APPNAME)"
echo "    Board App..........: $(BUILD_BOARDAPPNAME)"
echo "    FPGA Vendor........: $(BUILD_FPGA_VENDOR)"
echo "    ROS................: $(BUILD_ROS)"
echo "    ROS Path...........: $(ROS_PATH)"
echo "    Build FPGA.........: $(BUILD_FPGA_TARBALL)"
echo " "
echo "-----------------------------------------------------------------"
echo " "
$(foreach feat,$(FEATURES),\
echo "    FEATURE:$(feat) = $(FEAT_$(feat))";\
)
endef

HELP_SETTINGS += $(HELP_BUILD_SETTINGS)
HELP += $(HELP_BUILD_VARS)
HELP += $(HELP_BUILD_SETTINGS)

define HELP_USAGE

echo " "
echo " Use the 'save-settings' target to change the build settings"
echo " "
echo " Examples:"
echo "    # to just switch the processor setting, keeping other settings the same"
echo "    $ make TARGET=ppc"
echo "    "
echo "    # to specify the most common settings"
echo "    $ make TARGET=x86_64 BOARD=ETNA APPLICATION=ART CUSTOMER=AXIS"
echo "    "
echo "    # to also specify an FPGA part name"
echo "    $ make  FPGA=xc7k160    TARGET=x86_64 BOARD=ETNA APPLICATION=ART CUSTOMER=AXIS"
echo "    "
echo " "
endef

HELP += $(HELP_USAGE)

help:
	@echo $(HELP)
.PHONY: help

define HELP_FPGA_LIST

echo " "
echo "Available FPGAs (* Selected FPGA):"
$(if $(FPGA_TARBALL_LIST),,echo "  NO FPGAs AVAILABLE")
$(foreach fpga,$(FPGA_TARBALL_LIST),\
	echo -n "  "; \
	$(if $(findstring $(BUILD_FPGA_TARBALL),$(GITDIR)/fpga/images/$(BUILD_BOARD)-$(BUILD_CUSTOMER)-$(BUILD_APPLICATION)/$(fpga)),\
		echo -n "*";,\
		echo -n " ";\
	)\
	$(if $(findstring ./,$(dir $(fpga))),\
		echo "  $(sel)$(fpga)";,
		echo "  $(sel)[$(dir $(fpga))] $(notdir $(fpga))";
	)\
)
echo " "
#		echo "  $(sel)[$(subst /,,$(dir $(fpga)))] $(notdir $(fpga))";

echo " "

endef

show-fpgas:
	@echo $(HELP_FPGA_LIST)
.PHONY: show-fpgas

ifeq (1,$(settings_available))
show-settings:
	@echo $(HELP_SETTINGS)
	@echo $(HELP_FPGA_LIST)

show-target:
	@echo $(BUILD_TARGET)

show-board-target:
	@echo $(BOARD_TARGET)

show-board:
	@echo $(BUILD_BOARD)

show-customer:
	@echo $(BUILD_CUSTOMER)

show-application:
	@echo $(BUILD_APPLICATION)

else
show-settings:
	@echo '** NO SETTINGS **'

show-target:
	@echo '** NO SETTINGS **'

show-board-target:
	@echo '** NO SETTINGS **'

show-board:
	@echo '** NO SETTINGS **'

show-customer:
	@echo '** NO SETTINGS **'

show-application:
	@echo '** NO SETTINGS **'

endif
.PHONY: show-settings show-target


##############################################################################################
# ECLIPSE EXTERNAL TOOLS
##############################################################################################
exttools: $(EXTTOOLS)

##############################################################################################
# BUILD VARS
##############################################################################################
include make/buildvars.mk
