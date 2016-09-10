#ifndef _USER_H_
#define _USER_H_
#include <vector>
#include "Date.h"
#include "Record.h"

using namespace std;

class Book;
class Reader;


class User {
	public:
	User();
	string account;
	string name;

	protected:
	string password; 
	Date create_date;

};

class Reader: public User {
	public:
	Reader();
	Reader(string, string, string);
	void login(string);
	void readerInfo() const;
	void borrowBook(Book&);
	void returnBook(Book&);
	static int readers_num;
	friend void readInReader(vector<Reader>&);
	friend void writeOutReader(vector<Reader>);

	private:
	int records_num;
	vector<Reader_Record> records;
};


class Admin: public User {
	public:
	Admin();
	Admin(string, string, string);
	void adminInfo() const;
	void login(string);
	static int admins_num;
	friend void readInAdmin(vector<Admin>&);
	friend void writeOutAdmin(vector<Admin>);
};

#endif

