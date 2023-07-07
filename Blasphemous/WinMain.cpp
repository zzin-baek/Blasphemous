#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
POINT _ptClick = { 0, 0 };

// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{
    // �ν��Ͻ��� ���� ������ ��´�.
    _mg = new MainGame();
    _hInstance = hInstance;

    // 1-1. ������ â ����ü ���� �� �ʱ�ȭ
    // �����츦 ���� �� �ѹ��� �ʿ��ϱ� ������ ���ʿ��ϰ� ����(�޸�)�� �����ϰ� ���� �ʱ� ����
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                            // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                            // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);       // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     // ���콺 Ŀ��
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // ������ (���� �� ������)
    wndClass.hInstance = hInstance;                                     // �����츦 �ҿ��� ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                            // ������ ���ν���
    wndClass.lpszClassName = WINNAME;                                   // Ŭ���� �̸� (�ĺ��� ����)
    wndClass.lpszMenuName = NULL;                                       // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // ������ ��Ÿ�� (�ٽ� �׸��� ����)


    // 1-2. ������ Ŭ���� ���
    //gisterClass(&wndClass);

    //HRESULT hr;
    //hr = RegisterClass(&wndClass);
    //assert(SUCCEEDED(hr));

    RegisterClass(&wndClass);

#ifdef FULLSCREEN
    // ����̽� ��� ����ü(ȭ�� ���÷��� ���� ����ü)
    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));

    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;              // 32��Ʈ Ʈ���÷�
    dm.dmPanningWidth = 1980;          // ����
    dm.dmPelsHeight = 1020;            // ����
    dm.dmDisplayFrequency = 60;        // �ֻ��� (����� 60Hz)

    // �ʵ� ����
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

#else
    // 1-3. ȭ�鿡 ������ ������ â ����
    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

#endif

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    /*while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }*/

    while (GetMessage(&message, 0, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    return message.wParam;
}

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    // ���� ������ ũ�� ����
    // AdjustWindowRect(): RECT ����ü, ������ ��Ÿ��, �޴� ����
    AdjustWindowRect(&rc, WINSTYLE, false);

    // ���� ��Ʈ�� ������ ������ ������ ����
    // NOZORDER �� ���� ��ü�� ���� �� � ��ü�� �� ���� ��Ÿ�� ������ ����
    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}