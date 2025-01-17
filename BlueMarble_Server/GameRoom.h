﻿#pragma once
#include "TransferResource.h"
#include "MapManager.h"
#include <vector>
#include <time.h>
#include "commonGameResource.h"
#include "Card.h"
#include <mutex>

constexpr const int MAX_PLAYER = 4;

enum class GameState
{
	WAIT = 0,
	ROLL_DICE_SIGN = 1,
	LAND_TILE = 2,
	CARD_TILE = 3,
	DESERT_ISLAND_TILE = 4,
	OLYMPIC_TILE = 5,
	WORLD_TRABLE_TILE = 6,
	REVENUE_TILE = 7,
	NEXT_TURN = 9,
	GAME_OVER = 10,
};

enum SellState
{
	BUILD_LANDMARK = 0,
	PAY_TOLL = 1,
	TAKE_OVER_LAND = 2,
	PAY_TAX = 3,
};

class GameServer;
class GameRoom
{
private:
	GameServer* gameServer = nullptr;
	vector<SOCKET> userVector;

	int roomId = 0;

	vector<int> userPositionVector;	// 유저 위치
	vector<int> userMoneyVector;	// 유저 소지 자금
	vector<bool> bankruptcyVector;	// 파산 유무

	int takeControlPlayer = 0;	// 누구 차례인지 구분 변수
	int diceDoubleCount = 0;	// 주사위 더블 카운트 변수,

	vector<Card> holdCard;		// 소지 카드들

	vector<bool> isDesertIsland; // 감옥 여부
	vector<int> desertIslandCount;	// 감옥 카운트

	vector<bool> isFinishTurnProcessVector;	// 해당 차례 처리 유무 
	landData landBoardData;	// 건축물 데이터
	boardData board;		// 지역 정보 및 건물 가격 데이터

	char sendPacket[MAX_PACKET_SIZE] = {};

	mutex packetLastIndexMutex;
	unsigned int packetLastIndex = 0;	// 같은 게임에서 동시에 데이터를 보낼 경우, 같이 참조해서 문제점이 생겨서 뮤텍스 사용

	vector<int> selectLandIndex;
public:
	int connectPlayer = 0;
	clock_t startTime = 0;
	clock_t finishTime = 0;
	int beforeSellSign = -1;
	int preCardId = -1;
	bool isCheckTrapCard = false;	// 카드 사용유무 물어봤는지 여부
	int checkIsUsingTrapCardId = -1;	// 물어보기 전, 사용하고자 했던 카드 id
	int goalPrice = 0;
	bool isDouble = false;	// 더블 유무
	GameState state = GameState::ROLL_DICE_SIGN;

	GameRoom(vector<unsigned int> userSocketVector);

	vector<SOCKET> GetUserVector();
	vector<SOCKET>* GetPUserVector();
	vector<int>* GetPUserMoneyVector();
	vector<int> GetUserPositionVector();
	vector<bool> GetBackruptcyVector();

	vector<Card>* GetPHoldCard();

	void NextTurn();	// 차례 넘겨주기
	int GetTakeControlPlayer();	// 누구 차례인지 값 전송

	landData GetLandBoardData();	// 건축물 정보 전송
	landData* GetPLandBoardData();	// 건축물 정보 전송(포인터)
	boardData GetMapData();			// 맵의 정보 전송

	int GetDiceDoubleCount();		// 더블 카운트 전송
	void SetDiceDoubleCount(int count);	// 더블 카운트 변경

	bool IsDesertIsland();
	int GetDesertIslandCount();

	void SetIsDesertIsland(bool isDesert);
	void SetDesertIslandCount(int count);

	vector<int>* GetSelectLandIndex();

	bool CheckSendDelay();	// 딜레이 체크 함수
	void SendMapDataMethod(SOCKET& socekt);	// 맵 정보 전송 함수
	void SendRollDiceSignMethod(SOCKET& socket);	// 주사위 신호 전송 함수

	void DesertIslandMethod(const bool isCard = false);	// 감옥 처리

	void WorldTrableMethod();	// 세계여행 처리
	void WorldTrableSignSyncMethod();

	void OlympicMethod();	// 올림픽 처리
	void OlympicSyncMethod(int selectIndex);

	void SendRollTheDice(int value1, int value2, bool isDesertIsland);	// 주사위 눈 전송
	int MoveUserPosition(int diceValue);	// 캐릭터 보드판 위치 이동
	void MoveTileProcess();

	void SendPayTollSign();	// 통행료 지불
	void SendBuyLandSign();	// 구입 시 처리

	void SendLandSyncSign(int turn, bool isBuy);
	void SendBuildingSyncSign(int turn, bool isBuy, bool isBuyVilla, bool isBuyBuilding, bool isBuyHotel, int accumPrice);
	void SendPayTollSignSync(int turn, int tollPrice, bool isPass, int landOwner);

	void SendTakeOverSign(int landOwner);
	void SendTakeOverSignSync(int takeOverPrice, int owner);

	void SendCardSignSync(char* packet);
	bool CheckTrapCard(int cardId);

	void SendRevenueSign();
	void SendRevenueSignSync();

	void SendBuyLandMarkSign();
	void SendBuyLandMarkSignSync(int landMarkPrice); // 랜드마크 구입 싱크 메시지 전송

	void SendSellLandSign(int goalPrice, int state); // 매각 메시지 보내기
	void SendSellLandSignSync();

	void SendCardSign(Card card); // 카드 사용 메시지 전송
	void SendIsUseCardSign(int cardId);	// 카드 사용 유무 물어보기
	void DeleteUseTrapCard();	// 발동한 사용 카드 삭제시키기

	void CheckLandKindNSendMessage();
	void CheckPassNSellMessage();
		
	void CheckCanBuild();	// 인수 후 추가 건축 가능 유무 확인 후 처리

	void SendFinishTurnSign();	// 모든 처리 끝나고, 다음턴으로 넘어가도 되는지 확인 메시지 전송
	void CheckEndProcess(SOCKET clientSocket);	// 다음턴으로 이동

	void SendSelectLandIndex(int index, bool isSpaceBar);	// 선택한 지역인덱스 전송

	void SendGameOverSign();	// 게임오버 신호 보내기

	int GetBuildPrice(int turn);	// 유저 건축물 기준으로 건축 가격 리턴
	int TakeOverLand(int turn, int takeOverPrice);	// 인수 처리

	void BuyLandMark(int price);	// 인수 처리
	int TotalDisposalPrice();	// 전체 땅 처분 가격
	int DisposalPrice(int index);	// 땅 처분 가격
	int SellLand();	// 저장해놓은 땅 처분 처리

	int FindNextLand(int selectValue, bool isLeft);	// 그다음 소지한 지역 찾기

	void Bankruptcy(int index, bool isToll = false);	// 파산 처리

	void EndTurn();
};

