/*	������Ϸ	*/
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int seed = (unsigned)time(NULL);	//���������

void printMenu(int);
void menuCommand();
void printRule();
void passcode();
char getReply();
bool doExists(int, int[], int = 6);
void initRandomSeed();

class CWelfareLot;

class CCustomer {
private:
	char m_Name[20];
	int m_Money;
	int m_Prize;
	int m_Redball[6];
	int m_Blueball;
	int m_RedMatches;
	int m_BlueMatch;
	int m_BetMulti;
public:
	CCustomer(int money = 100) :m_Money(money), m_Prize(0), m_RedMatches(0), m_BlueMatch(0), m_BetMulti(1) {
		cout << "�������������� [1 �� 20 ���ַ�]��";
		cin.getline(m_Name, 20);
		cout << "\n��ӭ " << m_Name << "��\n";
	};
	int CheckInput(int range) {	//��������
		int num;
		while (!(cin >> num) || num < 1 || num > range) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "�Ƿ����롣��������� 1 �� " << range << " ֮���һ�����֣�";
		}
		return num;
	}
	void SetNumber() {	//����Ͷע
		int maxBetMulti = m_Money / 2 > 99 ? 99 : m_Money / 2;
		cout << "����ѡ�񵥱�Ͷע��౶Ͷע��ÿע�ۼ� 2 z������Ͷע������ 1���౶Ͷע������Ͷע���� [2~" << maxBetMulti << "]��";
		m_BetMulti = CheckInput(maxBetMulti);
		m_Money -= 2 * m_BetMulti;
		cout << "�ɹ�����Ͷע��";
		PrintMoney();
		cout << '\n' << m_Name << "����������ĺ�ɫ����� [1 ~ 33]��\n";
		for (int i = 0; i < 6; i++)
		{
			cout << "�����ɫ�� #" << i + 1 << " �ĺ��룺";
			m_Redball[i] = CheckInput(33);
		}
		cout << "�����������ɫ����� [1 ~ 16]��";
		m_Blueball = CheckInput(16);
	};
	void PrintSelection() const {	//��ʾ�û�ѡ��ǿ����ʾ��λ��
		cout << "���ѡ��Ϊ��\t��ɫ��";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "��ɫ��" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);
	void PrintMoney() const {
		cout << "��Ŀǰ�����Ϊ " << m_Money << " z��\n";
	}
	void PrintPrize() const {	//���Ͷע���
		cout << m_Name << "�����Ͷע���Ϊ��\n��ɫ����ͬ������" << m_RedMatches << "��"
			"��ɫ�����" << (m_BlueMatch ? "��ͬ" : "����ͬ") << "��\n\n";
		if (m_Prize) {
			cout << "��ϲ��" << m_Name << "����Ӯ����";
			switch (m_Prize) {
			case 6:
				cout << "һ�Ƚ���!";
				break;
			case 5:
				cout << "���Ƚ���";
				break;
			case 4:
				cout << "���Ƚ���";
				break;
			case 3:
				cout << "�ĵȽ���";
				break;
			case 2:
				cout << "��Ƚ���";
				break;
			case 1:
				cout << "���Ƚ���";
				break;
			}
		}
		else
			cout << "���ź���" << m_Name << "����û��Ӯ�ý���";
		cout << '\n';
	};
	void CalcRewards() {	//���㽱�����ý�������
		int reward = 0;
		switch (m_Prize) {
		case 6:
			reward = 10000000;
			break;
		case 5:
			reward = 500000;
			break;
		case 4:
			reward = 3000;
			break;
		case 3:
			reward = 200;
			break;
		case 2:
			reward = 10;
			break;
		case 1:
			reward = 5;
			break;
		}
		m_Money += reward * m_BetMulti;
		if (m_Prize) {
			cout << "���� " << reward << " z �Ѿ����ŵ�������";
			PrintMoney();
		}
		m_Prize = 0;
		m_RedMatches = 0;
		m_BlueMatch = 0;
	};
};

class CWelfareLot {
private:
	int m_LotRed[6];
	int m_LotBlue;
public:
	CWelfareLot() {	//���ɴ󽱺���
		int tempNum;
		for (int i = 0; i < 6; i++) {
			do	//��ֹ��ɫ���ظ�
				tempNum = rand() % 33 + 1;
			while (doExists(tempNum, m_LotRed, i));
			m_LotRed[i] = tempNum;
		}
		m_LotBlue = rand() % 16 + 1;
	};
	void PrintLot() const {	//ģ�Ⲣ��ʾ����
		int rndTime, rndNum;
		cout << "�󽱺���Ϊ��\t��ɫ��";
		//������ʾ��ɫ�����
		for (int i = 0; i < 6; i++) {
			rndTime = rand() % 10 + 6;	//���ƹ�����ʾ������6~15��
			for (int j = 0; j < rndTime; j++) {
				rndNum = rand() % 33 + 1;
				rndNum < 10 ? cout << '0' << rndNum << "\b\b" : cout << rndNum << "\b\b";
				Sleep(150);
			}
			cout << (m_LotRed[i] < 10 ? '0' : '\0') << m_LotRed[i] << '\t';
		}
		cout << "��ɫ��";
		//������ʾ��ɫ�����
		rndTime = rand() % 10 + 6;	//���ƹ�����ʾ������6~15��
		for (int i = 0; i < rndTime; i++) {
			rndNum = rand() % 16 + 1;
			cout << (rndNum < 10 ? '0' : '\0') << rndNum << "\b\b";
			Sleep(150);
		}
		cout << (m_LotBlue < 10 ? '0' : '\0') << m_LotBlue << '\n';
	};
	friend void CCustomer::Compare(CWelfareLot&);
};

void CCustomer::Compare(CWelfareLot& W) {	//���㽱��ȼ�
	for (int i = 0; i < 6; i++)
		m_RedMatches += doExists(m_Redball[i], W.m_LotRed);
	m_BlueMatch += (m_Blueball == W.m_LotBlue);
	switch (m_RedMatches) {	//��˫ɫ�������㽱��
	case 6:
		m_Prize += 2;
	case 5:
		m_Prize++;
	case 4:
		m_Prize++;
	case 3:
		m_Prize++;
	default:
		m_Prize += m_BlueMatch;
	}
};

int main() {
	char div[86] = "-----------------------------------------------------------------------------------\n";
	int play = 1;
	cout << div;
	cout << "** ��ӭ��������-˫ɫ�� **\n";
	cout << "	-by Inkorest of NJUST\n";
	cout << div << '\n';
	printMenu(1);
	cout << '\n';

	CCustomer user;

	cout << '\n';
	cout << "Ҫ�� CPU �Զ����������������\n";
	cout << "[Y] ��\n";
	cout << "[N] ��\n";
	cout << "���������";
	initRandomSeed();

	char reply;
	do {
		CWelfareLot wLot;
		cout << div;
		cout << "������� #" << play << '\n';
		cout << div << '\n';
		user.PrintMoney();
		user.SetNumber();
		cout << '\n' << div;
		user.PrintSelection();
		cout << div;
		wLot.PrintLot();
		cout << div;
		Sleep(500);
		user.Compare(wLot);
		user.PrintPrize();
		user.CalcRewards();
		cout << '\n';
		cout << "����������һ����Ϸ��\n";
		cout << "[Y] ȷ��\n";
		cout << "[M] ����Ϸ�˵�\n";
		cout << "[Q] �˳���Ϸ\n";
		cout << "���������";
		reply = getReply();
		cout << "\n";
		if (reply == 'M')
			printMenu(2);
		srand(++seed);
		play++;
	} while (reply != 'Q');

	cout << "��л�����渣��-˫ɫ��:)\n";
	return 0;
}

void printMenu(int status) {
	cout << "---------- ��Ϸ�˵� ----------\n";
	cout << "[G] " << (status == 1 ? "��ʼ" : "����") << "��Ϸ\n";
	cout << "[R] �鿴��Ϸ����\n";
	cout << "[C] �������Ա����\n";
	cout << "[Q] �˳���Ϸ\n";
	cout << "���������";
	menuCommand();
}

void menuCommand() {
	char command;
	cin >> command;
	while (cin.get() != '\n')
		command = '\0';
	switch (command) {
	case 'G':
	case 'g':
		break;
	case 'R':
	case 'r':
		printRule();
		printMenu(2);
		break;
	case 'C':
	case 'c':
		passcode();
		break;
	case 'Q':
	case 'q':
		cout << "\n��л�����渣��-˫ɫ��:)\n";
		exit(0);
	default:
		cout << "�Ƿ����롣���������룺";
		menuCommand();
	}
}

void printRule() {
	cout << '\n';
	cout << "------------------------------- ����-˫ɫ����Ϸ���� -------------------------------\n";
	cout << "1. ��ע���û�ͨ��֧��������Ͷע����ѡ����Ͷע / �౶Ͷע* ����Ȼ���� 33 ����ɫ���\n";
	cout << "	������ѡ 6 ������ 16 ����ɫ���������ѡ 1 ����Ϊ�Լ���Ͷע���롣\n";
	cout << "2. ������CPU �������趨�õ���������ӣ�����ó� 6 ����ɫ��󽱺���� 1 ����ɫ���\n";
	cout << "	���롣\n";
	cout << "3. ���㣺�����û���󽱺����ƥ����������û����н��ȼ��������Ž������н�����\n";
	cout << "*�౶Ͷע������ע�ۼ۵ĸ�������� 99 ����Ͷע�����н�������Ҳ����Ϊ������\n";
	cout << '\n';
	cout << "--------------------- ������ձ� ---------------------\n";
	cout << "����\t����\t�н���������ɫ�������/��ɫ����������\n";
	cout << "һ�Ƚ�\t10M z\t6/S\n";
	cout << "���Ƚ�\t500K z\t6/F\n";
	cout << "���Ƚ�\t3K z\t5/S\n";
	cout << "�ĵȽ�\t200 z\t5/F ���� 4/S\n";
	cout << "��Ƚ�\t10 z\t4/F ���� 3/S\n";
	cout << "���Ƚ�\t5 z\t2/S ���� 1/S ���� 0/S\n";
	cout << '\n';
	system("pause");
	cout << '\n';
}

void passcode() {

}

char getReply() {
	char reply;
	cin >> reply;
	while (cin.get() != '\n')
		reply = '\0';
	if (reply == 'Y' || reply == 'y' || reply == 'M' || reply == 'm' || reply == 'Q' || reply == 'q')
		return reply > 'Z' ? reply -= 32 : reply;
	cout << "�Ƿ����롣���������룺";
	getReply();
}

static void initRandomSeed() {	//��ʼ�����������
	char reply;
	cin >> reply;
	while (cin.get() != '\n')
		reply = '\0';
	switch (reply) {
	case 'Y':
	case 'y':
		cout << "�Ѿ��� CPU �Զ���������������ӡ�\n\n";
		break;
	case 'N':
	case 'n':
		cout << "�������������������Ϊ��������ӣ�";
		cin >> seed;
		cout << "�Ѿ��ɴ���������������ӡ�\n\n";
		break;
	default:
		cout << "�Ƿ����롣���������룺";
		initRandomSeed();
	}
	srand(seed);
}

bool doExists(int num, int array[], int arrayN) {
	for (int i = 0; i < arrayN; i++)
		if (num == array[i])
			return true;
	return false;
}