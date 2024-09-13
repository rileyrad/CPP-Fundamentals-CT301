#include "Holiday.h"
#include <iomanip>

using namespace std;

Holiday::Holiday(const string &name) 
: Priority_Event(name) {}

Holiday::Holiday(const string &name, bool is_gov) 
: Priority_Event(name, is_gov ? 0 : 15) {}

Holiday::Holiday(const string &name, const string &date)
: Priority_Event(name, date) {}

Holiday::Holiday(const string &name, const string &date, bool is_gov) 
: Priority_Event(name, date, is_gov ? 0 : 15) {}

Holiday::Holiday(const string &name, int y, int m, int d) 
: Priority_Event(name, y, m, d) {}

Holiday::Holiday(const string &name, int y, int m, int d, bool is_gov) 
: Priority_Event(name, y, m, d, is_gov ? 0 : 15) {}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the left object is zero. If it is, returns
// false, otherwise true. If the dates aren't the same, return the result of comparing the
// two dates.
bool Holiday::operator<(const Event &rhs) const {
	if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
		if (GetPriority() == 0) {
			return false;
		} else {
			return true;
		}
	}
	return year() < rhs.year() 
    || (year() == rhs.year() && (month() < rhs.month() 
    || (month() == rhs.month() && day() < rhs.day())));
}

/*operator<*/
// Creates a temporary Event object using the input string then compares
// the current object and the Event using the operator above this one (it 
// would otherwise contain the same code).
bool Holiday::operator<(const string &rhs) const {
	Event tmp(rhs);
    return (*this) < tmp;
}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the left object is zero (is a government 
// holiday), or the priority of the right object is greater than 15. If either of these are 
// true, return false, otherwise return true. If the dates aren't the same, return the result 
// of comparing the two dates.
bool Holiday::operator<(const Priority_Event &rhs) const {
	if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
		if (GetPriority() == 0 || rhs.GetPriority() > 15) {
			return false;
		} else {
			return true;
		}
	}
	return year() < rhs.year() 
    || (year() == rhs.year() && (month() < rhs.month() 
    || (month() == rhs.month() && day() < rhs.day())));
}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the left object is not zero (left side is 
// not a government holiday), or if the priority of the right object is 0 (right side is a 
// government holiday). If both of these are true, return true, otherwise false. If the dates 
// aren't the same, return the result of comparing the two dates.
bool Holiday::operator<(const Holiday &rhs) const {
	if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
		if (GetPriority() != 0 && rhs.GetPriority() == 0) {
			return true;
		} else {
			return false;
		}
	}
	return year() < rhs.year() 
    || (year() == rhs.year() && (month() < rhs.month() 
    || (month() == rhs.month() && day() < rhs.day())));
}

/*operator<<*/
// Formats the output stream with the Holiday name, whether it's a government Holiday or not,
// and the date.
ostream& operator<<(ostream &out, const Holiday &rhs) {
    const auto save_fill = out.fill('0');   
    out << rhs.GetName() << ", ";
    if (rhs.GetPriority() == 0) {
		out << "Is";
	} else {
		out << "Is Not";
	}
	return out << " a Government Holiday, Date: "
			   << setw(4) << rhs.year() << '-'
			   << setw(2) << rhs.month() << '-'
			   << setw(2) << rhs.day() << setfill(save_fill);
}