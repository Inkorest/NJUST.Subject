/*	福彩游戏	*/
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int seed = (unsigned)time(NULL);	//随机数种子

void printMenu(int);
void menuCommand();
void printRule();
void passcode();
char getReply();
bool doExists(int, int[], int = 6);
void initRandomSeed();

class CWelfareLot;

class CCustomer {
private:
	char m_Name[20];
	int m_Money;
	int m_Prize;
	int m_Redball[6];
	int m_Blueball;
	int m_RedMatches;
	int m_BlueMatch;
	int m_BetMulti;
public:
	CCustomer(int money = 100) :m_Money(money), m_Prize(0), m_RedMatches(0), m_BlueMatch(0), m_BetMulti(1) {
		cout << "请输入您的名字 [1 到 20 个字符]：";
		cin.getline(m_Name, 20);
		cout << "\n欢迎 " << m_Name << "！\n";
	};
	int CheckInput(int range) {	//限制输入
		int num;
		while (!(cin >> num) || num < 1 || num > range) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "非法输入。请输入介于 1 和 " << range << " 之间的一个数字：";
		}
		return num;
	}
	void SetNumber() {	//接受投注
		int maxBetMulti = m_Money / 2 > 99 ? 99 : m_Money / 2;
		cout << "您可选择单倍投注或多倍投注，每注售价 2 z。单倍投注请输入 1，多倍投注请输入投注倍数 [2~" << maxBetMulti << "]：";
		m_BetMulti = CheckInput(maxBetMulti);
		m_Money -= 2 * m_BetMulti;
		cout << "成功接受投注。";
		PrintMoney();
		cout << '\n' << m_Name << "，请输入你的红色球号码 [1 ~ 33]。\n";
		for (int i = 0; i < 6; i++)
		{
			cout << "输入红色球 #" << i + 1 << " 的号码：";
			m_Redball[i] = CheckInput(33);
		}
		cout << "请输入你的蓝色球号码 [1 ~ 16]：";
		m_Blueball = CheckInput(16);
	};
	void PrintSelection() const {	//显示用户选择，强制显示两位数
		cout << "你的选择为：\t红色球：";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "蓝色球：" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	};
	void Compare(CWelfareLot& W);
	void PrintMoney() const {
		cout << "您目前的余额为 " << m_Money << " z。\n";
	}
	void PrintPrize() const {	//输出投注结果
		cout << m_Name << "，你的投注结果为：\n红色球相同个数：" << m_RedMatches << "，"
			"蓝色球号码" << (m_BlueMatch ? "相同" : "不相同") << "。\n\n";
		if (m_Prize) {
			cout << "恭喜，" << m_Name << "！你赢得了";
			switch (m_Prize) {
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
	void CalcRewards() {	//计算奖金并重置奖级变量
		int reward = 0;
		switch (m_Prize) {
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
		if (m_Prize) {
			cout << "奖金 " << reward << " z 已经发放到您的余额。";
			PrintMoney();
		}
		m_Prize = 0;
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
	switch (m_RedMatches) {	//由双色球规则计算奖级
	case 6:
		m_Prize += 2;
	case 5:
		m_Prize++;
	case 4:
		m_Prize++;
	case 3:
		m_Prize++;
	default:
		m_Prize += m_BlueMatch;
	}
};

int main() {
	char div[86] = "-----------------------------------------------------------------------------------\n";
	int play = 1;
	cout << div;
	cout << "** 欢迎来到福彩-双色球！ **\n";
	cout << "	-by Inkorest of NJUST\n";
	cout << div << '\n';
	printMenu(1);
	cout << '\n';

	CCustomer user;

	cout << '\n';
	cout << "要由 CPU 自动生成随机数种子吗？\n";
	cout << "[Y] 是\n";
	cout << "[N] 否\n";
	cout << "请输入命令：";
	initRandomSeed();

	char reply;
	do {
		CWelfareLot wLot;
		cout << div;
		cout << "游玩局数 #" << play << '\n';
		cout << div << '\n';
		user.PrintMoney();
		user.SetNumber();
		cout << '\n' << div;
		user.PrintSelection();
		cout << div;
		wLot.PrintLot();
		cout << div;
		Sleep(500);
		user.Compare(wLot);
		user.PrintPrize();
		user.CalcRewards();
		cout << '\n';
		cout << "你想再游玩一次游戏吗？\n";
		cout << "[Y] 确认\n";
		cout << "[M] 打开游戏菜单\n";
		cout << "[Q] 退出游戏\n";
		cout << "请输入命令：";
		reply = getReply();
		cout << "\n";
		if (reply == 'M')
			printMenu(2);
		srand(++seed);
		play++;
	} while (reply != 'Q');

	cout << "感谢您游玩福彩-双色球！:)\n";
	return 0;
}

void printMenu(int status) {
	cout << "---------- 游戏菜单 ----------\n";
	cout << "[G] " << (status == 1 ? "开始" : "继续") << "游戏\n";
	cout << "[R] 查看游戏规则\n";
	cout << "[C] 输入管理员密码\n";
	cout << "[Q] 退出游戏\n";
	cout << "请输入命令：";
	menuCommand();
}

void menuCommand() {
	char command;
	cin >> command;
	while (cin.get() != '\n')
		command = '\0';
	switch (command) {
	case 'G':
	case 'g':
		break;
	case 'R':
	case 'r':
		printRule();
		printMenu(2);
		break;
	case 'C':
	case 'c':
		passcode();
		break;
	case 'Q':
	case 'q':
		cout << "\n感谢您游玩福彩-双色球！:)\n";
		exit(0);
	default:
		cout << "非法输入。请重新输入：";
		menuCommand();
	}
}

void printRule() {
	cout << '\n';
	cout << "------------------------------- 福彩-双色球游戏规则 -------------------------------\n";
	cout << "1. 下注：用户通过支付余额进行投注（可选单倍投注 / 多倍投注* ），然后在 33 个红色球号\n";
	cout << "	码中挑选 6 个、在 16 个蓝色球号码中挑选 1 个作为自己的投注号码。\n";
	cout << "2. 开奖：CPU 将按照设定好的随机数种子，随机得出 6 个红色球大奖号码和 1 个蓝色球大奖\n";
	cout << "	号码。\n";
	cout << "3. 结算：依据用户与大奖号码的匹配情况计算用户的中奖等级，并发放奖金（如中奖）。\n";
	cout << "*多倍投注：按单注售价的复倍（最大 99 倍）投注。若中奖，奖金也将变为复倍。\n";
	cout << '\n';
	cout << "--------------------- 奖金对照表 ---------------------\n";
	cout << "奖级\t奖金\t中奖条件（红色球配对数/蓝色球配对情况）\n";
	cout << "一等奖\t10M z\t6/S\n";
	cout << "二等奖\t500K z\t6/F\n";
	cout << "三等奖\t3K z\t5/S\n";
	cout << "四等奖\t200 z\t5/F 或者 4/S\n";
	cout << "五等奖\t10 z\t4/F 或者 3/S\n";
	cout << "六等奖\t5 z\t2/S 或者 1/S 或者 0/S\n";
	cout << '\n';
	system("pause");
	cout << '\n';
}

void passcode() {

}

char getReply() {
	char reply;
	cin >> reply;
	while (cin.get() != '\n')
		reply = '\0';
	if (reply == 'Y' || reply == 'y' || reply == 'M' || reply == 'm' || reply == 'Q' || reply == 'q')
		return reply > 'Z' ? reply -= 32 : reply;
	cout << "非法输入。请重新输入：";
	getReply();
}

static void initRandomSeed() {	//初始化随机数种子
	char reply;
	cin >> reply;
	while (cin.get() != '\n')
		reply = '\0';
	switch (reply) {
	case 'Y':
	case 'y':
		cout << "已经由 CPU 自动生成了随机数种子。\n\n";
		break;
	case 'N':
	case 'n':
		cout << "请输入你的幸运数字作为随机数种子：";
		cin >> seed;
		cout << "已经由此生成了随机数种子。\n\n";
		break;
	default:
		cout << "非法输入。请重新输入：";
		initRandomSeed();
	}
	srand(seed);
}

bool doExists(int num, int array[], int arrayN) {
	for (int i = 0; i < arrayN; i++)
		if (num == array[i])
			return true;
	return false;
}