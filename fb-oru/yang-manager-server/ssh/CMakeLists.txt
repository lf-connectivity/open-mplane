# Cmake file for yang-manager-server/sh

add_sources (SOURCES
	src/SshSession.cpp
	src/SftpSession.cpp
	src/SftpMgr.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(yms-ssh)

