#include "Book.h"
#include "Outside.h"
#include <iostream>

using namespace std;

int Book::books_num = 0;



Book::Book() {
	records_num = 0;
	total_num = in_num = out_num = 0;
}

Book::Book(string isbn) {
	ISBN = isbn;
	name = default_book_name;
	writer = default_write;
	publish_date = default_publish_date;
	records_num = 0;
	total_num = in_num = out_num = 0;
}

void Book::bookInfo() const {
	cout << "������" << name << endl;
	cout << "ISBN��" << ISBN << endl;
	cout << "���ߣ�" << writer << endl;
	cout << "�������ڣ�" << publish_date << endl;
	cout << "�ܲ�����" << total_num << endl;
	cout << "�ֹݴ�����" << in_num << endl;
	cout << "�ѽ������" << out_num << endl;
}

void Book::bookRecords() const {
	for (int i = 0; i != records_num; i++) {
		cout << records[i] << endl;
	}
}

void Book::lendBook(Reader& reader) {
	in_num--;
	out_num++;
	records_num++;
	records.push_back(Book_Record(0));
	int end = records.size() - 1;
	records[end].borrower_name = reader.name;
	records[end].borrower_account = reader.account;
}

void Book::retrieveBook(Reader& reader) {
	in_num++;
	out_num--;
	records_num++;
	records.push_back(Book_Record(1));
	int end = records.size() - 1;
	records[end].borrower_name = reader.name;
	records[end].borrower_account = reader.account;
}

vector<Book_Record>& Book::getRecords() {
	return records;
}