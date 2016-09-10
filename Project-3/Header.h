#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.h"
using namespace std;

const double default_max_overdraft = 1000;	//透支上限 

const string default_password = "sysu";		//默认密码 

const string default_name = "unknown";		//默认姓名 

const string default_sno = "unknown";		//默认学号 

const string default_academy = "unknown";	//默认学院 

void introSystem();			//介绍主系统界面 

void introCampusCard();		//介绍校园卡系统界面 

void introDepositCard();	//介绍储蓄卡系统界面 

void introBindingCard();	//介绍绑定卡系统界面 

void read_CampusCard(vector<campus_card>&);		//从文件读取校园卡信息 

void read_DepositCard(vector<deposit_card>&);	//从文件读取储蓄卡信息

void readBindingCard(vector<binding_card>&, vector<campus_card>&, vector<deposit_card>&);	//从文件读取绑定卡信息

void write_CampusCard(vector<campus_card>&);	//将校园卡信息存入文件 

void write_DepositCard(vector<deposit_card>&);	//将储蓄卡信息存入文件

void write_BindingCard(vector<binding_card>&);	//将绑定卡信息存入文件

int findCcardByAcc(string, vector<campus_card>);	//在所有校园卡中查找指定账户，有则返回下标，无则返回-1 

int findDcardByAcc(string, vector<deposit_card>);	//在所有储蓄卡中查找指定账户，有则返回下标，无则返回-1 

int findBcardByAcc(string, vector<binding_card>);	//在所有绑定卡中查找指定账户，有则返回下标，无则返回-1 

bool repeated(string, vector<campus_card>);		//判断输入账号是否有重复 

bool repeated(string, vector<deposit_card>);	//判断输入账号是否有重复

bool repeated(string, vector<binding_card>);	//判断输入账号是否有重复

void toPay(Card*, double);	//根据卡的类型选择支付方式 

#endif
