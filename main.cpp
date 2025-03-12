/*	������Ϸ	*/
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

int seed = (unsigned)time(NULL);	//���������
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
	bool m_AdminStatus = false;	//����Ա���
	bool m_ManualSet = false;	//�Ƿ�����Ԥ��
	vector<int> m_ManualRed = { 1, 2, 3, 4, 5, 6 };	//��ɫ�����Ԥ��
	int m_ManualBlue = 1;	//��ɫ�����Ԥ��
	bool m_ForceSN = false;	//�Ƿ�ǿ��ͷ��
public:
	CCustomer(int money = 100) :m_Balance(money) {};
	void EnterName() {
		system("cls");
		cout << "�������������� [1 �� 20 ���ַ�]��\n";
		getline(cin, m_Name);
		cout << "\n��ӭ " << m_Name << "��";
		Sleep(1500);
	}
	void SetNumber() {	//����Ͷע
		int maxBetMulti = m_Balance / 2 > 99 ? 99 : m_Balance / 2;
		if (maxBetMulti > 1) {
			cout << "����ѡ�񵥱�Ͷע��౶Ͷע��ÿע�ۼ� 2 z��\n";
			cout << "[1] ����Ͷע\n";
			cout << "[" << (maxBetMulti != 2 ? "2~" : "\0") << maxBetMulti << "] �౶Ͷע����\n";
			m_BetMulti = checkInput(maxBetMulti, "���������");
			m_Balance -= 2 * m_BetMulti;
			cout << "\n�ɹ�����Ͷע��";
		}
		else {
			Sleep(1500);
			cout << "�Ѿ��Զ������˵���Ͷע��";
		}
		PrintBalance();
		cout << "\n��������ĺ�ɫ����� [1 ~ 33]��\n";
		for (int i = 0; i < 6; i++) {
			m_Redball.push_back(checkInput(33, "�����ɫ�� #", 0, " �ĺ��룺", i + 1, m_Redball));
		}
		m_Blueball = checkInput(16, "�����������ɫ����� [1 ~ 16]��");
	}
	void PrintSelection() const {	//��ʾ�û�ѡ��ǿ����ʾ��λ��
		cout << "���ѡ��Ϊ��\t��ɫ��";
		for (int i = 0; i < 6; i++)
			cout << (m_Redball[i] < 10 ? '0' : '\0') << m_Redball[i] << '\t';
		cout << "��ɫ��" << (m_Blueball < 10 ? '0' : '\0') << m_Blueball << '\n';
	}
	void Compare(CWelfareLot&);
	void PrintBalance() const {
		cout << "��Ŀǰ�����Ϊ " << m_Balance << " z��\n";
	}
	void PrintPrize() const {	//���Ͷע���
		cout << m_Name << "�����Ͷע���Ϊ��\n��ɫ����ͬ������" << m_RedMatches << "��"
			"��ɫ�����" << (m_BlueMatch ? "��ͬ" : "����ͬ") << "��\n\n";
		if (m_Prize) {
			cout << "��ϲ��" << m_Name << "����Ӯ����";
			switch (m_Prize) {
			case 6:
				cout << "һ�Ƚ���!";
				break;
			case 5:
				cout << "���Ƚ���";
				break;
			case 4:
				cout << "���Ƚ���";
				break;
			case 3:
				cout << "�ĵȽ���";
				break;
			case 2:
				cout << "��Ƚ���";
				break;
			case 1:
				cout << "���Ƚ���";
				break;
			}
		}
		else
			cout << "���ź���" << m_Name << "����û��Ӯ�ý���";
	}
	void CalcRewards() {	//���㽱�����ý�������
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
			cout << "���� " << reward << " z �Ѿ����ŵ�������";
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
		cout << "�������Ա�˵� -----------------------------------------\n\n";
		cout << "���������Ա���� [���� E �˳�]��\n";
		string input;
		while (1) {
			while (1) {	//������������
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
				cout << "������ȷ���Ѿ�ȡ�ù���Ա��ݡ�";
				Sleep(1500);
				AdminOptions();
				return;
			}
			cout << "����������������룺\n";
			input.clear();
		}
	}
	bool AdminStatus() const {
		return m_AdminStatus ? 1 : 0;
	}
	void AdminOptions() {	//����Ա�˵�
		int choice = 0;
		while (1) {
			vector<string> options = { "[M] �ֶ��趨�󽱺���", "[F] ����ǿ�ƴ󽱺�����Ͷע������ͬ", "[A] �趨�û����", "[E] �˳�����Ա�˵�" };
			if (m_ForceSN)
				options[1] = "[F] ����ǿ�ƴ󽱺�����Ͷע������ͬ";
			bool loop = true;
			while (loop) {
				system("cls");
				cout << "----------------------------------- ����Ա�˵� -----------------------------------\n\n";
				for (int i = 0; i < options.size(); i++) {
					if (i == choice)
						cout << "> " << options[i] << '\n';
					else
						cout << "  " << options[i] << '\n';
				}
				cout << '\n';
				cout << "[��][��] ѡ��\n";
				cout << "[Enter] ȷ��\n";
				cout << "Ҳ����ֱ�Ӱ��¿�ݼ���\n";
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
		cout << "�趨�û���� -------------------------------------------\n\n";
		PrintBalance();
		cout << '\n';
		cout << "[����] �趨�µ��û���z��\n";
		cout << "[E] �ص�����Ա�˵�\n\n";
		int newBalance = checkInput(0, "���������", 1);
		if (!newBalance)
			return;
		m_Balance = newBalance;
		system("cls");
		cout << "��Ϣ ---------------------------------------------------\n\n";
		cout << "�Ѿ��ɹ��趨�µ��û���";
		PrintBalance();
		cout << "\n�������ع���Ա�˵�. . . ";
		Sleep(4000);
		return;
	}
	void GameOver() {
		cout << "\n\n���ź��������������ٽ���Ͷע����Ϸ������";
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
	void GenerateNumber() {	//���ɴ󽱺���
		if (m_ForceSN)
			return;
		if (m_ManualSet) {
			m_LotRed = m_Redball;
			m_LotBlue = m_Blueball;
			return;
		}
		int tempNum;
		for (int i = 0; i < 6; i++) {
			do	//��ֹ��ɫ���ظ�
				tempNum = rand() % 33 + 1;
			while (doExists(tempNum, m_LotRed));
			m_LotRed.push_back(tempNum);
		}
		m_LotBlue = rand() % 16 + 1;
	}
	void PrintLot() const {	//ģ�Ⲣ��ʾ����
		int rndTime, rndNum;
		cout << "�󽱺���Ϊ��\t��ɫ��";
		//������ʾ��ɫ�����
		for (int i = 0; i < 6; i++) {
			rndTime = rand() % 10 + 6;	//���ƹ�����ʾ������6~15��
			for (int j = 0; j < rndTime; j++) {
				rndNum = rand() % 33 + 1;
				rndNum < 10 ? cout << '0' << rndNum << "\b\b" : cout << rndNum << "\b\b";
				Sleep(150);
			}
			cout << (m_LotRed[i] < 10 ? '0' : '\0') << m_LotRed[i] << '\t';
		}
		cout << "��ɫ��";
		//������ʾ��ɫ�����
		rndTime = rand() % 10 + 6;	//���ƹ�����ʾ������6~15��
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

void CCustomer::Compare(CWelfareLot& W) {	//���㽱��ȼ�
	for (int i = 0; i < 6; i++)
		m_RedMatches += doExists(m_Redball[i], W.m_LotRed);
	m_BlueMatch += (m_Blueball == W.m_LotBlue);
	switch (m_RedMatches) {	//��˫ɫ�������㽱��
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
void CCustomer::ManualSet() {	//�ֶ��趨�󽱺���
	int choice = 0;
	while (1) {
		vector<string> options = { "[1] ��ɫ�� #1", "[2] ��ɫ�� #2", "[3] ��ɫ�� #3", "[4] ��ɫ�� #4", 
			"[5] ��ɫ�� #5", "[6] ��ɫ�� #6", "[B] ��ɫ��", "[S] ����Ԥ��Ĵ󽱺���", "[Q] �˳�" };
		if (m_ManualSet)
			options[7] = "[S] ����Ԥ��Ĵ󽱺���";
		int selected = -1;
		while (1) {
			system("cls");
			cout << "�ֶ��趨�󽱺��� -----------------------------------------\n\n";
			cout << "����Ԥ��----------------------\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == selected)
					cout << "�� ";
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
				cout << "[��][��] ѡ��\n";
				cout << "[Enter] ȷ��\n";
				cout << "Ҳ����ֱ�Ӱ��¿�ݼ���\n";
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
			temp = checkInput(33, "�������µĺ�ɫ�� #", -1, " ��Ԥ����� [���� E ȡ��]��", choice + 1, m_ManualRed);
			if (temp) {
				m_ManualRed[choice] = temp;
				cout << "�趨�ɹ���";
			}
			break;
		case 6:
			temp = checkInput(16, "�������µ���ɫ��Ԥ����� [���� E ȡ��]��", -1);
			if (temp) {
				m_ManualBlue = temp;
				cout << "�趨�ɹ���";
			}
			break;
		case 7:
			if (!m_ManualSet++) {
				cout << "������Ԥ��Ĵ󽱺��롣";
				if (m_ForceSN) {
					cout << "\n[����] ����ǿ�ƴ󽱺�����Ͷע������ͬ�����ã��˹��ܱ����Ρ�";
					Sleep(1500);
				}
			}
			else {
				m_ManualSet = false;
				cout << "�ѽ���Ԥ��Ĵ󽱺��롣";
			}
			break;
		case 8:
			return;
		}
		if (temp)
			Sleep(1500);
	}
}
void CCustomer::ForceSameNumber() {	//�趨ǿ�ƴ󽱺�����Ͷע������ͬ
	system("cls");
	cout << "��Ϣ ---------------------------------------------------\n\n";
	if (!m_ForceSN++)
		cout << "������ǿ�ƴ󽱺�����Ͷע������ͬ��";
	else {
		m_ForceSN = false;
		cout << "�ѽ���ǿ�ƴ󽱺�����Ͷע������ͬ��";
	}
	Sleep(3000);
}

CWelfareLot wLot;

int main() {
	getPasscode();
	string div = "-----------------------------------------------------------------------------------\n";
	int play = 1;
	cout << div << '\n';
	cout << "** ��ӭ��������-˫ɫ�� **\n";
	cout << '\n';
	cout << "	-by Inkorest of NJUST\n";
	cout << '\n';
	cout << div << '\n';
	cout << '\n';
	cout << "�밴�������ʼ. . . ";
	_getch();
	mainMenu(0);

	user.EnterName();

	initRandomSeed();
	Sleep(1500);

	char reply;
	while (1) {
		system("cls");
		cout << div;
		cout << "������� #" << play << '\n';
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
		vector<string> options = { "[G] ��ʼ��Ϸ", "[R] �鿴��Ϸ����", "[A] �������Ա����", "[Q] �˳���Ϸ" };
		if (status)
			options[0] = "[G] ������Ϸ";
		if (user.AdminStatus())
			options[2] = "[A] �������Ա�˵�";
		bool loop = true;
		while (loop) {
			system("cls");
			cout << "------------------------------------ ��Ϸ�˵� ------------------------------------\n\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == choice)
					cout << "> " << options[i] << '\n';
				else
					cout << "  " << options[i] << '\n';
			}
			cout << '\n';
			cout << "[��][��] ѡ��\n";
			cout << "[Enter] ȷ��\n";
			cout << "Ҳ����ֱ�Ӱ��¿�ݼ���\n";
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
		vector<string> options = { "[Y] ȷ��", "[M] ����Ϸ�˵�", "[Q] �˳���Ϸ" };
		bool loop = true;
		while (loop) {
			system("cls");
			cout << "�ٴ����� -----------------------------------------------\n\n";
			cout << "����������һ����Ϸ��\n\n";
			for (int i = 0; i < options.size(); i++) {
				if (i == choice)
					cout << "> " << options[i] << '\n';
				else
					cout << "  " << options[i] << '\n';
			}
			cout << '\n';
			cout << "[��][��] ѡ��\n";
			cout << "[Enter] ȷ��\n";
			cout << "Ҳ����ֱ�Ӱ��¿�ݼ���\n";
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
	cout << "------------------------------- ����-˫ɫ����Ϸ���� -------------------------------\n";
	cout << "1. ��ע���û�ͨ��֧��������Ͷע����ѡ����Ͷע / �౶Ͷע* ����Ȼ���� 33 ����ɫ���\n";
	cout << "	������ѡ 6 ������ 16 ����ɫ���������ѡ 1 ����Ϊ�Լ���Ͷע���롣\n";
	cout << "2. ������CPU �������趨�õ���������ӣ�����ó� 6 ����ɫ��󽱺���� 1 ����ɫ���\n";
	cout << "	���롣\n";
	cout << "3. ���㣺�����û���󽱺����ƥ����������û����н��ȼ��������Ž������н�����\n";
	cout << "*�౶Ͷע������ע�ۼ۵ĸ�������� 99 ����Ͷע�����н�������Ҳ����Ϊ������\n";
	cout << '\n';
	cout << '\n';
	cout << "--------------------- ������ձ� ---------------------\n";
	cout << "����\t����\t�н���������ɫ�������/��ɫ����������\n";
	cout << "һ�Ƚ�\t10M z\t6/S\n";
	cout << "���Ƚ�\t500K z\t6/F\n";
	cout << "���Ƚ�\t3K z\t5/S\n";
	cout << "�ĵȽ�\t200 z\t5/F ���� 4/S\n";
	cout << "��Ƚ�\t10 z\t4/F ���� 3/S\n";
	cout << "���Ƚ�\t5 z\t2/S ���� 1/S ���� 0/S\n";
	cout << '\n';
	cout << '\n';
	system("pause");
}

static void initRandomSeed() {	//��ʼ�����������
	int choice = 0;
	vector<string> options = { "[Y] ��", "[N] ��" };
	bool loop = true;
	while (loop) {
		system("cls");
		cout << "��ʼ����������� ---------------------------------------\n\n";
		cout << "Ҫ�� CPU �Զ����������������\n\n";
		for (int i = 0; i < options.size(); i++) {
			if (i == choice)
				cout << "> " << options[i] << '\n';
			else
				cout << "  " << options[i] << '\n';
		}
		cout << '\n';
		cout << "[��][��] ѡ��\n";
		cout << "[Enter] ȷ��\n";
		cout << "Ҳ����ֱ�Ӱ��¿�ݼ���\n";
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
		cout << "\n�Ѿ��� CPU �Զ���������������ӡ�";
		return;
	case 1:
		cout << '\n';
		seed = checkInput(0, "��������������ӣ�");
		srand(seed);
		cout << "�Ѿ��ɴ���������������ӡ�";
		return;
	}
}

bool doExists(int num, vector<int> array) {
	for (int arrNum : array)
		if (num == arrNum)
			return true;
	return false;
}

int checkInput(int range, string text, int exit, string altText, int alter, vector<int> array) {	//��������
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
				cout << "�û�����޷����ֶ��趨�� 2 z ���¡����������롣";
				Sleep(1500);
				continue;
			}
		}
		if (range && (num < 1 || num > range)) {
			cout << "\033[F\r" << blank << '\r';
			cout << "�Ƿ����롣��������� 1 �� " << range << " ֮���һ�����֡�";
			Sleep(1500);
			continue;
		}
		if (!isDigit) {
			cout << "\033[F\r" << blank << '\r';
			cout << "�Ƿ����롣���������롣";
			Sleep(1500);
			continue;
		}
		if (!array.empty() && doExists(num, array)) {
			cout << "\033[F\r" << blank << '\r';
			cout << "��ɫ����벻���ظ������������롣";
			Sleep(1500);
			continue;
		}
		return num;
	}
}

void endGame() {
	system("cls");
	cout << "��л�����渣��-˫ɫ��:)\n";
	exit(0);
}