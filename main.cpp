/*	福彩游戏	*/
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
		cout << "请输入您的名字 [1 到 20 个字符]：";
		cin.getline(m_Name, 20);
		cout << "\n欢迎 " << m_Name << "！\n";
		m_Money = money;
		m_Rank = 0;
		m_RedMatches = 0;
		m_BlueMatch = 0;
	};
	int CheckInput(int range) {	//限制输入
		int num;
		while (!(cin >> num) || num < 1 || num > range) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "非法输入，请输入介于 1 和 " << range << " 之间的一个数字：";
		}
		return num;
	}
	void SetNumber() {	//接受投注
		int maxBetMulti = m_Money / 2 > 99 ? 99 : m_Money / 2;
		cout << "您可选择单倍投注或多倍投注，每注售价 2 z。单倍投注请输入 1，多倍投注请输入投注倍数 [2~" << maxBetMulti << "]：";
		m_BetMulti = CheckInput(maxBetMulti);
		m_Money -= 2 * m_BetMulti;
		cout << "成功接受投注。";
		ShowMoney();
		cout << '\n' << m_Name << "，请输入你的红色球号码 [1 ~ 33]。\n";
		for (int i = 0; i < 6; i++)
		{
			cout << "输入红色球 #" << i + 1 << " 的号码：";
			m_Redball[i] = CheckInput(33);
		}
		cout << "请输入你的蓝色球号码 [1 ~ 16]：";
		m_Blueball = CheckInput(16);
	};
	void ShowChoice() const {	//显示用户选择，强制显示两位数
		cout << "你的选择为：\t红色球：";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "蓝色球：" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);
	void ShowMoney() const {
		cout << "您目前的余额为 " << m_Money << " z。\n";
	}
	void ShowRank() const {	//输出投注结果
		cout << m_Name << "，你的投注结果为：\n红色球相同个数：" << m_RedMatches << "，"
			"蓝色球号码" << (m_BlueMatch ? "相同" : "不相同") << "。\n\n";
		if (m_Rank) {
			cout << "恭喜，" << m_Name << "！你赢得了";
			switch (m_Rank) {
			case 6:
				cout << "一等奖！!";
				break;
			case 5:
				cout << "二等奖！";
				break;
			case 4:
				cout << "三等奖！";
				break;
			case 3:
				cout << "四等奖！";
				break;
			case 2:
				cout << "五等奖！";
				break;
			case 1:
				cout << "六等奖！";
				break;
			}
		}
		else
			cout << "很遗憾，" << m_Name << "，你没有赢得奖金！";
		cout << '\n';
	};
	void CalcRewards() {	//计算奖金并重置奖等变量
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
			cout << "您获得了 " << reward << " z。";
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
	void PrintLot() const {	//模拟并显示开奖
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
			cout << (m_LotRed[i] < 10 ? '0' : '\0') << m_LotRed[i] << '\t';
		}
		cout << "蓝色球：";
		//滚动显示蓝色球号码
		rndTime = rand() % 10 + 6;	//限制滚动显示次数（6~15）
		for (int i = 0; i < rndTime; i++) {
			rndNum = rand() % 16 + 1;
			cout << (rndNum < 10 ? '0' : '\0') << rndNum << "\b\b";
			Sleep(150);
		}
		cout << (m_LotBlue < 10 ? '0' : '\0') << m_LotBlue << '\n';
	};
	friend void CCustomer::Compare(CWelfareLot&);
};

void CCustomer::Compare(CWelfareLot& W) {	//计算奖金等级
	for (int i = 0; i < 6; i++)
		m_RedMatches += doExists(m_Redball[i], W.m_LotRed);
	m_BlueMatch += (m_Blueball == W.m_LotBlue);
	switch (m_RedMatches) {	//由双色球规则计算奖等
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
	cout << "* 欢迎来到福彩-双色球！ *\n";
	cout << "	-by Inkorest of NJUST\n";
	cout << div << '\n';

	CCustomer user;

	cout << "要由 CPU 自动生成随机数种子吗？[y 或者 n]：";
	initRandomSeed();

	CWelfareLot wLot;

	char Reply2;
	do {
		cout << div;
		cout << "游玩局数 #" << play << '\n';
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
		cout << "你想再游玩一次游戏吗？[y 或者 [其他]]：";
		cin >> Reply2;
		cout << "\n\n";
		play++;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "感谢您游玩福彩-双色球！:)\n";
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
		cout << "非法输入，请重新输入：";
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