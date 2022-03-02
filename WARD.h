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
	int totalbed = 100;//�ܴ���
	int freebed = 100;//���д�λ��
	void inward() { freebed--; }
	void outward() { freebed++; }
	void showtotalbed() { cout << "�ܴ�λ��:" << totalbed << endl; }
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
		cout << "#========================��������ϵͳ======================#" << endl;
		cout << "#==1.����סԺ   2.�����Ժ   3.���һ��ߴ�λ   4.�˳�ϵͳ===#" << endl;
		cout << "#==��ѡ�������";
		string k;
		int ktoint;
		do
		{
			cin >> k;
			ktoint = atoi(k.c_str());
			if (ktoint <= 0 || ktoint > 4) {
				cout << "�޷�ʶ�������ѡ����������룺";
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
			cout << "�����Ƿ�Ҫ��������ϵͳ�Ļ����ļ���(y/n):";
			do {
				cin >> op;
				if (op != "n" && op != "y") {
					cout << "�����������������룺";
				}
			} while (op != "n" && op != "y");
			if (op == "n") {
				string cmd1, cmd2;
				cmd1 = "del " + rootstr + "\\PMS_data\\Patient_Need_Livein\\*.*";
				system(cmd1.c_str());
				cmd2 = "del " + rootstr + "\\PMS_data\\Patient_Need_Livein\\Livingin\\*.*";
				system(cmd2.c_str());
				cout << "������ɡ�";
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

	int waitqueue() {//��ʾ�����ŶӶ���
		ifstream SHOWQUEUE;
		char line[30];
		SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
		if (!SHOWQUEUE.is_open()) {
			cout << "ϵͳ�Ҳ���ָ�����ļ���" << endl;
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

	void wardroom() {//��ʾסԺ����
		linenumber = 0;
		ifstream SHOWQUEUE;
		char line[30];
		SHOWQUEUE.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt");
		if (!SHOWQUEUE.is_open()) {
			cout << "�޷��鿴�Ѿ�סԺ��������ԭ�������Ŀǰ����סԺ�����ļ��𻵡�" << endl;
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
		cout << "��ǰ����������סԺ" << endl;
		cout << "��ǰ�ĵȴ�סԺ���У�" << endl;
		if (!waitqueue()) return;
		for (i = 0; i < w1.totalbed; i++) {
			if (w1.bed[i] == "0")
			{
				ofstream ALLOCATENEWLIVING;
				ALLOCATENEWLIVING.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\LIVEDIN.txt", ios::app);
				ifstream READQUEUELIST;
				READQUEUELIST.open(rootstr + "\\PMS_data\\Patient_Need_Livein\\NEEDLIVEIN.txt");
				cout << "��ѡ��Ҫ����סԺ�Ĳ�����ţ�";
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
					cout << "�޷��ҵ���ѡ�Ĳ��ˣ���ȷ�ϴ˲����Ƿ����б��еȺ���סԺ��";
					system("pause");
					system("cls");
					return;
				}
				else
				{
					PATIENTREADWARD.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt");
					if (!PATIENTREADWARD.is_open()) {
						cout << "�޷��ҵ��������ݿ��ļ���" << endl;
						PATIENTREADWARD.close();
						return;
					}
					else
					{
						cout << "�ɹ���ȡ���������ļ���Ŀǰ�ļ��а���������Ϊ��" << endl;
						while (PATIENTREADWARD.getline(historymessage, 256)) {
							cout << "   " << historymessage << endl;
						}
						PATIENTREADWARD.close();
						ALLOCATEPATIENT.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\" + selectpatient + "_" + id + "_db.txt", ios::app);
						cout << "Ŀǰ�п��д�λ����λ��Ϊ��" << i + 1 << endl;
						cout << "�����Զ����䴲λ...���Ժ�..." << endl;
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
						cout << "����סԺ�������̽�����";
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
		cout << "��ǰ�����������Ժ" << endl;
		searchward();
		cout << "ȷ��Ҫ�����Ժ������(y/n):";
		do {
			cin >> op;
			if (op != "n" && op != "y") {
				cout << "�����������������룺";
			}
		} while (op != "n" && op != "y");
		if (op == "n") {
			cout << "�����˳���";
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
			SYSTEMTIME st;//���屾��ʱ��������ñ���Ϊ�ṹ��
			GetLocalTime(&st);//��ȡ����ʱ�亯��������Ϊʱ�����ָ��
			int year = st.wYear;
			int month = st.wMonth;
			int day = st.wDay;
			string years, months, days;
			years = to_string(static_cast<long long>(year));
			months = to_string(static_cast<long long>(month));
			days = to_string(static_cast<long long>(day));
			ALLOCATEOUTWARD << "[" << years << months << days << "]" << "��Ժ" << endl;
			ALLOCATEOUTWARD.close();
			cout << "�ɹ������Ժ������" << endl;
			system("pause");
			system("cls");
		}
	}

	void searchward() {
		cout << "Ŀǰ����סԺ�Ĳ�����Ϣ���£�" << endl;
		wardroom();
		cout << "��������Ҫ���в����Ĳ������֤���룺";
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
			cout << "�ɹ���ȡ������Ϣ����ǰ���˵Ĵ�λΪ��" << bedline << endl;
		}
		else
		{
			cout << "δ�ҵ��˲��˵������Ϣ����ȷ�����Ƿ��Ѿ�סԺ��";
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