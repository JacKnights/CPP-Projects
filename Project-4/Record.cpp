#include "Record.h"

Record::Record() {
	create_date = Date();
	if_return = 0;
	deadline = default_deadline;
}


Reader_Record::Reader_Record() : Record() {
	create_date = Date();
	if_return = 0;
	deadline = default_deadline;
}

Reader_Record::Reader_Record(bool ir) : Record() {
	create_date = Date();
	if_return = ir;
	deadline = default_deadline;
}


Book_Record::Book_Record() : Record() {
	create_date = Date();
	if_return = 0;
	deadline = default_deadline;
}

Book_Record::Book_Record(bool ir) : Record() {
	create_date = Date();
	if_return = ir;
	deadline = default_deadline;
}

void Record::extendDeadline() {
	deadline += default_deadline;
}

string Book_Record::getBorrowerAccount() const {
	return borrower_account;
}