#pragma once
#include "CommonLibrary.h"

class NetworkSession
{
public:
	NetworkSession();
	~NetworkSession();

	void OnAccept(SOCKET socket, SOCKADDR_IN addr);
	void OnDisconnect();
	void OnReceive();

	SOCKET GetSocket();
	bool IsEnable();

private:
	SOCKET mSocket;
	SOCKADDR_IN mAddr;
};

