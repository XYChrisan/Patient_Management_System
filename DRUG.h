#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
char takenid[30];
string takenidtostr;
class Drug:public Patient
{
public:
	string name;
	int number;
	string illness;
	double price;
	Drug(string name, int number, string illness, double price) {
		this->name = name;
		this->number = number;
		this->illness = illness;
		this->price = price;
	}
	void showDrug() {
		cout << "药品:" << setw(18) << this->name << "  ";
		cout << "数量:" << this->number << endl;
	}//输出药品信息
	void outDrug(string id[]) {
		int k = 0;
		int i;
		while (id[k] != "") {
			ifstream file;
			ofstream writeinfo;
			string information;
			string illness;
			string name;
			string txt = rootstr + "\\PMS_Data\\Patient_Need_Drug\\" + id[k] + "_db.txt";
			string delet;
			file.open(txt, ios::in);
			while (getline(file, information)) {
				name = information.substr(0, 5);
				if (name == "Name:")
				{
					name = information.erase(0, 5);
					break;
				}
			}
			while (getline(file, information)) {
				illness = information.substr(0, 8);
				if (illness == "Illness:") {
					illness = information.erase(0, 8);
					for (i = 0; i < 24; i++) {
						if (illness == this->illness) {
							system("cls");
							this->number--;
							cout << "开药信息__";
							cout << "姓名:" << name << " 药品:" << this->name;
							cout << " 请支付:" << this->price << "元" << endl;
							file.close();
							writeinfo.open(txt);
							writeinfo << "Medicine:" << this->name << endl << "Price:" << this->price << endl;
							writeinfo.close();
							takenidtostr = takenid;
							string movefile = "copy " + rootstr + "\\PMS_Data\\Patient_Treatment_Record\\" + takenidtostr + ".txt+" + rootstr + "\\PMS_Data\\Patient_Need_Drug\\" + id[k] + "_db.txt " + rootstr + "\\PMS_Data\\Patient_Treatment_Record\\" + takenidtostr + ".txt";
							system(movefile.c_str());
							system("pause");
							system("cls");
							delet = "del " + txt;
							system(delet.c_str());
							break;
						}
					}
				}
			}
			k++;
		}
	}
};
void showAllDrug(Drug* drug[]) {
	system("cls");
	int i;
	string name;
	cout << "各种药品的库存:" << endl;
	for (i = 0; i < 24; i++) {
		drug[i]->showDrug();
	}
}//展示药品

void getid(string id[]) {
	int i = 0;
	ifstream file;
	string id1;
	char takeid[30];
	string txt = rootstr + "\\PMS_Data\\Patient_Need_Drug\\NEEDDRUG.txt";
	file.open(txt, ios::in);
	if (!file.is_open())
	{
		cout << "病人文件不存在或损坏" << endl;
		return;
	}
	while (getline(file, id1)) {
		if (id1 == "") break;
		id[i] = id1;
		strcpy(takeid, id1.c_str());
		strtok(takeid, "_");
		strcpy(takenid, strtok(NULL, "_"));
		i++;
	}
}//读取病人文件名

void addDrug(Drug* drug[]) {
	int i, j, k = 0, number;
	string n;
	int ntoint;
	string yes, name;
	cout << "=========================================药品库存已展示，是否添加药品？（y/n）=========================================" << endl;
	do {
		cin >> yes;
		if (yes != "n" && yes != "y") {
			cout << "输入有误，请重新输入：";
		}
	} while (yes != "n" && yes != "y");
	if (yes == "n") {
		system("cls");
		return;
	}
	else if (yes == "y") {
		cout << "请输入添加药品种类数(1-24)：";
		do
		{
			cin >> n;
			ntoint = atoi(n.c_str());
			if (ntoint <= 0 || ntoint > 24) {
				cout << "无法识别输入的选项，请重新输入：";
			}
		} while (ntoint <= 0 || ntoint > 24);
		for (j = 0; j < ntoint; j++) {
			cout << "添加药品名：";
			cin >> name;
			while (name != "克林霉素" && name != "万古霉素" && name != "利福平" && name != "止疼药" && name != "999皮炎平" && name != "氨甲环酸" && name != "蒲地蓝口服液" && name != "头孢丙烯片" && name != "阿司匹林"
				&& name != "甲硝锉" && name != "左氧氟沙星片" && name != "抗宫炎片" && name != "小儿伤风速效冲剂" && name != "小儿止咳糖浆" && name != "阿莫斯" && name != "红霉素软膏" && name != "黄连上清丸"
				&& name != "板蓝根" && name != "鼻炎宁颗粒" && name != "氯雷他定片" && name != "鼻立通" && name != "999止疼药" && name != "头孢克肟片" && name != "麻醉药") {
				cout << "输入药名错误，请重新输入添加药品名：";
				cin >> name;
			}
			cout << "添加药品数量：";
			cin >> number;
			for (i = 0; i < 24; i++) {
				if (drug[i]->name == name) {
					drug[i]->number += number;
					cout << "加药成功！" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
		}
	}
}

void outAllDrug(Drug* drug[], string id[]) {
	int i;
	for (i = 0; i < 24; i++) {
		drug[i]->outDrug(id);
	}
}//添加药品

void Pharmacy() {
	ifstream ROOT;
	char root[256];
	ROOT.open("config.txt");
	ROOT.getline(root, 3);
	const char* roottostring = root;
	rootstr = roottostring;
	ROOT.close();
	string id[300] = { "" };
	Drug* drug[24];
	drug[0] = new Drug("克林霉素", 25, "a1", 19.7);
	drug[1] = new Drug("万古霉素", 9, "a2", 20.56);
	drug[2] = new Drug("利福平", 67, "a3", 19.89);
	drug[3] = new Drug("止疼药", 49, "b1", 199.97);
	drug[4] = new Drug("999皮炎平", 97, "b2", 5.89);
	drug[5] = new Drug("氨甲环酸", 16, "b3", 9.98);
	drug[6] = new Drug("蒲地蓝口服液", 187, "c1", 4.97);
	drug[7] = new Drug("头孢丙烯片", 546, "c2", 14.36);
	drug[8] = new Drug("阿司匹林", 813, "c3", 25.65);
	drug[9] = new Drug("甲硝锉", 154, "d1", 88.57);
	drug[10] = new Drug("左氧氟沙星片", 453, "d2", 35.97);
	drug[11] = new Drug("抗宫炎片", 135, "d3", 59.58);
	drug[12] = new Drug("小儿伤风速效冲剂", 124, "e1", 12.54);
	drug[13] = new Drug("小儿止咳糖浆", 95, "e2", 16.95);
	drug[14] = new Drug("阿莫斯", 25, "e3", 25.56);
	drug[15] = new Drug("红霉素软膏", 36, "f1", 18.58);
	drug[16] = new Drug("黄连上清丸", 59, "f2", 85.69);
	drug[17] = new Drug("板蓝根", 48, "f3", 12.58);
	drug[18] = new Drug("鼻炎宁颗粒", 14, "f3", 35.59);
	drug[19] = new Drug("氯雷他定片", 79, "g2", 24.59);
	drug[20] = new Drug("鼻立通", 100, "g3", 18.69);
	drug[21] = new Drug("999止疼药", 57, "h1", 47.59);
	drug[22] = new Drug("头孢克肟片", 136, "h2", 16.59);
	drug[23] = new Drug("麻醉药", 14, "h3", 26.78);
	int a;
	string op;
	while (1) {
	cout << "=======================================================药房系统========================================================" << endl;
	cout << "展示药品仓库或添加药品请输入1，开药请输入2，退出请输入3" << endl;
		cin >> a;
		if (a == 1) {
			showAllDrug(drug);
			addDrug(drug);
		}
		else if (a == 2) {
			getid(id);
			outAllDrug(drug, id);
		}
		else if (a == 3) {
			system("cls");
			cout << "程序即将退出，请问是否还要保留药房系统缓存文件？(y/n):";
			do {
				cin >> op;
				if (op != "n" && op != "y") {
					cout << "输入有误，请重新输入：";
				}
			} while (op != "n" && op != "y");
			if (op == "n") {
				string cmd;
				cmd = "del " + rootstr + "\\PMS_data\\Patient_Need_Drug\\*.*";
				system(cmd.c_str());
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