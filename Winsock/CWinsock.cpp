#include "CWinsock.h"

#include <iostream>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

const CWinsock CWinsock::mCWinsock;

CWinsock::CWinsock()
{
	std::cout << "CWinsock::CWinsock()" << std::endl;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		std::cout << "WSAStartup failed with error: " << err << std::endl;
		exit(-1);
	}

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		std::cout << "Could not find a usable version of Winsock.dll" << std::endl;
		WSACleanup();
		exit(-1);
	}
	else
		std::cout << "The Winsock 2.2 dll was found okay" << std::endl;
}

CWinsock::~CWinsock()
{
	std::cout << "CWinsock::~CWinsock()" << std::endl;
	/* The Winsock DLL is acceptable. Proceed to use it. */

	/* Add network programming using Winsock here */

	/* then call WSACleanup when done using the Winsock dll */
	// system("pause");

	WSACleanup();
}