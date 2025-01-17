﻿#pragma once
#include "TransferResource.h"
#include <vector>

typedef struct MatchMakingPacket
{
	int maxPlayerSize;	// 플레이 인원 수
	vector<unsigned int> userSocket;
}matchMakingPacket;

class MatchingClient
{
private:
	static MatchingClient* instance;

	char sendPacket[MAX_PACKET_SIZE] = {};

	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress = {};
	HANDLE recvThreadHandle = nullptr;

	CALLBACK_FUNC_PACKET recvCBF = nullptr;

	MatchingClient();
	~MatchingClient();

	void PrintMatchingServerError(int errorCode);
	void Init();
	bool Connect();

	static UINT WINAPI RecvDataThread(void* arg);
	void RecvDataMethod();

	static void SetMatchUserPacketMethod(char* packet);
	void SetMatchUser(char* packet);
public:
	static MatchingClient* GetInstance();
	static void ReleaseInstance();

	void ConnectMathchServer();
	void LostConnectClient(unsigned int socket);

	void MakePacket(char header, int& packetLastIndex);
	void AppendPacketDataMethod(unsigned int data, unsigned int dataSize, int& packetLastIndex);
	void AppendPacketPointerData(char* data, unsigned int dataSize, int& packetLastIndex);
	void SendMessageToMatchServer();
};

