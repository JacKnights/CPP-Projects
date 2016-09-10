#include "Date.h"
#include <ctime>

Date::Date() {
	time_t rawtime; 
	tm timeinfo; 
	time (&rawtime); 
	localtime_s (&timeinfo, &rawtime);
	year = 1900 + timeinfo.tm_year;
	month = 1 + timeinfo.tm_mon;
	day = timeinfo.tm_mday;
}

Date::Date(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}