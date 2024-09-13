#include "Priority_Event.h"
#include <iomanip>

using namespace std;

Priority_Event::Priority_Event() 
: Event() {}

Priority_Event::Priority_Event(const string &name) 
: Event(), event_name(name) {}

Priority_Event::Priority_Event(const string &name, short priority) 
: Event(), event_name(name), event_priority(priority) {
	if (priority < 0) {
		throw(runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + to_string(priority) + "\n"));
	}
}

Priority_Event::Priority_Event(const string &name, const string &date)
: Event(date), event_name(name) {}

Priority_Event::Priority_Event(const string &name, const string &date, short priority) 
: Event(date), event_name(name), event_priority(priority) {
	if (priority < 0) {
		throw(runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + to_string(priority) + "\n"));
	}
}

Priority_Event::Priority_Event(const string &name, int y, int m, int d)
: Event(), event_name(name) {
	set(y, m, d);
}

Priority_Event::Priority_Event(const string &name, int y, int m, int d, short priority) 
: Event(), event_name(name), event_priority(priority) {
	if (priority < 0) {
		throw(runtime_error("Priority_Event - Error cannot set a priority less than 0. Given Priority: " + to_string(priority) + "\n"));
	}
	set(y, m, d);
}

/*GetName*/
// Returns the name of the event.
string Priority_Event::GetName() const {
    return event_name;
}

/*GetPriority*/
// Returns the priority of the event.
short Priority_Event::GetPriority() const {
    return event_priority;
}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the left object is greater than 10. If 
// it is, return true, otherwise false. If the dates aren't the same, return the result of 
// comparing the two dates.
bool Priority_Event::operator<(const Event &rhs) const {
	if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
		if(GetPriority() > 10) {
			return true;
		} else {
			return false;
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
bool Priority_Event::operator<(const string &rhs) const {
	Event tmp(rhs);
    return (*this) < tmp;
}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the left object is greater than the priority 
// of the right object. If it is, return true, otherwise false. If the dates aren't the same, 
// return the result of comparing the two dates.
bool Priority_Event::operator<(const Priority_Event &rhs) const {
	if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
		if(GetPriority() > rhs.GetPriority()) {
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
// Formats the output stream with the Priority_Event name, the priority,
// and the date.
ostream& operator<<(ostream &out, const Priority_Event &rhs) {
    const auto save_fill = out.fill('0');   
	return out << rhs.GetName() << ", Priority: " << rhs.GetPriority() << ", Date: "
			   << setw(4) << rhs.year() << '-'
			   << setw(2) << rhs.month() << '-'
			   << setw(2) << rhs.day() << setfill(save_fill);
}