/*	������Ϸ	*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int isMatch(int test, int cp_num[]);	//�Ƿ�����ƥ��
int getgamenbr();	//ȡ��һ�������

class CWelfareLot;	//����������

class CCustomer {	//�����û���
private:
	char szName[20];	//�û�����
	int nMoney;	//�û��ʽ�
	int nRank;	//�н��ĵȼ�
	int Welfare[6];	//Ͷע����
public:
	CCustomer(char name[], int money = 100) {
		strcpy_s(szName, name);
		nMoney = money;
	};	//���캯��
	int SetWelfare() {
		cout << "\n" << szName << "����������İ�ɫ����롣\n";
		cout << "\n";
		for (int j = 0; j < 5; j++)	//����5����ѡ����
		{
			cout << "������ #" << j + 1 << " �ĺ��룺";
			while (!(cin >> Welfare[j]))	//�������ͬʱ����������ͺʹ�С������
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "��Ǹ������һ���Ƿ����롣��������� 1 �� 48 ֮���һ�����֡�лл��\n";
			}
			if ((Welfare[j] < 1))
			{
				cout << "��Ǹ����������һ��С�� 0 �����֡���������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
			if ((Welfare[j] > 48))
			{
				cout << "��Ǹ����������һ������ 48 �����֡���������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
		}
		cout << '\n';
		cout << szName << "�����������ǿ������룺";
		cin >> Welfare[5];	//Ҫ������������һ�����룬����ǿ����
		return 1;
	};	//���ո���Ͷע���ɹ�����1
	void ShowChoice() {
		cout << szName << "�����ѡ��Ϊ��\t" << Welfare[0] << '\t' << Welfare[1] << '\t' << Welfare[2] << '\t' << Welfare[3] << '\t' << Welfare[4] << '\t' << "PB" << '\t' << Welfare[5] << '\n';
	};	//��ʾ�û�ѡ��
	void Compare(CWelfareLot& W);	//�Ƚϸ��ʣ���ֵ�н��ȼ�
	void ShowMoney() {
		cout << szName << "����Ŀǰ�Ĳʽ�Ϊ " << nMoney << " Z";
	}	//��ʾ�û��ʽ�
	void ShowRank() {
		cout << "\n�ϼ���ԣ�" << nRank << "\n\n";	//��ʾ�м����������
		switch (nRank) {
		case 6:	//���6���������Ӯ�ô�
			cout << "��ϲ��" << szName << "����Ӯ���� Jackpot����";
			break;
		case 5:
		case 4:
			cout << "��ϲ��" << szName << "����Ӯ���˶��Ƚ���";
			break;
		case 3:
		case 2:
			cout << "��ϲ��" << szName << "����Ӯ�������Ƚ���";
			break;
		default:
			cout << "���ź���" << szName << "����û��Ӯ�ý���";	//����δ��
		}
	};	//�����н��ȼ����㽱��������
};

class CWelfareLot {	//���帣����
private:
	int LotNum[6];	//�󽱺���
public:
	CWelfareLot() {
		LotNum[0] = getgamenbr();	//CPU����6���������
		LotNum[1] = getgamenbr();
		LotNum[2] = getgamenbr();
		LotNum[3] = getgamenbr();
		LotNum[4] = getgamenbr();
		LotNum[5] = getgamenbr();
	};	//���캯��
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
			LotNum[i] = nNum;	//�任���������ּ�Ϊ������
		}
	};	//��������
	void PrintLot() {
		cout << "CPU ��ѡ��Ϊ��\t\t" << LotNum[0] << '\t' << LotNum[1] << '\t' << LotNum[2] << '\t' << LotNum[3] << '\t' << LotNum[4] << '\t' << "PB" << '\t' << LotNum[5] << '\n';
	};	//����󽱺���
	friend void CCustomer::Compare(CWelfareLot&);	//�ж��û��Ƿ��н�
};

void CCustomer::Compare(CWelfareLot& W) {
	int truematch[6];
	truematch[0] = isMatch(Welfare[0], W.LotNum);		//�ж���������������CPU�������Ƿ����
	truematch[1] = isMatch(Welfare[1], W.LotNum);
	truematch[2] = isMatch(Welfare[2], W.LotNum);
	truematch[3] = isMatch(Welfare[3], W.LotNum);
	truematch[4] = isMatch(Welfare[4], W.LotNum);
	truematch[5] = isMatch(Welfare[5], W.LotNum);
	cout << szName << "��������Ϊ��\t" << truematch[0] << '\t' << truematch[1] << '\t' << truematch[2] << '\t' << truematch[3] << '\t' << truematch[4] << '\t' << "PB" << '\t' << truematch[5] << '\n';
	nRank = truematch[0] + truematch[1] + truematch[2] + truematch[3] + truematch[4] + truematch[5];	//����Ӧ������ȷ����Ŀ���
};

int main() {
	char name[20];
	int play = 1;
	int menu();
	cout << "-------------------------------\n";
	cout << "* ��ӭ����ǿ�����Ʊ�� *\n";
	cout << "-------------------------------\n";
	cout << "	-by Chris Grose, edited by Inkorest\n\n";
	cout << "������������� [1 �� 20 ���ַ�]��";
	cin.getline(name, 20);	//�����������
	CCustomer user(name);
	cout << "\n��ӭ " << name << "��" << endl;

	cout << "Ҫ�� CPU �Զ���������������� [y ���� n]" << endl;
	char Reply1;
label1:
	cin >> Reply1;
	switch (Reply1) {
	case 'Y':
	case 'y':
		srand((unsigned)time(NULL));
		cout << "�Ѿ��� CPU �Զ���������������ӡ�" << endl;
		break;
	case 'N':
	case 'n':
		int seed;
		cout << "�������������������Ϊ��������ӣ�";
		cin >> seed;	//�������������
		srand(seed);
		break;
	default:
		cout << "�Ƿ����룬���������룺"<<endl;
		goto label1;
	}

	CWelfareLot powerball;
	char Reply2;
	do {
		user.ShowMoney();
		user.SetWelfare();
		//������ս��
		cout << "\n****************************";
		cout << "\n������� #" << play;
		cout << "\n****************************\n";
		cout << '\n';
		powerball.PrintLot();
		cout << "-------------------------------\n";
		user.ShowChoice();
		cout << "-------------------------------\n";
		//��ʾ�ȽϽ��
		user.Compare(powerball);
		cout << "-------------------------------\n";

		user.ShowRank();

		cout << "\n****************************\n";
		cout << name << "������������һ����Ϸ�� [y ���� n]" << endl;
		cin >> Reply2;	//ѯ���Ƿ�����һ��
		play = play + 1;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "\n��л������ǿ�����Ʊ��" << name << "��:)" << endl;
	exit(1);
	return 0;
}

int getgamenbr()	//������ֵ1~48
{	return(rand() % 48 + 1);	}
int isMatch(int test, int cp_num[])	//�Ƚ�test�Ƿ���cp_num[]�е�ĳ������ȣ�����򷵻�1
{	int match = 0;
	for(int i=0;i<5;i++)
		if (test == cp_num[i])	match = 1;
	cout << "\n";
	return match;
}