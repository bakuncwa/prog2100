// PROG2100 Assignment 2 - Courses
// Console driver that demonstrates every Student method. All user input is
// handled here; the Student class holds the business logic.

#include "Student.h"

#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace
{
    const char* const COLLEGE = "Nova Scotia Community College";
    const size_t MAX_COURSE_NAME_LENGTH = 50;

    struct Option
    {
        const char* code;
        const char* name;
    };

    // Names from nscc.ca/about/index.asp and nscc.ca/contact/campus.aspx; the
    // codes are this program's own, not official NSCC codes.
    const Option SCHOOLS[] = {
        {"ST", "Institute of Skilled Trades"},
        {"AB", "School of Access, Business, Creative Industries and Education"},
        {"HH", "School of Health and Human Services"},
        {"AT", "School of Applied Technology and Innovation"},
    };

    const Option CAMPUSES[] = {
        {"AK", "Akerley Campus"},
        {"AV", "Annapolis Valley Campus"},
        {"BU", "Burridge Campus"},
        {"CU", "Cumberland Campus"},
        {"EC", "eCampus"},
        {"IT", "Institute of Technology Campus"},
        {"IV", "Ivany Campus"},
        {"KI", "Kingstec Campus"},
        {"LU", "Lunenburg Campus"},
        {"PI", "Pictou Campus"},
        {"SH", "Shelburne Campus"},
        {"SA", "Strait Area Campus"},
        {"SW", "Sydney Waterfront Campus"},
        {"TR", "Truro Campus"},
    };

    string toUpper(string text)
    {
        transform(text.begin(), text.end(), text.begin(),
                  [](unsigned char c) { return static_cast<char>(toupper(c)); });
        return text;
    }

    // Re-prompts until the entry is not blank, then returns it trimmed.
    string readRequired(const string& prompt)
    {
        const char* const whitespace = " \t\r";
        string line;

        while (true)
        {
            cout << prompt;
            if (!getline(cin, line))
            {
                // Throwing unwinds the stack, so live Students are still destroyed.
                throw runtime_error("Error: Unexpected end of input.");
            }

            const size_t start = line.find_first_not_of(whitespace);
            if (start != string::npos)
            {
                return line.substr(start, line.find_last_not_of(whitespace) - start + 1);
            }
            cout << "Error: Input cannot be empty.\n";
        }
    }

    bool askYesNo(const string& prompt)
    {
        while (true)
        {
            const string answer = toUpper(readRequired(prompt));
            if (answer == "Y" || answer == "N")
            {
                return answer == "Y";
            }
            cout << "Error: Invalid response. Expected Y or N.\n";
        }
    }

    // Accepts W followed by 7 digits, in either case.
    string readStudentId()
    {
        while (true)
        {
            const string id = toUpper(readRequired("Student ID (W#######): "));
            const bool digitsOnly = id.size() == 8 && all_of(id.begin() + 1, id.end(),
                [](unsigned char c) { return isdigit(c) != 0; });

            if (digitsOnly && id[0] == 'W')
            {
                return id;
            }
            cout << "Error: Invalid student ID format. Expected W#######.\n";
        }
    }

    // Lists the options, then re-prompts until a listed code is entered.
    template <size_t Count>
    string readChoice(const string& prompt, const Option (&options)[Count])
    {
        for (const Option& option : options)
        {
            cout << "  " << option.code << " - " << option.name << '\n';
        }

        while (true)
        {
            const string code = toUpper(readRequired(prompt));
            for (const Option& option : options)
            {
                if (code == option.code)
                {
                    return option.name;
                }
            }
            cout << "Error: Invalid code. Select a code from the list.\n";
        }
    }

    // Student allows only three members, so ID, school and campus are stored in its name.
    string readIdentity(const string& label)
    {
        const string fullName = readRequired(label + " full name: ");
        const string id = readStudentId();
        const string school = readChoice("School code: ", SCHOOLS);
        const string campus = readChoice("Campus code: ", CAMPUSES);
        return fullName + " (" + id + ") - " + school + ", " + campus + ", " + COLLEGE;
    }

    // Limits length and requires a letter or digit; symbols are otherwise allowed.
    string readCourseName(const string& prompt)
    {
        while (true)
        {
            const string course = readRequired(prompt);
            const bool hasLetterOrDigit = any_of(course.begin(), course.end(),
                [](unsigned char c) { return isalnum(c) != 0; });

            if (course.size() > MAX_COURSE_NAME_LENGTH)
            {
                cout << "Error: Course name exceeds " << MAX_COURSE_NAME_LENGTH << " characters.\n";
            }
            else if (!hasLetterOrDigit)
            {
                cout << "Error: Course name must contain a letter or digit.\n";
            }
            else
            {
                return course;
            }
        }
    }

    void enterCourses(Student& student)
    {
        do
        {
            student.add(readCourseName("Course name: "));
        } while (askYesNo("Add another course? (y/n): "));
    }

    void showWithAccessors(const Student& student)
    {
        cout << "Name: " << student.getName()
             << "\nNumber of courses: " << student.getNumCourses() << '\n';
        for (int i = 0; i < student.getNumCourses(); ++i)
        {
            cout << "  " << student.getCourse(i) << '\n';
        }
    }

    void heading(const string& title)
    {
        cout << "\n=== " << title << " ===\n";
    }

    // Returns true to run again.
    bool runDemo()
    {
        heading("1. Default constructor, then enter first student");
        Student first;
        showWithAccessors(first);
        first.setName(readIdentity("First student"));
        enterCourses(first);

        heading("2. First student using print() and <<");
        first.print();
        cout << first;

        heading("3. Copy first student into second, then write in the new name");
        Student second(first);
        second.setName(readIdentity("Second student"));
        second.print();

        heading("4. First student after reset()");
        first.reset();
        showWithAccessors(first);

        heading("5. Second student keeps its courses (deep copy)");
        showWithAccessors(second);

        heading("6. Enter third student, then third = second");
        Student third(readIdentity("Third student"));
        enterCourses(third);
        third.print();
        third = second;
        cout << third;

        heading("7. Change third student; second must not change (deep copy)");
        third.setName(readIdentity("Third student's new"));
        third.add(readCourseName("Course to add to third student only: "));
        cout << third << second;

        heading("8. Run again or exit; three destructor calls follow your answer");

        // Asked before the Students go out of scope, so the last three
        // destructor calls only show when the program exits.
        return askYesNo("Run again? (y/n): ");
    }
}

int main()
{
    try
    {
        while (runDemo())
        {
        }
    }
    catch (const exception& error)
    {
        cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
