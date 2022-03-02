#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<time.h>
#include"atlstr.h"
#include<windows.h>
#include"REGISTER.h"
#include"PATIENT.h"
using namespace std;
string dptchoice;
int dptchoicetoint;
class Department{//�洢������Ϣ
public:
	string Floor;
	string Doctor;
	string Room;
	int allnum = 0;
	int existstatus[3000];
	string departmentname = "";
	string numbak;
	string idbak;
	bool HaveFinishedTreat = false;
	int linenumber = 0;
	bool waitingforpush = false;
	int searchrecordbak;
	string rootstr;
	void DepartmentSystem() {
		ifstream ROOT;
		char root[256];
		ROOT.open("config.txt");
		ROOT.getline(root, 3);
		const char* roottostring = root;
		rootstr = roottostring;
		ROOT.close();
		memset(existstatus, 0, 3000);
		string choice;
		int choicetoint;
		string op;
		ChooseDepartment();
		while (1) {
			cout << "#=======================================���ҹ���ϵͳ=========================================#" << endl;
			cout << "#==��ǰ���ң�";
			switch (dptchoicetoint) {
			case 1:
				cout << "�ǿ�============================================================================#";
				break;
			case 2:
				cout << "���============================================================================#";
				break;
			case 3:
				cout << "�ڿ�============================================================================#";
				break;
			case 4:
				cout << "����============================================================================#";
				break;
			case 5:
				cout << "����============================================================================#";
				break;
			case 6:
				cout << "�ۿ�============================================================================#";
				break;
			case 7:
				cout << "���Ǻ��========================================================================#";
				break;
			case 8:
				cout << "��ǻ��==========================================================================#";
				break;
			}
			cout << "\n#==1.�鿴�ȴ��������   2.����   3.�޸ľ����¼   4.�л�����   5.��ɵ�ǰ����   6.�˳�ϵͳ===#" << endl;
			cout << "#==��ѡ��";
			do
			{
				cin >> choice;
				choicetoint = atoi(choice.c_str());
				if (choicetoint <= 0 || choicetoint > 6) {
					cout << "�޷�ʶ�������ѡ����������룺";
				}
			} while (choicetoint <= 0 || choicetoint > 6);
			switch (choicetoint) {
			case 1:
				UpdateDptdb(dptchoicetoint);
				system("pause");
				system("cls");
				break;
			case 2:
				Treatment();
				break;
			case 3:
				ModifyTreatInfo();
				break;
			case 4:
				if (waitingforpush == true)
				{
					cout << "�������л����ң���ǰ���һ���δ���͵������Ϣ�����ȷ��͵���һ������֮���ٽ�������²��ˡ�" << endl;
					system("pause");
					system("cls");
				}
				else ChooseDepartment();
				break;
			case 5:
				FinishingTreat();
				break;
			case 6:
				if (waitingforpush == true)
				{
					cout << "���ڲ����˳�����ǰ����δ���͵������Ϣ�����ȷ��͵���һ������֮�����˳���" << endl;
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "�Ƿ�Ҫ�����������ҵĻ����ļ���(y/n)��";
					do {
						cin >> op;
						if (op != "n" && op != "y") {
							cout << "�����������������룺";
						}
					} while (op != "n" && op != "y");
					if (op == "n") {
						string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8;
						cmd1 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\ENT\\*.*";
						cmd2 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\IM\\*.*";
						cmd3 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\OaG\\*.*";
						cmd4 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\Ophtalmology\\*.*";
						cmd5 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\Orthopedic\\*.*";
						cmd6 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\Pediatrics\\*.*";
						cmd7 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\Stomatology\\*.*";
						cmd8 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\Surgery\\*.*";
						system(cmd1.c_str());
						system(cmd2.c_str());
						system(cmd3.c_str());
						system(cmd4.c_str());
						system(cmd5.c_str());
						system(cmd6.c_str());
						system(cmd7.c_str());
						system(cmd8.c_str());
						cout << "������ɡ�";
						system("pause");
						system("cls");
						return;
					}
					else if (op == "y") {
						return;
					}
				}
			}
		}
	}

private:
	void UpdateDptdb(int dptchoicetoint) {
		linenumber = 0;
		system("cls");
		ifstream DPTINFO;
		char info[256];
		string tmp;
		switch (dptchoicetoint) {
		case 1:
			departmentname = "Orthopedic";
			break;
		case 2:
			departmentname = "Surgery";
			break;
		case 3:
			departmentname = "IM";
			break;
		case 4:
			departmentname = "OaG";
			break;
		case 5:
			departmentname = "Pediatrics";
			break;
		case 6:
			departmentname = "Ophtalmology";
			break;
		case 7:
			departmentname = "ENT";
			break;
		case 8:
			departmentname = "Stomatology";
			break;
		}
		DPTINFO.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
		cout << "��ǰ��δ��ϵĲ����б�" << endl;
		while (DPTINFO.getline(info, 30)) {
			cout << "   " << info << endl;
			linenumber++;
		}
		DPTINFO.close();
	}

	void ChooseDepartment() {//ѡ�����
		system("cls");
		cout << "#=========================================���ҹ���ϵͳ==========================================#" << endl;
		cout << "#==1.�ǿ� 2.��� 3.�ڿ� 4.���� 5.���� 6.�ۿ� 7.���Ǻ�� 8.��ǻ��================================#" << endl;
		cout << "#==��ѡ����Ŀ��ң�";
		do {
			cin >> dptchoice;
			dptchoicetoint = atoi(dptchoice.c_str());
			if (dptchoicetoint <= 0 || dptchoicetoint > 8)
				cout << "�������Ϣ�������������룺";
		} while (dptchoicetoint <= 0 || dptchoicetoint > 8);
		system("cls");
	}

	void Treatment() {//����
		if (waitingforpush == true)
		{
			cout << "��ǰ����δ���͵������Ϣ�����ȷ��͵���һ������֮���ٽ�������²��ˡ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		allnum++;
		SYSTEMTIME st;//���屾��ʱ��������ñ���Ϊ�ṹ��
		GetLocalTime(&st);//��ȡ����ʱ�亯��������Ϊʱ�����ָ��
		int year = st.wYear;
		int month = st.wMonth;
		int day = st.wDay;
		string years, months, days;
		years = to_string(static_cast<long long>(year));
		months = to_string(static_cast<long long>(month));
		days = to_string(static_cast<long long>(day));
		string disease;
		string diseasecode;
		cout << "Ŀǰ�Ĳ��˶��У�" << endl;
		UpdateDptdb(dptchoicetoint);
		ifstream PATIENTLISTCHECK;
		ofstream PATIENTTREAT;
		ifstream PATIENTREAD;
		string selectpatient;//��ѡ���˵ĹҺ����
		int selectpatientint;//ת����int���͵ĹҺ����
		char id[30];//���֤��Ϣ
		char patienthis[256];//������ʷ��¼�鿴
		int searchrecord = 0;//������¼ѡ��
		int lineint;
		int flag;
		string cmd2;
		do {
			ifstream PATIENTLISTCHECK;
			PATIENTLISTCHECK.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
			char str[2];
			PATIENTLISTCHECK.getline(str, 2);
			if (!PATIENTLISTCHECK.is_open() || str[0] == '\0') {
				cout << "��ǰû�в�����Ҫ��ϡ�" << endl;
				system("pause");
				system("cls");
				PATIENTLISTCHECK.close();
				return;
			}
			else
			{
				PATIENTLISTCHECK.close();
				PATIENTLISTCHECK.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
				cout << "��ѡ�����Ĳ�����ţ�";
				cin >> selectpatient;
				selectpatientint = atoi(selectpatient.c_str());
				while (!PATIENTLISTCHECK.eof()) {
					char line[256];//ԭ�ַ������и�֮���ɹҺ����
					PATIENTLISTCHECK.getline(line, 30);
					if (line[0] == '\0') break;
					else {
						strtok(line, "_");
						strcpy(id, strtok(NULL, "_"));
						lineint = atoi(line);
					}
					if (lineint == selectpatientint) {
						flag = 1;
						break;
					}
					else flag = 0;
					searchrecord++;
				}
				if (flag) break;
				if (searchrecord >= linenumber) {
					cout << "�Ҳ�����ѡ�Ĳ��ˣ�������ѡ���˵ĹҺ���ţ�";
				}
				PATIENTLISTCHECK.close();
			}
		} while (searchrecord >= linenumber);
		PATIENTREAD.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + selectpatient + "_" + id + "_db.txt");
		if (!PATIENTREAD.is_open()) {
			cout << "�޷��ҵ��������ݿ��ļ���" << endl;
		}
		else {
			cout << "�ɹ���ȡ�������ݿ��ļ����ļ���Ŀǰ����������Ϊ��" << endl;
			while (PATIENTREAD.getline(patienthis, 256)) {
				cout << "   " << patienthis << endl;
			}
			PATIENTREAD.close();
			PATIENTTREAT.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + selectpatient + "_" + id + "_db.txt", ios::app);
			cout << "������˲��˵Ĳ�����";
			cin >> disease;
			PATIENTTREAT << "[" << years << months << days << "]" << "TreatRecord:" << disease << endl;
			cout << "������˲��˵Ĳ�֢���ţ�";
			cin >> diseasecode;
			PATIENTTREAT << "Illness:" << diseasecode << endl;
			cout << "������ɣ��ȴ����͡�" << endl;
			waitingforpush = true;
			system("pause");
			PATIENTTREAT.close();
			system("cls");
			numbak = selectpatient;
			idbak = id;
		}
		searchrecordbak = searchrecord;
		HaveFinishedTreat = true;
	}

	void ModifyTreatInfo() {
		system("cls");
		ifstream PATIENTLISTCHECK;
		PATIENTLISTCHECK.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
		char str[2];
		PATIENTLISTCHECK.getline(str, 2);
		if (!PATIENTLISTCHECK.is_open() || str[0] == '\0') {
			cout << "��ǰû�в�����Ҫ��ϡ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "ʹ��˵������Ҫ�޸Ĳ�����Ϣ������TreatRecord��ð�ź�������޸ģ�" << endl;
			cout << "��Ҫ�޸Ŀ�ҩ��Ϣ������Illness��ð�ź�������޸ġ�" << endl;
			cout << "�벻Ҫ�޸ĳ����������κ���Ϣ��Ҳ��Ҫ��������ɾ�У�" << endl;
			cout << "�޸�֮����ǵñ����ļ���" << endl;
			system("pause");
			cout << endl;
			cout << "���ڵ����ⲿ�ı��༭�����б༭..." << endl;
			string cmd;
			cmd = "Notepad.exe " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt";
			system(cmd.c_str());
			cout << "������ɣ�";
			system("pause");
			system("cls");
			return;
		}
	}

	void FinishingTreat() {
		if (HaveFinishedTreat) {
			bool WhetherLiveIn, WhetherNeedDrug;
			string cmd, cmd2, cmd3, cmd4;
			system("cls");
			cout << "�˲����Ƿ���Ҫ����ҩ�1Ϊ�ǣ�0Ϊ�񣩣�";
			cin >> WhetherNeedDrug;
			if (WhetherNeedDrug) {
				cmd = "copy " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Need_Drug";
				system(cmd.c_str());
				ofstream NEEDDRUG;
				NEEDDRUG.open(rootstr + "\\PMS_Data\\Patient_Need_Drug\\NEEDDRUG.txt", ios::app);
				NEEDDRUG << numbak << "_" << idbak << endl;
				NEEDDRUG.close();
			}
			cout << "�˲����Ƿ���ҪסԺ��1Ϊ�ǣ�0Ϊ�񣩣�";
			cin >> WhetherLiveIn;
			if (WhetherLiveIn) {
				cmd = "copy " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Need_Livein";
				system(cmd.c_str());
				ofstream NEEDLIVEIN;
				NEEDLIVEIN.open(rootstr + "\\PMS_Data\\Patient_Need_Livein\\NEEDLIVEIN.txt", ios::app);
				NEEDLIVEIN << numbak << "_" << idbak << endl;
				NEEDLIVEIN.close();
			}
			cmd = "copy " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Treatment_Record";
			system(cmd.c_str());
			cmd = "rename " + rootstr + "\\PMS_Data\\Patient_Treatment_Record\\" + numbak + "_" + idbak + "_db.txt " + idbak + ".txt";
			system(cmd.c_str());
			ifstream READRAWLIST;
			ofstream UPDATELIST;
			READRAWLIST.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
			UPDATELIST.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST_BAK.txt");
			char str[256];
			int count = 0;
			while (!READRAWLIST.eof()) {
				READRAWLIST.getline(str, 30);
				if (count != searchrecordbak && str[0] != '\0') {
					UPDATELIST << str << endl;
				}
				count++;
			}
			READRAWLIST.close();
			cmd2 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt";
			system(cmd2.c_str());
			UPDATELIST.close();
			cmd3 = "rename " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST_BAK.txt PATIENTLIST.txt";
			system(cmd3.c_str());
			cout << "�ɹ������ļ���" << endl;
			cmd4 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt";
			system(cmd4.c_str());
			system("pause");
			system("cls");
			waitingforpush = false;
		}
		else
		{
			system("cls");
			cout << "Ŀǰû����Ҫ���͵Ĳ�����Ϣ����ȷ���Ƿ����Ѿ���Ϲ��Ĳ��ˣ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		HaveFinishedTreat = false;
	}
};
#endif