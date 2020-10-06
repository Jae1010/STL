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
		worker.m_Name = "员工";
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
	cout << "策划部门输出：" << endl;
	multimap<int, Worker>::iterator it =  m.find(CEHUA);
	int count = m.count(CEHUA);
	int index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "姓名：" << it->second.m_Name << "  工资为：" << it->second.m_Salary<<endl;
	}
	cout << "-----------------------------" << endl;
	cout << "美术部门输出：" << endl;
	it = m.find(MEISHU);
	count = m.count(MEISHU);
	index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "姓名：" << it->second.m_Name << "  工资为：" << it->second.m_Salary << endl;
	}
	cout << "-----------------------------" << endl;
	cout << "研发部门输出：" << endl;
	it = m.find(YANFA);
	count = m.count(YANFA);
	index = 0;
	for (; it != m.end() && index < count; ++it, ++index) {
		cout << "姓名：" << it->second.m_Name << "  工资为：" << it->second.m_Salary << endl;
	}

}


int main() {

	srand((unsigned int)time(NULL));
	//1.创建员工
	vector<Worker>vWorker;
	creatWorker(vWorker);

	//for (auto i : vWorker) {
	//	cout << i.m_Name <<"工资为" <<i.m_Salary << endl;
	//}

	//2.员工分组
	multimap<int, Worker>mWorker;
	setGroup(vWorker, mWorker);

	//3.分组显示员工

	showWorkerByGroup(mWorker);
	cout << endl;
	return 0;
}