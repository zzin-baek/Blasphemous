#pragma once

#define MAX_STATE 8

// bitset: 기본, 걷기, 점프, 앉기, 매달리기
typedef enum eState
{
	WALK,
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
	
	int _cnt;
	RECT _player;
	POINT _plPos;
	float _plPos_x, _plPos_y;
	bool _isLeft, _isGround;
	int _idx_x, _idx_y;

public:
	HRESULT init(void);
	void playerAction(void);
	void renderPlayer(HDC hdc);

	inline void setPosX(float x) { _plPos_x = x; }
	inline void setPosY(float y) { _plPos_y = y; }

	inline void setLeft(bool state) { _isLeft = state; }
	inline bool getLeft() { return _isLeft; }

	inline void setAction(char* _action) { wsprintf(_strAction, _action); }

	inline float getPosX() { return _plPos_x; }
	inline float getPosY() { return _plPos_y; }

	inline void setIdxX(int x) { _idx_x = x; }
	inline void setIdxY(int y) { _idx_y = y; }
	inline int getIdxX() { return _idx_x; }
	inline int getIdxY() { return _idx_y; }

	inline int getMaxFrameX() { return IMAGEMANAGER->findImage(_strAction)->getMaxFrameX(); }

	// 상태 getset
	bitset<MAX_STATE> getState() { return _plState; }
	bool isIdle() { return _plState.none(); }
	void setState(int num, bool state) { _plState.set(num, state); }
	void resetState() { _plState.reset(); }

	Player() {}
	~Player();
};