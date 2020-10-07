#include <iostream>
using namespace std;

#include "speechManager.h"

#include <vector>

int main() {
	srand((unsigned int)time(NULL));

	SpeechManager sm;

	//for (auto i : sm.m_Speaker)
	//	cout << "选手编号：" << i.first << "  名字为: " << i.second.m_Name <<"  分数为： "<<i.second.m_Score[0]<< endl;

	int choice = 0;

	while (true)
	{
		sm.show_Menu();

		cout << "请输入您的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //开始比赛
			sm.startSpeech();
			break;
		case 2: //查看往届记录
			sm.showRecord();
			break;
		case 3:	//清空记录
			sm.clearRecord();
			break;
		case 0:	//退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}

	}
	

	system("pause");
	return 0;
}
