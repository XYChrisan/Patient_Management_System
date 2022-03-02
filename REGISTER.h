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
	int i = 0;//��������ϵͳ�Һż�¼
	Patient patient[MAXLENGTH];//������ʱ����
	Department Orthopedic;//�ǿ�
	Department Surgery;//���
	Department IM;//�ڿ�
	Department OaG;//����
	Department Pediatrics;//����
	Department Ophtalmology;//�ۿ�
	Department ENT;//���Ǻ��
	Department Stomatology;//��ǻ��
	string rootstr;
	int RegisterSystem()//�Һ�ϵͳ
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
			cout << "#=========================�Һ�ϵͳ=========================#" << endl;
			cout << "#==��ѡ��ִ������========================================#" << endl;
			cout << "#==1.�Һ�   2.ɾ���Һ���Ϣ   3.��ѯ��ʷ�Һ�   4.�ر�ϵͳ===#" << endl << "#==��ѡ��";
			do {
				cin >> operation;
				operationtoint = atoi(operation.c_str());
				if (operationtoint <= 0 || operationtoint > 4)
					cout << "�������Ϣ�������������룺";
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
				cout << "���򼴽��˳��������Ƿ����Һ����ݣ�(y/n)��";
				do {
					cin >> op;
					if (op != "n" && op != "y") {
						cout << "�����������������룺";
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
	void InitDepartment() {//��ʼ����������Ϣ
		Orthopedic.Floor = "1";
		Orthopedic.Doctor = "������";
		Orthopedic.Room = "101";
		Surgery.Floor = "1";
		Surgery.Doctor = "������";
		Surgery.Room = "102";
		IM.Floor = "2";
		IM.Doctor = "�����";
		IM.Room = "201";
		OaG.Floor = "2";
		OaG.Doctor = "÷ܿ��";
		OaG.Room = "202";
		Pediatrics.Floor = "3";
		Pediatrics.Doctor = "��ϼ";
		Pediatrics.Room = "301";
		Ophtalmology.Floor = "3";
		Ophtalmology.Doctor = "������";
		Ophtalmology.Room = "302";
		ENT.Floor = "4";
		ENT.Doctor = "�Ͼ���";
		ENT.Room = "401";
		Stomatology.Floor = "4";
		Stomatology.Doctor = "�����";
		Stomatology.Room = "402";
	}
	void RegNewPatient()//�Һ�
	{
		int departmenttoint;
		string cmd;//����������ʾ��ʶ��
		char act[256];//string cmdת��Ϊ������ʾ������ʶ���char
		system("color 7");//�޸���ɫ
		if (i > 2800) {//����ڴ�״̬�Ƿ���
			cout << "��ʾ����ǰ�ڴ滺������������رճ����������棬�Ա�֤����֮���������С�" << endl;
		}
		i++;//�������˺͹Һ�
		patient[i].status = 1;//Ĭ�ϲ���Ϊ�ѹҺ�
		string filenumber = "";//���ڴ��ļ�ʶ���ļ���
		ofstream FILE;//�ļ���
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
		int sex;//��ʱ�Ա�
		int department;//��ʱ����
		filenumber = to_string(static_cast<long long>(i));//�Һź���ǿ��ת��string
		cout << "��ǰ���񣺹Һ�" << endl;
		cout << "��ǰ�������Ϊ��" << i << endl;
		cout << "�����벡�˵����֤���룺";
		cin >> patient[i].ID;//�ӽ����������֤����
		FILE.open(rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt");//�ԹҺ�_���֤����Ϊ��ʽ�������˹Һ���Ϣ�ļ�
		INFO << filenumber << "_" << patient[i].ID << endl;
		INFO.close();
		FILE << "Number:" << i << endl;//д�벡�˹Һ�
		FILE << "ID:" << patient[i].ID << endl;//���֤���������ļ�
		cout << "�����벡�˵�������";
		cin >> patient[i].name;//�ӽ�����������
		FILE << "Name:" << patient[i].name << endl;//���������ļ�
		cout << "�����벡�˵��Ա�1Ϊ�У�0ΪŮ����";
		do {
			cin >> sex;
			if (sex != 0 && sex != 1)
				cout << "�������Ϣ�������������룺";
		} while (sex != 0 && sex != 1);//У��������ȷ��
		patient[i].sex = sex;//��ȷ���봫�벡�������Ա����
		if (patient[i].sex == 1)//1Ϊ����
			FILE << "Sex:��" << endl;
		if (patient[i].sex == 0)//2ΪŮ��
			FILE << "Sex:Ů" << endl;
		cout << "������ҺŵĿ��ң�" << endl;
		cout << "1.�ǿ� 2.��� 3.�ڿ� 4.���� 5.���� 6.�ۿ� 7.���Ǻ�� 8.��ǻ��" << endl;
		cout << "������ѡ�";
		do {
			cin >> patient[i].department;
			departmenttoint = atoi(patient[i].department.c_str());
			if (departmenttoint <= 0 || departmenttoint > 8)
				cout << "�������Ϣ�������������룺";
		} while (departmenttoint <= 0 || departmenttoint > 8);
		switch (departmenttoint) {//�������Ϸ���
		case 1:
			INFO01.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Orthopedic\\PATIENTLIST.txt", ios::app);
			FILE << "Department:�ǿ�" << endl;
			cout << "\n��ѡ����ǣ��ǿ�" << endl;
			cout << "¥�㣺" << Orthopedic.Floor << endl;
			cout << "ҽ����" << Orthopedic.Doctor << endl;
			cout << "���ң�" << Orthopedic.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Orthopedic";
			strcpy(act, cmd.c_str());
			INFO01 << filenumber << "_" << patient[i].ID << endl;
			INFO01.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 2:
			INFO02.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Surgery\\PATIENTLIST.txt", ios::app);
			FILE << "Department:���" << endl;
			cout << "\n��ѡ����ǣ����" << endl;
			cout << "¥�㣺" << Surgery.Floor << endl;
			cout << "ҽ����" << Surgery.Doctor << endl;
			cout << "���ң�" << Surgery.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Surgery";
			strcpy(act, cmd.c_str());
			INFO02 << filenumber << "_" << patient[i].ID << endl;
			INFO02.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 3:
			INFO03.open(rootstr + "\\PMS_Data\\Department_Queue_db\\IM\\PATIENTLIST.txt", ios::app);
			FILE << "Department:�ڿ�" << endl;
			cout << "\n��ѡ����ǣ��ڿ�" << endl;
			cout << "¥�㣺" << IM.Floor << endl;
			cout << "ҽ����" << IM.Doctor << endl;
			cout << "���ң�" << IM.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\IM";
			strcpy(act, cmd.c_str());
			INFO03 << filenumber << "_" << patient[i].ID << endl;
			INFO03.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 4:
			INFO04.open(rootstr + "\\PMS_Data\\Department_Queue_db\\OaG\\PATIENTLIST.txt", ios::app);
			FILE << "Department:����" << endl;
			cout << "\n��ѡ����ǣ�����" << endl;
			cout << "¥�㣺" << OaG.Floor << endl;
			cout << "ҽ����" << OaG.Doctor << endl;
			cout << "���ң�" << OaG.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\OaG";
			strcpy(act, cmd.c_str());
			INFO04 << filenumber << "_" << patient[i].ID << endl;
			INFO04.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 5:
			INFO05.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Pediatrics\\PATIENTLIST.txt", ios::app);
			FILE << "Department:����" << endl;
			cout << "\n��ѡ����ǣ�����" << endl;
			cout << "¥�㣺" << Pediatrics.Floor << endl;
			cout << "ҽ����" << Pediatrics.Doctor << endl;
			cout << "���ң�" << Pediatrics.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Pediatrics";
			strcpy(act, cmd.c_str());
			INFO05 << filenumber << "_" << patient[i].ID << endl;
			INFO05.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 6:
			INFO06.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Ophtalmology\\PATIENTLIST.txt", ios::app);
			FILE << "Department:�ۿ�" << endl;
			cout << "\n��ѡ����ǣ��ۿ�" << endl;
			cout << "¥�㣺" << Ophtalmology.Floor << endl;
			cout << "ҽ����" << Ophtalmology.Doctor << endl;
			cout << "���ң�" << Ophtalmology.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Ophtalmology";
			strcpy(act, cmd.c_str());
			INFO06 << filenumber << "_" << patient[i].ID << endl;
			INFO06.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 7:
			INFO07.open(rootstr + "\\PMS_Data\\Department_Queue_db\\ENT\\PATIENTLIST.txt", ios::app);
			FILE << "Department:���Ǻ��" << endl;
			cout << "\n��ѡ����ǣ����Ǻ��" << endl;
			cout << "¥�㣺" << ENT.Floor << endl;
			cout << "ҽ����" << ENT.Doctor << endl;
			cout << "���ң�" << ENT.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\ENT";
			strcpy(act, cmd.c_str());
			INFO07 << filenumber << "_" << patient[i].ID << endl;
			INFO07.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		case 8:
			INFO08.open(rootstr + "\\PMS_Data\\Department_Queue_db\\Stomatology\\PATIENTLIST.txt", ios::app);
			FILE << "Department:��ǻ��" << endl;
			cout << "\n��ѡ����ǣ���ǻ��" << endl;
			cout << "¥�㣺" << Stomatology.Floor << endl;
			cout << "ҽ����" << Stomatology.Doctor << endl;
			cout << "���ң�" << Stomatology.Room << endl << endl;//��ӡ������Ϣ����Ļ
			cmd = "copy " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[i].ID + "_db.txt " + rootstr + "\\PMS_data\\Department_Queue_db\\Stomatology";
			strcpy(act, cmd.c_str());
			INFO08 << filenumber << "_" << patient[i].ID << endl;
			INFO08.close();
			system(act);//���ݲ�����Ϣ�������ļ���
			break;
		}
		system("color a");
		cout << "�Һ���ɣ�����һλ���˹Һ�!" << endl << endl;
		FILE.close();//��ɹҺŹ���
		system("pause");
		system("cls");
		system("color 7");//UI���涯Ч���Ż�
	}
	void ModifyRegInfo()//ɾ���Һ���Ϣ
	{
		string cmd;//����������ʾ��ʶ��
		string filenumber = "";
		char act[256];//string cmdת��Ϊ������ʾ������ʶ���char
		system("color 7");
		string p;//pΪ���˹Һź���
		int ptoint;
		cout << "��������Ҫɾ����Ϣ�Ĳ��˹Һź��루����-100���˳�����";
		do
		{
			cin >> p;
			ptoint = atoi(p.c_str());
			if (ptoint != -100) {
				if (ptoint <= 0 || ptoint > i || patient[ptoint].status == 0) {
					cout << "ָ���Ĳ��˲����ڣ����������룺";
				}
			}
			if (ptoint == -100) {
				break;
			}
		} while (ptoint <= 0 || ptoint > i || patient[ptoint].status == 0);//�������Ϸ����Լ����˹Һ���Ϣ�Ƿ�����ж�
		filenumber = to_string(static_cast<long long>(ptoint));//�Һź���ǿ��ת��string
		if (ptoint != -100) {
			cout << "ȷ��Ҫɾ���˲��˵ĹҺ���Ϣ��ɾ���󣬴��ļ������ɻָ���";
			system("pause");
			cout << endl;
			cmd = "del " + rootstr + "\\PMS_data\\Patient_db\\" + filenumber + "_" + patient[ptoint].ID + "_db.txt";
			strcpy(act, cmd.c_str());
			system(act);//ɾ��������Ϣ�ļ�
			system("color a");
			cout << "�˹Һ���Ϣ�ѱ�ɾ����";
			patient[ptoint].status = 0;
			system("pause");
			system("cls");
			system("color 7");
		}
		if (ptoint == -100) {//ģ���˳�
			system("color a");
			cout << "ģ���˳���";
			system("pause");
			system("cls");
			system("color 7");
		}
	}
	void ShowHistoryReg() //��ѯ��ʷ�Һ�
	{
		system("color 7");
		cout << "��ǰ�Ѿ��Һ�������" << i << endl;
		cout << "�Һ����飺" << endl;
		for (int t = 1; t <= i; t++) {
			if (patient[t].status) {//�жϹҺ��ļ��Ƿ���ڣ��Է���ȡʱ��������
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
				FILE.close();//ȫ����ӡ�ļ����ݵ���Ļ��
			}
		}
		system("pause");
		system("cls");
		system("color 7");
	}
	void ClearFiles() {
		system("color 7");
		cout << "��������...";
		
		string cmd;
		cmd = "del " + rootstr + "\\PMS_data\\Patient_db\\*.*";
		system(cmd.c_str());
		
		cout << "������ɣ�";
		
		system("pause");
		system("cls");
		system("color 7");
	}
};
#endif