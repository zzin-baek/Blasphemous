#pragma once
#include "SingletonBase.h"

#define SLOT_NUM 7

enum eSlot
{
	ROSARY,
	HERITAGE,
	QUEST,
	MEA,
	PRAY,
	SKILL,
	COLLECTION
};

struct tagItem
{
	string _iImage;
	/*char* _iName[CHAR_MAX];
	char* _iManual[CHAR_MAX];*/
	string _iName;
	string _iManual;
	bool _equip = false;
};

class Inventory : public SingletonBase<Inventory>
{
private:
	vector<tagItem> _rosary, _heritage, _quest, _mea, _pray, _skill;
	map<string, int> _equipRosary, _equipHeritage, _equipMea, _equipPray;

	int _alpha, _slot;
	int _eqRosary, _eqHeritage, _eqMea, _eqPray;
	int _slotSelect, _select, _cnt;
	int _rosarySelect, _heritageSelect, _questSelect, _meaSelect, _praySelect, _skillSelect;
	RECT _rosarySlot[14], _heritageSlot[7], _questSlot[30], _meaSlot[7], _praySlot[7];
	RECT _skillSlot[5];
	RECT _rosaryEquip[2], _heritageEquip[3], _meaEquip, _prayEquip;
	POINT _idx;

	bool _out;

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