/* ������Ϸ����Դ���뼰�ؼ�Դ����ע�����£� */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>

int isMatch(int test, int cp_num[]);	//�Ƿ�����ƥ��
int getgamenbr();	//ȡ��һ�������
int main()
{	char name[20], Reply2;
	int seed, PowerBall, total, play = 1;
	int truematch[6];
	int menu();
	cout << "-------------------------------\n";
	cout << "* Welcome to PowerBall! *\n";
	cout << "-------------------------------\n";
	cout << "	-by Chris Grose\n\n";
	cout << "Please enter your name [1 to 20 characters]: ";
	cin.getline(name, 20);	//�����������
	cout << "\nWelcome " << name << "! Please enter your lucky number for seed: ";
	cin >> seed;	//�������������
	srand(seed);
	do
	{	int num[5];	//������ѡ������
		int cp_num[6];	//CPU����������
		cout << "\n" << name << ", please enter your white ball numbers.\n";
		cout << "\n";
		int j;
		for (int j = 0; j < 5; j++)	//����5����ѡ����
		{	cout << "Enter Ball # " << j + 1 << ": ";
			while (!(cin >> num[j]))	//�������ͬʱ����������ͺʹ�С������
			{	cin.clear();
				while (!(cin.get() != '\n'))
				continue;
				cout << "Sorry, this is an invalid entry. Please enter a number between 1 and 48. Thank you!\n";
			}
			if ((num[j] < 1))
			{	cout << "Sorry, you have entered a number less than 0. Please enter a number between 1 and 48.\n";
				j--;
			}
			if ((num[j] > 48))
			{	cout << "Sorry, you have entered a number greater than 48. Please enter a number between 1 and 48.\n";
				j--;
			}
		}
		cout << '\n';
		cout << name << ", please enter your PowerBall number: ";
		cin >> PowerBall;	//Ҫ������������һ�����룬����������
		cp_num[0] = getgamenbr();	//���������6���������
		cp_num[1] = getgamenbr();
		cp_num[2] = getgamenbr();
		cp_num[3] = getgamenbr();
		cp_num[4] = getgamenbr();
		cp_num[5] = getgamenbr();
		truematch[0] = isMatch(num[0], cp_num);		/*�ж��������������������������Ƿ����*/
		truematch[1] = isMatch(num[1], cp_num);
		truematch[2] = isMatch(num[2], cp_num);
		truematch[3] = isMatch(num[3], cp_num);
		truematch[4] = isMatch(num[4], cp_num);
		truematch[5] = isMatch(num[5], cp_num);
		//������ս��
		cout << "\n****************************";
		cout<<"\nPlay # "<<play;
		cout << "\n****************************\n";
		cout << '\n';
		cout << "The computer picks were: " << cp_num[0] << "	" << cp_num[1] << "	" << cp_num[2] << "	" << cp_num[3] << "	" << cp_num[4] << "	" << "PB"<<"	"<<cp_num[5] << '\n';
		cout << "-------------------------------\n";
		cout << name << ", your picks were: " << num[0] << "	" << num[1] << "	" << num[2] << "	" << num[3] << "	" << num[4] << "	" << "PB" << "	" << PowerBall << '\n';
		cout << "-------------------------------\n";
		//��ʾ�ȽϽ��
		cout << name << ", your matches were: " << truematch[0] << "	" << truematch[1] << "	" << truematch[2] << "	" << truematch[3] << "	" << truematch[4] << "	" << "PB" << "	" << truematch[5] << '\n';
		cout << "-------------------------------\n";
		total = truematch[0] + truematch[1] + truematch[3] + truematch[4] + truematch[5];	/*����Ӧ������ȷ����Ŀ��ӣ��д�*/
		cout << "\nTotal Matches: " << total << "\n\n";	//��ʾ�м����������
		if (total == 6)	//���6���������Ӯ�ô�
		{	cout << "Congratulations " << name << "! You won the jackpot!!";	}
		else
			cout << "Sorry " << name << ", you did not win the jackpot!";	//����δ��
		cout << "\n****************************\n";
		cout << name << ", would you like to play the game again? [y or n]" << endl;
		cin >> Reply2;	//ѯ���Ƿ�����һ��
		play = play + 1;
	} while (Reply2 == 'y' || Reply2 == 'y');
	cout << "\nThank you for playing PowerBall " << name << "! :-" << endl;
	exit(1);
	return 0;
}
int getgamenbr()	//������ֵ1~48
{	return(rand() % 48 + 1);	}
int isMatch(int test, int cp_num[])	//�Ƚ�test�Ƿ���cp_num�����е�ĳ������ȣ�����򷵻�1
{	int match = 0;
	for(int i=0;i<5;i++)
		if (test == cp_num[i])	match = 1;
	cout << "\n";
	return match;
}