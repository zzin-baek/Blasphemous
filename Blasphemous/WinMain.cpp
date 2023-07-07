#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
POINT _ptClick = { 0, 0 };

// 콜백 함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{
    // 인스턴스를 전역 변수에 담는다.
    _mg = new MainGame();
    _hInstance = hInstance;

    // 1-1. 윈도우 창 구조체 선언 및 초기화
    // 윈도우를 만들 때 한번만 필요하기 때문에 불필요하게 스택(메모리)를 차지하게 하지 않기 위해
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                            // 클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                            // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);       // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                     // 마우스 커서
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // 아이콘 (제목 옆 아이콘)
    wndClass.hInstance = hInstance;                                     // 윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                            // 윈도우 프로시저
    wndClass.lpszClassName = WINNAME;                                   // 클래스 이름 (식별자 정보)
    wndClass.lpszMenuName = NULL;                                       // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                           // 윈도우 스타일 (다시 그리기 정보)


    // 1-2. 윈도우 클래스 등록
    //gisterClass(&wndClass);

    //HRESULT hr;
    //hr = RegisterClass(&wndClass);
    //assert(SUCCEEDED(hr));

    RegisterClass(&wndClass);

#ifdef FULLSCREEN
    // 디바이스 모드 구조체(화면 디스플레이 관련 구조체)
    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));

    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;              // 32비트 트루컬러
    dm.dmPanningWidth = 1980;          // 가로
    dm.dmPelsHeight = 1020;            // 세로
    dm.dmDisplayFrequency = 60;        // 주사율 (재생빈도 60Hz)

    // 필드 설정
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
    // 1-3. 화면에 보여줄 윈도우 창 생성
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

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    // 실제 윈도우 크기 조정
    // AdjustWindowRect(): RECT 구조체, 윈도우 스타일, 메뉴 유무
    AdjustWindowRect(&rc, WINSTYLE, false);

    // 얻어온 렉트의 정보로 윈도우 사이즈 세팅
    // NOZORDER 두 개의 객체가 있을 때 어떤 객체를 더 위에 나타낼 것인지 결정
    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}