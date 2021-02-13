#pragma once

#include "CommonLibrary.h"

enum class ePacketNumber
{
	GetID = 0,
	CreateStar = 1,
	RemoveStar = 2,
	MoveStar = 3
};

class Packet
{
public:
	int protocol;
	virtual char* Serialize() = 0;
};

class GetIdPacket : public Packet
{
public:
	char* Serialize() override;

	int id;
};

class CreateStarPacket : public Packet
{
public:	
	char* Serialize() override;

	int id;
	int x;
	int y;
};

class RemoveStarPacket : public Packet
{
public:	
	char* Serialize() override;

	int id;
};

class MoveStarPacket : public Packet
{
public:
	void Deserialize(char* buffer);
	char* Serialize() override;

	int id;
	int x;
	int y;
};