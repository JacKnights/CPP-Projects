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
 	year = 1900 + timeinfo->tm_year; //年
 	month = 1 + timeinfo->tm_mon;//月
 	day = timeinfo->tm_mday;   //日
 	hour = timeinfo->tm_hour;  //时
 	minute = timeinfo->tm_min; //分
 	second = timeinfo->tm_sec; //秒
}

void Record :: setRecord(string p, double s, bool io) {
	time_t rawtime; 
 	struct tm * timeinfo; 
 	time ( &rawtime ); 
 	timeinfo = localtime ( &rawtime );
 	year = 1900 + timeinfo->tm_year; //年
 	month = 1 + timeinfo->tm_mon;//月
 	day = timeinfo->tm_mday;   //日
 	hour = timeinfo->tm_hour;  //时
 	minute = timeinfo->tm_min; //分
 	second = timeinfo->tm_sec; //秒
 	place = p;
 	spending = s;
 	in_or_out = io;
}
//以上为历史记录类实现 

 

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
	cout << "|		已支付成功！\n";
	record_num++;
	string place;
	cout << "|	您在何地消费：";
	cin >> place;
	records.push_back(Record(place, money));
	records[records.size() - 1].setRecord(place, money, 0);
}

void Card :: printRecords() {
	vector<Record> :: iterator it;
	for (it = records.begin(); it < records.end(); it++) {
		if (!(*it).in_or_out) {
			cout << "|		" << (*it).year << "年" <<(*it).month << "月" << (*it).day << "日" << (*it).hour << "时" 
				 << (*it).minute << "分" << (*it).second << "秒，在" << (*it).place << "消费" << (*it).spending << "元" << endl;
		} else {
			cout << "|		" << (*it).year << "年" <<(*it).month << "月" << (*it).day << "日" << (*it).hour << "时" 
				 << (*it).minute << "分" << (*it).second << "秒，在" << (*it).place << "存入" << (*it).spending << "元" << endl;
		}	
	}
}


//以上为Card类实现

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
		 << "|                          您的校园卡信息\n"
		 << "\\  姓名：" << name << "\n"
		 << " \\  学号：" << sno << "\n"
		 << "  \\  学院：" << academy << "\n"
		 << "   \\  校园卡号："<< account << "\n"
		 << "    \\  校园卡余额："<< balance << "\n"
		 << "     \\  发卡日期："<< create_time.year << "年" << create_time.month << "月" << create_time.day << "日\n"
		 << "      + ------------------------------------------------------------\n";
}

void campus_card :: useCampusCard() {
	introCampusCard();
	int service;
	cout << "|	请选择校园卡功能："; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	请输入支付金额：";
				cin >> money;
				if (money < 0) {
					cout << "|		金额不合理！\n";
				} else {
					if (balance >= money) {
						toPay(this, money);
					} else {
						cout << "|		余额不足！\n";
					}
				}
				break;
			}
			case 2:{
				printCampusInfo();
				break;
			}
			case 3:{
				cout << "|	此卡使用流水记录如下：\n"; 
				printRecords();
				break;
			}
			case 4:{
				if (!getInitialized()) {
					string new_info;
					cout << "|	请输入姓名：";
					cin >> new_info;
					name = new_info;
					cout << "|		已修改姓名为" << getName() << "！\n";
					cout << "|	请输入学号：";
					cin >> new_info;
					sno = new_info;
					cout << "|		已修改学号为" << getSno() << "！\n";
					cout << "|	请输入学院：";
					cin >> new_info;
					academy = new_info;
					cout << "|		已修改学院为" << getAcademy() << "！\n";
					initialized = true;
				} else {
					cout << "|		已填写信息，无修改权限！\n";
				}
				break;
			}
			case 5:{
				string new_pw;
				cout << "|	请输入新密码：";
				cin >> new_pw;
				password = new_pw ;
				cout << "|		已设置新密码！\n";
				break;
			}
			default:{
				cout << "|		校园卡无此功能！\n";
				break;
			}
		}
		cout << "|	请选择校园卡功能："; 
		cin >> service;
	}
	cout << "|	校园卡账号已安全注销！\n"; 
}

//以上为campus_card类实现 




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
	cout << "|		已支付成功！\n";
	if (overdraft) {
		cout << "|		余额不足，已透支" << overdraft << "元！\n";
	}
	record_num++;
	string place;
	cout << "|	您在何地消费：";
	cin >> place;
	records.push_back(Record());
	records[records.size() - 1].setRecord(place, money, 0);
}

void deposit_card :: deposit(double d) {
	if (d < 0) {
		cout << "|		金额不合理！\n";
	} else {
		balance += d;
		if (balance < 0) {
			overdraft = -balance;
		} else {
			overdraft = 0;
		}
		cout << "|		已存储成功！\n";
		record_num++;
		cout << "|	您在何地存入：";
		string p;
		cin >> p;
		records.push_back(Record());
		records[records.size() - 1].setRecord(p, d, 1);
	}
	if (overdraft > 0) {
		cout << "|		仍透支" << overdraft << "元！\n"; 
	}
}

void deposit_card :: rechargeForCampusCard(campus_card c, double amount) {
	pay(amount);
	c.setBalance(c.getBalance() + amount);
}

void deposit_card :: printDepositInfo() {
	cout << "+------------------------------------------------------------------\n"
		 << "                          您的储蓄卡信息\n"
		 << "     /  姓名：" << name << "\n"
		 << "    /  储蓄卡号："<< account << "\n"
		 << "   /  储蓄卡余额：" << balance << "\n"
		 << "  /  透支额：" << overdraft << "\n"
		 << " /  发卡日期："<< create_time.year << "年" << create_time.month << "月" << create_time.day << "日\n"
		 << "+------------------------------------------------------------------\n";
}

void deposit_card :: useDepositCard(vector<campus_card> &Ccards, vector<deposit_card> &Dcards) {
	introDepositCard();
	int service;
	cout << "|	请选择储蓄卡功能："; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	请输入支付金额：";
				cin >> money;
				if (money < 0) {
					cout << "|		金额不合理！\n";
				} else {
					if (balance + default_max_overdraft >= money) {
						toPay(this, money);
					} else {
						cout << "|		支付失败，已超透支额上限！\n";
					}
				}
				break;
			}
			case 2:{
				double d;
				cout << "|	请输入存储金额：";
				cin >> d;
				deposit(d);
				break;
			}
			case 3:{
				double p;
				string account;
				cout << "|	请输入充值的校园卡号：";
				cin >> account;
				if (findCcardByAcc(account, Ccards) != -1) {
					cout << "|	请输入充值金额：";
					cin >> p;
					if (p > 0) {
						if (balance + default_max_overdraft >= p) {
							pay(p);
							Ccards[findCcardByAcc(account, Ccards)].setBalance(Ccards[findCcardByAcc(account, Ccards)].getBalance() + p);
							cout << "|		已充值成功！\n";
							if (overdraft) {
								cout << "|		储蓄卡余额不足，已透支" << overdraft << "元！\n";
							}
						} else {
							cout << "|		充值失败，已超透支额上限！\n";
						}
					} else {
						cout << "|		金额不合理！\n";
					}
				} else {
					cout << "|		无此校园卡账号！\n";
				}
				break;
			}
			case 4:{
				double p;
				string account;
				cout << "|	请输入转账的储蓄卡号：";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	请输入转账金额：";
					cin >> p;
					if (p > 0) {
						if (balance + default_max_overdraft >= p) {
							toPay(this, p);
							Dcards[findDcardByAcc(account, Dcards)].setBalance(Dcards[findDcardByAcc(account, Dcards)].getBalance() + p);
							cout << "|		已转账成功！\n";
						} else {
							cout << "|		充值失败，已超透支额上限！\n";
						}
					} else {
						cout << "|		金额不合理！\n";
					}
				} else {
					cout << "|		无此储蓄卡卡账号！\n";
				}
				break;
			}
			case 5:{
				printDepositInfo();
				break;
			}
			case 6:{
				cout << "|	此卡使用流水记录如下：\n"; 
				printRecords();
				break;
			}
			case 7:{
				string new_name;
				cout << "|	请输入新户主名：";
				cin >> new_name;
				name = new_name;
				cout << "|		已设置新户主名！\n";
				break;
			}
			case 8:{
				string new_pw;
				cout << "|	请输入新密码：";
				cin >> new_pw;
				password = new_pw;
				cout << "|		已设置新密码！\n";
				break;
			}
			default:{
				cout << "|		储蓄卡无此功能！\n";
				break;
			}
		}
		cout << "|	请选择储蓄卡功能："; 
		cin >> service;
	}
	cout << "|		储蓄卡账号已安全注销！\n";
}

//以上为deposit_card类实现 




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
		cout << "|		支付失败，已超透支额上限！\n";
	}
}

void binding_card :: printRecords() {
	cout << "|	校园卡使用记录如下：\n";
	binded_campus_card->printRecords();
	cout << "|	储蓄卡使用记录如下：\n";
	for (int i = 0; i < binded_deposit_cards.size(); i++) {
		binded_deposit_cards[i]->printRecords();
	}
}

void binding_card :: printBindingInfo() {
	cout << "+------------------------------------------------------------------\n"
		 << "|                          您的绑定卡信息\n"
		 << "      /  姓名：" << binded_campus_card->getName() << "\n"
		 << "     /  学号：" << binded_campus_card->getSno() << "\n"
		 << "    /  学院：" << binded_campus_card->getAcademy() << "\n"
		 << "   /  绑定卡号："<< account << "\n"
		 << "  /  发卡日期："<< create_time.year << "年" << create_time.month << "月" << create_time.day << "日\n"
		 << " /  校园卡号："<< binded_campus_card->account << "\n"
		 << "/  绑定卡余额："<< binded_campus_card->getBalance() << "\n";
		 for (int i = 0; i < binded_deposit_cards.size(); i++) {
		 	cout << "|  储蓄卡" << i << "卡号：" << binded_deposit_cards[i]->account << "\n";
		 }
		 cout << "+------------------------------------------------------------------\n";
}

void binding_card :: useBindingCard(vector<binding_card>& Bcards, vector<campus_card>& Ccards, vector<deposit_card>& Dcards) {
	introBindingCard();
	int service;
	cout << "|	请选择绑定卡功能："; 
	cin >> service;
	while (service) {
		switch (service) {
			case 1:{
				double money;
				cout << "|	请输入支付金额：";
				cin >> money;
				if (money < 0) {
					cout << "|		金额不合理！\n";
				} else {
					toPay(this, money);
				}
				break;
			}
			case 2:{
				double money;
				string account;
				cout << "|	选择存入的储蓄卡：";
				cin >> account;
				int i;
				for (i = 0; i < binded_deposit_cards_num; i++) {
					if (binded_deposit_cards[findDcardByAcc(account, Dcards)]->account == account) {
						break;
					}
				}
				if (i != binded_deposit_cards_num) {
					cout << "|	请输入存储金额：";
					cin >> money;
					binded_deposit_cards[findDcardByAcc(account, Dcards)]->deposit(money);
				} else {
					cout << "|		未绑定此储蓄卡！\n";
				}
				break;
			}
			case 3:{
				string account, pw;
				cout << "|	请输入添加的储蓄卡卡号：";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	请输入新加储蓄卡密码：";
					cin >> pw;
					if (pw == Dcards[findDcardByAcc(account, Dcards)].getPassword()) {
						binded_deposit_cards.push_back(new deposit_card());
						binded_deposit_cards[binded_deposit_cards.size() - 1] = &(Dcards[findDcardByAcc(account, Dcards)]);
						binded_deposit_cards_num++;
						cout << "|		绑定储蓄卡成功！\n";
					} else {
						cout << "|		密码错误，添加失败！\n";
					}
				} else {
					cout << "|		无此储蓄卡账号！\n";
				}
				break;
			}
			case 4:{
				double money;
				string account;
				cout << "|	请输入转账的储蓄卡号：";
				cin >> account;
				if (findDcardByAcc(account, Dcards) != -1) {
					cout << "|	请输入转账金额：";
					cin >> money;
					if (money >= 0) {
						toPay(this, money);
					} else {
						cout << "|		金额不合理！\n";
					}
				} else {
					cout << "|		无此储蓄卡账号！\n";
				}
				break;
			}
			case 5:{
				printBindingInfo();
				break;
			}
			case 6:{
				cout << "|	此卡使用流水记录如下：\n"; 
				printRecords();
				break;
			}
			case 7:{
				string new_pw;
				cout << "|	请输入新密码：";
				cin >> new_pw;
				setPassword(new_pw);
				cout << "|		已设置新密码！\n";
				break;
			}
			default:{
				cout << "|		绑定卡无此功能！\n";
				break;
			}
		}
		cout << "|	请选择绑定卡功能："; 
		cin >> service;
	}
	balance = binded_campus_card->getBalance();
	name = binded_campus_card->getName();
	sno = binded_campus_card->getSno();
	academy = binded_campus_card->getAcademy();
	initialized = binded_campus_card->getInitialized();
	cout << "|		绑定卡账号已安全注销！\n";
}

//以上为binding_card类实现 




void toPay(Card* ptr, double money) {
	ptr->pay(money);
}

//按卡类选择支付方式支付 

 

void introSystem() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                     欢迎使用SYSU校园卡管理系统                   |\n"
		 << "+------------------------------------------------------------------+\n"
		 << "|系统功能如下:                                                     |\n"
		 << "|    1激活校园卡                                                   |\n"
		 << "|    2激活储蓄卡                                                   |\n"
		 << "|    3激活绑定卡                                                   |\n"
		 << "|    4使用校园卡                                                   |\n"
		 << "|    5使用储蓄卡                                                   |\n"
		 << "|    6使用绑定卡                                                   |\n"
		 << "|    0退出                                                         |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introCampusCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      使用校园卡登录系统成功！                    |\n"
		 << "|  校园卡功能如下:                                                 |\n"
		 << "|    1支付                                                         |\n"
		 << "|    2查看账号信息                                                 |\n"
		 << "|    3查看使用记录                                                 |\n"
		 << "|    4初始化个人资料（只有一次机会）                               |\n"
		 << "|    5修改密码                                                     |\n"
		 << "|    0注销登录                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introDepositCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      使用储蓄卡登录系统成功！                    |\n"
		 << "|  储蓄卡功能如下:                                                 |\n"
		 << "|    1支出                                                         |\n"
		 << "|    2存入                                                         |\n"
		 << "|    3为校园卡充值                                                 |\n"
		 << "|    4转账                                                         |\n"
		 << "|    5查看账户信息                                                 |\n"
		 << "|    6查看使用记录                                                 |\n"
		 << "|    7修改户主                                                     |\n"
		 << "|    8修改密码                                                     |\n"
		 << "|    0注销登录                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

void introBindingCard() {
	cout << "+------------------------------------------------------------------+\n"
		 << "|                      使用绑定卡登录系统成功！                    |\n"
		 << "|  绑定卡功能如下:                                                 |\n"
		 << "|    1支付                                                         |\n"
		 << "|    2存入                                                         |\n"
		 << "|    3添加新的储蓄卡                                               |\n"
		 << "|    4转账                                                         |\n"
		 << "|    5查看账户信息                                                 |\n"
		 << "|    6查看使用记录                                                 |\n"
		 << "|    7修改密码                                                     |\n"
		 << "|    0注销登录                                                     |\n"
		 << "+------------------------------------------------------------------+\n";
}

//以上为纯输出函数 




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

//以上为文件输入输出实现 




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

//以上判断卡号是否重复 




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

//以上为按卡号返回下标 

