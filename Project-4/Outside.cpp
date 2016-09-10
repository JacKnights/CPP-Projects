#include "Outside.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

void libraryIntro() {
	cout << "+--------------��ӭʹ��SYSUͼ�����ϵͳ--------------+" << endl;
	cout << "|    ϵͳ�������£�                                  |" << endl;
	cout << "|        1.���ߵ�¼                                  |" << endl;
	cout << "|        2.����ע��                                  |" << endl;
	cout << "|        3.����Ա��¼                                |" << endl;
	cout << "|        4.����Աע��                                |" << endl;
	cout << "|        0.�˳�                                      |" << endl;
	cout << "+----------------------------------------------------+" << endl;
}

void readerIntro() {
	cout << "+-------------------------------------------------+" << endl;
	cout << "|    ���߿�ѡ�������£�                           |" << endl;
	cout << "|        1.����                                   |" << endl;
	cout << "|        2.����                                   |" << endl;
	cout << "|        3.����                                   |" << endl;
	cout << "|        4.��ѯͼ��                               |" << endl;
	cout << "|        5.��ӡ����ͼ����Ϣ                       |" << endl;
	cout << "|        6.�鿴���˼�¼                           |" << endl;
	cout << "|        0.�˳�                                   |" << endl;
	cout << "+-------------------------------------------------+" << endl;
}

void adminIntro() {
	cout << "+-------------------------------------------------+" << endl;
	cout << "|    ���߿�ѡ�������£�                           |" << endl;
	cout << "|        1.�ϼ�ͼ��                               |" << endl;
	cout << "|        2.�¼�ͼ��                               |" << endl;
	cout << "|        3.�޸�ͼ������                           |" << endl;
	cout << "|        4.��ѯͼ��                               |" << endl;
	cout << "|        5.��ӡ����ͼ����Ϣ                       |" << endl;
	cout << "|        6.�鿴���߼�¼                           |" << endl;
	cout << "|        0.�˳�                                   |" << endl;
	cout << "+-------------------------------------------------+" << endl;
}

int findAdminByAccount(string account, vector<Admin> admins) {
	for (int i = 0; i != admins.size(); i++) {
		if (account == admins[i].account) {
			return i;
		}
	}
	throw(logic_error("|�޴��˺ţ�"));
}

int findReaderByAccount(string account, vector<Reader> readers) {
	for (int i = 0; i != readers.size(); i++) {
		if (account == readers[i].account) {
			return i;
		}
	}
	throw(logic_error("|�޴��˺ţ�"));
}

int findBookByISBN(string ISBN, vector<Book> books) {
	for (int i = 0; i != books.size(); i++) {
		if (ISBN == books[i].ISBN) {
			return i;
		}
	}
	throw(logic_error("|�޴���ţ�"));
}

int findRecordByAccount(string account, vector<Book_Record> records) {
	for (int i = 0; i != records.size(); i++) {
		if (account== records[i].getBorrowerAccount()) {
			return i;
		}
	}
	throw(logic_error("|�޴˼�¼��"));
}

int findRecordByISBN(string isbn, const vector<Reader_Record> records) {
	for (int i = 0; i != records.size(); i++) {
		if (isbn== records[i].book_ISBN) {
			return i;
		}
	}
	throw(logic_error("|�޴˼�¼��"));
}

string newAccount(string old_account) {
	int tempint = atoi(old_account.c_str()) + 1;
	char tempchar[8];
	sprintf_s(tempchar, "%d", tempint);
	string tempstr(tempchar);
	string new_account = "";
	for (int i = 0; i != 8 - tempstr.size(); i++) {
		new_account += '0';	
	}
	new_account += tempchar;
	return new_account;
}

ostream& operator<<(ostream& out, Date date) {
	cout << date.year << "��" << date.month << "��" << date.day << "��";
	return out;
}

ostream& operator<<(ostream& out, Book_Record record) {
	cout << record.borrower_name << '(' << record.borrower_account << ')'<< "��" 
		<< record.create_date;
	if (record.if_return) {
		cout << "�黹";
	} else {
		cout << "���������Ϊ" << record.deadline << "��";
	}
	return out;
}

ostream& operator<<(ostream& out, Reader_Record record) {
	cout << "����" << record.create_date;
	if (record.if_return) {
		cout << "�黹";
	} else {
		cout << "���";
	}
	cout << record.book_name << '(' << record.book_ISBN << ')';
	if (!record.if_return) {
		cout << "������Ϊ" << record.deadline << "��";
	}
	return out;
}

void readInBook(vector<Book>& books) {
	ifstream read;
	read.open("Book.txt");
	read >> Book::books_num;
	for (int i = 0; i != Book::books_num; i++) {
		books.push_back(Book());
		read >> books[i].name 
			>> books[i].ISBN 
			>> books[i].writer
			>> books[i].publish_date.year 
			>> books[i].publish_date.month 
			>> books[i].publish_date.day
			>> books[i].total_num 
			>> books[i].in_num 
			>> books[i].out_num 
			>> books[i].records_num; 
		for (int j = 0; j != books[i].records_num; j++) {
			books[i].records.push_back(Book_Record());
			read >> books[i].records[j].borrower_name;
			read >> books[i].records[j].borrower_account;
			read >> books[i].records[j].create_date.year;
			read >> books[i].records[j].create_date.month;
			read >> books[i].records[j].create_date.day;
			read >> books[i].records[j].if_return;
			read >> books[i].records[j].deadline;
		}
	}
	read.close();
}

void writeOutBook(vector<Book> books) {
	ofstream write;
	write.open("Book.txt");
	write << Book::books_num << endl;
	for (int i = 0; i != Book::books_num; i++) {
		write << books[i].name << ' ' 
			<< books[i].ISBN << ' '
			<< books[i].writer << ' ' 
			<< books[i].publish_date.year << ' '
			<< books[i].publish_date.month << ' '
			<< books[i].publish_date.day << ' '
			<< books[i].total_num << ' '
			<< books[i].in_num << ' '
			<< books[i].out_num << ' ' 
			<< books[i].records_num << endl;
		for (int j = 0; j != books[i].records_num; j++) {
			write << ' ' << books[i].records[j].borrower_name << ' '
				<< books[i].records[j].borrower_account << ' '
				<< books[i].records[j].create_date.year << ' '
				<< books[i].records[j].create_date.month << ' '
				<< books[i].records[j].create_date.day << ' '
				<< books[i].records[j].if_return << ' '
				<< books[i].records[j].deadline << endl;
		}
	}
	write.close();
}


void readInReader(vector<Reader>& readers) {
	ifstream read;
	read.open("Reader.txt");
	read >> Reader::readers_num;
	for (int i = 0; i != Reader::readers_num; i++) {
		readers.push_back(Reader());
		read >> readers[i].name 
			>> readers[i].account 
			>> readers[i].password
			>> readers[i].create_date.year 
			>> readers[i].create_date.month
			>> readers[i].create_date.day
			>> readers[i].records_num;
		for (int j = 0; j != readers[i].records_num; j++) {
			readers[i].records.push_back(Reader_Record());
			read >> readers[i].records[j].book_name 
				>> readers[i].records[j].book_ISBN
				>> readers[i].records[j].create_date.year 
				>> readers[i].records[j].create_date.month
				>> readers[i].records[j].create_date.day 
				>> readers[i].records[j].if_return
				>> readers[i].records[j].deadline;
		}
	}
	read.close();
}

void writeOutReader(vector<Reader> readers) {
	ofstream write;
	write.open("Reader.txt");
	write << Reader::readers_num << endl;
	for (int i = 0; i != Reader::readers_num; i++) {
		write << readers[i].name << ' ' 
			<< readers[i].account << ' '
			<< readers[i].password << ' '
			<< readers[i].create_date.year << ' '
			<< readers[i].create_date.month << ' '
			<< readers[i].create_date.day << ' '
			<< readers[i].records_num << endl;
		for (int j = 0; j != readers[i].records_num; j++) {
			write << readers[i].records[j].book_name << ' '
				<< readers[i].records[j].book_ISBN << ' '
				<< readers[i].records[j].create_date.year << ' '
				<< readers[i].records[j].create_date.month << ' '
				<< readers[i].records[j].create_date.day << ' '
				<< readers[i].records[j].if_return << ' '
				<< readers[i].records[j].deadline << endl;
		}
	}
	write.close();
}

void readInAdmin(vector<Admin>& admins) {
	ifstream read;
	read.open("Admin.txt");
	read >> Admin::admins_num;
	for (int i = 0; i != Admin::admins_num; i++) {
		admins.push_back(Admin());
		read >> admins[i].name
			>> admins[i].account
			>> admins[i].password
			>> admins[i].create_date.year
			>> admins[i].create_date.month
			>> admins[i].create_date.day;
	}
	read.close();
}



void writeOutAdmin(vector<Admin> admins) {
	ofstream write;
	write.open("Admin.txt");
	write << Admin::admins_num << endl;
	for (int i = 0; i != Admin::admins_num; i++) {
		write << admins[i].name << ' ' 
			<< admins[i].account << ' '
			<< admins[i].password << ' '
			<< admins[i].create_date.year << ' '
			<< admins[i].create_date.month << ' '
			<< admins[i].create_date.day << endl;
	}
	write.close();
}