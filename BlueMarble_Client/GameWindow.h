﻿#pragma once
#include "SocketTransfer.h"

enum ButtonHWndKind
{
	ROLL_DICE_BTN = 0,
	SELECT_UI_BTN = 1,
	EXIT_UI_BTN = 2,
};

class RenderManager;
class BitmapManager;
class GameWindow
{
private:
	static GameWindow* instance;
	std::vector<HWND> hwndWindow;

	GameWindow();
	~GameWindow();

	void WmSizeMethod(HWND hWnd);
	void InitClass(HWND hWnd);
	void ReInitGame(HWND hWnd);
	void ResizeWindow(const LONG width, const LONG height, const POINT printPoint, HWND hWnd);
	void CreateButton(HWND hWnd);

	static void SendDiceTriggerMsgMethod();
	void SendDiceTriggerMsg();

	static void SendSelectBtnMsgMethod(bool isOK);
	void SendSelectBtnMsg(bool isOK);
public:
	static bool isReset;
	HWND g_hWnd = nullptr;

	static GameWindow* GetInstance();
	static void ReleaseInstance();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void GameUpdate();	// Game Update

	void ShowButton(int kind);
	void HideButton(int kind);
};

