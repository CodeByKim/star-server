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
	Contents::GetInstance().Process(*this, buffer);
}

void NetworkSession::OnDisconnect()
{	
	closesocket(mSocket);
	Contents::GetInstance().OnDisconnectClinet(mID);

	Release();	
}

void NetworkSession::Release()
{
	mSocket = INVALID_SOCKET;
	mAddr = { 0, };
	mID = -1;
	mPosition = { 10, 10 };		
}

void NetworkSession::Send(char* buffer)
{
	send(mSocket, buffer, PACKET_SIZE, 0);

	//buffer를 shared_ptr로 해야한다. 그리고 enable_shread_from_this를 상속받아서 구현해야 할듯...
	//패킷을 브로드캐스팅할 때 맘대로 delete 하면 안됨	
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

void NetworkSession::SetPos(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}