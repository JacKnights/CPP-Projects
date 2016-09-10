#ifndef _BOOK_H_
#define _BOOK_H_
#include <vector>
#include <string>
#include "User.h"
#include "Record.h"


class User;
class Reader;
class Admin;


class Book {
	public:
	Book();
	Book(string);
	void bookInfo() const;
	void bookRecords() const;
	void lendBook(Reader&);
	void retrieveBook(Reader&);
	vector<Book_Record>& getRecords();
	string name;
	string ISBN;
	string writer;
	Date publish_date;
	int total_num;
	int in_num;
	int out_num;
	static int books_num;
	friend void readInBook(vector<Book>&);
	friend void writeOutBook(vector<Book>);
	protected:
	int records_num;
	vector<Book_Record> records;
};


#endif

