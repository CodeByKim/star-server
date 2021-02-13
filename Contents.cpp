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
		
		std::shared_ptr<MoveStarPacket> packet = std::make_shared<MoveStarPacket>();
		packet->id = recvPacket.id;
		packet->x = recvPacket.x;
		packet->y = recvPacket.y;

		for (size_t i = 0; i < mConnectedSessions.size(); i++)
		{
			if (mConnectedSessions[i]->GetID() != recvPacket.id)
			{
				//MoveStarPacket packet;								
				mConnectedSessions[i]->Send(packet);
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
	//GetIdPacket packet;
	std::shared_ptr<GetIdPacket> packet = std::make_shared<GetIdPacket>();
	packet->id = session.GetID();

	session.Send(packet);
	mConnectedSessions.push_back(&session);

	OnCreateClient(session);
}

void Contents::OnCreateClient(NetworkSession& session)
{
	Position& newClientPos = session.GetPosition();

	std::shared_ptr<CreateStarPacket> broadcastPacket = std::make_shared<CreateStarPacket>();
	broadcastPacket->id = session.GetID();
	broadcastPacket->x = newClientPos.x;
	broadcastPacket->y = newClientPos.x;

	for (size_t i = 0; i < mConnectedSessions.size(); i++)
	{
		//새로 접속한 유저한테는 기존 유저데이터 전부 보내줘야 한다.
		if (session.GetID() != mConnectedSessions[i]->GetID())
		{
			Position& pos = mConnectedSessions[i]->GetPosition();

			//CreateStarPacket packet;			
			std::shared_ptr<CreateStarPacket> packet = std::make_shared<CreateStarPacket>();

			packet->id = mConnectedSessions[i]->GetID();
			packet->x = pos.x;
			packet->y = pos.y;

			session.Send(packet);
		}

		mConnectedSessions[i]->Send(broadcastPacket);
	}
}

void Contents::OnDisconnectClinet(int id)
{
	for (size_t i = 0; i < mConnectedSessions.size(); i++)
	{
		if (mConnectedSessions[i]->GetID() == id)
		{
			mConnectedSessions.erase(mConnectedSessions.begin() + i);
			break;
		}
	}

	for (size_t i = 0; i < mConnectedSessions.size(); i++)
	{
		if (mConnectedSessions[i]->GetID() != id)
		{			
			std::shared_ptr<RemoveStarPacket> packet = std::make_shared<RemoveStarPacket>();
			packet->id = id;

			mConnectedSessions[i]->Send(packet);
		}
	}
}

void Contents::OnMove()
{

}

void Contents::OnRemoveClinet()
{

}