#include "Stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    SOUNDMANAGER->addWaveFileWithKey("Hit_enemy_1", "Resources/Sound/penitent/PENITENT_ENEMY_HIT_4.wav");
    SOUNDMANAGER->addWaveFileWithKey("Hit_enemy_2", "Resources/Sound/penitent/PENITENT_ENEMY_HIT_3.wav");
    SOUNDMANAGER->addWaveFileWithKey("Hit_shield", "Resources/Sound/enemy/SHIELD_ENEMY_HIT_SHIELD.wav");
    SOUNDMANAGER->addWaveFileWithKey("Boss_defeat", "Resources/Sound/Boss_Fight_Ending.wav");
    SOUNDMANAGER->addWaveFileWithKey("Boss_Hit", "Rosources/Sound/penitent/PENITENT_BOSS_DEATH_HIT.wav");


    return S_OK;
}

void SoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    // mciSendString() : 장치에 특정 명령어를 전송하여 구동시키는 함수
    // ㄴ 문자열 명령어, 반환값을 알려줄 명령어, 반환될 길이, 핸들 콜백
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    PlaySound(fileName, NULL, SND_ASYNC | SND_ASYNC);
}

void SoundManager::playSoundWithKey(string key)
{
    //string first = "play ";
    //string finalQuery = first + key;

    string finalQuery = "seek " + key + " to start";
    mciSendString(finalQuery.c_str(), NULL, 0, NULL);
    string first = "play ";
    finalQuery = first + key;
    mciSendString(finalQuery.c_str(), NULL, 0, NULL);
}

void SoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::CheckAndReplayWithKey(string key)
{
    char ch[128];

    string first = "status ";
    string end = " mode";
    string finalQuery = first + key + end;

    const char* str = finalQuery.c_str();
    mciSendString(str, ch, 128, NULL);

    if (strcmp(ch, "stopped") == 0)
    {
        finalQuery = "seek " + key + " to start";
        mciSendString(finalQuery.c_str(), NULL, 0, NULL);
        first = "play ";
        finalQuery = first + key;
        mciSendString(finalQuery.c_str(), NULL, 0, NULL);
    }
}