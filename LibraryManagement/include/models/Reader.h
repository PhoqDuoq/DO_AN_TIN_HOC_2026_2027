#ifndef READER_H
#define READER_H

#include <string>
using namespace std;

/**
 * Struct representing a library reader (độc giả).
 * Fields follow the design specification for Week 4.
 */
struct Reader {
    string CMND;        // Unique identification number (cannot be empty)
    string fullName;    // Reader's full name (cannot be empty)
    string email;       // Email address (optional, but if present must contain '@')
    string phone;       // Phone number (optional, basic format validation will be done in manager)
    string cardType;    // Type of library card (e.g., "Student", "Teacher", "Adult")
};

#endif // READER_H