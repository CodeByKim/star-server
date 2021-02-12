#include "Packet.h"

char* GetIdPacket::Serialize()
{
	//int proto = 0;
	char* buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));

	return buffer;
}

char* CreateStarPacket::Serialize()
{
	//int proto = 1;
	char* buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));
	CopyMemory(buffer + 8, &x, sizeof(int));
	CopyMemory(buffer + 12, &y, sizeof(int));

	return buffer;
}

char* RemoveStarPacket::Serialize()
{
	//int proto = 2;
	char* buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));

	return buffer;
}

char* MoveStarPacket::Serialize()
{
	//int proto = 3;
	char* buffer = new char[PACKET_SIZE];

	CopyMemory(buffer + 0, &protocol, sizeof(int));
	CopyMemory(buffer + 4, &id, sizeof(int));
	CopyMemory(buffer + 8, &x, sizeof(int));
	CopyMemory(buffer + 12, &y, sizeof(int));

	return buffer;
}