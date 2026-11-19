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
    // Every constructor and overloaded operator prints a line showing it fired.
    // Invalid values throw std::invalid_argument (zero denominator, bad text)
    // or std::out_of_range (a part outside -2147483647..2147483647).
    Rational();                                         // 0/1
    Rational(int wholeNumber);                          // whole/1; also converts ints, e.g. 2 + r
    Rational(int numeratorValue, int denominatorValue);
    explicit Rational(const std::string& text);         // "-1/3" or "5"

    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other);

    // Answers are normalized. Division by zero throws std::domain_error.
    friend Rational operator+(const Rational& left, const Rational& right);
    friend Rational operator-(const Rational& left, const Rational& right);
    friend Rational operator*(const Rational& left, const Rational& right);
    friend Rational operator/(const Rational& left, const Rational& right);

    friend bool operator<(const Rational& left, const Rational& right);
    friend bool operator>(const Rational& left, const Rational& right);
    friend bool operator==(const Rational& left, const Rational& right);

    std::string toString() const; // "numerator/denominator"
    friend std::ostream& operator<<(std::ostream& out, const Rational& value);

private:
    int numerator;
    int denominator; // always > 0

    // Every stored value passes through here, so it is always normalized.
    void set(long long newNumerator, long long newDenominator);
};

#endif
