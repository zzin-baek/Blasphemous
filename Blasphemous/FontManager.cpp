#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);

    HFONT font = CreateFont
    (
        fontSize, 0, 0, 0, fontWeight,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );

    auto oldFont = (HFONT)SelectObject(hdc, font);

    SetTextColor(hdc, color);

    const int stringLength = strlen(printString);
    wchar_t charBuffer[256];

    ZeroMemory(charBuffer, stringLength);

    size_t sf;
    mbstowcs_s(&sf, charBuffer, 256, printString, length);
    TextOutW(hdc, destX, destY, charBuffer, wcslen(charBuffer));;

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, char* printString, int interval, const char* delimiter, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);

    HFONT font = CreateFont
    (
        fontSize, 0, 0, 0, 1,
        0, 0, 0,
        HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(fontName)
    );

    auto oldFont = (HFONT)SelectObject(hdc, font);

    SetTextColor(hdc, color);

    const int stringLength = strlen(printString);
    wchar_t charBuffer[256];

    ZeroMemory(charBuffer, stringLength);

    char* _context = NULL;
    char* _token = NULL;
    _token = strtok_s(printString, delimiter, &_context);

    int i = 0;
    while (_token)
    {
        TextOut(hdc, destX, destY + interval * i, _token, strlen(_token));
        _token = strtok_s(NULL, delimiter, &_context);
        i++;
    }

    SelectObject(hdc, oldFont);
    DeleteObject(font);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);
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
    SelectObject(hdc, oldFont);
    DeleteObject(font);
}
