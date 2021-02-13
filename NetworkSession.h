#pragma once
#include "CommonLibrary.h"

class NetworkSession
{
public:
	NetworkSession();
	~NetworkSession();

	void OnAccept(SOCKET socket, SOCKADDR_IN addr, int id);
	void OnDisconnect();
	void OnReceive(char* buffer, int recvCount);
	void Send(char* buffer);

	SOCKET GetSocket();
	bool IsEnable();
	int GetID();
	Position& GetPosition();
	void SetPos(int x, int y);

private:
	void Release();

	SOCKET mSocket;
	SOCKADDR_IN mAddr;
	int mID;
	Position mPosition;	
};

