# CMake build for Jenkins
# Continuous integration for applications. Building x86_64 host application and running tests
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
#
# Optional:
# V = Set verbose level (normally 0)
# MIGRATE = Set when migrating from an older build system, updating toolset etc
#

TOOLS=tools
V=${V:-0}
if [ -n "$MIGRATE" ]
then
	V=2
	TOOLS=update-tools
fi

# Start by setting the target product
cd $WORKSPACE/buildTools/cmake
SETTINGS="BOARD=$BUILD_BOARD CUSTOMER=$BUILD_CUSTOMER APPLICATION=$BUILD_APPLICATION TARGET=x86_64 DUPLEX=$BUILD_DUPLEX"
make GITDIR=$WORKSPACE save-settings $SETTINGS

##----------------------------------------------------------------------------------------------

# Build local tools
cd $WORKSPACE/buildTools/cmake
make V=$V GITDIR=$WORKSPACE $TOOLS
if [ $? -ne 0 ]; then
	exit 1
fi

if [ -n "$MIGRATE" ]
then
	make V=$V GITDIR=$WORKSPACE full-clean
fi


##----------------------------------------------------------------------------------------------
# Clear out any old test reports
cd $WORKSPACE
find . -name "coverage.xml" | xargs -i rm '{}'
find . -name "coverage.txt" | xargs -i rm '{}'
find . -name "cppcheck.xml" | xargs -i rm '{}'
find . -name "gtest.xml" | xargs -i rm '{}'
find . -name "cppunit.xml" | xargs -i rm '{}'


##----------------------------------------------------------------------------------------------
# Build libs, UTs
cd $WORKSPACE/buildTools/cmake
make V=$V GenTool
if [ $? -ne 0 ]; then
	exit 1
fi
make V=$V GITDIR=$WORKSPACE
if [ $? -ne 0 ]; then
	exit 1
fi

# run all checks - run the step individually so a fail means the other steps still get run
make V=$V GITDIR=$WORKSPACE cppcheck
make V=$V GITDIR=$WORKSPACE tests
make V=$V GITDIR=$WORKSPACE coverage

