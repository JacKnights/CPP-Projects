#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

class Record {
	//卡类使用历史纪录 
  public:
  	Record();
  	Record(string, double);
  	int year, month, day, hour, minute, second;
  	bool in_or_out;		//true为存入记录，false为支出记录 
  	string place;		//记录产生地点，由用户输入 
  	double spending;	//交易额 
	void setRecord(); 
	void setRecord(string, double, bool);
};

class Card {
	//卡基类，公有属性用于继承 
  public:
  	double getBalance();
  	string getName();
  	string getPassword();
  	string getRecord(int);
	virtual void pay(double);
	void setBalance(double);
  	void setName(string);
	void setPassword(string);
  	void printRecords();		//打印历史纪录 
	Card();
  	string account;				//账号 
  	int record_num;				//历史纪录数目 
  	vector<Record> records;		//历史纪录 
  	Record create_time;			//卡注册时间 
  protected:
  	double balance;		//账户余额 
  	string name;		//卡主姓名 
  	string password;	//密码 
};

class campus_card : virtual public Card {
	//校园卡，继承于Card类 
  public:
	campus_card();
	campus_card(string);
  	string getSno();
  	string getAcademy();
  	bool getInitialized();
  	void setInfo(int);
  	void setSno(string);
  	void setAcademy(string);
  	void setInitialized(bool);
  	void printCampusInfo();		//打印校园卡个人信息 
  	void useCampusCard();		//包装校园卡的各种功能 
  	friend void readCampusCard(vector<campus_card>&);	//友元函数，在读取文件信息时修改校园卡protected成员 
  	friend void writeCampusCard(vector<campus_card>&);	//友元函数，在写入文件信息时提取校园卡protected成员 
  	static int card_num;//已激活的校园卡数量 
  protected:
  	bool initialized;	//是否已初始化过校园卡信息，阻止已初始化对象信息再度被修改 
  	string sno;			//学号 
  	string academy;		//学院 
};

class deposit_card : virtual public Card {
	//储蓄卡类，继承于Card类 
  public:
	deposit_card();
	deposit_card(string);
	double getOverdraft();
	void setOverdraft(double);
	void pay(double);			//储蓄卡的支付方式，允许一定范围内透支 
	void deposit(double);
	void rechargeForCampusCard(campus_card, double);	//为指定校园卡充值 
	void printDepositInfo();	//打印储蓄卡信息 
	void useDepositCard(vector<campus_card>&, vector<deposit_card>&);	//包装储蓄卡功能 
	friend void readDepositCard(vector<deposit_card>&);		//友元函数，在读取文件信息时修改校园卡protected成员
	friend void writeDepositCard(vector<deposit_card>&);	//友元函数，在写入文件信息时提取校园卡protected成员 
  	static int card_num;		//已激活储蓄卡数量 
  protected:
  	double overdraft;		//透支额 
};

class binding_card : public campus_card, public deposit_card {
	//绑定卡类，继承于校园卡和储蓄卡 
  public:
	binding_card();
	binding_card(string, string, vector<campus_card>&);
	void printBindingInfo();	//打印绑定卡用户信息 
	void pay(double);
	void printRecords();		//重定义打印历史纪录函数，先输出校园卡纪录再输出储蓄卡纪录 
	void useBindingCard(vector<binding_card>&, vector<campus_card>&, vector<deposit_card>&);	//包装绑定卡功能 
	friend void readBindingCard(vector<binding_card>&);	//友元函数，方便读取 
	friend void writeBindingCard(vector<binding_card>&);//友元函数，方便写入 
  	static int card_num;		//已激活绑定卡数量 
  	campus_card* binded_campus_card;	//指针指向所绑定校园卡 
  	vector<deposit_card*> binded_deposit_cards;	//指针指向所绑定储蓄卡 
  	int binded_deposit_cards_num;		//所绑定的储蓄卡数量 
};


#endif
