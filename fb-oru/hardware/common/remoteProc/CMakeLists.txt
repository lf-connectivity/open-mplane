# Cmake file for common/RemoteProc

add_sources (SOURCES
	src/HostFile.cpp
	src/HostFileBase.cpp
	src/HostFileChannel.cpp
	src/HostFileFactory.cpp
	src/HostFileLinux.cpp
	src/HostFileMgr.cpp
	src/RemoteMsgHandlerBase.cpp
	src/RemoteMsgHandler.cpp
	src/RemoteMsgHandlerShim.cpp
	src/RemoteProc.cpp
	src/RpmsgMgr.cpp
	src/RemoteCommsMsgBase.cpp
	src/RemoteCommsMsgCmd.cpp
	src/RemoteCommsMsgReply.cpp
)

## Cppcheck
include (cppcheck)
addCppcheck(RemoteProc)

