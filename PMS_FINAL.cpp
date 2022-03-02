#define _CRT_SECURE_NO_WARNINGS
#include "WARD.h"
#include "REGISTER.h"
#include "PATIENT.h"
#include "DRUG.h"
#include <iostream>
#include <windows.h>
using namespace std;
int main()
{
	while (1) {//防止意外退出
		cout << "#===============================欢迎使用患者管理系统===============================#" << endl;
		string root;//定义系统文件夹根目录
		ifstream CHKIFROOTED;//用于检查目录是否创建
		CHKIFROOTED.open("config.txt");//尝试打开配置文件
		if (!CHKIFROOTED.is_open()) {//若配置文件不存在
			CHKIFROOTED.close();
			cout << "#==正在初始化..." << endl;
			cout << "#==请输入患者管理系统的文件存放路径（尽量选取磁盘根目录，例如D:）：";
			cin >> root;//选取系统文件夹根目录
			ofstream ROOT;//预备写入根目录数据的文件流
			ROOT.open("config.txt");//将根目录配置写入文件，以便后续模块读取
			ROOT << root;//写入根目录路径
			ROOT.close();
			cout << "正在创建目录..." << endl;
			string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8, cmd9, cmd10, cmd11, cmd12;
			cmd1 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\ENT";
			system(cmd1.c_str());
			cmd2 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\IM";
			system(cmd2.c_str());
			cmd3 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\OaG";
			system(cmd3.c_str());
			cmd4 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\Ophtalmology";
			system(cmd4.c_str());
			cmd5 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\Orthopedic";
			system(cmd5.c_str());
			cmd6 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\Pediatrics";
			system(cmd6.c_str());
			cmd7 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\Stomatology";
			system(cmd7.c_str());
			cmd8 = "mkdir " + root + "\\PMS_Data\\Department_Queue_db\\Surgery";
			system(cmd8.c_str());
			cmd9 = "mkdir " + root + "\\PMS_Data\\Patient_db";
			system(cmd9.c_str());
			cmd10 = "mkdir " + root + "\\PMS_Data\\Patient_Need_Drug";
			system(cmd10.c_str());
			cmd11 = "mkdir " + root + "\\PMS_Data\\Patient_Need_Livein\\Livingin";
			system(cmd11.c_str());
			cmd12 = "mkdir " + root + "\\PMS_Data\\Patient_Treatment_Record";
			system(cmd12.c_str());
			cout << "创建任务结束。";//创建目录
			Sleep(2000);
		}
		else {
			CHKIFROOTED.close();
			ifstream ROOT;//创建配置文件读取
			string rootstr;//记录配置文件中根目录位置
			char root[256];//读取行用
			ROOT.open("config.txt");//打开配置文件
			ROOT.getline(root, 3);//读取配置文件
			const char* roottostring = root;//配置根目录
			rootstr = roottostring;//记录根目录标记
			ROOT.close();
			system("cls");
			string select;//以字符串方式的输入选项，避免崩溃
			int selecttoint;//转换字符串到整形
			Department dpt;//设置一个科室
			Register reg;//设置挂号室
			Ward wd;//设置病房
			string op;//退出时选项
			while (1) {
				system("cls");
				reg.ShowDepartment();//部署科室
				cout << "#===============================欢迎使用患者管理系统===============================#" << endl;
				cout << "#==制作人：吴恺诚、赵柯、楚义、景晨宇================景科橙逸软件公司   版权所有===#" << endl;
				cout << "#================1.挂号室   2.诊室   3.药房   4.病房   5.关闭系统==================#" << endl;
				cout << "#==请选择要进入的模块：";
				do {
					cin >> select;
					selecttoint = atoi(select.c_str());//转换输入字符为整型
					if (selecttoint <= 0 || selecttoint > 5)
						cout << "输入的信息有误，请重新输入：";
				} while (selecttoint <= 0 || selecttoint > 5);//输入正确性判断
				switch (selecttoint) {//切换选项
				case 1:
					system("cls");
					reg.RegisterSystem();//挂号室子系统
					break;
				case 2:
					system("cls");
					dpt.DepartmentSystem();//科室子系统
					break;
				case 3:
					system("cls");
					Pharmacy();//药房子系统
					break;
				case 4:
					system("cls");
					wd.WardSystem();//病房子系统
					break;
				case 5:
					system("cls");
					cout << "系统即将退出，请问是否需要保留缓存文件？（建议删除）(y/n):";
					do {
						cin >> op;
						if (op != "n" && op != "y") {
							cout << "输入有误，请重新输入：";
						}
					} while (op != "n" && op != "y");//输入正确性判断
					if (op == "n") {
						string cmd;
						cmd = "rmdir /s " + rootstr + "\\PMS_Data";//删除数据文件夹
						system(cmd.c_str());
						cout << "清理完成。";
						system("pause");
						system("cls");
					}
					cout << "景科橙逸软件公司 出品" << endl;
					system("del config.txt");//删除配置文件
					Sleep(3000);
					exit(0);
				}
			}
		}
	}
	return 0;
}