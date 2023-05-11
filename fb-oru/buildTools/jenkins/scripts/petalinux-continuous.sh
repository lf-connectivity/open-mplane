# CMake build for Jenkins
# Continuous integration for applications. Building RM application
#
# Uses the environment variables to set parameters in the script
#
# Required variables:
#
# WORKSPACE = Jenkins workspace area
# BUILD_BOARD = Board
# BUILD_CUSTOMER = Board
# BUILD_APPLICATION = Board
# BUILD_NUMBER = Jenkins build number
# BUILD_DUPLEX = Supported build duplex
# FPGA = FPGA part
# PDF_HEADING = Heading string for customer pdf
#
#
# Optional:
# V = Set verbose level (normally 0)
# MIGRATE = Set when migrating from an older build system, updating toolset etc
#
TARGET=petalinux

## Include shared functions
. $WORKSPACE/buildTools/jenkins/scripts/build-functions.env

##-----------------------------------------------------------------------------------------------------
## Build
doBuild



