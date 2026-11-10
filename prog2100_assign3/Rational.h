// PROG2100 Assignment 3 - Rational Number Calculator
// Rational: a fraction of two ints. Inputs are stored as given; every
// arithmetic answer is normalized (lowest terms, positive denominator).

#ifndef RATIONAL_H
#define RATIONAL_H

#include <ostream>
#include <string>

class Rational
{
public:
    Rational();                                         // 0/1
    Rational(int wholeNumber);                          // whole/1; also converts ints, e.g. 2 + r
    Rational(int numeratorValue, int denominatorValue);
    explicit Rational(const std::string& text);         // "a/b" or "a"

    Rational(const Rational& other) = default;
    Rational& operator=(const Rational& other);

    // Arithmetic answers are normalized. Division by zero throws std::domain_error.
    friend Rational operator+(const Rational& left, const Rational& right);
    friend Rational operator-(const Rational& left, const Rational& right);
    friend Rational operator*(const Rational& left, const Rational& right);
    friend Rational operator/(const Rational& left, const Rational& right);

    friend bool operator<(const Rational& left, const Rational& right);
    friend bool operator>(const Rational& left, const Rational& right);
    friend bool operator==(const Rational& left, const Rational& right);

    friend std::ostream& operator<<(std::ostream& out, const Rational& value);

private:
    int numerator;
    int denominator;

    // Throws std::invalid_argument for a zero denominator, std::out_of_range past +/-INT_MAX.
    void set(long long newNumerator, long long newDenominator);
    long long compare(const Rational& other) const; // < 0, 0 or > 0, like left - right
    static Rational normalized(long long newNumerator, long long newDenominator);
};

#endif
