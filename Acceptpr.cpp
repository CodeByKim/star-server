#include "Acceptpr.h"
#include "NetworkSession.h"

Acceptor::Acceptor()
	: mListenSocket(INVALID_SOCKET)
	, mListenAddr{0,}
{		
}

Acceptor::~Acceptor()
{
}

bool Acceptor::Listen()
{
	mListenSocket = socket(PF_INET, SOCK_STREAM, 0);
	/*u_long on = 1;
	ioctlsocket(mListenSocket, FIONBIO, &on);*/

	ZeroMemory(&mListenAddr, sizeof(SOCKADDR_IN));
	mListenAddr.sin_family = AF_INET;
	mListenAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	mListenAddr.sin_port = htons(SERVER_PORT);

	if (bind(mListenSocket, (SOCKADDR*)&mListenAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		std::wcout << L"bind Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	if (listen(mListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::wcout << L"listen Error : " << WSAGetLastError() << std::endl;
		return false;
	}

	return true;
}

void Acceptor::Accept(NetworkSession& session, int id)
{
	SOCKADDR_IN clientAddr;
	int addrSize = sizeof(clientAddr);
	
	SOCKET clientSocket = accept(mListenSocket, (SOCKADDR*)&clientAddr, &addrSize);
	if (clientSocket != SOCKET_ERROR)
	{
		session.OnAccept(clientSocket, clientAddr, id);
		std::wcout << L"Net Client" << std::endl;
	}	
}

SOCKET Acceptor::GetSocket()
{
	return mListenSocket;
}