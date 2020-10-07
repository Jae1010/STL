#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "speaker.h"
#include <string>
#include <algorithm>
#include <ctime>
#include <functional>
#include <deque>
#include <numeric>
#include <fstream>

class SpeechManager {
public:
	//���캯��
	SpeechManager();

	//�˵�����
	void show_Menu();

	//�˳�����
	void exitSystem();

	//��������
	~SpeechManager();

	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void creatSpeaker();

	//������ �������̿��ƺ���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//���浽csv
	void saveRecod();

	//��ȡ������¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();


	//�ж��ļ��Ƿ�Ϊ��
	bool fileEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;

	//��ռ�¼
	void clearRecord();


	//��Ա����
	vector<int>v1;
	vector<int>v2;
	vector<int>vVectory;

	map<int, Speaker> m_Speaker;
	
	int m_Index;
};