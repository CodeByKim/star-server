#pragma once

#include "CommonLibrary.h"

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
	//void Deserialize(char* buffer) override;
	char* Serialize() override;

	int id;
	int x;
	int y;
};

class RemoveStarPacket : public Packet
{
public:
	//void Deserialize(char* buffer) override;
	char* Serialize() override;

	int id;
};

class MoveStarPacket : public Packet
{
public:
	//void Deserialize(char* buffer) override;
	char* Serialize() override;

	int id;
	int x;
	int y;
};