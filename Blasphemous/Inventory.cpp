#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
    IMAGEMANAGER->addImage("Inventory_rosary", "Resources/Image/Sheet/inventory_base_fill.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_heritage", "Resources/Image/Sheet/inventory_heritage.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_quest", "Resources/Image/Sheet/inventory_quest.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_mea", "Resources/Image/Sheet/inventory_mea.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_pray", "Resources/Image/Sheet/inventory_pray.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_skill", "Resources/Image/Sheet/inventory_skill.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addImage("Inventory_collection", "Resources/Image/Sheet/inventory_collection.bmp", 640 * 2, 360 * 2);
    IMAGEMANAGER->addFrameImage("ItemSelect", "Resources/Image/Sheet/ItemCursorAlt.bmp",
        240, 240, 4, 4, true, MAGENTA);

    IMAGEMANAGER->addImage("KB_E", "Resources/Image/Sheet/KB_E.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("KB_Q", "Resources/Image/Sheet/KB_Q.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("KB_RETURN", "Resources/Image/Sheet/KB_RETURN.bmp", 17 * 2, 18 * 2, true, MAGENTA);
    IMAGEMANAGER->addImage("Item_equip", "Resources/Image/Sheet/item_equip.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item_own", "Resources/Image/Sheet/item_own.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("SkillSelect", "Resources/Image/Sheet/skillSelect.bmp", 54, 54, true, MAGENTA);

    IMAGEMANAGER->addImage("Item1", "Resources/Image/sheet/item1.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item2", "Resources/Image/sheet/item2.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item3", "Resources/Image/sheet/item3.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item4", "Resources/Image/sheet/item4.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item5", "Resources/Image/sheet/item5.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Pray1", "Resources/Image/sheet/pray1.bmp", 60, 60, true, MAGENTA);

    _alpha = _slot = _slotSelect = _cnt = _score = 0;
    _select = _rosarySelect = _heritageSelect = _questSelect = _praySelect = 0;
    _eqRosary = _eqHeritage = _eqMea = _eqPray = 0;
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
        _meaSlot[i] = RectMake(200 + 72 * i, 474, 60, 60);
        _praySlot[i] = RectMake(200 + 72 * i, 474, 60, 60);
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            _questSlot[i * 5 + j] = RectMake(752 + 72 * j, 174 + 72 * i, 60, 60);
        }
    }

    _quest.push_back({ "Item3", "예아", "야얍", false });
    _mea.push_back({ "Item4", "d", "dd", false });

    _rosaryEquip[0] = RectMake(774, 394, 60, 60);
    _rosaryEquip[1] = RectMake(774, 470, 60, 60);

    _heritageEquip[0] = RectMake(790, 262, 60, 60);
    _heritageEquip[1] = RectMake(790, 354, 60, 60);
    _heritageEquip[2] = RectMake(790, 446, 60, 60);

    _meaEquip = RectMake(802, 292, 60, 60);
    _prayEquip = RectMake(802, 292, 60, 60);

    return S_OK;
}

void Inventory::update(void)
{
    if (KEYMANAGER->isOnceKeyDown('E'))
    {
        _slot++;
        _heritageSelect = 0;
        _rosarySelect = 0;
        _questSelect = 0;
        _meaSelect = 0;
        _praySelect = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        _slot--;
        if (_slot < 0)
            _slot = 6;
        _heritageSelect = 0;
        _rosarySelect = 0;
        _questSelect = 0;
        _meaSelect = 0;
    }

    _slotSelect = _slot % SLOT_NUM;

    if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
    {
        _out = true;
    }

    if (KEYMANAGER->isOnceKeyDown('D'))
    {
        switch (_slotSelect)
        {
        case ROSARY:
            _rosarySelect++;
            _rosarySelect %= 14;
            break;
        case HERITAGE:
            _heritageSelect++;
            _heritageSelect %= 7;
            break;
        case QUEST:
            _questSelect++;
            _questSelect % 30;
            break;
        case MEA:
            _meaSelect++;
            _meaSelect %= 7;
            break;
        case PRAY:
            break;
        case SKILL:
            break;
        case COLLECTION:
            break;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('A'))
    {
        switch (_slotSelect)
        {
        case ROSARY:
            _rosarySelect--;
            if (_rosarySelect < 0)
                _rosarySelect = 13;
            _rosarySelect %= 14;

            break;
        case HERITAGE:
            _heritageSelect--;
            if (_heritageSelect < 0)
                _heritageSelect = 6;
            _heritageSelect %= 7;
            break;
        case QUEST:
            _questSelect--;
            if (_questSelect < 0)
                _questSelect = 29;
            _questSelect %= 30;
            break;
        case MEA:
            _meaSelect--;
            if (_meaSelect < 0)
                _meaSelect = 6;
            _meaSelect %= 7;
            break;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('W'))
    {
        switch (_slotSelect)
        {
        case ROSARY:
            _rosarySelect -= 7;
            if (_rosarySelect < 0)
                _rosarySelect += 14;
            _rosarySelect %= 14;
            break;
        case HERITAGE:
            _heritageSelect -= 7;
            if (_heritageSelect < 0)
                _heritageSelect += 7;
            _heritageSelect %= 7;
            break;
        case QUEST:
            _questSelect -= 5;
            if (_questSelect < 0)
                _questSelect += 30;
            _questSelect %= 30;
            break;
        case MEA:
            _meaSelect -= 7;
            if (_meaSelect < 0)
                _meaSelect += 7;
            _meaSelect %= 7;
            break;
        case PRAY:
            break;
        case SKILL:
            break;
        case COLLECTION:
            break;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('S'))
    {
        switch (_slotSelect)
        {
        case ROSARY:
            _rosarySelect += 7;
            _rosarySelect %= 14;
            break;
        case HERITAGE:
            _heritageSelect += 7;
            _heritageSelect %= 7;
            break;
        case QUEST:
            _questSelect += 5;
            _questSelect %= 30;
            break;
        case MEA:
            _meaSelect += 7;
            _meaSelect %= 7;
            break;
        case PRAY:
            break;
        case SKILL:
            break;
        case COLLECTION:
            break;
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
    {
        if (_slotSelect == ROSARY && _rosarySelect < _rosary.size())
        {
            if (_rosary[_rosarySelect]._equip)
            {
                _rosary[_rosarySelect]._equip = false;
                _equipRosary.erase(_equipRosary.find(_rosary[_rosarySelect]._iImage));
                _eqRosary--;
            }
            else
            {
                if (_eqRosary < 2)
                {
                    _rosary[_rosarySelect]._equip = true;
                    _equipRosary.insert(make_pair(_rosary[_rosarySelect]._iImage, _eqRosary));
                    _eqRosary++;
                }
            }
        }
        else if (_slotSelect == HERITAGE && _heritageSelect < _heritage.size())
        {
            if (_heritage[_heritageSelect]._equip)
            {
                _heritage[_heritageSelect]._equip = false;
                _equipHeritage.erase(_equipHeritage.find(_heritage[_heritageSelect]._iImage));
                _eqHeritage--;
            }
            else
            {
                if (_eqHeritage < 3)
                {
                    _heritage[_heritageSelect]._equip = true;
                    _equipHeritage.insert(make_pair(_heritage[_heritageSelect]._iImage, _eqHeritage));
                    _eqHeritage++;
                }
            }
        }
        else if (_slotSelect == MEA && _meaSelect < _mea.size())
        {
            if (_mea[_meaSelect]._equip)
            {
                _mea[_meaSelect]._equip = false;
                _equipMea.erase(_equipMea.find(_mea[_meaSelect]._iImage));
                _eqMea--;
            }
            else
            {
                if (_eqMea < 1)
                {
                    _mea[_meaSelect]._equip = true;
                    _equipMea.insert(make_pair(_mea[_meaSelect]._iImage, _eqMea));
                    _eqMea++;
                }
            }
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
        if (!_equipRosary.empty())
        {
            for (auto iter = _equipRosary.begin(); iter != _equipRosary.end(); iter++)
            {
                IMAGEMANAGER->render("Item_equip", hdc, _rosaryEquip[iter->second].left, _rosaryEquip[iter->second].top);
                IMAGEMANAGER->render(iter->first.c_str(), hdc,
                    _rosaryEquip[iter->second].left, _rosaryEquip[iter->second].top);
            }
        }
        IMAGEMANAGER->frameRender("ItemSelect", hdc,
            _rosarySlot[_rosarySelect].left, _rosarySlot[_rosarySelect].top);
    }

    else if (_slotSelect == HERITAGE)
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
        if (!_equipHeritage.empty())
        {
            for (auto iter = _equipHeritage.begin(); iter != _equipHeritage.end(); iter++)
            {
                IMAGEMANAGER->render("Item_equip", hdc, _heritageEquip[iter->second].left, _heritageEquip[iter->second].top);
                IMAGEMANAGER->render(iter->first.c_str(), hdc,
                    _heritageEquip[iter->second].left, _heritageEquip[iter->second].top);
            }
        }
        IMAGEMANAGER->frameRender("ItemSelect", hdc, 
            _heritageSlot[_heritageSelect].left, _heritageSlot[_heritageSelect].top);
    }
    else if (_slotSelect == QUEST)
    {
        IMAGEMANAGER->render("Inventory_quest", hdc, 0, 0);

        if (!_quest.empty())
        {
            for (int i = 0; i < _quest.size(); i++)
            {

                IMAGEMANAGER->render("Item_own", hdc, _questSlot[i].left, _questSlot[i].top);
                IMAGEMANAGER->render(_quest[i]._iImage.c_str(), hdc, _questSlot[i].left, _questSlot[i].top);
            }
        }

        IMAGEMANAGER->frameRender("ItemSelect", hdc,
            _questSlot[_questSelect].left, _questSlot[_questSelect].top);
    }
    else if (_slotSelect == MEA)
    {
        IMAGEMANAGER->render("Inventory_mea", hdc, 0, 0);
        if (!_mea.empty())
        {
            for (int i = 0; i < _mea.size(); i++)
            {
                if (_mea[i]._equip)
                    IMAGEMANAGER->render("Item_equip", hdc, _meaSlot[i].left, _meaSlot[i].top);
                else
                    IMAGEMANAGER->render("Item_own", hdc, _meaSlot[i].left, _meaSlot[i].top);

                IMAGEMANAGER->render(_mea[i]._iImage.c_str(), hdc, _meaSlot[i].left, _meaSlot[i].top);
            }
        }
        if (!_equipMea.empty())
        {
            IMAGEMANAGER->render("Item_equip", hdc, _meaEquip.left, _meaEquip.top);
            IMAGEMANAGER->render(_equipMea.begin()->first.c_str(), hdc, _meaEquip.left, _meaEquip.top);
            
        }
        IMAGEMANAGER->frameRender("ItemSelect", hdc,
            _meaSlot[_meaSelect].left, _meaSlot[_meaSelect].top);
    }
    else if (_slotSelect == PRAY)
    {
        IMAGEMANAGER->render("Inventory_pray", hdc, 0, 0);
    }
    else if (_slotSelect == SKILL)
    {
        IMAGEMANAGER->render("Inventory_skill", hdc, 0, 0);
    }
    else if (_slotSelect == COLLECTION)
    {
        IMAGEMANAGER->render("Inventory_collection", hdc, 0, 0);
    }
}
