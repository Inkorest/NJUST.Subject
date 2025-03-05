/*	������Ϸ	*/
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int menu();
bool doExists(int, int[], int = 6);
void initRandomSeed();

class CWelfareLot;

class CCustomer {
private:
	char m_Name[20];
	int m_Money;
	int m_Rank;
	int m_Redball[6];
	int m_Blueball;
	int m_RedMatches;
	int m_BlueMatch;
	int m_BetMulti;
public:
	CCustomer(int money = 100) {
		cout << "�������������� [1 �� 20 ���ַ�]��";
		cin.getline(m_Name, 20);
		cout << "\n��ӭ " << m_Name << "��\n";
		m_Money = money;
		m_Rank = 0;
		m_RedMatches = 0;
		m_BlueMatch = 0;
	};
	int CheckInput(int range) {	//��������
		int num;
		while (!(cin >> num) || num < 1 || num > range) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "�Ƿ����룬��������� 1 �� " << range << " ֮���һ�����֣�";
		}
		return num;
	}
	void SetNumber() {	//����Ͷע
		int maxBetMulti = m_Money / 2 > 99 ? 99 : m_Money / 2;
		cout << "����ѡ�񵥱�Ͷע��౶Ͷע��ÿע�ۼ� 2 z������Ͷע������ 1���౶Ͷע������Ͷע���� [2~" << maxBetMulti << "]��";
		m_BetMulti = CheckInput(maxBetMulti);
		m_Money -= 2 * m_BetMulti;
		cout << "�ɹ�����Ͷע��";
		ShowMoney();
		cout << '\n' << m_Name << "����������ĺ�ɫ����� [1 ~ 33]��\n";
		for (int i = 0; i < 6; i++)
		{
			cout << "�����ɫ�� #" << i + 1 << " �ĺ��룺";
			m_Redball[i] = CheckInput(33);
		}
		cout << "�����������ɫ����� [1 ~ 16]��";
		m_Blueball = CheckInput(16);
	};
	void ShowChoice() const {	//��ʾ�û�ѡ��ǿ����ʾ��λ��
		cout << "���ѡ��Ϊ��\t��ɫ��";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "��ɫ��" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);
	void ShowMoney() const {
		cout << "��Ŀǰ�����Ϊ " << m_Money << " z��\n";
	}
	void ShowRank() const {	//���Ͷע���
		cout << m_Name << "�����Ͷע���Ϊ��\n��ɫ����ͬ������" << m_RedMatches << "��"
			"��ɫ�����" << (m_BlueMatch ? "��ͬ" : "����ͬ") << "��\n\n";
		if (m_Rank) {
			cout << "��ϲ��" << m_Name << "����Ӯ����";
			switch (m_Rank) {
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
	void CalcRewards() {	//���㽱�����ý��ȱ���
		int reward = 0;
		switch (m_Rank) {
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
		if (m_Rank) {
			cout << "������� " << reward << " z��";
			ShowMoney();
		}
		m_Rank = 0;
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
		m_Rank += 2;
	case 5:
		m_Rank++;
	case 4:
		m_Rank++;
	case 3:
		m_Rank++;
	default:
		m_Rank += m_BlueMatch;
	}
};

int main() {
	char div[85] = "----------------------------------------------------------------------------------\n";
	int play = 1;
	cout << div;
	cout << "* ��ӭ��������-˫ɫ�� *\n";
	cout << "	-by Inkorest of NJUST\n";
	cout << div << '\n';

	CCustomer user;

	cout << "Ҫ�� CPU �Զ����������������[y ���� n]��";
	initRandomSeed();

	CWelfareLot wLot;

	char Reply2;
	do {
		cout << div;
		cout << "������� #" << play << '\n';
		cout << div << '\n';
		user.ShowMoney();
		user.SetNumber();
		cout << '\n' << div;
		user.ShowChoice();
		cout << div;
		wLot.PrintLot();
		cout << div;
		Sleep(500);
		user.Compare(wLot);
		user.ShowRank();
		user.CalcRewards();
		cout << "����������һ����Ϸ��[y ���� [����]]��";
		cin >> Reply2;
		cout << "\n\n";
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "��л�����渣��-˫ɫ��:)\n";
	exit(1);
	return 0;
}

int menu() {
	return 0;
}

static void initRandomSeed() {	//��ʼ�����������
	char Reply1;
	cin >> Reply1;
	switch (Reply1) {
	case 'Y':
	case 'y':
		srand((unsigned)time(NULL));
		cout << "�Ѿ��� CPU �Զ���������������ӡ�\n\n";
		break;
	case 'N':
	case 'n':
		int seed;
		cout << "�������������������Ϊ��������ӣ�";
		cin >> seed;
		srand(seed);
		cout << "�Ѿ��ɴ���������������ӡ�\n";
		break;
	default:
		cout << "�Ƿ����룬���������룺";
		initRandomSeed();
	}
	cout << '\n';
}

bool doExists(int num, int array[], int arrayN) {
	for (int i = 0; i < arrayN; i++)
		if (num == array[i])
			return true;
	return false;
}