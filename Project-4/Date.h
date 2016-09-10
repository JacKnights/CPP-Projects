#ifndef _DATE_H_
#define _DATE_H_
#include <ostream>


class Date {
	public:
	Date();
	Date(int, int, int);
	friend std::ostream& operator<<(std::ostream&, Date);
	int year, month, day;
};

const Date default_publish_date(0, 0, 0);



#endif