#ifndef HOLIDAY_H_INCLUDED
#define HOLIDAY_H_INCLUDED

#include "Event.h"
#include "Priority_Event.h"

class Holiday : public Priority_Event {
public:
    // Constructors
    Holiday() = delete;
    Holiday(const std::string &name);
    Holiday(const std::string &name, bool is_gov);
    Holiday(const std::string &name, const std::string &date);
    Holiday(const std::string &name, const std::string &date, bool is_gov);
    Holiday(const std::string &name, int y, int m, int d);
    Holiday(const std::string &name, int y, int m, int d, bool is_gov);

    // Defaults for Destructor, Copy Constructor, Assignment Operator, 
    // Move Operator, Move Assignment Operator
    Holiday(const Holiday &rhs) = default;
    Holiday &operator=(const Holiday &rhs) = default;
    Holiday &operator=(Holiday &&rhs) = default;
    Holiday(Holiday &&rhs) = default;
    virtual ~Holiday() = default;

    /*operator<*/
    // Input: The rhs as an Event
    // Output: Boolean
    bool operator<(const Event &rhs) const;

    /*operator<*/
    // Input: The rhs as a String
    // Output: Boolean
    bool operator<(const std::string &rhs) const;

    /*operator<*/
    // Input: The rhs as a Priority_Event
    // Output: Boolean
    bool operator<(const Priority_Event &rhs) const;

    /*operator<*/
    // Input: The rhs as a Holiday
    // Output: Boolean
    bool operator<(const Holiday &rhs) const;
};
/*operator<<*/
// Input: An output stream and a Holiday
// Output: A formatted output stream
std::ostream& operator<<(std::ostream &out, const Holiday &rhs);

#endif /* HOLIDAY_H_INCLUDED */