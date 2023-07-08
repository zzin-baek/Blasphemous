#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, char* printString, int length, COLORREF color)
{
    SetBkMode(hdc, TRANSPARENT);

    /*
    font = CreateFont
    (
        ���� ũ��, ������, ����(��ü), ���� ����, ���� ����,
        ����(t/f), ����(t/f), ��Ҽ�,
        ���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
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
        ���� ũ��, ������, ����(��ü), ���� ����, ���� ����,
        ����(t/f), ����(t/f), ��Ҽ�,
        ���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
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
        if (���ǽ�)
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
