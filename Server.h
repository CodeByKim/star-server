#pragma once
#include "CommonLibrary.h"
#include "NetworkSession.h"
#include "Acceptpr.h"

class Server
{
public:
	Server();
	~Server();

	bool Listen();
	void Run();
	
private:
	void RegisterForSelect();	
	void Accept();

	Acceptor mAcceptor;
	NetworkSession mSession[MAX_CCU];
	int mConnectedUsers;
	int mID;
	FD_SET reads;
};