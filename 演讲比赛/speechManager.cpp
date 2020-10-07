#include"speechManager.h"


SpeechManager::SpeechManager() {
	//��ʼ������������
	this->initSpeech();

	//����12��ѡ��
	this->creatSpeaker();

	//���������¼
	this->loadRecord();
}

void SpeechManager::show_Menu() {
	cout << "****************************************" << endl;
	cout << "**********                  ***********" << endl;
	cout << "********** ��ӭ�μ��ݽ�����  **********" << endl;
	cout << "**********  1.��ʼ�ݽ�����  ************" << endl;
	cout << "**********  2.�鿴�����¼  ************" << endl;
	cout << "**********  3.��ձ�����¼  ************" << endl;
	cout << "**********  0.�˳���������  ************" << endl;
	cout << "**********                  *************" << endl;
	cout << "****************************************" << endl;
	cout <<endl;
}

void SpeechManager::exitSystem(){
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;

	//����¼�������
	this->m_Record.clear();
}

//����ѡ��
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); ++i) {
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		
		for (int j = 0; j < 2; ++j) {
			sp.m_Score[j] = 0;
		}

		this->v1.push_back(i + 10001);

		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

void SpeechManager::startSpeech() {
	//��һ�ֱ���	

	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���
	this->showScore();
	//4.�������
	this->saveRecod();

	// ��ʼ��
	this->initSpeech();

	//����12��ѡ��
	this->creatSpeaker();

	//���������¼
	this->loadRecord();

	cout << "���������ϣ���л���Ĳ��룡" << endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeechManager::speechDraw() {
	cout << "��<<" << this->m_Index << ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------" << endl;
	cout << "��ǩ˳�����£�" << endl;
	if (this->m_Index == 1) 
	{
		random_shuffle(v1.begin(), v1.end());
		for (auto& i : v1)
			cout << i << " ";
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (auto& i : v2)
			cout << i << " ";
		cout << endl;
	}
	cout << "-----------------------------" << endl;
	system("pause");
}


//����
void SpeechManager::speechContest() {
	cout << "------------��" << this->m_Index << "�ֱ�����ʽ��ʼ-----------" << endl;

	//׼����ʱ���� ���С��ɼ�
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //��¼��Ա��Ŀ 6��һ��

	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (auto& i : v_Src) {
		//��ί���

		++num;
		deque<double>d;
		for (int j = 0; j < 10; ++j) {
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0);
		double avg = sum / (double)d.size();
		
		//��ӡƽ����
		//cout << "��ţ�" << i << "  ������" << this->m_Speaker[i].m_Name << "  ƽ���֣�" << avg << endl;

		this->m_Speaker[i].m_Score[m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, i));

		//ÿ6��ȡǰ����
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (auto& j : groupScore) {
				cout << "��ţ�" << j.second << "  ������" << this->m_Speaker[j.second].m_Name 
					<< " �ɼ�Ϊ��" << j.first << endl;
			}
			//ȡǰ����
			int count = 0;
			for (auto& m : groupScore) {
				if (count < 3) {
					if (this->m_Index == 1) {
						v2.push_back(m.second);
						++count;
					}
					else
					{
						vVectory.push_back(m.second);
						++count;
					}
				}
			}
			groupScore.clear();
			cout << endl;
		}

		
	}
	cout << "------------��" << this->m_Index << "�ֱ�������-----------" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::showScore() {
	cout << "------------��" << this->m_Index << "�ֱ��������������-----------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else
	{
		v = vVectory;
	}

	for (auto& i : v) {
		cout << "��ţ�" << i << "  ������" << this->m_Speaker[i].m_Name
			<< " �ɼ�Ϊ��" << this->m_Speaker[i].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}


//���浽csv
void SpeechManager::saveRecod() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	
	//��ÿ���˵�����д�뵽�ļ���
	for (auto& i : vVectory) {
		ofs << i << "," << this->m_Speaker[i].m_Score[this->m_Index-1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "�ļ���¼�ɹ���" << endl;

	this->fileEmpty = false;
}


//��ȡ������¼
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	
	if (!ifs.is_open()) {
		this->fileEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char c;
	ifs >> c;
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��" << endl;
		this->fileEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileEmpty = false;
	//�������ȡ�ĵ���Ԫ�طŻ�ȥ
	ifs.putback(c);
	vector<string>v;	//���6��string�ַ���
	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;//�鵽��λ�õı���
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(index, v));
		v.clear();
		index++;
	}
	
	ifs.close();
}


//��ʾ�����¼
void SpeechManager::showRecord() {
	if (this->fileEmpty) {
		cout << "�ļ�Ϊ�ջ��߲����ڣ�" << endl;
	}

	for (auto& i : m_Record) {
		cout << "��" << i.first + 1 << "�죺"
			<< "�ھ���ţ�" << i.second[0] << "  �÷֣�" << i.second[1] << " "
			<< "�Ǿ���ţ�" << i.second[2] << "  �÷֣�" << i.second[3] << " "
			<< "������ţ�" << i.second[4] << "  �÷֣�" << i.second[5] << endl;

		//for (auto& j : i.second) {
		//	cout << j << " ";
		//}
		//cout << endl;
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord() {
	cout << " ȷ����ռ�¼��" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;
	int seclect;
	cin >> seclect;
	if (seclect == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();

		//����12��ѡ��
		this->creatSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;

	}

	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager() {

}

