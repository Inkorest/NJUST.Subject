/*	福彩游戏	*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int isMatch(int test, int cp_num[]);	//是否数字匹配
int getgamenbr();	//取得一个随机数

class CWelfareLot;	//声明福彩类

class CCustomer {	//定义用户类
private:
	char szName[20];	//用户姓名
	int nMoney;	//用户彩金
	int nRank;	//中奖的等级
	int Welfare[6];	//投注号码
public:
	CCustomer(char name[], int money = 100) {
		strcpy_s(szName, name);
		nMoney = money;
	};	//构造函数
	int SetWelfare() {
		cout << "\n" << szName << "，请输入你的白色球号码。\n";
		cout << "\n";
		for (int j = 0; j < 5; j++)	//输入5个所选号码
		{
			cout << "输入球 #" << j + 1 << " 的号码：";
			while (!(cin >> Welfare[j]))	//在输入的同时对输入的类型和大小做限制
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "抱歉，这是一个非法输入。请输入介于 1 和 48 之间的一个数字。谢谢！\n";
			}
			if ((Welfare[j] < 1))
			{
				cout << "抱歉，你输入了一个小于 0 的数字。请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
			if ((Welfare[j] > 48))
			{
				cout << "抱歉，你输入了一个大于 48 的数字。请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
		}
		cout << '\n';
		cout << szName << "，请输入你的强力球号码：";
		cin >> Welfare[5];	//要求玩家输入最后一个号码，叫做强力球
		return 1;
	};	//接收福彩投注，成功返回1
	void ShowChoice() {
		cout << szName << "，你的选择为：\t" << Welfare[0] << '\t' << Welfare[1] << '\t' << Welfare[2] << '\t' << Welfare[3] << '\t' << Welfare[4] << '\t' << "PB" << '\t' << Welfare[5] << '\n';
	};	//显示用户选择
	void Compare(CWelfareLot& W);	//比较福彩，赋值中奖等级
	void ShowMoney() {
		cout << szName << "，你目前的彩金为 " << nMoney << " Z";
	}	//显示用户彩金
	void ShowRank() {
		cout << "\n合计配对：" << nRank << "\n\n";	//显示有几个数字相等
		switch (nRank) {
		case 6:	//如果6个数字相等赢得大奖
			cout << "恭喜，" << szName << "！你赢得了 Jackpot！！";
			break;
		case 5:
		case 4:
			cout << "恭喜，" << szName << "！你赢得了二等奖！";
			break;
		case 3:
		case 2:
			cout << "恭喜，" << szName << "！你赢得了三等奖！";
			break;
		default:
			cout << "很遗憾，" << szName << "，你没有赢得奖金！";	//否则未获奖
		}
	};	//根据中奖等级计算奖金，输出结果
};

class CWelfareLot {	//定义福彩类
private:
	int LotNum[6];	//大奖号码
public:
	CWelfareLot() {
		LotNum[0] = getgamenbr();	//CPU产生6个随机号码
		LotNum[1] = getgamenbr();
		LotNum[2] = getgamenbr();
		LotNum[3] = getgamenbr();
		LotNum[4] = getgamenbr();
		LotNum[5] = getgamenbr();
	};	//构造函数
	void SetLot() {
		int nRnd, nNum;
		for (int i = 0; i < 6; i++) {	//要开出6个数字
			nRnd = rand();	//随机取循环次数，数字变换的时间长度是随机的
			for (int j = 0; j < nRnd; j++) {
				nNum = rand() % 21;	//随机取0~20之间的数字进行变换
				if (nNum < 10)
					cout << nNum << '\b';	//当取的数字小于10，即一位数，显示后光标左移一位，再继续变换的数字将原数字覆盖，出现摇奖效果
				else
					cout << nNum << "\b\b";	//当取的数字是两位数，左移两位
			}
			cout << nNum << " ";
			LotNum[i] = nNum;	//变换到最后的数字即为大奖数字
		}
	};	//开奖过程
	void PrintLot() {
		cout << "CPU 的选择为：\t\t" << LotNum[0] << '\t' << LotNum[1] << '\t' << LotNum[2] << '\t' << LotNum[3] << '\t' << LotNum[4] << '\t' << "PB" << '\t' << LotNum[5] << '\n';
	};	//输出大奖号码
	friend void CCustomer::Compare(CWelfareLot&);	//判断用户是否中奖
};

void CCustomer::Compare(CWelfareLot& W) {
	int truematch[6];
	truematch[0] = isMatch(Welfare[0], W.LotNum);		//判断玩家输入的数字与CPU产生的是否相等
	truematch[1] = isMatch(Welfare[1], W.LotNum);
	truematch[2] = isMatch(Welfare[2], W.LotNum);
	truematch[3] = isMatch(Welfare[3], W.LotNum);
	truematch[4] = isMatch(Welfare[4], W.LotNum);
	truematch[5] = isMatch(Welfare[5], W.LotNum);
	cout << szName << "，你的配对为：\t" << truematch[0] << '\t' << truematch[1] << '\t' << truematch[2] << '\t' << truematch[3] << '\t' << truematch[4] << '\t' << "PB" << '\t' << truematch[5] << '\n';
	nRank = truematch[0] + truematch[1] + truematch[2] + truematch[3] + truematch[4] + truematch[5];	//将对应数字正确的数目相加
};

int main() {
	char name[20];
	int play = 1;
	int menu();
	cout << "-------------------------------\n";
	cout << "* 欢迎来到强力球彩票！ *\n";
	cout << "-------------------------------\n";
	cout << "	-by Chris Grose, edited by Inkorest\n\n";
	cout << "请输入你的名字 [1 到 20 个字符]：";
	cin.getline(name, 20);	//输入玩家姓名
	CCustomer user(name);
	cout << "\n欢迎 " << name << "！" << endl;

	cout << "要由 CPU 自动生成随机数种子吗？ [y 或者 n]" << endl;
	char Reply1;
label1:
	cin >> Reply1;
	switch (Reply1) {
	case 'Y':
	case 'y':
		srand((unsigned)time(NULL));
		cout << "已经由 CPU 自动生成了随机数种子。" << endl;
		break;
	case 'N':
	case 'n':
		int seed;
		cout << "请输入你的幸运数字作为随机数种子：";
		cin >> seed;	//输入随机数种子
		srand(seed);
		break;
	default:
		cout << "非法输入，请重新输入："<<endl;
		goto label1;
	}

	CWelfareLot powerball;
	char Reply2;
	do {
		user.ShowMoney();
		user.SetWelfare();
		//输出最终结果
		cout << "\n****************************";
		cout << "\n游玩局数 #" << play;
		cout << "\n****************************\n";
		cout << '\n';
		powerball.PrintLot();
		cout << "-------------------------------\n";
		user.ShowChoice();
		cout << "-------------------------------\n";
		//显示比较结果
		user.Compare(powerball);
		cout << "-------------------------------\n";

		user.ShowRank();

		cout << "\n****************************\n";
		cout << name << "，你想再游玩一次游戏吗？ [y 或者 n]" << endl;
		cin >> Reply2;	//询问是否玩下一局
		play = play + 1;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "\n感谢您游玩强力球彩票，" << name << "！:)" << endl;
	exit(1);
	return 0;
}

int getgamenbr()	//获得随机值1~48
{	return(rand() % 48 + 1);	}
int isMatch(int test, int cp_num[])	//比较test是否与cp_num[]中的某个数相等，相等则返回1
{	int match = 0;
	for(int i=0;i<5;i++)
		if (test == cp_num[i])	match = 1;
	cout << "\n";
	return match;
}