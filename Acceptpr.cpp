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

void Acceptor::Accept(NetworkSession& session)
{
	SOCKADDR_IN clientAddr;
	int addrSize = sizeof(clientAddr);
	
	SOCKET clientSocket = accept(mListenSocket, (SOCKADDR*)&clientAddr, &addrSize);
	session.OnConnect(clientSocket, clientAddr);
}

SOCKET Acceptor::GetSocket()
{
	return mListenSocket;
}