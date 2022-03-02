#pragma once
#ifndef REGISTER_H
#define REGISTER_H

#include<iostream>
#include"PATIENT.h"
#include<fstream>
#include<string>
#include<cstring>
#include"atlstr.h"
#include"DEPARTMENT.h"
#define MAXLENGTH 3000
using namespace std;

class Register{
public:
	int i = 0;//单次启动系统挂号记录
	Patient patient[MAXLENGTH];//病人临时数组
	Department Orthopedic;//骨科
	Department Surgery;//外科
	Department IM;//内科
	Department OaG;//妇科
	Department Pediatrics;//儿科
	Department Ophtalmology;//眼科
	Department ENT;//耳鼻喉科
	Department Stomatology;//口腔科
	string rootstr;
	int RegisterSystem()//挂号系统
	{
		ifstream ROOT;
		char root[256];
		ROOT.open("config.txt");
		ROOT.getline(root, 3);
		const char* roottostring = root;
		rootstr = roottostring;
		ROOT.close();
		system("color 7");
		InitDepartment();
		string operation;
		int operationtoint;
		string op;
		while (1) {
			cout << "#=========================挂号系统=========================#" << endl;
			cout << "#==请选择执行任务：========================================#" << endl;
			cout << "#==1.挂号   2.删除挂号信息   3.查询历史挂号   4.关闭系统===#" << endl << "#==请选择：";
			do {
				cin >> operation;
				operationtoint = atoi(operation.c_str());
				if (operationtoint <= 0 || operationtoint > 4)
					cout << "输入的信息有误，请重新输入：";
			} while (operationtoint <= 0 || operationtoint > 4);
			system("cls");
			switch (operationtoint) {
			case 1:
				RegNewPatient();
				break;
			case 2:
				ModifyRegInfo();
				break;
			case 3:
				ShowHistoryReg();
				break;
			case 4:
				cout << "程序即将退出，请问是否保留挂号数据？(y/n)：";
				do {
					cin >> op;
					if (op != "n" && op != "y") {
						cout << "输入有误，请重新输入：";
					}
				} while (op != "n" && op != "y");
				if (op == "n") {
					ClearFiles();
					return 0;
				}
				else if (op == "y") {
					return 0;
				}
			}
		}
	}
	void ShowDepartment() {
		InitDepartment();
	}
private:
	void InitDepartment() {//初始化各科室信息
		Orthopedic.Floor = "1";
		Orthopedic.Doctor = "张尹晨";
		Orthopedic.Room = "101";
		Surgery.Floor = "1";
		Surgery.Doctor = "李晓明";
		Surgery.Room = "102";
		IM.Floor = "2";
		IM.Doctor = "沈润洁";
		IM.Room = "201";
		OaG.Floor = "2";
		OaG.Doctor = "梅芸霖";
		OaG.Room = "202";
		Pediatrics.Floor = "3";
		Pediatrics.Doctor = "宁霞";
		Pediatrics.Room = "301";
		Ophtalmology.Floor = "3";
		Ophtalmology.Doctor = "黄征齐";
		Ophtalmology.Room = "302";
		ENT.Floor = "4";
		ENT.Doctor = "严军辉";
		ENT.Room = "401";
		Stomatology.Floor = "4";
		Stomatology.Doctor = "李彩云";
		Stomatology.Room = "402";
	}
	void RegNewPatient()//挂号
	{
		int departmenttoint;
		string cmd;//用于命令提示符识别
		char act[256];//string cmd转换为命令提示符可以识别的char
		system("color 7");//修改颜色
		if (i > 2800) {//检查内存状态是否将满
			cout << "提示：当前内存缓冲区将满，请关闭程序以清理缓存，以保证程序之后正常运行。" << endl;
		}
		i++;//新增病人和挂号
		patient[i].status = 1;//默认病人为已挂号
		string filenumber = "";//用于打开文件识别文件名
		ofstream FILE;//文件流
		ofstream INFO;
		ofstream INFO01;
		ofstream INFO02;
		ofstream INFO03;
		ofstream INFO04;
		ofstream INFO05;
		ofstream INFO06;
		ofstream INFO07;
		ofstream INFO08;
		INFO.open(rootstr + "\\PMS_Data\\Patientinfolist.txt", ios_base::app);
		int sex;//临时性别
		int department;//临时科室
		filenumber = to_string(static_cast<long long>(i));//挂号号码强制转换string
		cout << "当前任务：挂号" << endl;
		cout << "当前病人序号为：" << i << endl;
		cout << "请输入病人的身份证号码：";
		cin >> patient[i].ID;//从界面请求身份证号码
		FILE.open(rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt");//以挂号_身份证号码为格式创建病人挂号信息文件
		INFO << filenumber << "_" << patient[i].ID << endl;
		INFO.close();
		FILE << "Number:" << i << endl;//写入病人挂号
		FILE << "ID:" << patient[i].ID << endl;//身份证号码流入文件
		cout << "请输入病人的姓名：";
		cin >> patient[i].name;//从界面请求姓名
		FILE << "Name:" << patient[i].name << endl;//姓名流入文件
		cout << "请输入病人的性别（1为男，0为女）：";
		do {
			cin >> sex;
			if (sex != 0 && sex != 1)
				cout << "输入的信息有误，请重新输入：";
		} while (sex != 0 && sex != 1);//校验输入正确性
		patient[i].sex = sex;//正确输入传入病人数组性别对象
		if (patient[i].sex == 1)//1为男性
			FILE << "Sex:男" << endl;
		if (patient[i].sex == 0)//2为女性
			FILE << "Sex:女" << endl;
		cout << "请输入挂号的科室：" << endl;
		cout << "1.骨科 2.外科 3.内科 4.妇科 5.儿科 6.眼科 7.耳鼻喉科 8.口腔科" << endl;
		cout << "请输入选项：";
		do {
			cin >> patient[i].department;
			departmenttoint = atoi(patient[i].department.c_str());
			if (departmenttoint <= 0 || departmenttoint > 8)
				cout << "输入的信息有误，请重新输入：";
		} while (departmenttoint <= 0 || departmenttoint > 8);
		switch (departmenttoint) {//检查输入合法性
		case 1:
			INFO01.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Orthopedic\\PATIENTLIST.txt", ios::app);
			FILE << "Department:骨科" << endl;
			cout << "\n您选择的是：骨科" << endl;
			cout << "楼层：" << Orthopedic.Floor << endl;
			cout << "医生：" << Orthopedic.Doctor << endl;
			cout << "科室：" << Orthopedic.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Orthopedic";
			strcpy(act, cmd.c_str());
			INFO01 << filenumber << "_" << patient[i].ID << endl;
			INFO01.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 2:
			INFO02.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Surgery\\PATIENTLIST.txt", ios::app);
			FILE << "Department:外科" << endl;
			cout << "\n您选择的是：外科" << endl;
			cout << "楼层：" << Surgery.Floor << endl;
			cout << "医生：" << Surgery.Doctor << endl;
			cout << "科室：" << Surgery.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Surgery";
			strcpy(act, cmd.c_str());
			INFO02 << filenumber << "_" << patient[i].ID << endl;
			INFO02.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 3:
			INFO03.open(rootstr + "\\PMS_Data\\Department_Queue_db\\IM\\PATIENTLIST.txt", ios::app);
			FILE << "Department:内科" << endl;
			cout << "\n您选择的是：内科" << endl;
			cout << "楼层：" << IM.Floor << endl;
			cout << "医生：" << IM.Doctor << endl;
			cout << "科室：" << IM.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\IM";
			strcpy(act, cmd.c_str());
			INFO03 << filenumber << "_" << patient[i].ID << endl;
			INFO03.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 4:
			INFO04.open(rootstr + "\\PMS_Data\\Department_Queue_db\\OaG\\PATIENTLIST.txt", ios::app);
			FILE << "Department:妇科" << endl;
			cout << "\n您选择的是：妇科" << endl;
			cout << "楼层：" << OaG.Floor << endl;
			cout << "医生：" << OaG.Doctor << endl;
			cout << "科室：" << OaG.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\OaG";
			strcpy(act, cmd.c_str());
			INFO04 << filenumber << "_" << patient[i].ID << endl;
			INFO04.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 5:
			INFO05.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Pediatrics\\PATIENTLIST.txt", ios::app);
			FILE << "Department:儿科" << endl;
			cout << "\n您选择的是：儿科" << endl;
			cout << "楼层：" << Pediatrics.Floor << endl;
			cout << "医生：" << Pediatrics.Doctor << endl;
			cout << "科室：" << Pediatrics.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Pediatrics";
			strcpy(act, cmd.c_str());
			INFO05 << filenumber << "_" << patient[i].ID << endl;
			INFO05.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 6:
			INFO06.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Ophtalmology\\PATIENTLIST.txt", ios::app);
			FILE << "Department:眼科" << endl;
			cout << "\n您选择的是：眼科" << endl;
			cout << "楼层：" << Ophtalmology.Floor << endl;
			cout << "医生：" << Ophtalmology.Doctor << endl;
			cout << "科室：" << Ophtalmology.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Ophtalmology";
			strcpy(act, cmd.c_str());
			INFO06 << filenumber << "_" << patient[i].ID << endl;
			INFO06.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 7:
			INFO07.open(rootstr + "\\PMS_Data\\Department_Queue_db\\ENT\\PATIENTLIST.txt", ios::app);
			FILE << "Department:耳鼻喉科" << endl;
			cout << "\n您选择的是：耳鼻喉科" << endl;
			cout << "楼层：" << ENT.Floor << endl;
			cout << "医生：" << ENT.Doctor << endl;
			cout << "科室：" << ENT.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\ENT";
			strcpy(act, cmd.c_str());
			INFO07 << filenumber << "_" << patient[i].ID << endl;
			INFO07.close();
			system(act);//传递病人信息到科室文件夹
			break;
		case 8:
			INFO08.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Stomatology\\PATIENTLIST.txt", ios::app);
			FILE << "Department:口腔科" << endl;
			cout << "\n您选择的是：口腔科" << endl;
			cout << "楼层：" << Stomatology.Floor << endl;
			cout << "医生：" << Stomatology.Doctor << endl;
			cout << "科室：" << Stomatology.Room << endl << endl;//打印科室信息到屏幕
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Stomatology";
			strcpy(act, cmd.c_str());
			INFO08 << filenumber << "_" << patient[i].ID << endl;
			INFO08.close();
			system(act);//传递病人信息到科室文件夹
			break;
		}
		system("color a");
		cout << "挂号完成！请下一位病人挂号!" << endl << endl;
		FILE.close();//完成挂号过程
		system("pause");
		system("cls");
		system("color 7");//UI界面动效与优化
	}
	void ModifyRegInfo()//删除挂号信息
	{
		string cmd;//用于命令提示符识别
		string filenumber = "";
		char act[256];//string cmd转换为命令提示符可以识别的char
		system("color 7");
		string p;//p为病人挂号号码
		int ptoint;
		cout << "请输入想要删除信息的病人挂号号码（输入-100以退出）：";
		do
		{
			cin >> p;
			ptoint = atoi(p.c_str());
			if (ptoint != -100) {
				if (ptoint <= 0 || ptoint > i || patient[ptoint].status == 0) {
					cout << "指定的病人不存在，请重新输入：";
				}
			}
			if (ptoint == -100) {
				break;
			}
		} while (ptoint <= 0 || ptoint > i || patient[ptoint].status == 0);//检查输入合法性以及病人挂号信息是否存在判断
		filenumber = to_string(static_cast<long long>(ptoint));//挂号号码强制转换string
		if (ptoint != -100) {
			cout << "确定要删除此病人的挂号信息吗？删除后，此文件将不可恢复！";
			system("pause");
			cout << endl;
			cmd = "del " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[ptoint].ID + "_db.txt";
			strcpy(act, cmd.c_str());
			system(act);//删除病人信息文件
			system("color a");
			cout << "此挂号信息已被删除。";
			patient[ptoint].status = 0;
			system("pause");
			system("cls");
			system("color 7");
		}
		if (ptoint == -100) {//模块退出
			system("color a");
			cout << "模块退出。";
			system("pause");
			system("cls");
			system("color 7");
		}
	}
	void ShowHistoryReg() //查询历史挂号
	{
		system("color 7");
		cout << "当前已经挂号人数：" << i << endl;
		cout << "挂号详情：" << endl;
		for (int t = 1; t <= i; t++) {
			if (patient[t].status) {//判断挂号文件是否存在，以防读取时出现问题
				ifstream FILE;
				string filenumber = "";
				char data[65535];
				CString cdata = "";
				filenumber = to_string(static_cast<long long>(t));
				FILE.open(rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[t].ID + "_db.txt");
				while (!FILE.eof())
				{
					FILE.getline(data, 65535);
					cdata = data + cdata;
					cout << "   " << data << endl;
				}
				cout << endl;
				FILE.close();//全部打印文件内容到屏幕上
			}
		}
		system("pause");
		system("cls");
		system("color 7");
	}
	void ClearFiles() {
		system("color 7");
		cout << "正在清理...";
		
		string cmd;
		cmd = "del " + rootstr + "\\PMS_data\\Patient_db\\*.*";
		system(cmd.c_str());
		
		cout << "清理完成！";
		
		system("pause");
		system("cls");
		system("color 7");
	}
};
#endif