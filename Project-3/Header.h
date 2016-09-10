#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Card.h"
using namespace std;

const double default_max_overdraft = 1000;	//͸֧���� 

const string default_password = "sysu";		//Ĭ������ 

const string default_name = "unknown";		//Ĭ������ 

const string default_sno = "unknown";		//Ĭ��ѧ�� 

const string default_academy = "unknown";	//Ĭ��ѧԺ 

void introSystem();			//������ϵͳ���� 

void introCampusCard();		//����У԰��ϵͳ���� 

void introDepositCard();	//���ܴ��ϵͳ���� 

void introBindingCard();	//���ܰ󶨿�ϵͳ���� 

void read_CampusCard(vector<campus_card>&);		//���ļ���ȡУ԰����Ϣ 

void read_DepositCard(vector<deposit_card>&);	//���ļ���ȡ�����Ϣ

void readBindingCard(vector<binding_card>&, vector<campus_card>&, vector<deposit_card>&);	//���ļ���ȡ�󶨿���Ϣ

void write_CampusCard(vector<campus_card>&);	//��У԰����Ϣ�����ļ� 

void write_DepositCard(vector<deposit_card>&);	//�������Ϣ�����ļ�

void write_BindingCard(vector<binding_card>&);	//���󶨿���Ϣ�����ļ�

int findCcardByAcc(string, vector<campus_card>);	//������У԰���в���ָ���˻������򷵻��±꣬���򷵻�-1 

int findDcardByAcc(string, vector<deposit_card>);	//�����д���в���ָ���˻������򷵻��±꣬���򷵻�-1 

int findBcardByAcc(string, vector<binding_card>);	//�����а󶨿��в���ָ���˻������򷵻��±꣬���򷵻�-1 

bool repeated(string, vector<campus_card>);		//�ж������˺��Ƿ����ظ� 

bool repeated(string, vector<deposit_card>);	//�ж������˺��Ƿ����ظ�

bool repeated(string, vector<binding_card>);	//�ж������˺��Ƿ����ظ�

void toPay(Card*, double);	//���ݿ�������ѡ��֧����ʽ 

#endif
