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
class Department{//存储科室信息
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
			cout << "#=======================================科室管理系统=========================================#" << endl;
			cout << "#==当前科室：";
			switch (dptchoicetoint) {
			case 1:
				cout << "骨科============================================================================#";
				break;
			case 2:
				cout << "外科============================================================================#";
				break;
			case 3:
				cout << "内科============================================================================#";
				break;
			case 4:
				cout << "妇科============================================================================#";
				break;
			case 5:
				cout << "儿科============================================================================#";
				break;
			case 6:
				cout << "眼科============================================================================#";
				break;
			case 7:
				cout << "耳鼻喉科========================================================================#";
				break;
			case 8:
				cout << "口腔科==========================================================================#";
				break;
			}
			cout << "\n#==1.查看等待就诊队列   2.就诊   3.修改就诊记录   4.切换科室   5.完成当前就诊   6.退出系统===#" << endl;
			cout << "#==请选择：";
			do
			{
				cin >> choice;
				choicetoint = atoi(choice.c_str());
				if (choicetoint <= 0 || choicetoint > 6) {
					cout << "无法识别输入的选项，请重新输入：";
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
					cout << "您不能切换科室，当前科室还有未发送的诊断信息，请先发送到下一个部门之后再进行诊断新病人。" << endl;
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
					cout << "现在不能退出，当前还有未发送的诊断信息，请先发送到下一个部门之后再退出。" << endl;
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "是否要保留所有诊室的缓存文件？(y/n)：";
					do {
						cin >> op;
						if (op != "n" && op != "y") {
							cout << "输入有误，请重新输入：";
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
						cout << "清理完成。";
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
		cout << "当前尚未诊断的病人列表：" << endl;
		while (DPTINFO.getline(info, 30)) {
			cout << "   " << info << endl;
			linenumber++;
		}
		DPTINFO.close();
	}

	void ChooseDepartment() {//选择科室
		system("cls");
		cout << "#=========================================科室管理系统==========================================#" << endl;
		cout << "#==1.骨科 2.外科 3.内科 4.妇科 5.儿科 6.眼科 7.耳鼻喉科 8.口腔科================================#" << endl;
		cout << "#==请选择你的科室：";
		do {
			cin >> dptchoice;
			dptchoicetoint = atoi(dptchoice.c_str());
			if (dptchoicetoint <= 0 || dptchoicetoint > 8)
				cout << "输入的信息有误，请重新输入：";
		} while (dptchoicetoint <= 0 || dptchoicetoint > 8);
		system("cls");
	}

	void Treatment() {//就诊
		if (waitingforpush == true)
		{
			cout << "当前还有未发送的诊断信息，请先发送到下一个部门之后再进行诊断新病人。" << endl;
			system("pause");
			system("cls");
			return;
		}
		allnum++;
		SYSTEMTIME st;//定义本地时间变量，该变量为结构体
		GetLocalTime(&st);//获取本地时间函数，参数为时间变量指针
		int year = st.wYear;
		int month = st.wMonth;
		int day = st.wDay;
		string years, months, days;
		years = to_string(static_cast<long long>(year));
		months = to_string(static_cast<long long>(month));
		days = to_string(static_cast<long long>(day));
		string disease;
		string diseasecode;
		cout << "目前的病人队列：" << endl;
		UpdateDptdb(dptchoicetoint);
		ifstream PATIENTLISTCHECK;
		ofstream PATIENTTREAT;
		ifstream PATIENTREAD;
		string selectpatient;//所选病人的挂号序号
		int selectpatientint;//转换成int类型的挂号序号
		char id[30];//身份证信息
		char patienthis[256];//病人历史记录查看
		int searchrecord = 0;//搜索记录选项
		int lineint;
		int flag;
		string cmd2;
		do {
			ifstream PATIENTLISTCHECK;
			PATIENTLISTCHECK.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
			char str[2];
			PATIENTLISTCHECK.getline(str, 2);
			if (!PATIENTLISTCHECK.is_open() || str[0] == '\0') {
				cout << "当前没有病人需要诊断。" << endl;
				system("pause");
				system("cls");
				PATIENTLISTCHECK.close();
				return;
			}
			else
			{
				PATIENTLISTCHECK.close();
				PATIENTLISTCHECK.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\PATIENTLIST.txt");
				cout << "请选择就诊的病人序号：";
				cin >> selectpatient;
				selectpatientint = atoi(selectpatient.c_str());
				while (!PATIENTLISTCHECK.eof()) {
					char line[256];//原字符串，切割之后变成挂号序号
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
					cout << "找不到所选的病人，请重新选择病人的挂号序号：";
				}
				PATIENTLISTCHECK.close();
			}
		} while (searchrecord >= linenumber);
		PATIENTREAD.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + selectpatient + "_" + id + "_db.txt");
		if (!PATIENTREAD.is_open()) {
			cout << "无法找到病人数据库文件！" << endl;
		}
		else {
			cout << "成功读取病人数据库文件，文件中目前包含的内容为：" << endl;
			while (PATIENTREAD.getline(patienthis, 256)) {
				cout << "   " << patienthis << endl;
			}
			PATIENTREAD.close();
			PATIENTTREAT.open(rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + selectpatient + "_" + id + "_db.txt", ios::app);
			cout << "请输入此病人的病历：";
			cin >> disease;
			PATIENTTREAT << "[" << years << months << days << "]" << "TreatRecord:" << disease << endl;
			cout << "请输入此病人的病症代号：";
			cin >> diseasecode;
			PATIENTTREAT << "Illness:" << diseasecode << endl;
			cout << "就诊完成，等待发送。" << endl;
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
			cout << "当前没有病人需要诊断。" << endl;
			system("pause");
			system("cls");
			return;
		}
		else {
			cout << "使用说明：若要修改病历信息，请在TreatRecord的冒号后面进行修改；" << endl;
			cout << "若要修改开药信息，请在Illness的冒号后面进行修改。" << endl;
			cout << "请不要修改除这两处的任何信息！也不要随意增、删行！" << endl;
			cout << "修改之后请记得保存文件！" << endl;
			system("pause");
			cout << endl;
			cout << "正在调用外部文本编辑器进行编辑..." << endl;
			string cmd;
			cmd = "Notepad.exe " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt";
			system(cmd.c_str());
			cout << "任务完成！";
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
			cout << "此病人是否需要购买药物（1为是，0为否）：";
			cin >> WhetherNeedDrug;
			if (WhetherNeedDrug) {
				cmd = "copy " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Need_Drug";
				system(cmd.c_str());
				ofstream NEEDDRUG;
				NEEDDRUG.open(rootstr + "\\PMS_Data\\Patient_Need_Drug\\NEEDDRUG.txt", ios::app);
				NEEDDRUG << numbak << "_" << idbak << endl;
				NEEDDRUG.close();
			}
			cout << "此病人是否需要住院（1为是，0为否）：";
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
			cout << "成功发送文件！" << endl;
			cmd4 = "del " + rootstr + "\\PMS_Data\\Department_Queue_db\\" + departmentname + "\\" + numbak + "_" + idbak + "_db.txt";
			system(cmd4.c_str());
			system("pause");
			system("cls");
			waitingforpush = false;
		}
		else
		{
			system("cls");
			cout << "目前没有需要发送的病人信息，请确认是否有已经诊断过的病人！" << endl;
			system("pause");
			system("cls");
			return;
		}
		HaveFinishedTreat = false;
	}
};
#endif