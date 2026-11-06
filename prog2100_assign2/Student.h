// PROG2100 Assignment 2 - Courses
// Student class: a name plus a heap array of course names sized exactly to
// numCourses, so no slot is ever unused and an empty list allocates nothing.

#ifndef STUDENT_H
#define STUDENT_H

#include <ostream>
#include <string>

class Student
{
public:
    Student();                                        // no name, empty list
    explicit Student(const std::string& studentName); // named, empty list

    // Rule of three
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    // Accessors and mutator
    const std::string& getName() const;
    int getNumCourses() const;
    const std::string& getCourse(int index) const; // throws std::out_of_range
    void setName(const std::string& studentName);

    void add(const std::string& course); // grows courseList by one slot
    void reset();                        // empties the list, keeps the name
    void print() const;                  // outputs the name and all courses

    // Outputs the same details as print().
    friend std::ostream& operator<<(std::ostream& out, const Student& student);

private:
    std::string name;
    int numCourses;
    std::string* courseList;

    // Allocates a new array of size capacity and deep copies count strings.
    static std::string* cloneList(const std::string* source, int count, int capacity);
    void trace(const char* method) const;
    void writeTo(std::ostream& out) const;
};

#endif
