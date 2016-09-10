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

//----------------------------����ΪUser-----------------------------------

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
	cout << "|  �û�����" << name << endl;
	cout << "|  �˺ţ�" << account << endl;
	cout << "|  ע�����ڣ�" << create_date << endl;

}

void Reader::login(string password) {
	if (password != this->password) {
		throw(logic_error("|�������"));
	}
	readerIntro();
	readerInfo();
	vector<Book> books;
	readInBook(books);
	char service;
	cout << "|ѡ����߹��ܣ�";
	cin >> service;
	while (service != '0') {
		cin.sync();
		switch (service) {
			case '1':{
				try {
					string ISBN;
					cout << "|������ţ�";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					borrowBook(books[pos]);
					cout << "|����ɹ���" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what();
					cout << "|����ʧ�ܡ�" << endl;
				}
				break;
			}
			case '2':{
				try {
					string ISBN;
					cout << "|�黹��ţ�";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					returnBook(books[pos]);
					cout << "|�黹�ɹ���" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what();
					cout << "|�黹ʧ�ܡ�" << endl;
				}
				break;
			}
			case '3':{
				try {
					string ISBN;
					cout << "|������ţ�";
					cin >> ISBN;
					int pos1 = findBookByISBN(ISBN, books);
					int pos2 = findRecordByAccount(account, books[pos1].getRecords());
					books[pos1].getRecords()[pos2].extendDeadline();//
					int pos3 = findRecordByISBN(ISBN, records);
					records[pos3].extendDeadline();
					cout << "|������" << default_deadline << "�졣" << endl;
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '4':{
				try {
					string ISBN;
					cout << "|��ѯ��ţ�";
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
				cout << "|����ͼ����Ϣ���£�" << endl;
				for (int i = 0; i != books.size(); i++) {
					books[i].bookInfo();
					cout << "+--------------" << endl;
				}
				break;
			}
			case '6':{
				cout << "|����ʹ�ü�¼���£�" << endl;
				for (int i = 0; i != records.size(); i++) {
					cout << records[i] << endl;
				}
				break;
			}
			default:{
				cout << "|�޴˹��ܣ�" << endl;
				break;
			}
		}
		cout << "+------------------------------------+" << endl;
		cout << "|ѡ����߹��ܣ�";
		cin >> service;
	}
	writeOutBook(books);
	cout << "���˳������˺š�" << endl;
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


//----------------------------����ΪReader-----------------------------------


Admin::Admin(): User() {

}

Admin::Admin(string new_name, string new_account, string new_password): User() {
	account = new_account;
	name = new_name;
	password = new_password;
}

void Admin::adminInfo() const {
	cout << "|  ����Ա��" << name << endl;
	cout << "|  �˺ţ�" << account << endl;
	cout << "|  ע�����ڣ�" << create_date << endl;
}

void Admin::login(string password) {
	if (password != this->password) {
		throw(logic_error("|�������"));
	}
	adminInfo();
	vector<Book> books;
	readInBook(books);
	char service;
	cout << "|ѡ�����Ա���ܣ�";
	cin >> service;
	while (service != '0') {
		cin.sync();
		switch (service) {
			case '1':{
				string isbn;
				cout << "|�ϼ���ţ�";
				cin >> isbn;
				books.push_back(Book(isbn));
				int end = books.size() - 1;
				cout << "|������";
				cin >> books[end].name;
				cout << "|���ߣ�";
				cin >> books[end].writer;
				cout << "|�����ꡢ�¡��գ�";
				cin >> books[end].publish_date.year
					>> books[end].publish_date.month >> books[end].publish_date.day;
				cout << "|������";
				cin >> books[end].total_num;
				books[end].in_num = books[end].total_num;
				books[end].out_num = 0;
				cout << "|���ϼܸ��顣" << endl;
				break;
			}
			case '2':{
				string isbn;
				cout << "|�¼���ţ�";
				cin >> isbn;
				int pos = findBookByISBN(isbn, books);
				vector<Book>::iterator it = books.begin() + pos;
				books.erase(it);
				cout << "|���¼ܸ��顣" << endl;
				break;
			}
			case '3':{
				try {
					string ISBN;
					cout << "|�޸���ţ�";
					cin >> ISBN;
					int pos = findBookByISBN(ISBN, books);
					cout << "|�޸�������";
					int change;
					cin >> change;
					if (books[pos].in_num + change >= 0) {
						books[pos].in_num += change;
						books[pos].total_num = books[pos].in_num + books[pos].out_num;
						cout << "|�Ѹ���������" << endl;
					} else {
						cout << "|�������㣬�޸�ʧ�ܡ�" << endl;
					}
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			case '4':{
				try {
					string ISBN;
					cout << "|��ѯ��ţ�";
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
				cout << "|����ͼ����Ϣ���£�" << endl;
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
					cout << "|��ѯ�û���";
					cin >> account;
					int pos = findReaderByAccount(account, readers);
					readers[pos].readerInfo();
				} catch (logic_error no_book) {
					cout << no_book.what() << endl;
				}
				break;
			}
			default:{
				cout << "|�޴˹��ܣ�" << endl;
				break;
			}
		}
		cout << "+------------------------------------+" << endl;
		cout << "|ѡ�����Ա���ܣ�";
		cin >> service;
	}
	writeOutBook(books);
	cout << "���˳�����Ա�˺š�" << endl;
}