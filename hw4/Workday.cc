#include "Workday.h"
#include "Priority_Event.h"
#include "Event.h"
#include <iomanip>

using namespace std;

Workday::Workday(const string &name) 
: Event(), job_name(name) {}

Workday::Workday(const string &name, double pay) 
: Event(), job_name(name), hourly_pay(pay) {}

Workday::Workday(const string &name, const string &date) 
: Event(date), job_name(name) {}

Workday::Workday(const string &name, const string &date, double pay) 
: Event(date), job_name(name), hourly_pay(pay) {}

Workday::Workday(const string &name, int year, int month, int day)
: Event(), job_name(name) {
    set(year, month, day);
}

/*GetName*/
// Returns the name of the event.
string Workday::GetName() const {
    return job_name;
}

/*GetPay*/
// Returns the pay of the event.
double Workday::GetPay() const {
    return hourly_pay;
}

/*operator<*/
// The year, month, and day of the left and right side are compared and the result is returned.
bool Workday::operator<(const Event &rhs) const {
    return year() < rhs.year() 
    || (year() == rhs.year() && (month() < rhs.month() 
    || (month() == rhs.month() && day() < rhs.day())));
}

/*operator<*/
// Creates a temporary Event object using the input string then compares
// the current object and the Event using the operator above this one (it 
// would otherwise contain the same code).
bool Workday::operator<(const string &rhs) const {
    Event tmp(rhs);
    return (*this) < tmp;
}

/*operator<*/
// The year, month, and day of the left and right side are compared through a conditional
// statement to check if the two objects have the same date. If they are the same, another
// conditional statement checks if the priority of the right object is less than 10. If it 
// is, return true, otherwise false. If the dates aren't the same, return the result of 
// comparing the two dates.
bool Workday::operator<(const Priority_Event &rhs) const {
    if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
        if (rhs.GetPriority() < 10) {
            return true;
        } else {
            return false;
        }
    }
    return (*this) < rhs;
}

/*operator<*/
// Compares the year, month, and day of the left and right sides. If the left side's date is
// earlier than the right side's date, return true. Otherwise compare the dates to see if they
// are the same. If the dates are the same and the pay of the left side is less than the pay of
// the right side, return true. Otherwise return false.
bool Workday::operator<(const Workday &rhs) const {
    if (year() < rhs.year() 
    || (year() == rhs.year() && (month() < rhs.month() 
    || (month() == rhs.month() && day() < rhs.day())))) {
        return true;
    } else if (year() == rhs.year() && month() == rhs.month() && day() == rhs.day()) {
        if (GetPay() < rhs.GetPay()) {
            return true;
        }
    }
    return false;
}

/*operator<<*/
// Formats the output stream with the Workday name, the pay (two decimal points), and the date.
ostream &operator<<(ostream &out, const Workday &rhs) {
	const auto save_fill = out.fill('0');   
	return out << rhs.GetName() << ", Pay: $" << fixed << setprecision(2) << rhs.GetPay() << ", Date: "
			   << setw(4) << rhs.year() << '-'
			   << setw(2) << rhs.month() << '-'
			   << setw(2) << rhs.day() << setfill(save_fill);
}