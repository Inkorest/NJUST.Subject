/*	福彩游戏	*/
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
		cout << "请输入您的名字 [1 到 20 个字符]：";
		cin.getline(m_Name, 20);
		cout << "\n欢迎 " << m_Name << "！\n\n";
		m_Money = money;
		m_Rank = 0;
	};
	bool SetNumber() {
		cout << m_Name << "，请输入你的红色球号码 [1 ~ 33]。\n";
		for (int j = 0; j < 6; j++)
		{
			cout << "输入红色球 #" << j + 1 << " 的号码：";
			while (!(cin >> m_Redball[j]))	//限制输入
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "非法输入，请输入介于 1 和 33 之间的一个数字。\n";
			}
			if ((m_Redball[j] < 1))
			{
				cout << "输入过小，请输入介于 1 和 33 之间的一个数字。\n";
				j--;
			}
			if ((m_Redball[j] > 33))
			{
				cout << "输入过大，请输入介于 1 和 33 之间的一个数字。\n";
				j--;
			}
		}
		cout << '\n' << m_Name << "，请输入你的蓝色球号码 [1 ~ 16]：";
		cin >> m_Blueball;
		return true;
	};
	void ShowChoice() const {	//显示用户选择，强制显示两位数
		cout << "你的选择为：\t红色球：";
		for (int i = 0; i < 6; i++) {
			if (m_Redball[i] < 10)
				cout << '0';
			cout << m_Redball[i] << '\t';
		}
		cout << "蓝色球：";
		if (m_Blueball < 10)
			cout << '0';
		cout << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);	//比较号码
	void ShowMoney() const {
		cout << "您目前的彩金为 " << m_Money << " Z。\n\n";
	}
	void ShowRank() const {	//计算奖金并输出结果
		cout << "\n合计配对：" << m_Rank << "\n\n";
		switch (m_Rank) {
		case 6:
			cout << "恭喜，" << m_Name << "！你赢得了 Jackpot！！";
			break;
		case 5:
		case 4:
			cout << "恭喜，" << m_Name << "！你赢得了二等奖！";
			break;
		case 3:
		case 2:
			cout << "恭喜，" << m_Name << "！你赢得了三等奖！";
			break;
		default:
			cout << "很遗憾，" << m_Name << "，你没有赢得奖金！";
		}
	};
};

class CWelfareLot {
private:
	int m_LotRed[6];
	int m_LotBlue;
public:
	CWelfareLot() {	//生成大奖号码
		int tempNum;
		for (int i = 0; i < 6; i++) {
			do	//防止红色球重复
				tempNum = rand() % 33 + 1;
			while (doExists(tempNum, m_LotRed, i));
			m_LotRed[i] = tempNum;
		}
		m_LotBlue = rand() % 16 + 1;
	};
	void SetAndPrintLot() const {	//模拟并显示开奖
		int rndTime, rndNum;
		cout << "大奖号码为：\t红色球：";
		//滚动显示红色球号码
		for (int i = 0; i < 6; i++) {
			rndTime = rand() % 10 + 6;	//限制滚动显示次数（6~15）
			for (int j = 0; j < rndTime; j++) {
				rndNum = rand() % 33 + 1;
				rndNum < 10 ? cout << '0' << rndNum << "\b\b" : cout << rndNum << "\b\b";
				Sleep(150);
			}
			if (m_LotRed[i] < 10)
				cout << '0';
			cout << m_LotRed[i] << '\t';
		}
		cout << "蓝色球：";
		//滚动显示蓝色球号码
		rndTime = rand() % 10 + 6;	//限制滚动显示次数（6~15）
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
	cout << "* 欢迎来到福彩-双色球！ *\n";
	cout << "-------------------------------\n";
	cout << "	-by Inkorest of NJUST\n\n";

	CCustomer user;

	cout << "要由 CPU 自动生成随机数种子吗？ [y 或者 n]\n";
	initRandomSeed();

	CWelfareLot wLot;
	char Reply2;
	do {
		user.ShowMoney();
		user.SetNumber();
		cout << "\n****************************";
		cout << "\n游玩局数 #" << play;
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
		cout << "你想再游玩一次游戏吗？ [y 或者 [其他]]" << endl;
		cin >> Reply2;
		cout << '\n' << '\n';
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "感谢您游玩福彩-双色球！:)" << endl;
	exit(1);
	return 0;
}

int menu() {
	return 0;
}

static void initRandomSeed() {	//初始化随机数种子
	char Reply1;
	cin >> Reply1;
	switch (Reply1) {
	case 'Y':
	case 'y':
		srand((unsigned)time(NULL));
		cout << "已经由 CPU 自动生成了随机数种子。\n\n";
		break;
	case 'N':
	case 'n':
		int seed;
		cout << "请输入你的幸运数字作为随机数种子：";
		cin >> seed;
		srand(seed);
		cout << "已经由此生成了随机数种子。\n";
		break;
	default:
		cout << "非法输入，请重新输入：" << endl;
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