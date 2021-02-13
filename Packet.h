#pragma once

#include "CommonLibrary.h"

enum class ePacketNumber
{
	GetID = 0,
	CreateStar = 1,
	RemoveStar = 2,
	MoveStar = 3
};

class Packet : public std::enable_shared_from_this<Packet>
{
public:
	int protocol;
	char* buffer = nullptr;
	virtual void Serialize() = 0;

	~Packet()
	{
		if (buffer != nullptr)
		{
			delete[] buffer;
			std::cout << "패킷 삭제" << std::endl;
		}
			
	}

	std::shared_ptr<Packet> GetSharedPtr()
	{
		return shared_from_this();
	}

	char* GetBuffer()
	{
		return buffer;
	}
};

class GetIdPacket : public Packet
{
public:
	GetIdPacket();
	void Serialize() override;

	int id;
};

class CreateStarPacket : public Packet
{
public:	
	CreateStarPacket();
	void Serialize() override;

	int id;
	int x;
	int y;
};

class RemoveStarPacket : public Packet
{
public:	
	RemoveStarPacket();
	void Serialize() override;

	int id;
};

class MoveStarPacket : public Packet
{
public:
	MoveStarPacket();
	void Deserialize(char* buffer);
	void Serialize() override;

	int id;
	int x;
	int y;
};