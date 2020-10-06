#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

using namespace std;

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker{
public:
	string  m_Name;
	int m_Salary;
	Worker() = default;
	Worker(string name, int salary) :m_Name(name), m_Salary(salary){}
	~Worker() = default;
};

void creatWorker(vector<Worker>& v) {
	string nameSeed = "ABCDEFGHIJ";
	for (int i = 0; i < 10; ++i) {
		Worker worker;
		worker.m_Name = "Ա��";
		worker.m_Name += nameSeed[i];
		worker.m_Salary = rand() % 10001 + 10000;
		v.push_back(worker);
	}
}

void setGroup(vector<Worker>& v, multimap<int, Worker>& m) {
	for (vector<Worker>::iterator it = v.begin(); it != v.end(); ++it) {
		int deptId = rand() % 3;
		m.insert(make_pair(deptId, *it));
	}
}

void showWorkerByGroup(multimap<int, Worker>& m) {
	cout << "�߻����������" << endl;
	multimap<int, Worker>::iterator it =  m.find(CEHUA);
	int count = m.count(CEHUA);
	int index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "������" << it->second.m_Name << "  ����Ϊ��" << it->second.m_Salary<<endl;
	}
	cout << "-----------------------------" << endl;
	cout << "�������������" << endl;
	it = m.find(MEISHU);
	count = m.count(MEISHU);
	index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "������" << it->second.m_Name << "  ����Ϊ��" << it->second.m_Salary << endl;
	}
	cout << "-----------------------------" << endl;
	cout << "�з����������" << endl;
	it = m.find(YANFA);
	count = m.count(YANFA);
	index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "������" << it->second.m_Name << "  ����Ϊ��" << it->second.m_Salary << endl;
	}

}


int main() {

	srand((unsigned int)time(NULL));
	//1.����Ա��
	vector<Worker>vWorker;
	creatWorker(vWorker);

	//for (auto i : vWorker) {
	//	cout << i.m_Name <<"����Ϊ" <<i.m_Salary << endl;
	//}

	//2.Ա������
	multimap<int, Worker>mWorker;
	setGroup(vWorker, mWorker);

	//3.������ʾԱ��

	showWorkerByGroup(mWorker);
	cout << endl;
	return 0;
}