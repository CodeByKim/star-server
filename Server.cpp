#include "Server.h"

Server::Server()
	: mSession{}
	, mConnectedUsers(0)
	, mID(0)
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
			std::cout << "Accept ÁøÀÔ" << std::endl;
			mAcceptor.Accept(mSession[i], mID);
			mConnectedUsers += 1;
			mID += 1;

			return;
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
				char buffer[BUFFER_SIZE];
				int recvCount = recv(mSession[i].GetSocket(), buffer, BUFFER_SIZE, 0);

				if (recvCount == 0 || recvCount == SOCKET_ERROR)
				{
					mConnectedUsers -= 1;
					mSession[i].OnDisconnect();
					continue;
				}

				mSession[i].OnReceive(buffer, recvCount);
			}
		}
	}
}