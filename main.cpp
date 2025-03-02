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
int main()
{	char name[20], Reply1, Reply2;
	int PowerBall, total, play = 1;
	int truematch[6];
	int menu();
	cout << "-------------------------------\n";
	cout << "* 欢迎来到强力球彩票！ *\n";
	cout << "-------------------------------\n";
	cout << "	-by Chris Grose, edited by Inkorest\n\n";
	cout << "请输入你的名字 [1 到 20 个字符]：";
	cin.getline(name, 20);	//输入玩家姓名
	cout << "\n欢迎 " << name << "！" << endl;
	cout << "你想由 CPU 自动生成随机数种子吗？ [y 或者 n]" << endl;
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
	do
	{	int num[5];	//输入所选的数字
		int cp_num[6];	//CPU产生的数字
		cout << "\n" << name << "，请输入你的白色球号码。\n";
		cout << "\n";
		for (int j = 0; j < 5; j++)	//输入5个所选号码
		{	cout << "输入球 #" << j + 1 << " 的号码：";
			while (!(cin >> num[j]))	//在输入的同时对输入的类型和大小做限制
			{	cin.clear();
				while (!(cin.get() != '\n'))
				continue;
				cout << "抱歉，这是一个非法输入。请输入介于 1 和 48 之间的一个数字。谢谢！\n";
			}
			if ((num[j] < 1))
			{	cout << "抱歉，你输入了一个小于 0 的数字。请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
			if ((num[j] > 48))
			{	cout << "抱歉，你输入了一个大于 48 的数字。请输入介于 1 和 48 之间的一个数字。\n";
				j--;
			}
		}
		cout << '\n';
		cout << name << "，请输入你的强力球号码：";
		cin >> PowerBall;	//要求玩家输入最后一个号码，叫做强力球
		cp_num[0] = getgamenbr();	//CPU产生6个随机号码
		cp_num[1] = getgamenbr();
		cp_num[2] = getgamenbr();
		cp_num[3] = getgamenbr();
		cp_num[4] = getgamenbr();
		cp_num[5] = getgamenbr();
		truematch[0] = isMatch(num[0], cp_num);		//判断玩家输入的数字与CPU产生的是否相等
		truematch[1] = isMatch(num[1], cp_num);
		truematch[2] = isMatch(num[2], cp_num);
		truematch[3] = isMatch(num[3], cp_num);
		truematch[4] = isMatch(num[4], cp_num);
		truematch[5] = isMatch(num[5], cp_num);
		//输出最终结果
		cout << "\n****************************";
		cout<<"\n游玩局数 #"<<play;
		cout << "\n****************************\n";
		cout << '\n';
		cout << "CPU 的选择为：\t" << cp_num[0] << '\t' << cp_num[1] << '\t' << cp_num[2] << '\t' << cp_num[3] << '\t' << cp_num[4] << '\t' << "PB" << '\t' << cp_num[5] << '\n';
		cout << "-------------------------------\n";
		cout << name << "，你的选择为：\t" << num[0] << '\t' << num[1] << '\t' << num[2] << '\t' << num[3] << '\t' << num[4] << '\t' << "PB" << '\t' << PowerBall << '\n';
		cout << "-------------------------------\n";
		//显示比较结果
		cout << name << "，你的配对为：\t" << truematch[0] << '\t' << truematch[1] << '\t' << truematch[2] << '\t' << truematch[3] << '\t' << truematch[4] << '\t' << "PB" << '\t' << truematch[5] << '\n';
		cout << "-------------------------------\n";
		total = truematch[0] + truematch[1] + truematch[2] + truematch[3] + truematch[4] + truematch[5];	//将对应数字正确的数目相加
		cout << "\n合计配对：" << total << "\n\n";	//显示有几个数字相等
		if (total == 6)	//如果6个数字相等赢得大奖
		{	cout << "恭喜，" << name << "！你赢得了 Jackpot！！";	}
		else
			cout << "很遗憾，" << name << "，你没有赢得 Jackpot！";	//否则未获奖
		cout << "\n****************************\n";
		cout << name << "，你想再游玩一次游戏吗？ [y 或者 n]" << endl;
		cin >> Reply2;	//询问是否玩下一局
		play = play + 1;
	} while (Reply2 == 'Y' || Reply2 == 'y');
	cout << "\n感谢你游玩强力球彩票，" << name << "！:)" << endl;
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