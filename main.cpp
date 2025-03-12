/*	福彩游戏	*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <cmath>

using namespace std;

constexpr int UP = 72;
constexpr int DOWN = 80;
constexpr int ENTER = 13;

int seed = (unsigned)time(NULL);	//随机数种子
string passcode;

void getPasscode();
void mainMenu(int);
void inquiry();
void printRule();
bool doExists(int, vector<int>);
void initRandomSeed();
int checkInput(int = 0, string = "\0", int = 0, string = "\0", int = 0, vector<int> = {});
void endGame();

class CCustomer;
class CWelfareLot;

class CCustomer {
private:
	string m_Name;
	int m_Balance;
	int m_Prize = 0;
	vector<int> m_Redball;
	int m_Blueball;
	int m_RedMatches = 0;
	int m_BlueMatch = 0;
	int m_BetMulti = 1;
	bool m_AdminStatus = false;	//管理员身份
	bool m_ManualSet = false;	//是否启用预设
	vector<int> m_ManualRed = { 1, 2, 3, 4, 5, 6 };	//红色球号码预设
	int m_ManualBlue = 1;	//蓝色球号码预设
	bool m_ForceSN = false;	//是否强制头奖
public:
	CCustomer(int money = 100) :m_Balance(money) {};
	void EnterName() {
		system("cls");
		cout << "请输入您的名字 [1 到 20 个字符]：\n";
		getline(cin, m_Name);
		cout << "\n欢迎 " << m_Name << "！";
		Sleep(1500);
	}
	void SetNumber() {	//接受投注
		int maxBetMulti = m_Balance / 2 > 99 ? 99 : m_Balance / 2;
		if (maxBetMulti > 1) {
			cout << "您可选择单倍投注或多倍投注，每注售价 2 z。\n";
			cout << "[1] 单倍投注\n";
			cout << "[" << (maxBetMulti != 2 ? "2~" : "\0") << maxBetMulti << "] 多倍投注倍数\n";
			m_BetMulti = checkInput(maxBetMulti, "请输入命令：");
			m_Balance -= 2 * m_BetMulti;
			cout << "\n成功接受投注。";
		}
		else {
			Sleep(1500);
			cout << "已经自动进行了单倍投注。";
		}
		PrintBalance();
		cout << "\n请输入你的红色球号码 [1 ~ 33]。\n";
		for (int i = 0; i < 6; i++) {
			m_Redball.push_back(checkInput(33, "输入红色球 #", 0, " 的号码：", i + 1, m_Redball));
		}
		m_Blueball = checkInput(16, "请输入你的蓝色球号码 [1 ~ 16]：");
	}
	void PrintSelection() const {	//显示用户选择，强制显示两位数
		cout << "你的选择为：\t红色球：";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "蓝色球：" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	}
	void Compare(CWelfareLot&);
	void PrintBalance() const {
		cout << "您目前的余额为 " << m_Balance << " z。\n";
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
	}
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
		reward *= m_BetMulti;
		m_Balance += reward;
		if (m_Prize) {
			cout << "奖金 " << reward << " z 已经发放到您的余额。";
			PrintBalance();
		}
		else if (m_Balance < 2)
			GameOver();
		m_Prize = 0;
		m_RedMatches = 0;
		m_BlueMatch = 0;
	}
	void AdminAccess() {
		if (m_AdminStatus) {
			AdminOptions();
			return;
		}
		system("cls");
		cout << "进入管理员菜单 -----------------------------------------\n\n";
		cout << "请输入管理员密码 [输入 E 退出]：\n";
		string input;
		while (1) {
			while (1) {	//屏蔽密码输入
				char ch = _getch();
				if (ch == '\b' && !input.empty()) {
					input.pop_back();
					cout << "\b \b";
				}
				else if (ch == '\r') {
					cout << '\n';
					break;
				}
				else if (ch != '\b') {
					input += ch;
					cout << '*';
				}
			}
			if (input == "E" || input == "e")
				return;
			cout << '\n';
			if (input == passcode) {
				m_AdminStatus = true;
				cout << "密码正确。已经取得管理员身份。";
				Sleep(1500);
				AdminOptions();
				return;
			}
			cout << "密码错误。请重新输入：\n";
			input.clear();
		}
	}
	bool AdminStatus() const {
		return m_AdminStatus ? 1 : 0;
	}
	void AdminOptions() {	//管理员菜单
		int choice = 0;
		while (1) {
			vector<string> options = { "[M] 手动设定大奖号码", "[F] 启用强制大奖号码与投注号码相同", "[A] 设定用户余额", "[E] 退出管理员菜单" };
			if (m_ForceSN)
				options[1] = "[F] 禁用强制大奖号码与投注号码相同";
			bool loop = true;
			while (loop) {
				system("cls");
				cout << "----------------------------------- 管理员菜单 -----------------------------------\n\n";
				for (int i = 0; i < options.size(); i++) {
					if (i == choice)
						cout << "> " << options[i] << '\n';
					else
						cout << "  " << options[i] << '\n';
				}
				cout << '\n';
				cout << "[↑][↓] 选择\n";
				cout << "[Enter] 确认\n";
				cout << "也可以直接按下快捷键。\n";
				int key = _getch();
				switch (key) {
				case 'M':
				case 'm':
					choice = 0;
					loop = false;
					break;
				case 'F':
				case 'f':
					choice = 1;
					loop = false;
					break;
				case 'A':
				case 'a':
					choice = 2;
					loop = false;
					break;
				case 'E':
				case 'e':
					return;
				}
				if (key == 224) {
					key = _getch();
					switch (key) {
					case UP:
						choice = choice == 0 ? (options.size() - 1) : --choice;
						break;
					case DOWN:
						choice = choice == (options.size() - 1) ? 0 : ++choice;
						break;
					}
				}
				else if (key == ENTER)
					break;
			}
			switch (choice) {
			case 0:
				ManualSet();
				break;
			case 1:
				ForceSameNumber();
				break;
			case 2:
				AdjustBalance();
				break;
			case 3:
				return;
			}
		}
	}
	void SyncData(CWelfareLot&);
	void ManualSet();
	void ForceSameNumber();
	void AdjustBalance() {
		system("cls");
		cout << "设定用户余额 -------------------------------------------\n\n";
		PrintBalance();
		cout << '\n';
		cout << "[数字] 设定新的用户余额（z）\n";
		cout << "[E] 回到管理员菜单\n\n";
		int newBalance = checkInput(0, "请输入命令：", 1);
		if (!newBalance)
			return;
		m_Balance = newBalance;
		system("cls");
		cout << "信息 ---------------------------------------------------\n\n";
		cout << "已经成功设定新的用户余额。";
		PrintBalance();
		cout << "\n即将返回管理员菜单. . . ";
		Sleep(4000);
		return;
	}
	void GameOver() {
		cout << "\n\n很遗憾，您的余额不足以再进行投注。游戏结束。";
		Sleep(4000);
		endGame();
	}
};

CCustomer user;

class CWelfareLot {
private:
	vector<int> m_LotRed;
	int m_LotBlue;
	vector<int> m_Redball;
	int m_Blueball;
	bool m_ManualSet = false;
	bool m_ForceSN = false;
public:
	void GenerateNumber() {	//生成大奖号码
		if (m_ForceSN)
			return;
		if (m_ManualSet) {
			m_LotRed = m_Redball;
			m_LotBlue = m_Blueball;
			return;
		}
		int tempNum;
		for (int i = 0; i < 6; i++) {
			do	//防止红色球重复
				tempNum = rand() % 33 + 1;
			while (doExists(tempNum, m_LotRed));
			m_LotRed.push_back(tempNum);
		}
		m_LotBlue = rand() % 16 + 1;
	}
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
	}
	friend void CCustomer::Compare(CWelfareLot&);
	friend void CCustomer::SyncData(CWelfareLot&);
	friend void CCustomer::ManualSet();
	friend void CCustomer::ForceSameNumber();
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
}
void CCustomer::SyncData(CWelfareLot& W) {
	if (W.m_ManualSet = m_ManualSet) {
		W.m_Redball = m_ManualRed;
		W.m_Blueball = m_ManualBlue;
	}
	if (W.m_ForceSN = m_ForceSN) {
		W.m_LotRed = m_Redball;
		W.m_LotBlue = m_Blueball;
	}
}
void CCustomer::ManualSet() {	//手动设定大奖号码
	int choice = 0;
	while (1) {
		vector<string> options = { "[1] 红色球 #1", "[2] 红色球 #2", "[3] 红色球 #3", "[4] 红色球 #4", 
			"[5] 红色球 #5", "[6] 红色球 #6", "[B] 蓝色球", "[S] 启用预设的大奖号码", "[Q] 退出" };
		if (m_ManualSet)
			options[7] = "[S] 禁用预设的大奖号码";
		int selected = -1;
		while (1) {
			system("cls");
			cout << "手动设定大奖号码 -----------------------------------------\n\n";
			cout << "您的预设----------------------\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == selected)
					cout << "● ";
				else if (i == choice)
					cout << "> ";
				else
					cout << "  ";
				cout << options[i] << "\t    ";
				if (i < 6)
					cout << m_ManualRed[i];
				if (i == 6)
					cout << m_ManualBlue << '\n';
				cout << '\n';
			}
			cout << '\n';
			if (selected + 1)
				break;
			else {
				cout << "[↑][↓] 选择\n";
				cout << "[Enter] 确认\n";
				cout << "也可以直接按下快捷键。\n";
			}
			int key = _getch();
			if (key > 48 && key < 55) {
				choice = key - 49;
				key = ENTER;
			}
			switch (key) {
			case 'B':
			case 'b':
				choice = 6;
				key = ENTER;
				break;
			case 'S':
			case 's':
				choice = 7;
				key = ENTER;
				break;
			case 'Q':
			case 'q':
				return;
			}
			if (key == 224) {
				key = _getch();
				switch (key) {
				case UP:
					choice = choice == 0 ? (options.size() - 1) : --choice;
					break;
				case DOWN:
					choice = choice == (options.size() - 1) ? 0 : ++choice;
					break;
				}
			}
			else if (key == ENTER)
				selected = choice;
		}
		int temp = 1;
		switch (choice) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			temp = checkInput(33, "请输入新的红色球 #", -1, " 的预设号码 [输入 E 取消]：", choice + 1, m_ManualRed);
			if (temp) {
				m_ManualRed[choice] = temp;
				cout << "设定成功。";
			}
			break;
		case 6:
			temp = checkInput(16, "请输入新的蓝色球预设号码 [输入 E 取消]：", -1);
			if (temp) {
				m_ManualBlue = temp;
				cout << "设定成功。";
			}
			break;
		case 7:
			if (!m_ManualSet++) {
				cout << "已启用预设的大奖号码。";
				if (m_ForceSN) {
					cout << "\n[警告] 由于强制大奖号码与投注号码相同已启用，此功能被屏蔽。";
					Sleep(1500);
				}
			}
			else {
				m_ManualSet = false;
				cout << "已禁用预设的大奖号码。";
			}
			break;
		case 8:
			return;
		}
		if (temp)
			Sleep(1500);
	}
}
void CCustomer::ForceSameNumber() {	//设定强制大奖号码与投注号码相同
	system("cls");
	cout << "信息 ---------------------------------------------------\n\n";
	if (!m_ForceSN++)
		cout << "已启用强制大奖号码与投注号码相同。";
	else {
		m_ForceSN = false;
		cout << "已禁用强制大奖号码与投注号码相同。";
	}
	Sleep(3000);
}

CWelfareLot wLot;

int main() {
	getPasscode();
	string div = "-----------------------------------------------------------------------------------\n";
	int play = 1;
	cout << div << '\n';
	cout << "** 欢迎来到福彩-双色球！ **\n";
	cout << '\n';
	cout << "	-by Inkorest of NJUST\n";
	cout << '\n';
	cout << div << '\n';
	cout << '\n';
	cout << "请按任意键开始. . . ";
	_getch();
	mainMenu(0);

	user.EnterName();

	initRandomSeed();
	Sleep(1500);

	char reply;
	while (1) {
		system("cls");
		cout << div;
		cout << "游玩局数 #" << play << '\n';
		cout << div << '\n';
		user.PrintBalance();
		cout << '\n';
		user.SetNumber();
		user.SyncData(wLot);
		wLot.GenerateNumber();
		cout << '\n' << div;
		user.PrintSelection();
		cout << div;
		wLot.PrintLot();
		cout << div;
		Sleep(500);
		user.Compare(wLot);
		user.PrintPrize();
		cout << '\n';
		user.CalcRewards();
		cout << '\n';
		system("pause");
		inquiry();
		srand(++seed);
		play++;
	}
	return 0;
}

void getPasscode() {
	ifstream file;
	file.open("passcode.txt");
	file >> passcode;
	file.close();
}

void mainMenu(int status) {
	int choice = 0;
	while (1) {
		vector<string> options = { "[G] 开始游戏", "[R] 查看游戏规则", "[A] 输入管理员密码", "[Q] 退出游戏" };
		if (status)
			options[0] = "[G] 继续游戏";
		if (user.AdminStatus())
			options[2] = "[A] 进入管理员菜单";
		bool loop = true;
		while (loop) {
			system("cls");
			cout << "------------------------------------ 游戏菜单 ------------------------------------\n\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == choice)
					cout << "> " << options[i] << '\n';
				else
					cout << "  " << options[i] << '\n';
			}
			cout << '\n';
			cout << "[↑][↓] 选择\n";
			cout << "[Enter] 确认\n";
			cout << "也可以直接按下快捷键。\n";
			int key = _getch();
			switch (key) {
			case 'G':
			case 'g':
				return;
			case 'R':
			case 'r':
				choice = 1;
				loop = false;
				break;
			case 'A':
			case 'a':
				choice = 2;
				loop = false;
				break;
			case 'Q':
			case 'q':
				endGame();
			}
			if (key == 224) {
				key = _getch();
				switch (key) {
				case UP:
					choice = choice == 0 ? (options.size() - 1) : --choice;
					break;
				case DOWN:
					choice = choice == (options.size() - 1) ? 0 : ++choice;
					break;
				}
			}
			else if (key == ENTER)
				break;
		}
		switch (choice) {
		case 0:
			return;
		case 1:
			printRule();
			break;
		case 2:
			user.AdminAccess();
			break;
		case 3:
			endGame();
		}
	}
}

void inquiry() {
	int choice = 0;
	while (1) {
		vector<string> options = { "[Y] 确认", "[M] 打开游戏菜单", "[Q] 退出游戏" };
		bool loop = true;
		while (loop) {
			system("cls");
			cout << "再次游玩 -----------------------------------------------\n\n";
			cout << "您想再游玩一次游戏吗？\n\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == choice)
					cout << "> " << options[i] << '\n';
				else
					cout << "  " << options[i] << '\n';
			}
			cout << '\n';
			cout << "[↑][↓] 选择\n";
			cout << "[Enter] 确认\n";
			cout << "也可以直接按下快捷键。\n";
			int key = _getch();
			switch (key) {
			case 'Y':
			case 'y':
				return;
			case 'M':
			case 'm':
				choice = 1;
				loop = false;
				break;
			case 'Q':
			case 'q':
				endGame();
			}
			if (key == 224) {
				key = _getch();
				switch (key) {
				case UP:
					choice = choice == 0 ? (options.size() - 1) : --choice;
					break;
				case DOWN:
					choice = choice == (options.size() - 1) ? 0 : ++choice;
					break;
				}
			}
			else if (key == ENTER)
				break;
		}
		switch (choice) {
		case 0:
			return;
		case 1:
			mainMenu(1);
			return;
		case 2:
			endGame();
		}
	}
}

void printRule() {
	system("cls");
	cout << "------------------------------- 福彩-双色球游戏规则 -------------------------------\n";
	cout << "1. 下注：用户通过支付余额进行投注（可选单倍投注 / 多倍投注* ），然后在 33 个红色球号\n";
	cout << "	码中挑选 6 个、在 16 个蓝色球号码中挑选 1 个作为自己的投注号码。\n";
	cout << "2. 开奖：CPU 将按照设定好的随机数种子，随机得出 6 个红色球大奖号码和 1 个蓝色球大奖\n";
	cout << "	号码。\n";
	cout << "3. 结算：依据用户与大奖号码的匹配情况计算用户的中奖等级，并发放奖金（如中奖）。\n";
	cout << "*多倍投注：按单注售价的复倍（最大 99 倍）投注。若中奖，奖金也将变为复倍。\n";
	cout << '\n';
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
	cout << '\n';
	system("pause");
}

static void initRandomSeed() {	//初始化随机数种子
	int choice = 0;
	vector<string> options = { "[Y] 是", "[N] 否" };
	bool loop = true;
	while (loop) {
		system("cls");
		cout << "初始化随机数种子 ---------------------------------------\n\n";
		cout << "要由 CPU 自动生成随机数种子吗？\n\n";
		for (int i = 0; i < options.size(); i++) {
			if (i == choice)
				cout << "> " << options[i] << '\n';
			else
				cout << "  " << options[i] << '\n';
		}
		cout << '\n';
		cout << "[↑][↓] 选择\n";
		cout << "[Enter] 确认\n";
		cout << "也可以直接按下快捷键。\n";
		int key = _getch();
		switch (key) {
		case 'Y':
		case 'y':
			choice = 0;
			loop = false;
			break;
		case 'N':
		case 'n':
			choice = 1;
			loop = false;
			break;
		}
		if (key == 224) {
			key = _getch();
			switch (key) {
			case UP:
				choice = choice == 0 ? (options.size() - 1) : --choice;
				break;
			case DOWN:
				choice = choice == (options.size() - 1) ? 0 : ++choice;
				break;
			}
		}
		else if (key == ENTER)
			break;
	}
	switch (choice) {
	case 0:
		srand(seed);
		cout << "\n已经由 CPU 自动生成了随机数种子。";
		return;
	case 1:
		cout << '\n';
		seed = checkInput(0, "请输入随机数种子：");
		srand(seed);
		cout << "已经由此生成了随机数种子。";
		return;
	}
}

bool doExists(int num, vector<int> array) {
	for (int arrNum : array)
		if (num == arrNum)
			return true;
	return false;
}

int checkInput(int range, string text, int exit, string altText, int alter, vector<int> array) {	//限制输入
	string blank(50, ' ');
	while (1) {
		cout << '\r' << blank << '\r' << text;
		if (alter)
			cout << alter << altText;
		string input;
		getline(cin, input);
		if (input.empty()) {
			cout << "\033[F";
			continue;
		}
		int num;
		bool isDigit = true;
		for (char ch : input)
			if (!isdigit(ch)) {
				isDigit = false;
				break;
			}
		num = isDigit ? stoi(input) : 0;
		if (exit) {
			if (input == "E" || input == "e")
				return 0;
			if (exit + 1 && isDigit && num < 2) {
				cout << "\033[F\r" << blank << '\r';
				cout << "用户余额无法被手动设定到 2 z 以下。请重新输入。";
				Sleep(1500);
				continue;
			}
		}
		if (range && (num < 1 || num > range)) {
			cout << "\033[F\r" << blank << '\r';
			cout << "非法输入。请输入介于 1 和 " << range << " 之间的一个数字。";
			Sleep(1500);
			continue;
		}
		if (!isDigit) {
			cout << "\033[F\r" << blank << '\r';
			cout << "非法输入。请重新输入。";
			Sleep(1500);
			continue;
		}
		if (!array.empty() && doExists(num, array)) {
			cout << "\033[F\r" << blank << '\r';
			cout << "红色球号码不能重复。请重新输入。";
			Sleep(1500);
			continue;
		}
		return num;
	}
}

void endGame() {
	system("cls");
	cout << "感谢您游玩福彩-双色球！:)\n";
	exit(0);
}