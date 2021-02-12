#include "Contents.h"
#include "NetworkSession.h"
#include "Packet.h"

Contents::Contents()
{
}

void Contents::Process(char* recvData)
{
	//패킷을 만들고..
	
	//패킷을 핸들링한다.
}

Contents& Contents::GetInstance()
{
	static Contents instance;
	return instance;
}

void Contents::OnConnectedClinet(NetworkSession& session)
{	
	GetIdPacket packet;
	packet.protocol = 0;
	packet.id = session.GetID();

	session.Send(packet.Serialize());	
	mConnectedSessions.push_back(&session);

	OnCreateClient(session);
}

void Contents::OnCreateClient(NetworkSession& session)
{
	Position& newClientPos = session.GetPosition();

	CreateStarPacket broadcastPacket;
	broadcastPacket.protocol = 1;
	broadcastPacket.id = session.GetID();
	broadcastPacket.x = newClientPos.x;
	broadcastPacket.y = newClientPos.x;

	for (int i = 0; i < mConnectedSessions.size(); i++)
	{
		//새로 접속한 유저한테는 기존 유저데이터 전부 보내줘야 한다.
		if (session.GetID() != mConnectedSessions[i]->GetID())
		{
			Position& pos = mConnectedSessions[i]->GetPosition();

			CreateStarPacket packet;
			packet.protocol = 1;
			packet.id = mConnectedSessions[i]->GetID();
			packet.x = pos.x;
			packet.y = pos.y;

			session.Send(packet.Serialize());
		}

		mConnectedSessions[i]->Send(broadcastPacket.Serialize());
	}

	
}

void Contents::OnMove()
{

}

void Contents::OnRemoveClinet()
{

}