// PROG2100 Assignment 3 - Rational Number Calculator
// Rational: a fraction stored as two ints, always normalized
// (lowest terms, positive denominator), e.g. 4/-8 is stored as -1/2.

#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>
#include <string>

class Rational
{
public:
    // Constructors. Invalid values throw std::invalid_argument (zero denominator,
    // bad text) or std::out_of_range (a part outside -2147483647..2147483647).
    Rational();                                         // Rubric: default constructor, 0/1
    Rational(int wholeNumber);                          // Rubric: whole number constructor, whole/1 (also lets 2 + r work)
    Rational(int numeratorValue, int denominatorValue); // Rubric: two-argument constructor
    explicit Rational(const std::string& text);         // Rubric: string constructor, "-1/3" or "5"

    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other);         // Rubric: overloaded =

    // Rubric: overloaded math operators. Answers are normalized; / by zero throws std::domain_error.
    friend Rational operator+(const Rational& left, const Rational& right);
    friend Rational operator-(const Rational& left, const Rational& right);
    friend Rational operator*(const Rational& left, const Rational& right);
    friend Rational operator/(const Rational& left, const Rational& right);

    // Rubric: overloaded logical operators, each returns bool.
    friend bool operator<(const Rational& left, const Rational& right);
    friend bool operator>(const Rational& left, const Rational& right);
    friend bool operator==(const Rational& left, const Rational& right);

    // Rubric: overloaded output operator, prints "numerator/denominator".
    friend std::ostream& operator<<(std::ostream& out, const Rational& value);

private:
    int numerator;
    int denominator; // always > 0

    // Rubric: normalization. Every value passes through here before it is stored.
    void set(long long newNumerator, long long newDenominator);
};

#endif
