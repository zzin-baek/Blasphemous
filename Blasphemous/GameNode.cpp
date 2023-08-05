#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
    return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;


    if (managerInit)
    {
        // 로케일 설정
        // ㄴ 프로그램의 명령어가 여러가지 언어로 주어져 있는 경우 이중에 어떤 언어의 것을
        // 출력할 것인지에 대한 설정
        setlocale(LC_ALL, "korean");

        SetTimer(_hWnd, 1, 10, NULL);

        RND->init();
        KEYMANAGER->init();
        IMAGEMANAGER->init();
        SOUNDMANAGER->init();
        EFFECT->init();

        PLAYER->init();
        INVENTORY->init();
    }

    return S_OK;
}

void GameNode::release(void)
{
    if (_managerInit)
    {
        KillTimer(_hWnd, 1);

        RND->releaseSingleton();
        KEYMANAGER->releaseSingleton();
        IMAGEMANAGER->release();
        IMAGEMANAGER->releaseSingleton();
        SOUNDMANAGER->releaseSingleton();
        EFFECT->releaseSingleton();

        PLAYER->releaseSingleton();
        INVENTORY->releaseSingleton();
        //SAFE_DELETE(_doubleBuffer);
    }

    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
    InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        this->render();
        EndPaint(hWnd, &ps);
        break;
    case WM_MOUSEMOVE:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);

        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_F1:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}