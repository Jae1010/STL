#include <iostream>
using namespace std;

#include "speechManager.h"

#include <vector>

int main() {
	srand((unsigned int)time(NULL));

	SpeechManager sm;

	//for (auto i : sm.m_Speaker)
	//	cout << "ѡ�ֱ�ţ�" << i.first << "  ����Ϊ: " << i.second.m_Name <<"  ����Ϊ�� "<<i.second.m_Score[0]<< endl;

	int choice = 0;

	while (true)
	{
		sm.show_Menu();

		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //��ʼ����
			sm.startSpeech();
			break;
		case 2: //�鿴�����¼
			sm.showRecord();
			break;
		case 3:	//��ռ�¼
			sm.clearRecord();
			break;
		case 0:	//�˳�ϵͳ
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
