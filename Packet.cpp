#include "Packet.h"

GetIdPacket::GetIdPacket()
{
	protocol = (int)ePacketNumber::GetID;
}

void GetIdPacket::Serialize()
{	
	buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));

	//return buffer;
}

CreateStarPacket::CreateStarPacket()
{
	protocol = (int)ePacketNumber::CreateStar;
}

void CreateStarPacket::Serialize()
{	
	buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));
	CopyMemory(buffer + 8, &x, sizeof(int));
	CopyMemory(buffer + 12, &y, sizeof(int));

	//return buffer;
}

RemoveStarPacket::RemoveStarPacket()
{
	protocol = (int)ePacketNumber::RemoveStar;
}

void RemoveStarPacket::Serialize()
{	
	buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));

	//return buffer;
}

MoveStarPacket::MoveStarPacket()
{
	protocol = (int)ePacketNumber::MoveStar;
}

void MoveStarPacket::Serialize()
{	
	buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));
	CopyMemory(buffer + 8, &x, sizeof(int));
	CopyMemory(buffer + 12, &y, sizeof(int));

	//return buffer;
}

void MoveStarPacket::Deserialize(char* buffer)
{
	CopyMemory(&protocol, buffer + 0, sizeof(int));
	CopyMemory(&id, buffer + 4, sizeof(int));
	CopyMemory(&x, buffer + 8, sizeof(int));
	CopyMemory(&y, buffer + 12, sizeof(int));
}