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
//! D2D/D3D �������
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

// ����� ���� ��� ����
#include "CommonMacroFucntion.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "SoundManager.h"

// # �̱��� #
#define RND					RandomFunction::getSingleton()
#define KEYMANAGER			KeyManager::getSingleton()
#define IMAGEMANAGER		ImageManager::getSingleton()
#define FONTMANAGER			FontManager::getSingleton()
#define SOUNDMANAGER		SoundManager::getSingleton()

// Ÿ��Ʋ
#define WINNAME					(LPTSTR)(TEXT("Blasphemous"))

//! ��üȭ��
//#define FULLSCREEN		

#ifdef FULLSCREEN
#define WINSTART_X				0
#define WINSTART_Y				0
// GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ������ ��ȯ
// �� SM_CXSCREEN + SM_CYSCREEN = ���� ȭ�� �ػ� X / Y �� ��ȯ
#define WINSIZE_X				GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y				GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE				WS_POPUPWINDOW | WS_MAXIMIZE

#else
// # ��ũ�� # (������ â �ʱ�ȭ)
#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				1280
#define WINSIZE_Y				720

// WS_CAPTION: Ÿ��Ʋ �ٸ� ������ ���� �ɼ�
// WS_SYSMENU: ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#endif

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;