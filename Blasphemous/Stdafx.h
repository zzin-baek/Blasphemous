#pragma once

#pragma warning(disable : 4005)

#include <SDKDDKVER.h>

#define WIN32_LEAN_AND_MEAN

#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment (lib, "msimg32.lib")

#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <cassert>
#include <bitset>
#include <deque>

#define		PI			3.141592653f
#define		M_E         2.7182818284590452354
#define		MAGENTA		RGB(255, 0, 255)

using namespace std;

// 사용자 정의 헤더 파일
#include "CommonMacroFucntion.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Effect.h"

#include "Player.h"
#include "Inventory.h"

// # 싱글톤 #
#define RND					RandomFunction::getSingleton()
#define KEYMANAGER			KeyManager::getSingleton()
#define IMAGEMANAGER		ImageManager::getSingleton()
#define FONTMANAGER			FontManager::getSingleton()
#define SOUNDMANAGER		SoundManager::getSingleton()
#define EFFECT				Effect::getSingleton()

#define PLAYER				Player::getSingleton()
#define INVENTORY			Inventory::getSingleton()

// 타이틀
#define WINNAME					(LPTSTR)(TEXT("Blasphemous"))

#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				1280
#define WINSIZE_Y				720

#define WINSTYLE			WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;
