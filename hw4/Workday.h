#ifndef WORKDAY_H_INCLUDED
#define WORKDAY_H_INCLUDED

#include "Event.h"
#include "Priority_Event.h"

class Workday : public Event {
    // Member variables to track the name and pay.
    std::string job_name;
    double hourly_pay = 15.00;

public:
    // Constructors
    Workday() = delete;
    Workday(const std::string &name);
    Workday(const std::string &name, double pay);
    Workday(const std::string &name, const std::string &date);
    Workday(const std::string &name, const std::string &date, double pay);
    Workday(const std::string &name, int year, int month, int day);

    // Defaults for Destructor, Copy Constructor, Assignment Operator, 
    // Move Operator, Move Assignment Operator
    Workday(const Workday &rhs) = default;
    Workday &operator=(const Workday &rhs) = default;
    Workday &operator=(Workday &&rhs) = default;
    Workday(Workday &&rhs) = default;
    virtual ~Workday() = default;

    /*GetName*/
    // Input: None
    // Output: The name (string)
    std::string GetName() const;

    /*GetPay*/
    // Input: None
    // Output: The pay (double)
    double GetPay() const;

    /*operator<*/
    // Input: The rhs as an Event
    // Output: Boolean
    bool operator<(const Event &rhs) const;

    /*operator<*/
    // Input: The rhs as a string
    // Output: Boolean
    bool operator<(const std::string &rhs) const;

    /*operator<*/
    // Input: The rhs as a Priority_Event
    // Output: Boolean
    bool operator<(const Priority_Event &rhs) const;

    /*operator<*/
    // Input: The rhs as a Workday
    // Output: Boolean
    bool operator<(const Workday &rhs) const; 
};
/*operator<<*/
// Input: An output stream and a Workday
// Output: A formatted output stream
std::ostream& operator<<(std::ostream &out, const Workday &rhs);

#endif /* WORKDAY_H_INCLUDED */
