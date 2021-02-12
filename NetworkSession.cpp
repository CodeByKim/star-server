#include "NetworkSession.h"
#include "Contents.h"

NetworkSession::NetworkSession()
	: mSocket(INVALID_SOCKET)
	, mAddr{0,}
	, mID(-1)
	, mPosition{10,10}
{
}

NetworkSession::~NetworkSession()
{
}

void NetworkSession::OnAccept(SOCKET socket, SOCKADDR_IN addr, int id)
{
	mSocket = socket;
	mAddr = addr;
	mID = id;

	Contents::GetInstance().OnConnectedClinet(*this);
}

void NetworkSession::OnReceive(char* buffer, int recvCount)
{	
	Contents::GetInstance().Process(buffer);
}

void NetworkSession::OnDisconnect()
{
	closesocket(mSocket);
	mSocket = INVALID_SOCKET;	
}

void NetworkSession::Send(char* buffer)
{
	send(mSocket, buffer, PACKET_SIZE, 0);

	//buffer�� shared_ptr�� �ؾ��Ѵ�. �׸��� enable_shread_from_this�� ��ӹ޾Ƽ� �����ؾ� �ҵ�...
	//��Ŷ�� ��ε�ĳ������ �� ����� delete �ϸ� �ȵ�	
}

SOCKET NetworkSession::GetSocket()
{
	return mSocket;
}

bool NetworkSession::IsEnable()
{
	return mSocket != INVALID_SOCKET;
}

int NetworkSession::GetID()
{
	return mID;
}

Position& NetworkSession::GetPosition()
{
	return mPosition;
}