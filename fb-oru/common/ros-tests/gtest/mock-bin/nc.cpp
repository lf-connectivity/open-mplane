#include <iostream>

#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>  // needed for memset

#include "Socket.h"

using namespace Mplane ;

class NcSocket : public Socket {
public:
	NcSocket() :
		Socket()
	{
		create() ;
	}

	virtual ~NcSocket() {}

	int getFd() { return mSock; }
};

int main(int argc, char **argv)
{
	if (argc <= 1)
	{
		std::cerr << "Usage: nc host:port" << std::endl ;
		return 1 ;
	}

	std::string host(argv[1]) ;
	unsigned port(0) ;
	if (argc > 2)
	{
		port = (unsigned)std::strtoul(argv[2], NULL, 10 ) ;
	}
	else
	{
		std::size_t pos(host.find(":")) ;
		if (pos != std::string::npos)
		{
			port = (unsigned)std::strtoul( host.substr(pos+1).c_str(), NULL, 10 ) ;
			host = host.substr(0, pos) ;
		}
	}

	NcSocket socket ;
	if (!socket.connect(host, port))
	{
		std::cerr << "Failed to connect to " << host << ":" << port << std::endl ;
		return 1 ;
	}

	int cfd(socket.getFd());

	/* Select loop copying stdin to cfd, and cfd to stdout */
	fd_set readfds, testfds;
	FD_ZERO(&readfds);
	FD_SET(cfd, &readfds);
	FD_SET(STDIN_FILENO, &readfds);

	for (;;)
	{
		int fd;
		int ofd;
		int nread;

		testfds = readfds;

		if (select(cfd + 1, &testfds, NULL, NULL, NULL) < 0)
		{
			std::cerr << "Select error" << std::endl ;
			return 1 ;
		}

//std::cerr << "! cfd=" << cfd << std::endl ;

		char iobuf[1024] ;
		fd = STDIN_FILENO;
		while (1)
		{
			if (FD_ISSET(fd, &testfds))
			{
				nread = ::read(fd, iobuf, sizeof(iobuf));
//std::cerr << "! nread=" << nread << " fd=" << fd << std::endl ;
				if (fd == cfd)
				{
					if (nread < 1)
						::exit(0);
					ofd = STDOUT_FILENO;
				}
				else
				{
					if (nread < 1)
					{
						/* Close outgoing half-connection so they get EOF,
						 * but leave incoming alone so we can see response */
						::shutdown(cfd, SHUT_WR);
						FD_CLR(STDIN_FILENO, &readfds);
					}
					ofd = cfd;
				}

//std::cerr << "! write nread=" << nread << " ofd=" << ofd << std::endl ;
				if (nread > 0)
					::write(ofd, iobuf, nread);
			}
			if (fd == cfd)
				break;
			fd = cfd;
		}
	}
}
