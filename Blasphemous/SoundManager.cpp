#include "Stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    return S_OK;
}

void SoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    // mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ� �ݹ�
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;

    const char* str = finalQuery.c_str();

    // mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ� �ݹ�
    mciSendString(str, NULL, 0, NULL);  // ���带 ����� �� �Բ� ������ ����� �ִ���
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    /*
    SND_ASYNC: ����ϸ鼭 �����ڵ带 ����
    �� �񵿱� Ŭ����

    SND_LOOP: �ݺ� ���

    SND_NODEFALST: ������ ��ο� ������ ��� ������� ������� �ʴ´�.
    */
    PlaySound(fileName, NULL, SND_ASYNC | SND_ASYNC);
}

void SoundManager::playSoundWithKey(string key)
{
    string first = "play ";
    string finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}
