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
int main()
{	char name[20], Reply1, Reply2;
	int PowerBall, total, play = 1;
	int truematch[6];
	int menu();
	cout << "-------------------------------\n";
	cout << "* ��ӭ����ǿ�����Ʊ�� *\n";
	cout << "-------------------------------\n";
	cout << "	-by Chris Grose, edited by Inkorest\n\n";
	cout << "������������� [1 �� 20 ���ַ�]��";
	cin.getline(name, 20);	//�����������
	cout << "\n��ӭ " << name << "��" << endl;
	cout << "������ CPU �Զ���������������� [y ���� n]" << endl;
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
	do
	{	int num[5];	//������ѡ������
		int cp_num[6];	//CPU����������
		cout << "\n" << name << "����������İ�ɫ����롣\n";
		cout << "\n";
		for (int j = 0; j < 5; j++)	//����5����ѡ����
		{	cout << "������ #" << j + 1 << " �ĺ��룺";
			while (!(cin >> num[j]))	//�������ͬʱ����������ͺʹ�С������
			{	cin.clear();
				while (!(cin.get() != '\n'))
				continue;
				cout << "��Ǹ������һ���Ƿ����롣��������� 1 �� 48 ֮���һ�����֡�лл��\n";
			}
			if ((num[j] < 1))
			{	cout << "��Ǹ����������һ��С�� 0 �����֡���������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
			if ((num[j] > 48))
			{	cout << "��Ǹ����������һ������ 48 �����֡���������� 1 �� 48 ֮���һ�����֡�\n";
				j--;
			}
		}
		cout << '\n';
		cout << name << "�����������ǿ������룺";
		cin >> PowerBall;	//Ҫ������������һ�����룬����ǿ����
		cp_num[0] = getgamenbr();	//CPU����6���������
		cp_num[1] = getgamenbr();
		cp_num[2] = getgamenbr();
		cp_num[3] = getgamenbr();
		cp_num[4] = getgamenbr();
		cp_num[5] = getgamenbr();
		truematch[0] = isMatch(num[0], cp_num);		//�ж���������������CPU�������Ƿ����
		truematch[1] = isMatch(num[1], cp_num);
		truematch[2] = isMatch(num[2], cp_num);
		truematch[3] = isMatch(num[3], cp_num);
		truematch[4] = isMatch(num[4], cp_num);
		truematch[5] = isMatch(num[5], cp_num);
		//������ս��
		cout << "\n****************************";
		cout<<"\n������� #"<<play;
		cout << "\n****************************\n";
		cout << '\n';
		cout << "CPU ��ѡ��Ϊ��\t" << cp_num[0] << '\t' << cp_num[1] << '\t' << cp_num[2] << '\t' << cp_num[3] << '\t' << cp_num[4] << '\t' << "PB" << '\t' << cp_num[5] << '\n';
		cout << "-------------------------------\n";
		cout << name << "�����ѡ��Ϊ��\t" << num[0] << '\t' << num[1] << '\t' << num[2] << '\t' << num[3] << '\t' << num[4] << '\t' << "PB" << '\t' << PowerBall << '\n';
		cout << "-------------------------------\n";
		//��ʾ�ȽϽ��
		cout << name << "��������Ϊ��\t" << truematch[0] << '\t' << truematch[1] << '\t' << truematch[2] << '\t' << truematch[3] << '\t' << truematch[4] << '\t' << "PB" << '\t' << truematch[5] << '\n';
		cout << "-------------------------------\n";
		total = truematch[0] + truematch[1] + truematch[2] + truematch[3] + truematch[4] + truematch[5];	//����Ӧ������ȷ����Ŀ���
		cout << "\n�ϼ���ԣ�" << total << "\n\n";	//��ʾ�м����������
		if (total == 6)	//���6���������Ӯ�ô�
		{	cout << "��ϲ��" << name << "����Ӯ���� Jackpot����";	}
		else
			cout << "���ź���" << name << "����û��Ӯ�� Jackpot��";	//����δ��
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