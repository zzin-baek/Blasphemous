#pragma once
#include "GameNode.h"


// ������ �����ְ�, ������ ���� �� �ʰ��� ��ȣ�ۿ� ������ �����ֱ� ���� ��
class BaseMap : public GameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BaseMap() {}
	~BaseMap() {}
};

