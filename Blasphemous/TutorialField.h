#pragma once

class TutorialField
{
public:
	HRESULT init(void);
	void render(HDC hdc);

	TutorialField() {}
	~TutorialField() {}
};

