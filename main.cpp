/*	������Ϸ	*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <Windows.h>
using namespace std;

int menu();
bool doExists(int, int[]);
bool doExists(int, int[], int);
void initRandomSeed();

class CWelfareLot;

class CCustomer {
private:
	char m_Name[20];
	int m_Money;
	int m_Rank;
	int m_Redball[6];
	int m_Blueball;
public:
	CCustomer(int money = 100) {
		cout << "�������������� [1 �� 20 ���ַ�]��";
		cin.getline(m_Name, 20);
		cout << "\n��ӭ " << m_Name << "��\n\n";
		m_Money = money;
		m_Rank = 0;
	};
	bool SetNumber() {
		cout << m_Name << "����������ĺ�ɫ����� [1 ~ 33]��\n";
		for (int j = 0; j < 6; j++)
		{
			cout << "�����ɫ�� #" << j + 1 << " �ĺ��룺";
			while (!(cin >> m_Redball[j]))	//��������
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "�Ƿ����룬��������� 1 �� 33 ֮���һ�����֡�\n";
			}
			if ((m_Redball[j] < 1))
			{
				cout << "�����С����������� 1 �� 33 ֮���һ�����֡�\n";
				j--;
			}
			if ((m_Redball[j] > 33))
			{
				cout << "���������������� 1 �� 33 ֮���һ�����֡�\n";
				j--;
			}
		}
		cout << '\n' << m_Name << "�������������ɫ����� [1 ~ 16]��";
		cin >> m_Blueball;
		return true;
	};
	void ShowChoice() const {	//��ʾ�û�ѡ��ǿ����ʾ��λ��
		cout << "���ѡ��Ϊ��\t��ɫ��";
		for (int i = 0; i < 6; i++) {
			if (m_Redball[i] < 10)
				cout << '0';
			cout << m_Redball[i] << '\t';
		}
		cout << "��ɫ��";
		if (m_Blueball < 10)
			cout << '0';
		cout << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);	//�ȽϺ���
	void ShowMoney() const {
		cout << "��Ŀǰ�Ĳʽ�Ϊ " << m_Money << " Z��\n\n";
	}
	void ShowRank() const {	//���㽱��������
		cout << "\n�ϼ���ԣ�" << m_Rank << "\n\n";
		switch (m_Rank) {
		case 6:
			cout << "��ϲ��" << m_Name << "����Ӯ���� Jackpot����";
			break;
		case 5:
		case 4:
			cout << "��ϲ��" << m_Name << "����Ӯ���˶��Ƚ���";
			break;
		case 3:
		case 2:
			cout << "��ϲ��" << m_Name << "����Ӯ�������Ƚ���";
			break;
		default:
			cout << "���ź���" << m_Name << "����û��Ӯ�ý���";
		}
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
	void SetAndPrintLot() const {	//ģ�Ⲣ��ʾ����
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
			if (m_LotRed[i] < 10)
				cout << '0';
			cout << m_LotRed[i] << '\t';
		}
		cout << "��ɫ��";
		//������ʾ��ɫ�����
		rndTime = rand() % 10 + 6;	//���ƹ�����ʾ������6~15��
		for (int i = 0; i < rndTime; i++) {
			rndNum = rand() % 16 + 1;
			rndNum < 10 ? cout << '0' << rndNum << "\b\b" : cout << rndNum << "\b\b";
			Sleep(150);
		}
		if (m_LotBlue < 10)
			cout << '0';
		cout << m_LotBlue << '\n';
	};
	friend void CCustomer::Compare(CWelfareLot&);
};

void CCustomer::Compare(CWelfareLot& W) {
	for (int i = 0; i < 6; i++)
		m_Rank += doExists(m_Redball[i], W.m_LotRed);
	m_Rank += (m_Blueball == W.m_LotBlue);
};

int main() {
	int play = 1;
	cout << "-------------------------------\n";
	cout << "* ��ӭ��������-˫ɫ�� *\n";
	cout << "-------------------------------\n";
	cout << "	-by Inkorest of NJUST\n\n";

	CCustomer user;

	cout << "Ҫ�� CPU �Զ���������������� [y ���� n]\n";
	initRandomSeed();

	CWelfareLot wLot;
	char Reply2;
	do {
		user.ShowMoney();
		user.SetNumber();
		cout << "\n****************************";
		cout << "\n������� #" << play;
		cout << "\n****************************\n";
		cout << '\n';
		cout << "-------------------------------\n";
		user.ShowChoice();
		cout << "-------------------------------\n";
		wLot.SetAndPrintLot();
		cout << "-------------------------------\n";
		Sleep(750);
		user.Compare(wLot);
		user.ShowRank();
		cout << "\n****************************\n";
		cout << "����������һ����Ϸ�� [y ���� [����]]" << endl;
		cin >> Reply2;
		cout << '\n' << '\n';
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "��л�����渣��-˫ɫ��:)" << endl;
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
		cout << "�Ƿ����룬���������룺" << endl;
		initRandomSeed();
	}
	cout << '\n';
}

bool doExists(int num, int array[]){
	int size = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < size; i++)
		if (num == array[i])
			return true;
	return false;
}

bool doExists(int num, int array[], int arrayN) {
	for (int i = 0; i < arrayN; i++)
		if (num == array[i])
			return true;
	return false;
}