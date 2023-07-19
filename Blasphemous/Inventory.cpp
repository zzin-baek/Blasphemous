#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
    IMAGEMANAGER->addImage("Inventory_rosary", "Resources/Image/Sheet/inventory_base_fill.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_heritage", "Resources/Image/Sheet/inventory_heritage.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addFrameImage("ItemSelect", "Resources/Image/Sheet/ItemCursorAlt.bmp",
        240, 240, 4, 4, true, MAGENTA);

    IMAGEMANAGER->addImage("KB_E", "Resources/Image/Sheet/KB_E.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("KB_Q", "Resources/Image/Sheet/KB_Q.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("KB_RETURN", "Resources/Image/Sheet/KB_RETURN.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("Item_equip", "Resources/Image/Sheet/item_equip.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item_own", "Resources/Image/Sheet/item_own.bmp", 60, 60, true, MAGENTA);

    IMAGEMANAGER->addImage("Item1", "Resources/Image/sheet/item1.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item2", "Resources/Image/sheet/item2.bmp", 60, 60, true, MAGENTA);


    _alpha = _slot = _slotSelect = _cnt = 0;
    _select = _rosarySelect = _heritageSelect = 0;
    _idx = { 0, 0 };
    _out = false;

    // 가로간격 72, 세로간격 72
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _rosarySlot[i * 7 + j] = RectMake(200 + 72 * j, 474 + 72 * i, 60, 60);
        }
    }
    for (int i = 0; i < 7; i++)
    {
        _heritageSlot[i] = RectMake(200 + 72 * i, 474, 60, 60);
    }

    //_rosary.push_back({ "Item1", "hey", "yes", true});
    //_heritage.push_back({ "Item2", "yes", "hey", false});

    return S_OK;
}

void Inventory::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('E'))
    {
        _slot++;
        _heritageSelect = 0;
        _rosarySelect = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        _slot--;
        _heritageSelect = 0;
        _rosarySelect = 0;
    }

    _slotSelect = _slot % SLOT_NUM;

    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        _out = true;
    }

    if (KEYMANAGER->isOnceKeyDown('D'))
    {
        if (_slotSelect == ROSARY)
        {
            _rosarySelect++;
            _rosarySelect %= 14;
        }
        else if (_slotSelect == HERITAGE)
        {
            _heritageSelect++;
            _heritageSelect %= 7;
        }

    }
    if (KEYMANAGER->isOnceKeyDown('A'))
    {
        if (_slotSelect == ROSARY)
        {
            _rosarySelect--;
            _rosarySelect %= 14;
        }
        else if (_slotSelect == HERITAGE)
        {
            _heritageSelect--;
            _heritageSelect %= 7;
        }

    }
    if (KEYMANAGER->isOnceKeyDown('W'))
    {
        if (_slotSelect == ROSARY)
        {
            _rosarySelect -= 7;
            _rosarySelect %= 14;
            //cout<<_rosarySelect<<endl;
        }
        else if (_slotSelect == HERITAGE)
        {
            _heritageSelect -= 7;
            _heritageSelect %= 7;
        }

    }
    if (KEYMANAGER->isOnceKeyDown('S'))
    {
        if (_slotSelect == ROSARY)
        {
            _rosarySelect += 7;
            _rosarySelect %= 14;
        }
        else if (_slotSelect == HERITAGE)
        {
            _heritageSelect += 7;
            _heritageSelect %= 7;
        }

    }

    _cnt++;
    if (_cnt % 6 == 0)
    {
        _select++;
        if (_select > 15)
            _select = 0;

        _idx.x = _select % 4;
        _idx.y = _select / 4;

        IMAGEMANAGER->findImage("ItemSelect")->setFrameX(_idx.x);
        IMAGEMANAGER->findImage("ItemSelect")->setFrameY(_idx.y);
    }
}

void Inventory::addItem(int num, tagItem _itemInfo)
{
    if (num == ROSARY)
        _rosary.push_back(_itemInfo);
    else if (num == HERITAGE)
        _heritage.push_back(_itemInfo);
}

void Inventory::printInfo(HDC hdc, tagItem _itemInfo)
{
}

void Inventory::render(HDC hdc)
{
    if (_slotSelect == 0)
    {
        IMAGEMANAGER->render("Inventory_rosary", hdc, 0, 0);
        
        if (!_rosary.empty())
        {
            for (int i = 0; i < _rosary.size(); i++)
            {
                if (_rosary[i]._equip)
                    IMAGEMANAGER->render("Item_equip", hdc, _rosarySlot[i].left, _rosarySlot[i].top);
                else
                    IMAGEMANAGER->render("Item_own", hdc, _rosarySlot[i].left, _rosarySlot[i].top);

                IMAGEMANAGER->render(_rosary[i]._iImage.c_str(), hdc, _rosarySlot[i].left, _rosarySlot[i].top);
            }
        }

        IMAGEMANAGER->frameRender("ItemSelect", hdc, 
            _rosarySlot[_rosarySelect].left, _rosarySlot[_rosarySelect].top);
    }
    else
    {
        IMAGEMANAGER->render("Inventory_heritage", hdc, 0, 0);

        if (!_heritage.empty())
        {
            for (int i = 0; i < _heritage.size(); i++)
            {
                if (_heritage[i]._equip)
                    IMAGEMANAGER->render("Item_equip", hdc, _heritageSlot[i].left, _heritageSlot[i].top);
                else
                    IMAGEMANAGER->render("Item_own", hdc, _heritageSlot[i].left, _heritageSlot[i].top);

                IMAGEMANAGER->render(_heritage[i]._iImage.c_str(), hdc, _heritageSlot[i].left, _heritageSlot[i].top);
            }
        }

        IMAGEMANAGER->frameRender("ItemSelect", hdc, 
            _heritageSlot[_heritageSelect].left, _heritageSlot[_heritageSelect].top);
    }

    

}
