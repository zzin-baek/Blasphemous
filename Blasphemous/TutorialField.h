#pragma once

class TutorialField
{
private:
	POINT _idx;
	int _cnt, _num;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);

	TutorialField() {}
	~TutorialField() {}
};

