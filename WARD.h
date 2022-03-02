#pragma once
#ifndef WARD_H
#define WARD_H
#include<fstream>
#include<cstring>
#include<string>
#include<iostream>
#include<Windows.h>
#include<iomanip>

using namespace std;
string rootstr;
class Ward{
public:
	string bed[100];
	int totalbed = 100;//总床数
	int freebed = 100;//空闲床位数
	void inward() { freebed--; }
	void outward() { freebed++; }
	void showtotalbed() { cout << "总床位数:" << totalbed << endl; }
	int linenumber = 0;
	int i = 0;
	string ID;
	int searchrecordnew = 0;
	string bedlinebak;
	string rootstr;
	void WardSystem() {
		for (int j = 0; j < w1.totalbed; j++) {
			w1.bed[j] = "0";
		}
		while (1) {
			InitWard();
		}
	}

private:
	void InitWard() {
		ifstream ROOT;
		char root[256];
		ROOT.open("config.txt");
		ROOT.getline(root, 3);
		const char* roottostring = root;
		rootstr = roottostring;
		ROOT.close();
		system("cls");
		string op;
		cout << "#========================病房管理系统======================#" << endl;
		cout << "#==1.办理住院   2.办理出院   3.查找患者床位   4.退出系统===#" << endl;
		cout << "#==请选择操作：";
		string k;
		int ktoint;
		do
		{
			cin >> k;
			ktoint = atoi(k.c_str());
			if (ktoint <= 0 || ktoint > 4) {
				cout << "无法识别输入的选项，请重新输入：";
			}
		} while (ktoint <= 0 || ktoint > 4);
		if (ktoint == 1) {
			system("cls");
			w1.inward();
			setinward();
		}
		else if (ktoint == 2) {
			system("cls");
			w1.outward();
			setoutward();
		}
		else if (ktoint == 3) {
			system("cls");
			searchward();
			system("pause");
		}
		else if (ktoint == 4) {
			system("cls");
			cout << "请问是否要保留病房系统的缓存文件？(y/n):";
			do {
				cin >> op;
				if (op != "n" && op != "y") {
					cout << "输入有误，请重新输入：";
				}
			} while (op != "n" && op != "y");
			if (op == "n") {
				string cmd1, cmd2;
				cmd1 = "del " + rootstr + "\\PMS_data\\Patient_Need_Livein\\*.*";
				system(cmd1.c_str());
				cmd2 = "del " + rootstr + "\\PMS_data\\Patient_Need_Livein\\Livingin\\*.*";
				system(cmd2.c_str());
				cout << "清理完成。";
				system("pause");
				system("cls");
				return;
			}
			else if (op == "y") {
				return;
			}
			return;
		}
	}

	int waitqueue() {//显示病房排队队列
		ifstream SHOWQUEUE;
		char line[30];
		SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
		if (!SHOWQUEUE.is_open()) {
			cout << "系统找不到指定的文件。" << endl;
			SHOWQUEUE.close();
			system("pause");
			system("cls");
			return 0;
		}
		else
		{
			SHOWQUEUE.close();
			SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
			while (!SHOWQUEUE.eof()) {
				SHOWQUEUE.getline(line, 30);
				cout << "   " << line << endl;
			}
		}
		SHOWQUEUE.close();
		return 1;
	}

	void wardroom() {//显示住院名单
		linenumber = 0;
		ifstream SHOWQUEUE;
		char line[30];
		SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
		if (!SHOWQUEUE.is_open()) {
			cout << "无法查看已经住院的名单，原因可能是目前无人住院或者文件损坏。" << endl;
			SHOWQUEUE.close();
			system("pause");
			system("cls");
			return;
		}
		else
		{
			SHOWQUEUE.close();
			SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
			while (!SHOWQUEUE.eof()) {
				SHOWQUEUE.getline(line, 30);
				cout << "   " << line << endl;
				linenumber++;
			}
		}
		SHOWQUEUE.close();
		return;
	}

	void setinward() {
		string selectpatient;
		int selectpatientint;
		int flag;
		char historymessage[256];
		int searchrecord = 0;
		ifstream PATIENTREADWARD;
		ofstream ALLOCATEPATIENT;
		char id[30];
		int lineint;
		cout << "当前操作：办理住院" << endl;
		cout << "当前的等待住院队列：" << endl;
		if (!waitqueue()) return;
		for (i = 0; i < w1.totalbed; i++) {
			if (w1.bed[i] == "0")
			{
				ofstream ALLOCATENEWLIVING;
				ALLOCATENEWLIVING.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt", ios::app);
				ifstream READQUEUELIST;
				READQUEUELIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
				cout << "请选择要安排住院的病人序号：";
				cin >> selectpatient;
				selectpatientint = atoi(selectpatient.c_str());
				while (!READQUEUELIST.eof()) {
					char line[256];
					READQUEUELIST.getline(line, 30);
					if (line[0] == '\0')
						break;
					else
					{
						strtok(line, "_");
						strcpy(id, strtok(NULL, "_"));
						lineint = atoi(line);
					}
					if (lineint == selectpatientint) {
						flag = 1;
						break;
					}
					else
						flag = 0;
					searchrecord++;
				}
				READQUEUELIST.close();
				if (!flag) {
					cout << "无法找到所选的病人，请确认此病人是否在列表中等候安排住院！";
					system("pause");
					system("cls");
					return;
				}
				else
				{
					PATIENTREADWARD.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt");
					if (!PATIENTREADWARD.is_open()) {
						cout << "无法找到病人数据库文件！" << endl;
						PATIENTREADWARD.close();
						return;
					}
					else
					{
						cout << "成功读取病人数据文件，目前文件中包含的内容为：" << endl;
						while (PATIENTREADWARD.getline(historymessage, 256)) {
							cout << "   " << historymessage << endl;
						}
						PATIENTREADWARD.close();
						ALLOCATEPATIENT.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt", ios::app);
						cout << "目前有空闲床位，床位号为：" << i + 1 << endl;
						cout << "正在自动分配床位...请稍候..." << endl;
						w1.bed[i] = id;
						ALLOCATEPATIENT << "Status:LivingIn" << endl;
						ALLOCATEPATIENT << "Bed:" << i + 1 << endl;
						ALLOCATEPATIENT.close();
						ALLOCATENEWLIVING << i + 1 << "." << id << endl;
						ALLOCATENEWLIVING.close();

						string cmd1 = "copy " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\Livingin";
						system(cmd1.c_str());
						string cmd4 = "del " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt";
						system(cmd4.c_str());
						ifstream READRAWLIST;
						ofstream UPDATELIST;
						READRAWLIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
						UPDATELIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN_BAK.txt");
						char str[256];
						int count = 0;
						while (!READRAWLIST.eof()) {
							READRAWLIST.getline(str, 30);
							if (count != searchrecord && str[0] != '\0') {
								UPDATELIST << str << endl;
							}
							count++;
						}
						READRAWLIST.close();
						string cmd2 = "del " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\NEEDLIVEIN.txt";
						system(cmd2.c_str());
						UPDATELIST.close();
						string cmd3 = "rename " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\NEEDLIVEIN_BAK.txt NEEDLIVEIN.txt";
						system(cmd3.c_str());
						string itostring = to_string(i + 1);
						string cmd5 = "rename " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\Livingin\\" + selectpatient + "_" + id + "_db.txt " + itostring + "_" + id + ".txt";
						system(cmd5.c_str());
						string cmd6 = "del " + rootstr + "\\PMS_Data\\Patient_Need_Livein\\Livingin\\" + selectpatient + "_" + id + "_db.txt";
						system(cmd6.c_str());
						cout << "办理住院手续流程结束。";
						system("pause");
						system("cls");
						return;
					}
				}
			}

		}
	}

	void setoutward() {
		string op;
		cout << "当前操作：办理出院" << endl;
		searchward();
		cout << "确认要办理出院手续吗？(y/n):";
		do {
			cin >> op;
			if (op != "n" && op != "y") {
				cout << "输入有误，请重新输入：";
			}
		} while (op != "n" && op != "y");
		if (op == "n") {
			cout << "程序退出。";
			system("pause");
			system("cls");
			return;
		}
		else if (op == "y") {
			ifstream CHECKLIST;
			CHECKLIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
			char id[30];
			string idbak;
			int flag;
			char bedline[30];
			while (!CHECKLIST.eof()) {
				char line[256];
				CHECKLIST.getline(bedline, 30);
				const char* idtostring;
				if (line[0] == '\0')
					break;
				else
				{
					strtok(bedline, ".");
					strcpy(id, strtok(NULL, "."));
					idtostring = id;
					idbak = idtostring;
				}
				if (idbak == ID) {
					flag = 1;
					break;
				}
				else
					flag = 0;
				searchrecordnew++;
			}
			CHECKLIST.close();
			ifstream READRAWLIST;
			ofstream UPDATELIST;
			READRAWLIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
			UPDATELIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN_BAK.txt");
			char str[256];
			int count = 0;
			while (!READRAWLIST.eof()) {
				READRAWLIST.getline(str, 30);
				if (count != searchrecordnew && str[0] != '\0') {
					UPDATELIST << str << endl;
				}
				count++;
			}
			READRAWLIST.close();
			UPDATELIST.close();
			string cmd1 = "del " + rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt";
			system(cmd1.c_str());
			string cmd2 = "rename " + rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN_BAK.txt LIVEDIN.txt";
			system(cmd2.c_str());
			ofstream ALLOCATEOUTWARD;
			ALLOCATEOUTWARD.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\Livingin\\" + bedlinebak + "_" + ID + ".txt", ios::app);
			SYSTEMTIME st;//定义本地时间变量，该变量为结构体
			GetLocalTime(&st);//获取本地时间函数，参数为时间变量指针
			int year = st.wYear;
			int month = st.wMonth;
			int day = st.wDay;
			string years, months, days;
			years = to_string(static_cast<long long>(year));
			months = to_string(static_cast<long long>(month));
			days = to_string(static_cast<long long>(day));
			ALLOCATEOUTWARD << "[" << years << months << days << "]" << "出院" << endl;
			ALLOCATEOUTWARD.close();
			cout << "成功办理出院手续！" << endl;
			system("pause");
			system("cls");
		}
	}

	void searchward() {
		cout << "目前正在住院的病人信息如下：" << endl;
		wardroom();
		cout << "请输入需要进行操作的病人身份证号码：";
		cin >> ID;
		ifstream CHECKLIST;
		CHECKLIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
		int flag;
		char bedline[30];
		while (!CHECKLIST.eof()) {
			char id[30];
			char line[256];
			string idbak;
			CHECKLIST.getline(bedline, 30);
			if (line[0] == '\0')
				break;
			else
			{
				strtok(bedline, ".");
				strcpy(id, strtok(NULL, "."));
				idbak = id;
			}
			if (idbak == ID) {
				flag = 1;
				break;
			}
			else
				flag = 0;
			searchrecordnew++;
		}
		CHECKLIST.close();
		if (flag) {
			cout << "成功获取病人信息，当前病人的床位为：" << bedline << endl;
		}
		else
		{
			cout << "未找到此病人的相关信息，请确认其是否已经住院。";
			system("pause");
			system("cls");
			return;
		}
		const char* toreadbedline;
		toreadbedline = bedline;
		bedlinebak = toreadbedline;
	}

}w1;
#endif