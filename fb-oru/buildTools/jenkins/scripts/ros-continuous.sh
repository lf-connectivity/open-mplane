# CMake build for Jenkins
# Continuous integration for ros. Builds OS for PPC application
#
# Uses the environment variables to set parameters in the script
#
# Required variables:
#
# WORKSPACE = Jenkins workspace area
# BUILD_BOARD = Board
# BUILD_NUMBER = Jenkins build number
#
# Optional:
# V = Set verbose level (normally 0)
# MIGRATE = Set when migrating from an older build system, updating toolset etc
#


cd $WORKSPACE/ros

V=${V:-0}
if [ -n "$MIGRATE" ]
then
	echo Migrating, cleaning out any existing builds...
	make full-clean BOARD=HOST
	make full-clean BOARD=$BUILD_BOARD
fi

# Rebuild OS if necessary
if [ -d build/$BUILD_BOARD/packages ]
then
	# Remove any old package
	rm -rf build/$BUILD_BOARD/packages/*
fi

# HOST - Incremental build
make V=$V BOARD=HOST BUILD_NUMBER=$BUILD_NUMBER
if [ $? -ne 0 ]; then
	exit 1
fi

# BOARD - Incremental build
make V=$V BOARD=$BUILD_BOARD BUILD_NUMBER=$BUILD_NUMBER
if [ $? -ne 0 ]; then
	exit 1
fi


