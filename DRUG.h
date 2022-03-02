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
		cout << "ҩƷ:" << setw(18) << this->name << "  ";
		cout << "����:" << this->number << endl;
	}//���ҩƷ��Ϣ
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
							cout << "��ҩ��Ϣ__";
							cout << "����:" << name << " ҩƷ:" << this->name;
							cout << " ��֧��:" << this->price << "Ԫ" << endl;
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
	cout << "����ҩƷ�Ŀ��:" << endl;
	for (i = 0; i < 24; i++) {
		drug[i]->showDrug();
	}
}//չʾҩƷ

void getid(string id[]) {
	int i = 0;
	ifstream file;
	string id1;
	char takeid[30];
	string txt = rootstr + "\\PMS_Data\\Patient_Need_Drug\\NEEDDRUG.txt";
	file.open(txt, ios::in);
	if (!file.is_open())
	{
		cout << "�����ļ������ڻ���" << endl;
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
}//��ȡ�����ļ���

void addDrug(Drug* drug[]) {
	int i, j, k = 0, number;
	string n;
	int ntoint;
	string yes, name;
	cout << "=========================================ҩƷ�����չʾ���Ƿ����ҩƷ����y/n��=========================================" << endl;
	do {
		cin >> yes;
		if (yes != "n" && yes != "y") {
			cout << "�����������������룺";
		}
	} while (yes != "n" && yes != "y");
	if (yes == "n") {
		system("cls");
		return;
	}
	else if (yes == "y") {
		cout << "���������ҩƷ������(1-24)��";
		do
		{
			cin >> n;
			ntoint = atoi(n.c_str());
			if (ntoint <= 0 || ntoint > 24) {
				cout << "�޷�ʶ�������ѡ����������룺";
			}
		} while (ntoint <= 0 || ntoint > 24);
		for (j = 0; j < ntoint; j++) {
			cout << "���ҩƷ����";
			cin >> name;
			while (name != "����ù��" && name != "���ù��" && name != "����ƽ" && name != "ֹ��ҩ" && name != "999Ƥ��ƽ" && name != "���׻���" && name != "�ѵ����ڷ�Һ" && name != "ͷ�߱�ϩƬ" && name != "��˾ƥ��"
				&& name != "�����" && name != "������ɳ��Ƭ" && name != "������Ƭ" && name != "С���˷���Ч���" && name != "С��ֹ���ǽ�" && name != "��Ī˹" && name != "��ù�����" && name != "����������"
				&& name != "������" && name != "����������" && name != "��������Ƭ" && name != "����ͨ" && name != "999ֹ��ҩ" && name != "ͷ�߿��Ƭ" && name != "����ҩ") {
				cout << "����ҩ�������������������ҩƷ����";
				cin >> name;
			}
			cout << "���ҩƷ������";
			cin >> number;
			for (i = 0; i < 24; i++) {
				if (drug[i]->name == name) {
					drug[i]->number += number;
					cout << "��ҩ�ɹ���" << endl;
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
}//���ҩƷ

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
	drug[0] = new Drug("����ù��", 25, "a1", 19.7);
	drug[1] = new Drug("���ù��", 9, "a2", 20.56);
	drug[2] = new Drug("����ƽ", 67, "a3", 19.89);
	drug[3] = new Drug("ֹ��ҩ", 49, "b1", 199.97);
	drug[4] = new Drug("999Ƥ��ƽ", 97, "b2", 5.89);
	drug[5] = new Drug("���׻���", 16, "b3", 9.98);
	drug[6] = new Drug("�ѵ����ڷ�Һ", 187, "c1", 4.97);
	drug[7] = new Drug("ͷ�߱�ϩƬ", 546, "c2", 14.36);
	drug[8] = new Drug("��˾ƥ��", 813, "c3", 25.65);
	drug[9] = new Drug("�����", 154, "d1", 88.57);
	drug[10] = new Drug("������ɳ��Ƭ", 453, "d2", 35.97);
	drug[11] = new Drug("������Ƭ", 135, "d3", 59.58);
	drug[12] = new Drug("С���˷���Ч���", 124, "e1", 12.54);
	drug[13] = new Drug("С��ֹ���ǽ�", 95, "e2", 16.95);
	drug[14] = new Drug("��Ī˹", 25, "e3", 25.56);
	drug[15] = new Drug("��ù�����", 36, "f1", 18.58);
	drug[16] = new Drug("����������", 59, "f2", 85.69);
	drug[17] = new Drug("������", 48, "f3", 12.58);
	drug[18] = new Drug("����������", 14, "f3", 35.59);
	drug[19] = new Drug("��������Ƭ", 79, "g2", 24.59);
	drug[20] = new Drug("����ͨ", 100, "g3", 18.69);
	drug[21] = new Drug("999ֹ��ҩ", 57, "h1", 47.59);
	drug[22] = new Drug("ͷ�߿��Ƭ", 136, "h2", 16.59);
	drug[23] = new Drug("����ҩ", 14, "h3", 26.78);
	int a;
	string op;
	while (1) {
	cout << "=======================================================ҩ��ϵͳ========================================================" << endl;
	cout << "չʾҩƷ�ֿ�����ҩƷ������1����ҩ������2���˳�������3" << endl;
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
			cout << "���򼴽��˳��������Ƿ�Ҫ����ҩ��ϵͳ�����ļ���(y/n):";
			do {
				cin >> op;
				if (op != "n" && op != "y") {
					cout << "�����������������룺";
				}
			} while (op != "n" && op != "y");
			if (op == "n") {
				string cmd;
				cmd = "del " + rootstr + "\\PMS_data\\Patient_Need_Drug\\*.*";
				system(cmd.c_str());
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