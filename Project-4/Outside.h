#ifndef _OUTSIDE_H_
#define _OUTSIDE_H_
#include "Book.h"
#include "User.h"
#include "Record.h"

const string default_system_password = "sysulibrary";

void libraryIntro();

void readerIntro();

void adminIntro();

int findAdminByAccount(string, const vector<Admin>);

int findReaderByAccount(string, const vector<Reader>);

int findBookByISBN(string, const vector<Book>);

int findRecordByAccount(string, const vector<Book_Record>);

int findRecordByISBN(string, const vector<Reader_Record>);

ostream& operator<<(ostream&, Date);

string newAccount(string);

void readInBook(vector<Book>&);

void readInReader(vector<Reader>&);

void readInAdmin(vector<Admin>&);

void writeOutBook(vector<Book>);

void writeOutReader(vector<Reader>);

void writeOutAdmin(vector<Admin>);

#endif