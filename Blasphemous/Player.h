#pragma once

#define MAX_STATE 10

// bitset: �⺻, �ȱ�, ����, �ɱ�, �Ŵ޸���
enum eState
{
	WALK = 0,
	JUMP,
	ATTACK,
	CROUCH,
	CLIMB,
	DODGE,
	HANGON,
	PARRY,
	HIT,
	PORTION
};

struct plImageInfo
{
	int timing;
	POINT leftMove;
	POINT rightMove;
};

// bool _isGround: �ٴ����� ��������
class Player
{
private:

	time_t timer;
	struct tm t;

	char _strAction[128];
	bitset<MAX_STATE> _plState;
	deque<string> _actionList;
	map<string, plImageInfo> _sync;
	vector<int> _attackTime, _comboTime;
	
	RECT _player;
	POINT _plPos;
	float _plPos_x, _plPos_y, _centerX, _centerY;
	bool _isLeft, _isGround, _isFixed, _hold;
	int _hitCool;
	int _cnt, _idx_x, _idx_y;
	POINT _center;
	float _tempX, _tempY;

	int _hp, _portion;

	char _loc[128], _action[128];

public:
	HRESULT init(void);
	void initTiming(void);
	void playerAction(void);
	void playerMove(void);
	void comboAttack(void);
	void renderPlayer(HDC hdc);
	void renderProfile(HDC hdc);

	inline void setPosX(float x) { _plPos_x = x; }
	inline void setPosY(float y) { _plPos_y = y; }
	inline void setPosX(int x) { _plPos.x = x; }
	inline void setPosY(int y) { _plPos.y = y; }

	inline float getPosX() { return _plPos_x; }
	inline float getPosY() { return _plPos_y; }
	//inline int getPosX() { return _plPos.x; }
	//inline int getPosY() { return _plPos.y; }

	
	inline void setGround(bool state) { _isGround = state; }
	inline bool getGround() { return _isGround; }
	inline bool getLeft() { return _isLeft; }
	inline void setHold(bool state) { _hold = state; }

	inline void setAction(char* _action) { wsprintf(_strAction, _action); }

	inline int getMaxFrameX() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	// ���� getset
	bitset<MAX_STATE> getState() { return _plState; }
	void setState(int num, bool state) { _plState.set(num, state); }
	bool isEmpty() { return _actionList.empty(); }

	inline RECT getRect() { return _player; }
	inline int getCenterX() { return _centerX; }
	inline int getCenterY() { return _centerY; }

	void setHP(int hp) { _hp = hp; }
	int getHP() { return _hp; }

	Player() {}
	~Player();
};