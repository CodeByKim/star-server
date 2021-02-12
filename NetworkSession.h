#pragma once
#include "CommonLibrary.h"

class NetworkSession
{
public:
	NetworkSession();
	~NetworkSession();

	void OnConnect(SOCKET socket, SOCKADDR_IN addr);
	void OnDisconnect();
	void OnReceive();

	SOCKET GetSocket();
	bool IsEnable();

private:
	SOCKET mSocket;
};

