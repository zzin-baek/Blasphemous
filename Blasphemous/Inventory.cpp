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
    IMAGEMANAGER->addImage("Blank1", "Resources/Image/Sheet/blank1.bmp", 60, 60, true, MAGENTA);

    IMAGEMANAGER->addImage("Item1", "Resources/Image/sheet/item1.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item2", "Resources/Image/sheet/item2.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item3", "Resources/Image/sheet/item3.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item4", "Resources/Image/sheet/item4.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Item5", "Resources/Image/sheet/item5.bmp", 60, 60, true, MAGENTA);
    IMAGEMANAGER->addImage("Pray1", "Resources/Image/sheet/pray1.bmp", 60, 60, true, MAGENTA);

    _alpha = _slot = _slotSelect = _cnt = 0;
    _select = _rosarySelect = _heritageSelect = _questSelect = _praySelect = _skillSelect = _colSelect = 0;
    _eqRosary = _eqHeritage = _eqMea = _eqPray = 0;
    _idx = { 0, 0 };
    _out = false;

    // ���ΰ��� 72, ���ΰ��� 72
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            _rosarySlot[i * 7 + j] = RectMake(200 + 72 * j, 474 + 72 * i, 60, 60);
            _collectSlot[i * 7 + j] = RectMake(200 + 72 * j, 474 + 72 * i, 60, 60);
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

    for (int i = 0; i < 5; i++)
    {
        _skillSlot[i] = RectMake(216 + 60 * i, 250, 54, 54);
    }


    // �̸� �־� ���� ������
    _quest.push_back({ "Item3", "�ż��� ȸ���� ��ó", 
        {"��ȸ���� ��ȥ �� ȸ����", "�������� �巯���� Ȳ��", "���� ���� ¡ǥ."}, false });
    _mea.push_back({ "Item4", "���� �Ƿ� ��Ƴ��� ����", 
        { "�޸��� ���˰� �Բ� ǥ�鿡 ����", "������ �� �ִ� ���� �߽ɺ� ���.", "�޾� ���ķ� ���� óġ�� ������",
         "�����ڿ��� ü���� ����������", "���� ����� ȸ������ �پ���."}, false });
    _pray.push_back({ "Pray1", "�θ����Ƴ�", { "������ ������ �¾ ������", "�ҷ��� �޾� ���� ����",
        "���θ��� ��� ���� �����ϴ�", "�⵵���̴�." }, false });
    _collection.push_back({ "Item5", "���ڻ� ���� ô�߻�", {"���� ������� �پ ����", "�Ƿ����� ������ �� ��",
        "���޶������� ����� ����", "������ �ε��� �޾Ҵٰ� �ϰ�", "�ִ�."}, false });

    _skill.push_back({ "skill1", "������ ����", { "��ȸ�ڰ� �� ��° �޺� ������", "������ ��Ĩ�ϴ�."}, false });
    _skill.push_back({ "skill2", "�˾��� �г�", { "Į���� �޾� ���� ���� ���߽���",
        "��ȸ�ڰ� ��� ������� �߻�������, ", "�����ϰ� �ı����� ������ ���մϴ�." }, false});
    _skill.push_back({ "skill3", "������ ��", { "�޾� ���� �����ڰ� Į���� ����� ",
        "�ڽ��� �ǿ� �ູ�� ������ ������", "����� ����� �ż��� ����Դϴ�.", "������ ����մϴ�." }, false});
    _skill.push_back({ "skill4", "�˾��� ����", { "���� �ӵ��� �̿��� ������", "����ġ�� ������ ���մϴ�." }, false });
    _skill.push_back({ "skill5", "�ż��� ���", { "��ȸ�ڰ� ȸ�� ����� �̿���",
        "���� �� ���� ���� �޾� ���ĸ�", "�񷯳ֽ��ϴ�." }, false });


    _rt = RectMake(208, 180, 60, 60);

    // ������ Ż����
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
        _rosarySelect = _heritageSelect = _questSelect = _praySelect = _skillSelect = _colSelect = 0;
    }
    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        _slot--;
        if (_slot < 0)
            _slot = 6;
        _rosarySelect = _heritageSelect = _questSelect = _praySelect = _skillSelect = _colSelect = 0;
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
            _praySelect++;
            _praySelect %= 7;
            break;
        case SKILL:
            _skillSelect++;
            if (_skillSelect > 4)
                _skillSelect = 4;
            break;
        case COLLECTION:
            _colSelect++;
            _colSelect %= 14;
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
        case PRAY:
            _praySelect--;
            if (_praySelect < 0)
                _praySelect = 6;
            _praySelect %= 7;
            break;
        case SKILL:
            _skillSelect--;
            if (_skillSelect < 0)
                _skillSelect = 0;
            break;
        case COLLECTION:
            _colSelect--;
            if (_colSelect < 0)
                _colSelect = 13;
            _colSelect %= 14;
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
            _praySelect -= 7;
            if (_praySelect < 0)
                _praySelect += 7;
            _praySelect %= 7;
            break;
        case SKILL:
            break;
        case COLLECTION:
            _colSelect -= 7;
            if (_colSelect < 0)
                _colSelect += 14;
            _colSelect %= 14;
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
            _praySelect += 7;
            _praySelect %= 7;
            break;
        case SKILL:
            break;
        case COLLECTION:
            _colSelect += 7;
            _colSelect %= 14;
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
        else if (_slotSelect == PRAY && _praySelect < _pray.size())
        {
            if (_pray[_praySelect]._equip)
            {
                _pray[_praySelect]._equip = false;
                _equipPray.erase(_equipPray.find(_pray[_praySelect]._iImage));
                _eqPray--;
            }
            else
            {
                if (_eqPray < 1)
                {
                    _pray[_praySelect]._equip = true;
                    _equipPray.insert(make_pair(_pray[_praySelect]._iImage, _eqPray));
                    _eqPray++;
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

            if (_rosarySelect < _rosary.size())
            {
                IMAGEMANAGER->render(_rosary[_rosarySelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _rosary[_rosarySelect]._iName, strlen(_rosary[_rosarySelect]._iName), RGB(171, 154, 63));
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 200, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _rosary[_rosarySelect]._iManual[i], strlen(_rosary[_rosarySelect]._iManual[i]), RGB(101, 96, 68));
                }
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
            if (_heritageSelect < _heritage.size())
            {
                IMAGEMANAGER->render(_heritage[_heritageSelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _heritage[_heritageSelect]._iName, strlen(_heritage[_heritageSelect]._iName), RGB(171, 154, 63));
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 210, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _heritage[_heritageSelect]._iManual[i], strlen(_heritage[_heritageSelect]._iManual[i]), RGB(101, 96, 68));
                }
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

            if (_questSelect < _quest.size())
            {
                IMAGEMANAGER->render(_quest[_questSelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _quest[_questSelect]._iName, strlen(_quest[_questSelect]._iName), RGB(171, 154, 63));
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 220, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _quest[_questSelect]._iManual[i], strlen(_quest[_questSelect]._iManual[i]), RGB(101, 96, 68));
                }
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
            if (_meaSelect < _mea.size())
            {
                IMAGEMANAGER->render(_mea[_meaSelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _mea[_meaSelect]._iName, strlen(_mea[_meaSelect]._iName), RGB(171, 154, 63));
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 220, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _mea[_meaSelect]._iManual[i], strlen(_mea[_meaSelect]._iManual[i]), RGB(101, 96, 68));
                }
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
        if (!_pray.empty())
        {
            for (int i = 0; i < _pray.size(); i++)
            {
                if (_pray[i]._equip)
                    IMAGEMANAGER->render("Item_equip", hdc, _praySlot[i].left, _praySlot[i].top);
                else
                    IMAGEMANAGER->render("Item_own", hdc, _praySlot[i].left, _praySlot[i].top);

                IMAGEMANAGER->render(_pray[i]._iImage.c_str(), hdc, _praySlot[i].left, _praySlot[i].top);
                
            }
            if (_praySelect < _pray.size())
            {
                IMAGEMANAGER->render(_pray[_praySelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _pray[_praySelect]._iName, strlen(_pray[_praySelect]._iName), RGB(171, 154, 63));
               
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 220, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _pray[_praySelect]._iManual[i], strlen(_pray[_praySelect]._iManual[i]), RGB(101, 96, 68));
                }
            }
        }
        if (!_equipPray.empty())
        {
            IMAGEMANAGER->render("Item_equip", hdc, _prayEquip.left, _prayEquip.top);
            IMAGEMANAGER->render(_equipPray.begin()->first.c_str(), hdc, _prayEquip.left, _prayEquip.top);

        }
        IMAGEMANAGER->frameRender("ItemSelect", hdc,
            _praySlot[_praySelect].left, _praySlot[_praySelect].top);
        for(int i=0;i<7;i++)
            IMAGEMANAGER->alphaRender("Blank1", hdc, _praySlot[i].left, _praySlot[i].top, 190);
    }
    else if (_slotSelect == SKILL)
    {
        IMAGEMANAGER->render("Inventory_skill", hdc, 0, 0);

        IMAGEMANAGER->render("SkillSelect", hdc, _skillSlot[_skillSelect].left, _skillSlot[_skillSelect].top);

        FONTMANAGER->drawText(hdc, 640, 280, "Neo�ձٸ� Pro", 35, 1,
            _skill[_skillSelect]._iName, strlen(_skill[_skillSelect]._iName), RGB(171, 154, 63));
        for (int i = 0; i < 7; i++)
        {
            FONTMANAGER->drawText(hdc, 670, 350 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                _skill[_skillSelect]._iManual[i], strlen(_skill[_skillSelect]._iManual[i]), RGB(101, 96, 68));
        }
    }
    else if (_slotSelect == COLLECTION)
    {
        IMAGEMANAGER->render("Inventory_collection", hdc, 0, 0);
        if (!_collection.empty())
        {
            for (int i = 0; i < _collection.size(); i++)
            {
                if (_collection[i]._equip)
                    IMAGEMANAGER->render("Item_equip", hdc, _collectSlot[i].left, _collectSlot[i].top);
                else
                    IMAGEMANAGER->render("Item_own", hdc, _collectSlot[i].left, _collectSlot[i].top);

                IMAGEMANAGER->render(_collection[i]._iImage.c_str(), hdc, _collectSlot[i].left, _collectSlot[i].top);
            }
            if (_colSelect < _collection.size())
            {
                IMAGEMANAGER->render(_collection[_colSelect]._iImage.c_str(), hdc, _rt.left, _rt.top);
                FONTMANAGER->drawText(hdc, 285, 200, "Neo�ձٸ� Pro", 35, 1,
                    _collection[_colSelect]._iName, strlen(_collection[_colSelect]._iName), RGB(171, 154, 63));
                for (int i = 0; i < 7; i++)
                {
                    FONTMANAGER->drawText(hdc, 220, 255 + 35 * i, "Neo�ձٸ� Pro", 30, 1,
                        _collection[_colSelect]._iManual[i], strlen(_collection[_colSelect]._iManual[i]), RGB(101, 96, 68));
                }
            }
        }
        IMAGEMANAGER->frameRender("ItemSelect", hdc,
            _collectSlot[_colSelect].left, _collectSlot[_colSelect].top);
    }

}