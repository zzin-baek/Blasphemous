#pragma once

#define MAX_STATE 8
#define MAX_QUEUE 10

// bitset: 기본, 걷기, 점프, 앉기, 매달리기
enum eState
{
	WALK = 0,
	JUMP,
	CROUCH,
	DODGE,
	HANGON
};
// bool _isGround: 바닥인지 공중인지

class Player
{
private:
	char _strAction[128];
	bitset<MAX_STATE> _plState;
	deque<string> _actionList;
	
	RECT _player;
	float _plPos_x, _plPos_y;
	float _centerX, _centerY;
	bool _isLeft, _isGround, _isFixed;
	int _cnt, _idx_x, _idx_y;
	float _tempX, _tempY;

	char _loc[128];
	char _action[128];

public:
	HRESULT init(void);
	void playerAction(void);
	void playerMove(void);
	void renderPlayer(HDC hdc);

	inline void setPosX(float x) { _plPos_x = x; }
	inline void setPosY(float y) { _plPos_y = y; }

	inline float getPosX() { return _plPos_x; }
	inline float getPosY() { return _plPos_y; }
	
	inline void setGround(bool state) { _isGround = state; }
	inline bool getGround() { return _isGround; }

	inline void setAction(char* _action) { wsprintf(_strAction, _action); }

	inline int getMaxFrameX() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	// 상태 getset
	bitset<MAX_STATE> getState() { return _plState; }
	void setState(int num, bool state) { _plState.set(num, state); }

	inline RECT getRect() { return _player; }

	Player() {}
	~Player();
};