#pragma once
#include "SingletonBase.h"

enum eSlot
{
	ROSARY,
	HERITAGE,
	QUEST,
	MEA,
	PRAY,
	SKILL,
	COLLECTION,
	MAX_SLOT
};

struct tagItem
{
	string _iImage;
	char _iName[CHAR_MAX];
	char _iManual[MAX_SLOT][CHAR_MAX];
	bool _equip = false;
};

class Inventory : public SingletonBase<Inventory>
{
private:
	vector<tagItem> _rosary, _heritage, _quest, _mea, _pray, _skill, _collection;
	map<string, int> _equipRosary, _equipHeritage, _equipMea, _equipPray;

	int _alpha, _slot;
	POINT _idx;
	bool _out;

	int _eqRosary, _eqHeritage, _eqMea, _eqPray;
	int _slotSelect, _select, _cnt;
	int _rosarySelect, _heritageSelect, _questSelect, _meaSelect, _praySelect, _skillSelect, _colSelect;

	RECT _rosarySlot[14], _heritageSlot[7], _questSlot[30], _meaSlot[7];
	RECT _praySlot[7], _skillSlot[5], _collectSlot[14];
	RECT _rosaryEquip[2], _heritageEquip[3], _meaEquip, _prayEquip;
	RECT _rt;
	
public:
	HRESULT init(void);
	void update(void);
	void addItem(int num, tagItem _itemInfo);
	void printInfo(HDC hdc, tagItem _itemInfo);
	void render(HDC hdc);

	bool getOut() { return _out; }
	void setOut(bool state) { _out = state; }

	Inventory() {}
	~Inventory() {}
};