#pragma once
#include "CommonLibrary.h"

class NetworkSession;

class Acceptor
{
public:
	Acceptor();
	~Acceptor();

	bool Listen();
	void Accept(NetworkSession& session);
	SOCKET GetSocket();

private:
	SOCKET mListenSocket;
	SOCKADDR_IN mListenAddr;
};

