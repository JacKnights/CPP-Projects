#include <iostream>
#include "User.h"
#include "Outside.h"
#include <iomanip>

using namespace std;

int Reader::readers_num = 0;

int Admin::admins_num = 0;





User::User() {
	create_date = Date();
}

//----------------------------以上为User-----------------------------------

Reader::Reader(): User() {
	records_num = 0;
}

Reader::Reader(string new_name, string new_account, string new_password): User() {
	account = new_account;
	name = new_name;
	password = new_password;
	records_num = 0;
}



void Reader::readerInfo() const {
	cout << "|  用户名：" << name << endl;
	cout << "|  账号：" << account << endl;
	cout << "|  注册日期：" << create_date << endl;

}

void Reader::login(string password) {
	if (password != this->password) {
		throw(logic_error("|密码错误！"));
	}
	readerIntro();
	readerInfo();
	vector<Book> books;
	readInBook(books);
	char service;
	cout << "|选择读者功能：";
	cin >> service;
	while (service != '0') {
		cin.sync();
		switch (service) {
			case '1':{
				try {
					string ISBN;
					cout << "|借阅书号：";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					borrowBook(books[pos]);
					cout << "|借书成功。" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what();
					cout << "|借书失败。" << endl;
				}
				break;
			}
			case '2':{
				try {
					string ISBN;
					cout << "|归还书号：";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					returnBook(books[pos]);
					cout << "|归还成功。" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what();
					cout << "|归还失败。" << endl;
				}
				break;
			}
			case '3':{
				try {
					string ISBN;
					cout << "|续借书号：";
					cin >> ISBN;
					int pos1 = findBookByISBN(ISBN, books);
					int pos2 = findRecordByAccount(account, books[pos1].getRecords());
					books[pos1].getRecords()[pos2].extendDeadline();//
					int pos3 = findRecordByISBN(ISBN, records);
					records[pos3].extendDeadline();
					cout << "|已续期" << default_deadline << "天。" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '4':{
				try {
					string ISBN;
					cout << "|查询书号：";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					books[pos].bookInfo();
					books[pos].bookRecords();
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '5':{
				cout << "|所有图书信息如下：" << endl;
				for (int i = 0; i != books.size(); i++) {
					books[i].bookInfo();
					cout << "+--------------" << endl;
				}
				break;
			}
			case '6':{
				cout << "|您的使用记录如下：" << endl;
				for (int i = 0; i != records.size(); i++) {
					cout << records[i] << endl;
				}
				break;
			}
			default:{
				cout << "|无此功能！" << endl;
				break;
			}
		}
		cout << "+------------------------------------+" << endl;
		cout << "|选择读者功能：";
		cin >> service;
	}
	writeOutBook(books);
	cout << "已退出读者账号。" << endl;
}

void Reader::borrowBook(Book& book) {
	book.lendBook(*this);
	records_num++;
	records.push_back(Reader_Record(0));
	int end = records.size() - 1;
	records[end].book_ISBN = book.ISBN;
	records[end].book_name = book.name;
}

void Reader::returnBook(Book& book) {
	book.retrieveBook(*this);
	records_num++;
	records.push_back(Reader_Record(1));
	int end = records.size() - 1;
	records[end].book_ISBN = book.ISBN;
	records[end].book_name = book.name;
}


//----------------------------以上为Reader-----------------------------------


Admin::Admin(): User() {

}

Admin::Admin(string new_name, string new_account, string new_password): User() {
	account = new_account;
	name = new_name;
	password = new_password;
}

void Admin::adminInfo() const {
	cout << "|  管理员：" << name << endl;
	cout << "|  账号：" << account << endl;
	cout << "|  注册日期：" << create_date << endl;
}

void Admin::login(string password) {
	if (password != this->password) {
		throw(logic_error("|密码错误！"));
	}
	adminInfo();
	vector<Book> books;
	readInBook(books);
	char service;
	cout << "|选择管理员功能：";
	cin >> service;
	while (service != '0') {
		cin.sync();
		switch (service) {
			case '1':{
				string isbn;
				cout << "|上架书号：";
				cin >> isbn;
				books.push_back(Book(isbn));
				int end = books.size() - 1;
				cout << "|书名：";
				cin >> books[end].name;
				cout << "|作者：";
				cin >> books[end].writer;
				cout << "|出版年、月、日：";
				cin >> books[end].publish_date.year
					>> books[end].publish_date.month >> books[end].publish_date.day;
				cout << "|总数：";
				cin >> books[end].total_num;
				books[end].in_num = books[end].total_num;
				books[end].out_num = 0;
				cout << "|已上架该书。" << endl;
				break;
			}
			case '2':{
				string isbn;
				cout << "|下架书号：";
				cin >> isbn;
				int pos = findBookByISBN(isbn, books);
				vector<Book>::iterator it = books.begin() + pos;
				books.erase(it);
				cout << "|已下架该书。" << endl;
				break;
			}
			case '3':{
				try {
					string ISBN;
					cout << "|修改书号：";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					cout << "|修改数量：";
					int change;
					cin >> change;
					if (books[pos].in_num + change >= 0) {
						books[pos].in_num += change;
						books[pos].total_num = books[pos].in_num + books[pos].out_num;
						cout << "|已更改数量。" << endl;
					} else {
						cout << "|数量不足，修改失败。" << endl;
					}
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '4':{
				try {
					string ISBN;
					cout << "|查询书号：";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					books[pos].bookInfo();
					books[pos].bookRecords();
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '5':{
				cout << "|所有图书信息如下：" << endl;
				for (int i = 0; i != books.size(); i++) {
					books[i].bookInfo();
				}
				break;
			}
			case '6':{
				try {
					vector<Reader> readers;
					readInReader(readers);
					string account;
					cout << "|查询用户：";
					cin >> account;
					int pos = findReaderByAccount(account, readers);
					readers[pos].readerInfo();
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			default:{
				cout << "|无此功能！" << endl;
				break;
			}
		}
		cout << "+------------------------------------+" << endl;
		cout << "|选择管理员功能：";
		cin >> service;
	}
	writeOutBook(books);
	cout << "已退出管理员账号。" << endl;
}