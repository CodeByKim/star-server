#include "Server.h"

Server::Server()
	: mSession{}
	, mConnectedUsers(0)
{
	WSADATA data;
	int result = WSAStartup(MAKEWORD(2, 2), &data);
	if (result != 0)
	{
		std::wcout << L"WSAStartup : " << WSAGetLastError() << std::endl;
		return;
	}
}

Server::~Server()
{
	WSACleanup();
}

bool Server::Listen()
{
	return mAcceptor.Listen();
}

void Server::RegisterForSelect()
{
	FD_ZERO(&reads);
	FD_SET(mAcceptor.GetSocket(), &reads);

	for (int i = 0; i < MAX_CCU; i++)
	{
		if (mSession[i].IsEnable())
		{
			FD_SET(mSession[i].GetSocket(), &reads);
		}
	}
}

void Server::Accept()
{
	for (int i = 0; i < MAX_CCU; i++)
	{
		if (!mSession[i].IsEnable())
		{
			mAcceptor.Accept(mSession[i]);
			mConnectedUsers += 1;
		}
	}
}

void Server::Run()
{			
	while (true)
	{		
		RegisterForSelect();
		if (select(0, &reads, 0, 0, NULL) == SOCKET_ERROR)
		{
			std::wcout << L"select error : " << WSAGetLastError() << std::endl;
			return;
		}

		if(FD_ISSET(mAcceptor.GetSocket(), &reads))
		{
			Accept();
		}

		for (int i = 0; i < MAX_CCU; i++)
		{
			if (FD_ISSET(mSession[i].GetSocket(), &reads))
			{
				mSession[i].OnReceive();				
			}
		}
	}
}
