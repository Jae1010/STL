#include"speechManager.h"


SpeechManager::SpeechManager() {
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->creatSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManager::show_Menu() {
	cout << "****************************************" << endl;
	cout << "**********                  ***********" << endl;
	cout << "********** 欢迎参加演讲比赛  **********" << endl;
	cout << "**********  1.开始演讲比赛  ************" << endl;
	cout << "**********  2.查看往届记录  ************" << endl;
	cout << "**********  3.清空比赛记录  ************" << endl;
	cout << "**********  0.退出比赛程序  ************" << endl;
	cout << "**********                  *************" << endl;
	cout << "****************************************" << endl;
	cout <<endl;
}

void SpeechManager::exitSystem(){
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVectory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;

	//将记录容器清空
	this->m_Record.clear();
}

//增加选手
void SpeechManager::creatSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); ++i) {
		string name = "选手";
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
	//第一轮比赛	

	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示结果
	this->showScore();
	//4.保存分数
	this->saveRecod();

	// 初始化
	this->initSpeech();

	//创建12名选手
	this->creatSpeaker();

	//加载往届记录
	this->loadRecord();

	cout << "本届比赛完毕！感谢您的参与！" << endl;
	system("pause");
	system("cls");
}

//抽签
void SpeechManager::speechDraw() {
	cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
	cout << "-----------------------------" << endl;
	cout << "抽签顺序如下：" << endl;
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


//比赛
void SpeechManager::speechContest() {
	cout << "------------第" << this->m_Index << "轮比赛正式开始-----------" << endl;

	//准备临时容器 存放小组成绩
	multimap<double, int, greater<double>> groupScore;

	int num = 0; //记录人员数目 6人一组

	vector<int>v_Src;
	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	for (auto& i : v_Src) {
		//评委打分

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
		
		//打印平均分
		//cout << "编号：" << i << "  姓名：" << this->m_Speaker[i].m_Name << "  平均分：" << avg << endl;

		this->m_Speaker[i].m_Score[m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, i));

		//每6人取前三名
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (auto& j : groupScore) {
				cout << "编号：" << j.second << "  姓名：" << this->m_Speaker[j.second].m_Name 
					<< " 成绩为：" << j.first << endl;
			}
			//取前三名
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
	cout << "------------第" << this->m_Index << "轮比赛结束-----------" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore() {
	cout << "------------第" << this->m_Index << "轮比赛晋级结果如下-----------" << endl;
	vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else
	{
		v = vVectory;
	}

	for (auto& i : v) {
		cout << "编号：" << i << "  姓名：" << this->m_Speaker[i].m_Name
			<< " 成绩为：" << this->m_Speaker[i].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}


//保存到csv
void SpeechManager::saveRecod() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	
	//将每个人的数据写入到文件中
	for (auto& i : vVectory) {
		ofs << i << "," << this->m_Speaker[i].m_Score[this->m_Index-1] << ",";
	}
	ofs << endl;

	ofs.close();
	cout << "文件记录成功！" << endl;

	this->fileEmpty = false;
}


//读取分数记录
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in);
	
	if (!ifs.is_open()) {
		this->fileEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char c;
	ifs >> c;
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->fileEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileEmpty = false;
	//将上面读取的单个元素放回去
	ifs.putback(c);
	vector<string>v;	//存放6个string字符串
	string data;
	int index = 0;

	while (ifs >> data)
	{
		//cout << data << endl;
		int pos = -1;//查到，位置的变量
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


//显示往届记录
void SpeechManager::showRecord() {
	if (this->fileEmpty) {
		cout << "文件为空或者不存在！" << endl;
	}

	for (auto& i : m_Record) {
		cout << "第" << i.first + 1 << "届："
			<< "冠军编号：" << i.second[0] << "  得分：" << i.second[1] << " "
			<< "亚军编号：" << i.second[2] << "  得分：" << i.second[3] << " "
			<< "季军编号：" << i.second[4] << "  得分：" << i.second[5] << endl;

		//for (auto& j : i.second) {
		//	cout << j << " ";
		//}
		//cout << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord() {
	cout << " 确认清空记录？" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;
	int seclect;
	cin >> seclect;
	if (seclect == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建12名选手
		this->creatSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;

	}

	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager() {

}

