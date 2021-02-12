#include "NetworkSession.h"

NetworkSession::NetworkSession()
	: mSocket(INVALID_SOCKET)
	, mAddr{0,}
{
}

NetworkSession::~NetworkSession()
{
}

void NetworkSession::OnAccept(SOCKET socket, SOCKADDR_IN addr)
{
	mSocket = socket;
	mAddr = addr;
}

void NetworkSession::OnReceive()
{
	char buffer[BUFFER_SIZE];
	int recvCount = recv(mSocket, buffer, BUFFER_SIZE, 0);

	if (recvCount == 0)
	{
		OnDisconnect();		
	}
}

void NetworkSession::OnDisconnect()
{
	closesocket(mSocket);
	mSocket = INVALID_SOCKET;
}

SOCKET NetworkSession::GetSocket()
{
	return mSocket;
}

bool NetworkSession::IsEnable()
{
	return mSocket != INVALID_SOCKET;
}
