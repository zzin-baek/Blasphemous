#pragma once
#include "SingletonBase.h"

// ������ ���� ���̺귯�� (���)
// �ð� / ���� -> PlaySound()
#include <mmsystem.h>
// mciSendString() �̶�� �Լ��� ����ϱ� ����
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")

class SoundManager : public SingletonBase <SoundManager>
{
public:
	HRESULT init(void);
	//MP3
	void addMp3FileWithKey(string key, string fileName);
	// WAV
	void addWaveFileWithKey(string key, string fileName);
	// ȿ����
	void playEffectSoundWave(char* fileName);
	// MP3 ���
	void playSoundWithKey(string key);
	// MP3 ��� �ݺ�
	void CheckAndReplayWithKey(string key);
	// ����
	void stopMp3WithKey(string key);


	SoundManager() {}
	~SoundManager() {}
};

