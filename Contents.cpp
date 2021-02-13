#include "Contents.h"
#include "NetworkSession.h"
#include "Packet.h"

Contents::Contents()
{
}

void Contents::Process(NetworkSession& session, char* recvData)
{
	int protocol = -1;
	CopyMemory(&protocol, recvData, sizeof(int));

	switch (protocol)
	{
	case 3:		
		MoveStarPacket recvPacket;
		recvPacket.Deserialize(recvData);
		session.SetPos(recvPacket.x, recvPacket.y);

		int requestId = recvPacket.id;
		for (int i = 0; i < mConnectedSessions.size(); i++)
		{
			if (mConnectedSessions[i]->GetID() != requestId)
			{
				MoveStarPacket packet;
				packet.protocol = 3;
				packet.id = requestId;
				packet.x = recvPacket.x;
				packet.y = recvPacket.y;
				mConnectedSessions[i]->Send(packet.Serialize());
			}
		}
		break;
	}
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