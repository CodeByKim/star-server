#include "Contents.h"
#include "NetworkSession.h"
#include "Packet.h"

Contents::Contents()
{
}

void Contents::Process(char* recvData)
{
	//��Ŷ�� �����..
	
	//��Ŷ�� �ڵ鸵�Ѵ�.
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
		//���� ������ �������״� ���� ���������� ���� ������� �Ѵ�.
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