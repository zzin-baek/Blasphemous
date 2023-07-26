#pragma once

#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// GetTickCount(): API 공용 함수
		// ㄴ API함수로 OS가 부팅된 후의 경과 시간을 체크해 준다.
		// ㄴ 밀리세컨 단위로 체크가 가능하며 밀리세컨 단위로 시간 값을 반환하기 때문에 규모가 크지않은 로직에 적합하다. (randomDevice 부적합)
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init(void) { return S_OK; }

	inline int getInt(int num)
	{
		return rand() % num;
	}
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}

	int getIntArray(int* arr, int size)
	{
		//int size = sizeof(arr) / sizeof(int);

		return arr[rand() % size];
	}

};