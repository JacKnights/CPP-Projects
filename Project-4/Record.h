#pragma once
#include <string>
#include <vector>
#include "Date.h"

using namespace std;



const int default_deadline = 30;
const string default_book_name = "unknown";
const string default_write = "unknown";

class Record {
	public:
	Record();
	void extendDeadline();
	protected:
	bool if_return;
	Date create_date;
	int deadline;

};

class Book_Record : public Record {
	public:
	Book_Record();
	Book_Record(bool);
	string getBorrowerAccount() const;
	friend ostream& operator<<(ostream&, Book_Record);
	friend class Book;
	friend void readInBook(vector<Book>&);
	friend void writeOutBook(vector<Book>);
	private:
	string borrower_name;
	string borrower_account;
};

class Reader;

class Reader_Record : public Record {
	public:
	Reader_Record();
	Reader_Record(bool);
	string book_name;
	string book_ISBN;
	friend ostream& operator<<(ostream&, Reader_Record);
	friend void readInReader(vector<Reader>&);
	friend void writeOutReader(vector<Reader>);
	private:
	bool if_return;
	Date create_date;
	int deadline;
};