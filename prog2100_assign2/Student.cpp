// PROG2100 Assignment 2 - Courses
// Student implementation. Performs no user input; the driver owns the interface.

#include "Student.h"

#include <iostream>
#include <stdexcept>

using namespace std;

Student::Student() : numCourses(0), courseList(nullptr)
{
    trace("default constructor");
}

Student::Student(const string& studentName) : name(studentName), numCourses(0), courseList(nullptr)
{
    trace("string constructor");
}

Student::Student(const Student& other)
    : name(other.name),
      numCourses(other.numCourses),
      courseList(cloneList(other.courseList, other.numCourses, other.numCourses))
{
    trace("copy constructor");
}

Student& Student::operator=(const Student& other)
{
    trace("assignment operator");
    if (this != &other)
    {
        // Copy before freeing so a failed allocation leaves this object intact.
        string* copy = cloneList(other.courseList, other.numCourses, other.numCourses);
        delete[] courseList;
        courseList = copy;
        numCourses = other.numCourses;
        name = other.name;
    }
    return *this;
}

Student::~Student()
{
    trace("destructor");
    if (courseList != nullptr)
    {
        delete[] courseList;
        courseList = nullptr;
    }
}

const string& Student::getName() const
{
    return name;
}

int Student::getNumCourses() const
{
    return numCourses;
}

const string& Student::getCourse(int index) const
{
    if (index < 0 || index >= numCourses)
    {
        throw out_of_range("Course index out of range");
    }
    return courseList[index];
}

void Student::setName(const string& studentName)
{
    name = studentName;
}

// Resizes by deep copying into a block one slot larger, then frees the old one.
void Student::add(const string& course)
{
    trace("add");
    cout << "  [courseList resized from " << numCourses << " to " << numCourses + 1
         << " by deep copy]\n";
    string* grown = cloneList(courseList, numCourses, numCourses + 1);
    grown[numCourses] = course;
    delete[] courseList;
    courseList = grown;
    ++numCourses;
}

void Student::reset()
{
    trace("reset");
    delete[] courseList;
    courseList = nullptr;
    numCourses = 0;
}

void Student::print() const
{
    trace("print");
    writeTo(cout);
}

ostream& operator<<(ostream& out, const Student& student)
{
    student.trace("operator<<");
    student.writeTo(out);
    return out;
}

string* Student::cloneList(const string* source, int count, int capacity)
{
    if (capacity == 0)
    {
        return nullptr;
    }

    string* copy = new string[capacity];
    for (int i = 0; i < count; ++i)
    {
        copy[i] = source[i];
    }
    return copy;
}

// Reports each key method as it runs, as the assignment requires.
void Student::trace(const char* method) const
{
    cout << "  [" << method << " called on \"" << name << "\"]\n";
}

void Student::writeTo(ostream& out) const
{
    out << "Name: " << name << "\nCourses (" << numCourses << "):\n";
    for (int i = 0; i < numCourses; ++i)
    {
        out << "  " << i + 1 << ". " << courseList[i] << '\n';
    }
}
