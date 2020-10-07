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
	//构造函数
	SpeechManager();

	//菜单功能
	void show_Menu();

	//退出功能
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void initSpeech();

	//创建12名选手
	void creatSpeaker();

	//开比赛 比赛流程控制函数
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void showScore();

	//保存到csv
	void saveRecod();

	//读取分数记录
	void loadRecord();

	//显示往届记录
	void showRecord();


	//判断文件是否为空
	bool fileEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;

	//清空记录
	void clearRecord();


	//成员属性
	vector<int>v1;
	vector<int>v2;
	vector<int>vVectory;

	map<int, Speaker> m_Speaker;
	
	int m_Index;
};