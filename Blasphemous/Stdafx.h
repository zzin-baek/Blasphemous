#pragma once

#pragma warning(disable : 4005)

#include <SDKDDKVER.h>

// #include <ole2.h>
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
#define		MAGENTA		RGB(255, 0, 255)

using namespace std;

/*
//! D2D/D3D 헤더파일
#include <D2D1.h>
#include <d2d1helper.h>
#include <D3Dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory*				_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*		_ID2DRenderTarget = nullptr;
*/

// 사용자 정의 헤더 파일
#include "CommonMacroFucntion.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "SoundManager.h"

// # 싱글톤 #
#define RND					RandomFunction::getSingleton()
#define KEYMANAGER			KeyManager::getSingleton()
#define IMAGEMANAGER		ImageManager::getSingleton()
#define FONTMANAGER			FontManager::getSingleton()
#define SOUNDMANAGER		SoundManager::getSingleton()

// 타이틀
#define WINNAME					(LPTSTR)(TEXT("Blasphemous"))

//! 전체화면
//#define FULLSCREEN		

#ifdef FULLSCREEN
#define WINSTART_X				0
#define WINSTART_Y				0
// GetSystemMetrics(): 인자로 전달되는 시스템 설정 정보를 반환
// ㄴ SM_CXSCREEN + SM_CYSCREEN = 현재 화면 해상도 X / Y 축 반환
#define WINSIZE_X				GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y				GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE				WS_POPUPWINDOW | WS_MAXIMIZE

#else
// # 매크로 # (윈도우 창 초기화)
#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				1280
#define WINSIZE_Y				720

// WS_CAPTION: 타이틀 바를 가지기 위한 옵션
// WS_SYSMENU: 제목 표시줄에 컨트롤 메뉴 상자 창
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;