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
	vector<tagItem> _rosary;
	vector<tagItem> _heritage;
	map<string, int> _equipRosary;
	map<string, int> _equipHeritage;

	int _alpha, _slot;
	int _eqRosary, _eqHeritage;
	int _slotSelect, _select, _cnt;
	int _rosarySelect, _heritageSelect;
	RECT _rosarySlot[14], _heritageSlot[7];
	RECT _rosaryEquip[2], _heritageEquip[3];
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