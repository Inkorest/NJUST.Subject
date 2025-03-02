/* 福彩游戏——源代码及关键源代码注解如下： */
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>

int isMatch(int test, int cp_num[]);	//是否数字匹配
int getgamenbr();	//取得一个随机数
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
	cin.getline(name, 20);	//输入玩家姓名
	cout << "\nWelcome " << name << "! Please enter your lucky number for seed: ";
	cin >> seed;	//输入随机数种子
	srand(seed);
	do
	{	int num[5];	//输入所选的数字
		int cp_num[6];	//CPU产生的数字
		cout << "\n" << name << ", please enter your white ball numbers.\n";
		cout << "\n";
		int j;
		for (int j = 0; j < 5; j++)	//输入5个所选号码
		{	cout << "Enter Ball # " << j + 1 << ": ";
			while (!(cin >> num[j]))	//在输入的同时对输入的类型和大小做限制
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
		cin >> PowerBall;	//要求玩家输入最后一个号码，叫做能量球
		cp_num[0] = getgamenbr();	//计算机产生6个随机号码
		cp_num[1] = getgamenbr();
		cp_num[2] = getgamenbr();
		cp_num[3] = getgamenbr();
		cp_num[4] = getgamenbr();
		cp_num[5] = getgamenbr();
		truematch[0] = isMatch(num[0], cp_num);		/*判断玩家输入的数字与计算机产生的是否相等*/
		truematch[1] = isMatch(num[1], cp_num);
		truematch[2] = isMatch(num[2], cp_num);
		truematch[3] = isMatch(num[3], cp_num);
		truematch[4] = isMatch(num[4], cp_num);
		truematch[5] = isMatch(num[5], cp_num);
		//输出最终结果
		cout << "\n****************************";
		cout<<"\nPlay # "<<play;
		cout << "\n****************************\n";
		cout << '\n';
		cout << "The computer picks were: " << cp_num[0] << "	" << cp_num[1] << "	" << cp_num[2] << "	" << cp_num[3] << "	" << cp_num[4] << "	" << "PB"<<"	"<<cp_num[5] << '\n';
		cout << "-------------------------------\n";
		cout << name << ", your picks were: " << num[0] << "	" << num[1] << "	" << num[2] << "	" << num[3] << "	" << num[4] << "	" << "PB" << "	" << PowerBall << '\n';
		cout << "-------------------------------\n";
		//显示比较结果
		cout << name << ", your matches were: " << truematch[0] << "	" << truematch[1] << "	" << truematch[2] << "	" << truematch[3] << "	" << truematch[4] << "	" << "PB" << "	" << truematch[5] << '\n';
		cout << "-------------------------------\n";
		total = truematch[0] + truematch[1] + truematch[3] + truematch[4] + truematch[5];	/*将对应数字正确的数目相加（有错）*/
		cout << "\nTotal Matches: " << total << "\n\n";	//显示有几个数字相等
		if (total == 6)	//如果6个数字相等赢得大奖
		{	cout << "Congratulations " << name << "! You won the jackpot!!";	}
		else
			cout << "Sorry " << name << ", you did not win the jackpot!";	//否则未获奖
		cout << "\n****************************\n";
		cout << name << ", would you like to play the game again? [y or n]" << endl;
		cin >> Reply2;	//询问是否玩下一局
		play = play + 1;
	} while (Reply2 == 'y' || Reply2 == 'y');
	cout << "\nThank you for playing PowerBall " << name << "! :-" << endl;
	exit(1);
	return 0;
}
int getgamenbr()	//获得随机值1~48
{	return(rand() % 48 + 1);	}
int isMatch(int test, int cp_num[])	//比较test是否与cp_num数组中的某个数相等，相等则返回1
{	int match = 0;
	for(int i=0;i<5;i++)
		if (test == cp_num[i])	match = 1;
	cout << "\n";
	return match;
}