﻿#pragma once
#include <vector>
#include <WinSock2.h>
#include "commonGameResource.h"

class GameRoom;
class GameManager
{
private:
	static GameManager* instance;
	std::vector<GameRoom*> roomVector;

	GameManager();
	~GameManager();
public:
	static GameManager* GetInstance();
	static void ReleaseInstance();

	void CreateRoom(SOCKET& user1, SOCKET& user2);
	GameRoom* GetRoom(int index);
	int FindBelongRoom(SOCKET& socket);	// 속한 게임방 찾기

	void ArriveLandTileMethod(GameRoom* room);

	static UINT WINAPI RoomLogicThread(void* arg);
	void RoomLogicThreadMethod(GameRoom* room);

	static void RollTheDiceMethod(GameRoom* room);
	void RollTheDice(GameRoom* room);

	static void BuyLandMethod(GameRoom* room, char* data);
	void BuyLand(GameRoom* room, char* data);

	static void BuyBuildingMethod(GameRoom* room, char* data);
	void BuyBuilding(GameRoom* room, char* data);

	static void PayTollMethod(GameRoom* room, char* data);
	void PayToll(GameRoom* room, char* data);

	static void TakeOverMethod(GameRoom* room, char* data);
	void TakeOver(GameRoom* room, char* data);

	static void BuyLandMarkMethod(GameRoom* room, char* data);
	void BuyLandMark(GameRoom* room, char* data);
};

