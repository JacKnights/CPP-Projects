#include <vector>
#include "Header.h"
using namespace std;

int campus_card :: card_num = 0;
int deposit_card :: card_num = 0;
int binding_card :: card_num = 0;

Record :: Record() {
}

Record :: Record(string p, double s) {
	place = p;
	spending = s;
}

void Record :: setRecord() {
	time_t rawtime; 
 	struct tm * timeinfo; 
 	time ( &rawtime ); 
 	timeinfo = localtime ( &rawtime );
 	year = 1900 + timeinfo->tm_year; //��
 	month = 1 + timeinfo->tm_mon;//��
 	day = timeinfo->tm_mday;   //��
 	hour = timeinfo->tm_hour;  //ʱ
 	minute = timeinfo->tm_min; //��
 	second = timeinfo->tm_sec; //��
}

void Record :: setRecord(string p, double s, bool io) {
	time_t rawtime; 
 	struct tm * timeinfo; 
 	time ( &rawtime ); 
 	timeinfo = localtime ( &rawtime );
 	year = 1900 + timeinfo->tm_year; //��
 	month = 1 + timeinfo->tm_mon;//��
 	day = timeinfo->tm_mday;   //��
 	hour = timeinfo->tm_hour;  //ʱ
 	minute = timeinfo->tm_min; //��
 	second = timeinfo->tm_sec; //��
 	place = p;
 	spending = s;
 	in_or_out = io;
}
//����Ϊ��ʷ��¼��ʵ�� 

 

Card :: Card() {
	balance = 0;
	record_num = 0;
	password = default_password;
	name = default_name; 
}

double Card :: getBalance() {
  	return balance;
}

string Card :: getName() {
	return name;
}

string Card :: getPassword() {
	return password;
}

void Card :: setBalance(double amount) {
	balance = amount;
}

void Card :: setName(string n) {
	name = n;
}

void Card :: setPassword(string pw) {
	password = pw; 
}

void Card :: pay(double money) {
	balance -= money;
	cout << "|		��֧���ɹ���\n";
	record_num++;
	string place;
	cout << "|	���ںε����ѣ�";
	cin >> place;
	records.push_back(Record(place, money));
	records[records.size() - 1].setRecord(place, money, 0);
}

void Card :: printRecords() {
	vector<Record> :: iterator it;
	for (it = records.begin(); it < records.end(); it++) {
		if (!(*it).in_or_out) {
			cout << "|		" << (*it).year << "��" <<(*it).month << "��" << (*it).day << "��" << (*it).hour << "ʱ" 
				 << (*it).minute << "��" << (*it).second << "�룬��" << (*it).place << "����" << (*it).spending << "Ԫ" << endl;
		} else {
			cout << "|		" << (*it).year << "��" <<(*it).month << "��" << (*it).day << "��" << (*it).hour << "ʱ" 
				 << (*it).minute << "��" << (*it).second << "�룬��" << (*it).place << "����" << (*it).spending << "Ԫ" << endl;
		}	
	}
}


//����ΪCard��ʵ��

campus_card :: campus_card() : Card() {
	sno = default_sno;
	academy = default_academy;
	initialized = 0;
}

campus_card :: campus_card(string acc) : Card() {
	account = acc;
	sno = default_sno;
	academy = default_academy;
	initialized = 0;
	campus_card :: card_num++;
}


string campus_card :: getSno() {
	return sno;
}

string campus_card :: getAcademy() {
	return academy;
}

bool campus_card :: getInitialized() {
	return initialized;
}

void campus_card :: setSno(string s) {
	sno = s;
}

void campus_card :: setAcademy(string a) {
	academy = a;
}

void campus_card :: setInitialized(bool i) {
	initialized = i;
}

void campus_card :: printCampusInfo() {
	cout << "+------------------------------------------------------------------\n"
		 << "|                          ����У԰����Ϣ\n"
		 << "\\  ������" << name << "\n"
		 << " \\  ѧ�ţ�" << sno << "\n"
		 << "  \\  ѧԺ��" << academy << "\n"
		 << "   \\  У԰���ţ�"<< account << "\n"
		 << "    \\  У԰����"<< balance << "\n"
		 << "     \\  �������ڣ�"<< create_time.year << "��" << create_time.month << "��" << create_time.day << "��\n"
		 << "      + ------------------------------------------------------------\n";
}

void campus_card :: useCampusCard() {
	introCampusCard();
	int service;
	cout << "|	��ѡ��У԰�����ܣ�"; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	������֧����";
				cin >> money;
				if (money < 0) {
					cout << "|		������\n";
				} else {
					if (balance >= money) {
						toPay(this, money);
					} else {
						cout << "|		���㣡\n";
					}
				}
				break;
			}
			case 2:{
				printCampusInfo();
				break;
			}
			case 3:{
				cout << "|	�˿�ʹ����ˮ��¼���£�\n"; 
				printRecords();
				break;
			}
			case 4:{
				if (!getInitialized()) {
					string new_info;
					cout << "|	������������";
					cin >> new_info;
					name = new_info;
					cout << "|		���޸�����Ϊ" << getName() << "��\n";
					cout << "|	������ѧ�ţ�";
					cin >> new_info;
					sno = new_info;
					cout << "|		���޸�ѧ��Ϊ" << getSno() << "��\n";
					cout << "|	������ѧԺ��";
					cin >> new_info;
					academy = new_info;
					cout << "|		���޸�ѧԺΪ" << getAcademy() << "��\n";
					initialized = true;
				} else {
					cout << "|		����д��Ϣ�����޸�Ȩ�ޣ�\n";
				}
				break;
			}
			case 5:{
				string new_pw;
				cout << "|	�����������룺";
				cin >> new_pw;
				password = new_pw ;
				cout << "|		�����������룡\n";
				break;
			}
			default:{
				cout << "|		У԰���޴˹��ܣ�\n";
				break;
			}
		}
		cout << "|	��ѡ��У԰�����ܣ�"; 
		cin >> service;
	}
	cout << "|	У԰���˺��Ѱ�ȫע����\n"; 
}

//����Ϊcampus_card��ʵ�� 




deposit_card :: deposit_card() : Card() {
	overdraft = 0;
}

deposit_card :: deposit_card(string acc) : Card() {
	account = acc;
	overdraft = 0;
	deposit_card :: card_num++;
}

double deposit_card :: getOverdraft() {
	return overdraft;
}
	
void deposit_card :: setOverdraft(double o) {
	overdraft = o;
}

void deposit_card :: pay(double money) {
	balance -= money;
	if (balance < 0) {
		overdraft = -balance;
	} else {
		overdraft = 0;
	}
	cout << "|		��֧���ɹ���\n";
	if (overdraft) {
		cout << "|		���㣬��͸֧" << overdraft << "Ԫ��\n";
	}
	record_num++;
	string place;
	cout << "|	���ںε����ѣ�";
	cin >> place;
	records.push_back(Record());
	records[records.size() - 1].setRecord(place, money, 0);
}

void deposit_card :: deposit(double d) {
	if (d < 0) {
		cout << "|		������\n";
	} else {
		balance += d;
		if (balance < 0) {
			overdraft = -balance;
		} else {
			overdraft = 0;
		}
		cout << "|		�Ѵ洢�ɹ���\n";
		record_num++;
		cout << "|	���ںεش��룺";
		string p;
		cin >> p;
		records.push_back(Record());
		records[records.size() - 1].setRecord(p, d, 1);
	}
	if (overdraft > 0) {
		cout << "|		��͸֧" << overdraft << "Ԫ��\n"; 
	}
}

void deposit_card :: rechargeForCampusCard(campus_card c, double amount) {
	pay(amount);
	c.setBalance(c.getBalance() + amount);
}

void deposit_card :: printDepositInfo() {
	cout << "+------------------------------------------------------------------\n"
		 << "                          ���Ĵ����Ϣ\n"
		 << "     /  ������" << name << "\n"
		 << "    /  ����ţ�"<< account << "\n"
		 << "   /  �����" << balance << "\n"
		 << "  /  ͸֧�" << overdraft << "\n"
		 << " /  �������ڣ�"<< create_time.year << "��" << create_time.month << "��" << create_time.day << "��\n"
		 << "+------------------------------------------------------------------\n";
}

void deposit_card :: useDepositCard(vector<campus_card> &Ccards, vector<deposit_card> &Dcards) {
	introDepositCard();
	int service;
	cout << "|	��ѡ������ܣ�"; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	������֧����";
				cin >> money;
				if (money < 0) {
					cout << "|		������\n";
				} else {
					if (balance + default_max_overdraft >= money) {
						toPay(this, money);
					} else {
						cout << "|		֧��ʧ�ܣ��ѳ�͸֧�����ޣ�\n";
					}
				}
				break;
			}
			case 2:{
				double d;
				cout << "|	������洢��";
				cin >> d;
				deposit(d);
				break;
			}
			case 3:{
				double p;
				string account;
				cout << "|	�������ֵ��У԰���ţ�";
				cin >> account;
				if (findCcardByAcc(account, Ccards) != -1) {
					cout << "|	�������ֵ��";
					cin >> p;
					if (p > 0) {
						if (balance + default_max_overdraft >= p) {
							pay(p);
							Ccards[findCcardByAcc(account, Ccards)].setBalance(Ccards[findCcardByAcc(account, Ccards)].getBalance() + p);
							cout << "|		�ѳ�ֵ�ɹ���\n";
							if (overdraft) {
								cout << "|		������㣬��͸֧" << overdraft << "Ԫ��\n";
							}
						} else {
							cout << "|		��ֵʧ�ܣ��ѳ�͸֧�����ޣ�\n";
						}
					} else {
						cout << "|		������\n";
					}
				} else {
					cout << "|		�޴�У԰���˺ţ�\n";
				}
				break;
			}
			case 4:{
				double p;
				string account;
				cout << "|	������ת�˵Ĵ���ţ�";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	������ת�˽�";
					cin >> p;
					if (p > 0) {
						if (balance + default_max_overdraft >= p) {
							toPay(this, p);
							Dcards[findDcardByAcc(account, Dcards)].setBalance(Dcards[findDcardByAcc(account, Dcards)].getBalance() + p);
							cout << "|		��ת�˳ɹ���\n";
						} else {
							cout << "|		��ֵʧ�ܣ��ѳ�͸֧�����ޣ�\n";
						}
					} else {
						cout << "|		������\n";
					}
				} else {
					cout << "|		�޴˴�����˺ţ�\n";
				}
				break;
			}
			case 5:{
				printDepositInfo();
				break;
			}
			case 6:{
				cout << "|	�˿�ʹ����ˮ��¼���£�\n"; 
				printRecords();
				break;
			}
			case 7:{
				string new_name;
				cout << "|	�������»�������";
				cin >> new_name;
				name = new_name;
				cout << "|		�������»�������\n";
				break;
			}
			case 8:{
				string new_pw;
				cout << "|	�����������룺";
				cin >> new_pw;
				password = new_pw;
				cout << "|		�����������룡\n";
				break;
			}
			default:{
				cout << "|		����޴˹��ܣ�\n";
				break;
			}
		}
		cout << "|	��ѡ������ܣ�"; 
		cin >> service;
	}
	cout << "|		����˺��Ѱ�ȫע����\n";
}

//����Ϊdeposit_card��ʵ�� 




binding_card :: binding_card() : campus_card(), deposit_card() {
	
}

binding_card :: binding_card(string acc, string Cacc, vector<campus_card>& Ccards) : campus_card(), deposit_card() {
	account = acc;
	binded_campus_card = &Ccards[findCcardByAcc(Cacc, Ccards)];
	binding_card :: card_num++;
	binded_deposit_cards_num = 0;
}

void binding_card :: pay(double money) {
	double max_money = 0;
	double rest = money;
	for (int i = 0; i < binded_deposit_cards.size(); i++) {
		max_money += (binded_deposit_cards[i]->getBalance() + default_max_overdraft);
	}
	if (binded_campus_card->getBalance() >= rest) {
		binded_campus_card->pay(rest);
	} else if (max_money >= rest) {
		rest -= binded_campus_card->getBalance();
		binded_campus_card->pay(binded_campus_card->getBalance());
		for (int i = 0; i < binded_deposit_cards.size(); i++) {
			if (binded_deposit_cards[i]->getBalance() + default_max_overdraft >= rest) {
				binded_deposit_cards[i]->pay(rest);
			}
		}
	} else {
		cout << "|		֧��ʧ�ܣ��ѳ�͸֧�����ޣ�\n";
	}
}

void binding_card :: printRecords() {
	cout << "|	У԰��ʹ�ü�¼���£�\n";
	binded_campus_card->printRecords();
	cout << "|	���ʹ�ü�¼���£�\n";
	for (int i = 0; i < binded_deposit_cards.size(); i++) {
		binded_deposit_cards[i]->printRecords();
	}
}

void binding_card :: printBindingInfo() {
	cout << "+------------------------------------------------------------------\n"
		 << "|                          ���İ󶨿���Ϣ\n"
		 << "      /  ������" << binded_campus_card->getName() << "\n"
		 << "     /  ѧ�ţ�" << binded_campus_card->getSno() << "\n"
		 << "    /  ѧԺ��" << binded_campus_card->getAcademy() << "\n"
		 << "   /  �󶨿��ţ�"<< account << "\n"
		 << "  /  �������ڣ�"<< create_time.year << "��" << create_time.month << "��" << create_time.day << "��\n"
		 << " /  У԰���ţ�"<< binded_campus_card->account << "\n"
		 << "/  �󶨿���"<< binded_campus_card->getBalance() << "\n";
		 for (int i = 0; i < binded_deposit_cards.size(); i++) {
		 	cout << "|  ���" << i << "���ţ�" << binded_deposit_cards[i]->account << "\n";
		 }
		 cout << "+------------------------------------------------------------------\n";
}

void binding_card :: useBindingCard(vector<binding_card>& Bcards, vector<campus_card>& Ccards, vector<deposit_card>& Dcards) {
	introBindingCard();
	int service;
	cout << "|	��ѡ��󶨿����ܣ�"; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	������֧����";
				cin >> money;
				if (money < 0) {
					cout << "|		������\n";
				} else {
					toPay(this, money);
				}
				break;
			}
			case 2:{
				double money;
				string account;
				cout << "|	ѡ�����Ĵ����";
				cin >> account;
				int i;
				for (i = 0; i < binded_deposit_cards_num; i++) {
					if (binded_deposit_cards[findDcardByAcc(account, Dcards)]->account == account) {
						break;
					}
				}
				if (i != binded_deposit_cards_num) {
					cout << "|	������洢��";
					cin >> money;
					binded_deposit_cards[findDcardByAcc(account, Dcards)]->deposit(money);
				} else {
					cout << "|		δ�󶨴˴����\n";
				}
				break;
			}
			case 3:{
				string account, pw;
				cout << "|	��������ӵĴ�����ţ�";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	�������¼Ӵ�����룺";
					cin >> pw;
					if (pw == Dcards[findDcardByAcc(account, Dcards)].getPassword()) {
						binded_deposit_cards.push_back(new deposit_card());
						binded_deposit_cards[binded_deposit_cards.size() - 1] = &(Dcards[findDcardByAcc(account, Dcards)]);
						binded_deposit_cards_num++;
						cout << "|		�󶨴���ɹ���\n";
					} else {
						cout << "|		����������ʧ�ܣ�\n";
					}
				} else {
					cout << "|		�޴˴���˺ţ�\n";
				}
				break;
			}
			case 4:{
				double money;
				string account;
				cout << "|	������ת�˵Ĵ���ţ�";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	������ת�˽�";
					cin >> money;
					if (money >= 0) {
						toPay(this, money);
					} else {
						cout << "|		������\n";
					}
				} else {
					cout << "|		�޴˴���˺ţ�\n";
				}
				break;
			}
			case 5:{
				printBindingInfo();
				break;
			}
			case 6:{
				cout << "|	�˿�ʹ����ˮ��¼���£�\n"; 
				printRecords();
				break;
			}
			case 7:{
				string new_pw;
				cout << "|	�����������룺";
				cin >> new_pw;
				setPassword(new_pw);
				cout << "|		�����������룡\n";
				break;
			}
			default:{
				cout << "|		�󶨿��޴˹��ܣ�\n";
				break;
			}
		}
		cout << "|	��ѡ��󶨿����ܣ�"; 
		cin >> service;
	}
	balance = binded_campus_card->getBalance();
	name = binded_campus_card->getName();
	sno = binded_campus_card->getSno();
	academy = binded_campus_card->getAcademy();
	initialized = binded_campus_card->getInitialized();
	cout << "|		�󶨿��˺��Ѱ�ȫע����\n";
}

//����Ϊbinding_card��ʵ�� 




void toPay(Card* ptr, double money) {
	ptr->pay(money);
}

//������ѡ��֧����ʽ֧�� 

 

void introSystem() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                     ��ӭʹ��SYSUУ԰������ϵͳ                   |\n"
		 << "+------------------------------------------------------------------+\n"
		 << "|ϵͳ��������:                                                     |\n"
		 << "|    1����У԰��                                                   |\n"
		 << "|    2����                                                   |\n"
		 << "|    3����󶨿�                                                   |\n"
		 << "|    4ʹ��У԰��                                                   |\n"
		 << "|    5ʹ�ô��                                                   |\n"
		 << "|    6ʹ�ð󶨿�                                                   |\n"
		 << "|    0�˳�                                                         |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introCampusCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      ʹ��У԰����¼ϵͳ�ɹ���                    |\n"
		 << "|  У԰����������:                                                 |\n"
		 << "|    1֧��                                                         |\n"
		 << "|    2�鿴�˺���Ϣ                                                 |\n"
		 << "|    3�鿴ʹ�ü�¼                                                 |\n"
		 << "|    4��ʼ���������ϣ�ֻ��һ�λ��ᣩ                               |\n"
		 << "|    5�޸�����                                                     |\n"
		 << "|    0ע����¼                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introDepositCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      ʹ�ô����¼ϵͳ�ɹ���                    |\n"
		 << "|  �����������:                                                 |\n"
		 << "|    1֧��                                                         |\n"
		 << "|    2����                                                         |\n"
		 << "|    3ΪУ԰����ֵ                                                 |\n"
		 << "|    4ת��                                                         |\n"
		 << "|    5�鿴�˻���Ϣ                                                 |\n"
		 << "|    6�鿴ʹ�ü�¼                                                 |\n"
		 << "|    7�޸Ļ���                                                     |\n"
		 << "|    8�޸�����                                                     |\n"
		 << "|    0ע����¼                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introBindingCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      ʹ�ð󶨿���¼ϵͳ�ɹ���                    |\n"
		 << "|  �󶨿���������:                                                 |\n"
		 << "|    1֧��                                                         |\n"
		 << "|    2����                                                         |\n"
		 << "|    3����µĴ��                                               |\n"
		 << "|    4ת��                                                         |\n"
		 << "|    5�鿴�˻���Ϣ                                                 |\n"
		 << "|    6�鿴ʹ�ü�¼                                                 |\n"
		 << "|    7�޸�����                                                     |\n"
		 << "|    0ע����¼                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

//����Ϊ��������� 




void readCampusCard(vector<campus_card>& Ccards) {
	ifstream read;
	read.open("campus_card.txt");
	read >> campus_card :: card_num;
	for (int i = 0; i < campus_card :: card_num; i++) {
		campus_card *tmp1 = new campus_card();
		Ccards.push_back(*tmp1);
		read >> Ccards[i].record_num;
		bool initialized;
		read >> Ccards[i].account >> Ccards[i].name >> Ccards[i].sno >> Ccards[i].academy
			 >> Ccards[i].balance >> Ccards[i].password >> Ccards[i].initialized
			 >> Ccards[i].create_time.year >> Ccards[i].create_time.month >> Ccards[i].create_time.day;
		for (int j = 0; j < Ccards[i].record_num; j++) {
			Ccards[i].records.push_back(Record());
			read >> Ccards[i].records[j].year >> Ccards[i].records[j].month >> Ccards[i].records[j].day
				 >> Ccards[i].records[j].hour >> Ccards[i].records[j].minute >> Ccards[i].records[j].second
				 >> Ccards[i].records[j].place >> Ccards[i].records[j].spending >> Ccards[i].records[j].in_or_out;
		}
	}
}

void readDepositCard(vector<deposit_card>& Dcards) {
	ifstream read;
	read.open("deposit_card.txt");
	read >> deposit_card :: card_num;
	for (int i = 0; i < deposit_card :: card_num; i++) {
		deposit_card *tmp2 = new deposit_card();
		Dcards.push_back(*tmp2);
		read >> Dcards[i].record_num;
		read >> Dcards[i].account >> Dcards[i].name >> Dcards[i].balance >> Dcards[i].overdraft >> Dcards[i].password
			 >> Dcards[i].create_time.year >> Dcards[i].create_time.month >> Dcards[i].create_time.day;
		for (int j = 0; j < Dcards[i].record_num; j++) {
			Dcards[i].records.push_back(Record());
			read >> Dcards[i].records[j].year >> Dcards[i].records[j].month >> Dcards[i].records[j].day
				 >> Dcards[i].records[j].hour >> Dcards[i].records[j].minute >> Dcards[i].records[j].second
				 >> Dcards[i].records[j].place >> Dcards[i].records[j].spending >> Dcards[i].records[j].in_or_out;
		}
	}
}

void readBindingCard(vector<binding_card>& Bcards, vector<campus_card>& Ccards, vector<deposit_card>& Dcards) {
	ifstream read;
	read.open("binding_card.txt");
	read >> binding_card :: card_num;
	for (int i = 0; i < binding_card :: card_num; i++)  {
		Bcards.push_back(binding_card());
		string password, account;
		read >> Bcards[i].account >> password >> account >> Bcards[i].binded_deposit_cards_num
			 >> Bcards[i].create_time.year >> Bcards[i].create_time.month >> Bcards[i].create_time.day;
		Bcards[i].setPassword(password);
		Bcards[i].binded_campus_card = &Ccards[findCcardByAcc(account, Ccards)];
		for (int j = 0; j < Bcards[i].binded_deposit_cards_num; j++) {
			Bcards[i].binded_deposit_cards.push_back(new deposit_card());
			read >> Bcards[i].binded_deposit_cards[j]->account;
			Bcards[i].binded_deposit_cards[j] = &Dcards[findDcardByAcc(Bcards[i].binded_deposit_cards[j]->account, Dcards)];
		}
	}
}

void writeCampusCard(vector<campus_card>& Ccards) {
	ofstream write;
	write.open("campus_card.txt");
	write << campus_card :: card_num << endl;
	vector<campus_card> :: iterator itc = Ccards.begin();
	while (itc < Ccards.end()) {
		write << (*itc).record_num << endl;
		write << (*itc).account << " " << (*itc).getName() << " " << (*itc).getSno() << " " << (*itc).getAcademy() 
			  << " " << (*itc).getBalance() << " " << (*itc).getPassword() << " " << (*itc).getInitialized()
			  << " " << (*itc).create_time.year << " " << (*itc).create_time.month << " " << (*itc).create_time.day << endl;
		vector<Record> :: iterator ic = (*itc).records.begin();
		while (ic < (*itc).records.end()) {
			write  << " "<< (*ic).year << " " << (*ic).month << " " << (*ic).day << " " 
				   << (*ic).hour << " " << (*ic).minute << " " << (*ic).second << " " << (*ic).place << " "
				   << (*ic).spending << " " << (*ic).in_or_out << endl;
			ic++;
		}
		itc++;
	}
}

void writeDepositCard(vector<deposit_card>& Dcards) {
	ofstream write;
	write.open("deposit_card.txt");
	write << deposit_card :: card_num << endl;
	vector<deposit_card> :: iterator itd = Dcards.begin();
	while (itd < Dcards.end()) {
		write << (*itd).record_num << endl;
		write << (*itd).account << " " << (*itd).getName() << " " << (*itd).getBalance() << " "
			  << (*itd).getOverdraft() << " " << (*itd).getPassword()
			  << " " << (*itd).create_time.year << " " << (*itd).create_time.month << " " << (*itd).create_time.day << endl;
		vector<Record> :: iterator id = (*itd).records.begin();
		while (id < (*itd).records.end()) {
			write  << " "<< (*id).year << " " << (*id).month << " " << (*id).day << " " 
				   << (*id).hour << " " << (*id).minute << " " << (*id).second << " "
				   << (*id).place << " " << (*id).spending  << " " << (*id).in_or_out << endl;
			id++;
		}
		itd++;
	}
}

void writeBindingCard(vector<binding_card>& Bcards) {
	ofstream write;
	write.open("binding_card.txt");
	write << binding_card :: card_num << endl;
	for (int i = 0; i < Bcards.size(); i++) {
		write << Bcards[i].account << " " << Bcards[i].getPassword() << " "
			  << Bcards[i].binded_campus_card->account <<  " " << Bcards[i].binded_deposit_cards_num
			  << " " << Bcards[i].create_time.year << " " << Bcards[i].create_time.month << " " << Bcards[i].create_time.day << endl;
		for (int j = 0; j < Bcards[i].binded_deposit_cards_num; j++) {
			write << Bcards[i].binded_deposit_cards[j]->account << endl;
		}
	}
}

//����Ϊ�ļ��������ʵ�� 




bool repeated(string s, vector<campus_card> cards) {
	int i = 0;
	while (i < cards.size()) { 
	 	if (s == cards[i].account) {
	 		return true;
	 	}
	 	i++;
	}
	return false;
}

bool repeated(string s, vector<deposit_card> cards) {
	int i = 0;
	while (i < cards.size()) { 
	 	if (s == cards[i].account) {
	 		return true;
	 	}
	 	i++;
	}
	return false;
}

bool repeated(string s, vector<binding_card> cards) {
	int i = 0;
	while (i < cards.size()) { 
	 	if (s == cards[i].account) {
	 		return true;
	 	}
	 	i++;
	}
	return false;
}

//�����жϿ����Ƿ��ظ� 




int findCcardByAcc(string acc, vector<campus_card> Ccards) {
	for (int i = 0; i < Ccards.size(); i++) {
		if (acc == Ccards[i].account) {
			return i;
		}
	}
	return -1;
}

int findDcardByAcc(string acc, vector<deposit_card> Dcards) {
	for (int i = 0; i < Dcards.size(); i++) {
		if (acc == Dcards[i].account) {
			return i;
		}
	}
	return -1;
}

int findBcardByAcc(string acc, vector<binding_card> Bcards) {
	for (int i = 0; i < Bcards.size(); i++) {
		if (acc == Bcards[i].account) {
			return i;
		}
	}
	return -1;
}

//����Ϊ�����ŷ����±� 

