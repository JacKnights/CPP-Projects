#include <iostream>
#include "Outside.h"

using namespace std;

int main() {
	libraryIntro();
	char service;
	cout << "|选择系统功能：";
	cin >> service;
	while (service != '0') {
		cin.sync();
		switch (service) {
			case '1':{
				vector<Reader> readers;
				readInReader(readers);
				string account;
				cout << "|账号:";
				cin >> account;
				try {
					int pos = findReaderByAccount(account, readers);
					string password;
					cout << "|密码:";
					cin >> password;
					try {
						readers[pos].login(password);
						writeOutReader(readers);
					} catch (logic_error wrong_password) {
						cout << wrong_password.what() << endl;
					}
				} catch(logic_error no_account) {
					cout << no_account.what() << endl;
				}
				break;
			}

			case '2':{
				vector<Reader> readers;
				readInReader(readers);
				string name;
				cout << "|新用户名：";
				cin >> name;
				string password;
				cout << "|设置密码：";
				cin >> password;
				int end = readers.size() - 1; 
				string account = newAccount(readers[end].account);
				readers.push_back(Reader(name, account, password));
				Reader::readers_num++;
				cout << "|注册成功！新账号为：" << account << endl;
				writeOutReader(readers);
				break;
			}

			case '3':{
				vector<Admin> admins;
				readInAdmin(admins);
				string account;
				cout << "|账号:";
				cin >> account;
				try {
					int pos = findAdminByAccount(account, admins);
					string password;
					cout << "|密码:";
					cin >> password;
					try {
						admins[pos].login(password);
						writeOutAdmin(admins);
					} catch (logic_error wrong_password) {
						cout << wrong_password.what() << endl;
					}
				} catch(logic_error no_account) {
					cout << no_account.what() << endl;
				}
				break;
			}

			case '4':{
				try {
					string system_password;
					cout << "|系统密码：";
					cin >> system_password;
					if (system_password != default_system_password) {
						throw(logic_error("|密码错误！"));
					}
					vector<Admin> admins;
					readInAdmin(admins);
					string name;
					cout << "|新管理员名：";
					cin >> name;
					string password;
					cout << "|设置密码：";
					cin >> password;
					int end = admins.size() - 1;
					string account = newAccount(admins[end].account);
					admins.push_back(Admin(name, account, password));
					Admin::admins_num++;
					cout << "|注册成功！新账号为：" << account << endl;
					writeOutAdmin(admins);
				} catch(logic_error wrong_password) {
					cout << wrong_password.what() << endl;
				}
				break;
			}
		}
		cout << "+----------------------------------------------------+" << endl;
		cout << "|选择系统功能：";
		cin >> service;
	}
	cout << "已退出系统。" << endl;
	return 0;
}