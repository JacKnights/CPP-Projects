#include <windows.h>
#include "Function.cpp"

using namespace std;

int main() {
	
	introSystem();
	
	vector<campus_card> Ccards;
	vector<deposit_card> Dcards;
	vector<binding_card> Bcards;
	
	readCampusCard(Ccards);
	readDepositCard(Dcards);
	readBindingCard(Bcards, Ccards, Dcards);
	
	int service;
	string account;
	cout << "|请选择系统功能：" ;
	cin >> service;
	while (service) {
		//系统运行直到按0退出 
		switch (service) {
			
			case 1:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	激活校园卡号:" ;
				cin >> account;
				if (account[0] == 'c' && account.length() == 6 && !repeated(account, Ccards)) {
					Ccards.push_back(campus_card(account));
					Ccards[Ccards.size() - 1].create_time.setRecord();
					cout << "|		校园卡激活成功！\n";
					cout << "|	请设置密码：";
					string pw;
					cin >> pw;
					Ccards[Ccards.size() - 1].setPassword(pw);
					cout << "|		密码设置成功！\n";
				} else {
					cout << "|		激活失败！卡号有误或已被激活！\n";
				}
				break;
			}
			//输入账号激活校园卡
			
			case 2:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
				cout << "|	激活储蓄卡号:" ;
				cin >> account;
				if (account[0] == 'd' && account.length() == 6 && !repeated(account, Dcards)) {
					Dcards.push_back(deposit_card(account));
					cout << "|		储蓄卡激活成功！\n";
					Dcards[Dcards.size() - 1].create_time.setRecord();
					cout << "|	请设置密码：";
					string pw;
					cin >> pw;
					Dcards[Dcards.size() - 1].setPassword(pw);
				} else {
					cout << "|		激活失败！卡号有误或已被激活！\n";
				}
				break;
			}
			//输入账号激活储蓄卡
			
			case 3:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
				cout << "|	激活绑定卡号:" ;
				cin >> account;
				if (account[0] == 'b' && account.length() == 6 && !repeated(account, Bcards)) {
					string  Cacc, Dacc, password;
					cout << "|	输入绑定的校园卡号:";
					cin >> Cacc;
					if (findCcardByAcc(Cacc, Ccards) != -1) {
						cout << "|	输入校园卡密码：";
						cin >> password;
						if (password == Ccards[findCcardByAcc(Cacc, Ccards)].getPassword()) {
							Bcards.push_back(binding_card(account, Cacc, Ccards));
							cout << "|		绑定卡激活成功！\n";
							Bcards[Bcards.size() - 1].create_time.setRecord();
							cout << "|	请设置密码：";
							cin >> password;
							Bcards[Bcards.size() - 1].setPassword(password);
							cout << "|		密码设置成功！\n";
						} else {
							cout << "|		密码错误，绑定失败！\n";
						}
					} else {
						cout << "|		不存在此校园卡！\n";
					}
				} else {
					cout << "|		激活失败！卡号有误或已被激活！\n";
				}
				break;
			}
			//输入激活绑定卡账号并绑定指定校园卡 
			
			case 4:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	登录校园卡号:" ;
				cin >> account;
				if (findCcardByAcc(account, Ccards) == -1) {
					cout << "|		无此账号！\n";
				} else {
					cout << "|	请输入密码：";
					string password;
					cin >> password;
					if (password != Ccards[findCcardByAcc(account, Ccards)].getPassword()) {
						cout << "|		密码错误！\n";
					} else {
						Ccards[findCcardByAcc(account, Ccards)].useCampusCard();
					}
				}
				break;
			}
			//登录校园卡 
			
			case 5:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
				cout << "|	登录储蓄卡号:" ;
				cin >> account;
				if (findDcardByAcc(account, Dcards) == -1) {
					cout << "|		无此账号！\n";
				} else {
					cout << "|	请输入密码：";
					string password;
					cin >> password;
					if (password != Dcards[findDcardByAcc(account, Dcards)].getPassword()) {
						cout << "|		密码错误！\n";
					} else {
						Dcards[findDcardByAcc(account, Dcards)].useDepositCard(Ccards, Dcards);
					}
				}
				break;
			}
			//登录储蓄卡 
			
			case 6:{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
				cout << "|	登录绑定卡号:" ;
				cin >> account;
				if (findBcardByAcc(account, Bcards) == -1) {
					cout << "|		无此账号！\n";
				} else {
					cout << "|	请输入密码：";
					string password;
					cin >> password;
					if (password != Bcards[findBcardByAcc(account, Bcards)].getPassword()) {
						cout << "|		密码错误！\n";
					} else {
						Bcards[findBcardByAcc(account, Bcards)].useBindingCard(Bcards, Ccards, Dcards);
					}
				}
				break;
			}
			//登录绑定卡 
			
			default:{
				cout << "|		无此功能！请重新输入！\n";
				break;
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
		cout << "+------------------------------------------------------------------\n";
		cout << "|请选择系统功能：" ;
		cin >> service;
	}
	
	writeCampusCard(Ccards);
	writeDepositCard(Dcards);
	writeBindingCard(Bcards);
	cout << "|系统已安全退出！"; 
	return 0;
}
