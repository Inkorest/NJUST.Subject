/*	福彩游戏	*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

bool isMatch(int, int[]);
int getGameNbr(int = 33);
void initRandomSeed() {	//初始化随机数种子
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
		cin >> seed;	//输入随机数种子
		srand(seed);
		cout << "已经由此生成了随机数种子。\n";
		break;
	default:
		cout << "非法输入，请重新输入：" << endl;
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
		cout << "\n欢迎 " << m_Name << "！\n\n";
	};
	bool SetNumber() {	//接受彩票投注，成功返回true
		cout << m_Name << "，请输入你的红色球号码。\n";
		for (int j = 0; j < 6; j++)	//输入5个所选号码
		{
			cout << "输入红色球 #" << j + 1 << " 的号码：";
			while (!(cin >> m_Redball[j]))	//对输入作限制
			{
				cin.clear();
				while (!(cin.get() != '\n'))
					continue;
				cout << "非法输入，请输入介于 1 和 48 之间的一个数字。\n";
			}
			if ((m_Redball[j] < 1))
			{
				cout << "输入过小，请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
			if ((m_Redball[j] > 48))
			{
				cout << "输入过大，请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
		}
		cout << '\n';
		cout << m_Name << "，请输入你的蓝色球号码：";
		cin >> m_Blueball;	//要求玩家输入蓝色球号码
		return true;
	};
	void ShowChoice() {
		cout << m_Name << "，你的选择为：\t" << m_Redball[0] << '\t' << m_Redball[1] << '\t' << m_Redball[2] << '\t' 
			<< m_Redball[3] << '\t' << m_Redball[4] << '\t' << m_Redball[5] << '\t' << "PB " << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);	//比较福彩，赋值中奖等级
	void ShowMoney() {
		cout << m_Name << "，你目前的彩金为 " << m_Money << " Z。\n\n";
	}
	void ShowRank() {	//根据中奖等级计算奖金，输出结果
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
	CWelfareLot() {	//CPU生成大奖号码
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
			m_LotRed[i] = nNum;	//变换到最后的数字即为大奖数字
		}
	};	//开奖过程
	void PrintLot() {
		cout << "CPU 的选择为：\t" << m_LotRed[0] << '\t' << m_LotRed[1] << '\t' << m_LotRed[2] << '\t' 
			<< m_LotRed[3] << '\t' << m_LotRed[4] << '\t' << m_LotRed[5] << '\t' << "PB " << m_LotBlue << '\n';
	};
	friend void CCustomer::Compare(CWelfareLot&);	//判断用户是否中奖
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
	cout << "* 欢迎来到福彩-双色球！ *\n";
	cout << "-------------------------------\n";
	cout << "	-by Inkorest of NJUST\n\n";
	cout << "请输入您的名字 [1 到 20 个字符]：";
	cin.getline(name, 20);
	CCustomer user(name);

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
		wLot.PrintLot();
		cout << "-------------------------------\n";
		user.ShowChoice();
		cout << "-------------------------------\n";
		user.Compare(wLot);
		user.ShowRank();
		cout << "\n****************************\n";
		cout << name << "，你想再游玩一次游戏吗？ [y 或者 [其他]]" << endl;
		cin >> Reply2;
		cout << '\n' << '\n';
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "感谢您游玩福彩-双色球，" << name << "！:)" << endl;
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