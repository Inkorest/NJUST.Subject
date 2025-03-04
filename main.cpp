/*	������Ϸ	*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

bool isMatch(int, int[]);
int getGameNbr(int = 33);
void initRandomSeed() {	//��ʼ�����������
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
		cin >> seed;	//�������������
		srand(seed);
		cout << "�Ѿ��ɴ���������������ӡ�\n";
		break;
	default:
		cout << "�Ƿ����룬���������룺" << endl;
		initRandomSeed();
	}
	cout << '\n';
}

class CWelfareLot;

class CCustomer {
private:
	char m_Name[20];
	int m_Money;
	int m_Rank;
	int m_Redball[6];
	int m_Blueball;
public:
	CCustomer(char name[], int money = 100) {
		strcpy_s(m_Name, name);
		m_Money = money;
		cout << "\n��ӭ " << m_Name << "��\n\n";
	};
	bool SetNumber() {	//���ܲ�ƱͶע���ɹ�����true
		cout << m_Name << "����������ĺ�ɫ����롣\n";
		for (int j = 0; j < 6; j++)	//����5����ѡ����
		{
			cout << "�����ɫ�� #" << j + 1 << " �ĺ��룺";
			while (!(cin >> m_Redball[j]))	//������������
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "�Ƿ����룬��������� 1 �� 48 ֮���һ�����֡�\n";
			}
			if ((m_Redball[j] < 1))
			{
				cout << "�����С����������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
			if ((m_Redball[j] > 48))
			{
				cout << "���������������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
		}
		cout << '\n';
		cout << m_Name << "�������������ɫ����룺";
		cin >> m_Blueball;	//Ҫ�����������ɫ�����
		return true;
	};
	void ShowChoice() {
		cout << m_Name << "�����ѡ��Ϊ��\t" << m_Redball[0] << '\t' << m_Redball[1] << '\t' << m_Redball[2] << '\t' 
			<< m_Redball[3] << '\t' << m_Redball[4] << '\t' << m_Redball[5] << '\t' << "PB " << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);	//�Ƚϸ��ʣ���ֵ�н��ȼ�
	void ShowMoney() {
		cout << m_Name << "����Ŀǰ�Ĳʽ�Ϊ " << m_Money << " Z��\n\n";
	}
	void ShowRank() {	//�����н��ȼ����㽱��������
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
	CWelfareLot() {	//CPU���ɴ󽱺���
		m_LotRed[0] = getGameNbr();
		m_LotRed[1] = getGameNbr();
		m_LotRed[2] = getGameNbr();
		m_LotRed[3] = getGameNbr();
		m_LotRed[4] = getGameNbr();
		m_LotRed[5] = getGameNbr();
		m_LotBlue = getGameNbr(16);
	};
	void SetLot() {
		int nRnd, nNum;
		for (int i = 0; i < 6; i++) {	//Ҫ����6������
			nRnd = rand();	//���ȡѭ�����������ֱ任��ʱ�䳤���������
			for (int j = 0; j < nRnd; j++) {
				nNum = rand() % 21;	//���ȡ0~20֮������ֽ��б任
				if (nNum < 10)
					cout << nNum << '\b';	//��ȡ������С��10����һλ������ʾ��������һλ���ټ����任�����ֽ�ԭ���ָ��ǣ�����ҡ��Ч��
				else
					cout << nNum << "\b\b";	//��ȡ����������λ����������λ
			}
			cout << nNum << " ";
			m_LotRed[i] = nNum;	//�任���������ּ�Ϊ������
		}
	};	//��������
	void PrintLot() {
		cout << "CPU ��ѡ��Ϊ��\t" << m_LotRed[0] << '\t' << m_LotRed[1] << '\t' << m_LotRed[2] << '\t' 
			<< m_LotRed[3] << '\t' << m_LotRed[4] << '\t' << m_LotRed[5] << '\t' << "PB " << m_LotBlue << '\n';
	};
	friend void CCustomer::Compare(CWelfareLot&);	//�ж��û��Ƿ��н�
};

void CCustomer::Compare(CWelfareLot& W) {
	int truematch[6];
	truematch[0] = isMatch(m_Redball[0], W.m_LotRed);
	truematch[1] = isMatch(m_Redball[1], W.m_LotRed);
	truematch[2] = isMatch(m_Redball[2], W.m_LotRed);
	truematch[3] = isMatch(m_Redball[3], W.m_LotRed);
	truematch[4] = isMatch(m_Redball[4], W.m_LotRed);
	truematch[5] = (m_Blueball == W.m_LotBlue);
	m_Rank = truematch[0] + truematch[1] + truematch[2] + truematch[3] + truematch[4] + truematch[5];
};

int main() {
	char name[20];
	int play = 1;
	int menu();
	cout << "-------------------------------\n";
	cout << "* ��ӭ��������-˫ɫ�� *\n";
	cout << "-------------------------------\n";
	cout << "	-by Inkorest of NJUST\n\n";
	cout << "�������������� [1 �� 20 ���ַ�]��";
	cin.getline(name, 20);
	CCustomer user(name);

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
		wLot.PrintLot();
		cout << "-------------------------------\n";
		user.ShowChoice();
		cout << "-------------------------------\n";
		user.Compare(wLot);
		user.ShowRank();
		cout << "\n****************************\n";
		cout << name << "������������һ����Ϸ�� [y ���� [����]]" << endl;
		cin >> Reply2;
		cout << '\n' << '\n';
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "��л�����渣��-˫ɫ��" << name << "��:)" << endl;
	exit(1);
	return 0;
}

int getGameNbr(int range) {
	return(rand() % range + 1);
}
bool isMatch(int temp, int cp_num[]){
	for(int i=0;i<5;i++)
		if (temp == cp_num[i])
			return true;
	return false;
}