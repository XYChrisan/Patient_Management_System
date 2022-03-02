#pragma once
#ifndef PATIENT_H
#define PATIENT_H
#include<iostream>
using namespace std;
class Patient {
public:
	string name;//姓名
	bool sex;//性别，1男0女
	int age;//年龄
	string ID;//身份证号码
	int number;//挂号
	string department;//科室
	string diseasehistory;//病历
	int status;//文件存在状态
};
#endif