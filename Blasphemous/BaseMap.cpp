#include "Stdafx.h"
#include "BaseMap.h"

HRESULT BaseMap::init(void)
{
    IMAGEMANAGER->addImage("¹è°æ", "Resources/Image/Background/ ??", WINSIZE_X, WINSIZE_Y);
    return S_OK;
}

void BaseMap::release(void)
{
}

void BaseMap::update(void)
{
}

void BaseMap::render(void)
{
}
