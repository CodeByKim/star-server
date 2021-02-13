#pragma once
#include "CommonLibrary.h"

class NetworkSession;

class Contents
{
public:
	Contents();

	void OnConnectedClinet(NetworkSession& session);
	void OnDisconnectClinet(int id);
	void Process(NetworkSession& session, char* recvData);
	
	static Contents& GetInstance();	

private:	
	void OnCreateClient(NetworkSession& session);
	void OnMove();
	void OnRemoveClinet();	
	
	std::vector<NetworkSession*> mConnectedSessions;
};

