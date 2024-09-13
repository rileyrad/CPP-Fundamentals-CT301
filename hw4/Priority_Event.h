#ifndef PRIORITY_EVENT_H_INCLUDED
#define PRIORITY_EVENT_H_INCLUDED

#include <string>
#include "Event.h"

class Priority_Event : public Event {
    // Member variables for name and priority with set defaults.
    std::string event_name = "New Event";
    short event_priority = 10;

public:
    // Constructors
    Priority_Event();
    Priority_Event(const std::string &name);
    Priority_Event(const std::string &name, short priority);
    Priority_Event(const std::string &name, const std::string &date);
    Priority_Event(const std::string &name, const std::string &date, short priority);
    Priority_Event(const std::string &name, int y, int m, int d);
    Priority_Event(const std::string &name, int y, int m, int d, short priority);

    // Defaults for Destructor, Copy Constructor, Assignment Operator, 
    // Move Operator, Move Assignment Operator
    Priority_Event(const Priority_Event &rhs) = default;
    Priority_Event &operator=(const Priority_Event &rhs) = default;
    Priority_Event &operator=(Priority_Event &&rhs) = default;
    Priority_Event(Priority_Event &&rhs) = default;
    virtual ~Priority_Event() = default;

    /*GetName*/
    // Input: None
    // Output: The name (string)
    std::string GetName() const;

    /*GetPriority*/
    // Input: None
    // Output: The priority (short)
    short GetPriority() const;

    /*operator<*/
    // Input: The rhs as an Event
    // Output: Boolean
    virtual bool operator<(const Event &rhs) const;

    /*operator<*/
    // Input: The rhs as a string
    // Output: Boolean
    virtual bool operator<(const std::string &rhs) const;

    /*operator<*/
    // Input: The rhs as a Priority_Event
    // Output: Boolean
    virtual bool operator<(const Priority_Event &rhs) const;
};
/*operator<<*/
// Input: An output stream and a Priority_Event
// Output: A formatted output stream
std::ostream& operator<<(std::ostream &out, const Priority_Event &rhs);

#endif /* PRIORITY_EVENT_H_INCLUDED */