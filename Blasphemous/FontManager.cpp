#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);

    /*
    font = CreateFont
    (
        문자 크기, 문자폭, 기울기(전체), 문자 방향, 문자 굵기,
        기울기(t/f), 밑줄(t/f), 취소선,
        문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
    );

    */
    HFONT font = CreateFont
    (
        fontSize, 0, 0, 0, fontWeight,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );

    // auto font = (HFONT)SelectObject(hdc, font);
    auto oldFont = (HFONT)SelectObject(hdc, font);

    SetTextColor(hdc, color);

    const int stringLength = strlen(printString);
    wchar_t charBuffer[256];

    ZeroMemory(charBuffer, stringLength);

    TextOut(hdc, destX, destY, printString, strlen(printString));
    //TextOutW();

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);

    /*
    font = CreateFont
    (
        문자 크기, 문자폭, 기울기(전체), 문자 방향, 문자 굵기,
        기울기(t/f), 밑줄(t/f), 취소선,
        문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
    );

    */
    HFONT font = CreateFont
    (
        fontSize, 0, 0, 0, fontWeight,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );

    auto oldFont = (HFONT)SelectObject(hdc, font);

    SetTextColor(hdc, color);

    const int stringLength = wcslen(printString);
    wchar_t charBuffer[256];

    ZeroMemory(charBuffer, stringLength);

    TextOutW(hdc, destX, destY, printString, stringLength);
    //TextOutW();

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printStringArr, int length, COLORREF color)
{
    int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);

    /*int lineCount = 0;
    for (int i = 0; i < arraySize; i++)
    {
        if (조건식)
        {
            if ()
            {

            }
            else
            {
                break;
            }
        }
        else
        {

 }
    }*/
}
