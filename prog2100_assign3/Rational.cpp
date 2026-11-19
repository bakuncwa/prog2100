// PROG2100 Assignment 3 - Rational Number Calculator
// Rational implementation. Errors are thrown; the driver decides how to show them.

#include "Rational.h"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace
{
    const char* const RANGE_ERROR = "Error: Value out of range. Use -2147483647 to 2147483647.";

    // Shows that a constructor or overloaded operator ran.
    void fired(const char* method)
    {
        cout << "  [" << method << " fired]\n";
    }

    // INT_MIN is excluded so negating a value can never overflow.
    int toInt(long long value)
    {
        if (value < -INT_MAX || value > INT_MAX)
        {
            throw out_of_range(RANGE_ERROR);
        }
        return static_cast<int>(value);
    }

    // Euclid's algorithm; the result is never negative.
    long long gcd(long long a, long long b)
    {
        while (b != 0)
        {
            const long long remainder = a % b;
            a = b;
            b = remainder;
        }
        return a < 0 ? -a : a;
    }

    // Moves the sign to the numerator and reduces to lowest terms, e.g. 4/-8 -> -1/2.
    // The denominator must not be 0.
    void reduce(long long& top, long long& bottom)
    {
        if (bottom < 0)
        {
            top = -top;
            bottom = -bottom;
        }
        const long long divisor = gcd(top, bottom);
        top /= divisor;
        bottom /= divisor;
    }

    // Builds an operator's answer. Reducing first lets answers such as
    // 4294967294/4294967294 fit in int as 1/1.
    Rational answer(long long top, long long bottom)
    {
        reduce(top, bottom);
        return Rational(toInt(top), toInt(bottom));
    }

    const char* skipSpaces(const char* p)
    {
        while (*p == ' ' || *p == '\t')
        {
            ++p;
        }
        return p;
    }

    // Reads one signed whole number at p and moves p past it. Returns false if no digits.
    // Values too big for long long, or outside int range, throw std::out_of_range.
    bool readPart(const char*& p, int& value)
    {
        p = skipSpaces(p);
        if (*p != '+' && *p != '-' && (*p < '0' || *p > '9'))
        {
            return false; // strtoll would otherwise skip other whitespace such as '\n'
        }
        char* end;
        errno = 0;
        const long long parsed = strtoll(p, &end, 10);
        if (end == p)
        {
            return false; // a sign with no digits
        }
        if (errno == ERANGE)
        {
            throw out_of_range(RANGE_ERROR);
        }
        value = toInt(parsed);
        p = skipSpaces(end);
        return true;
    }
}

Rational::Rational() : numerator(0), denominator(1)
{
    fired("default constructor");
}

Rational::Rational(int wholeNumber)
{
    fired("whole number constructor");
    set(wholeNumber, 1);
}

Rational::Rational(int numeratorValue, int denominatorValue)
{
    fired("two-argument constructor");
    set(numeratorValue, denominatorValue);
}

// Accepts "a/b" or "a", an optional sign on each part, and spaces around the parts.
// Decimals, letters, a space after a sign and extra slashes are rejected.
// Parses in place with no regex and no heap allocation.
Rational::Rational(const string& text)
{
    fired("string constructor");
    const char* p = text.c_str();
    const char* const textEnd = p + text.size(); // catches an embedded '\0'
    int top = 0;
    int bottom = 1;

    bool valid = readPart(p, top);
    if (valid && *p == '/')
    {
        ++p;
        valid = readPart(p, bottom);
    }
    if (!valid || p != textEnd)
    {
        throw invalid_argument("Error: Invalid number. Expected a fraction (-1/2) or a whole number (5).");
    }
    set(top, bottom);
}

Rational& Rational::operator=(const Rational& other)
{
    fired("operator=");
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

// Members are at most INT_MAX, so every product and sum below fits in long long.

// a/b + c/d = (ad + cb) / bd
Rational operator+(const Rational& left, const Rational& right)
{
    fired("operator+");
    return answer(static_cast<long long>(left.numerator) * right.denominator
                      + static_cast<long long>(right.numerator) * left.denominator,
                  static_cast<long long>(left.denominator) * right.denominator);
}

// a/b - c/d = (ad - cb) / bd
Rational operator-(const Rational& left, const Rational& right)
{
    fired("operator-");
    return answer(static_cast<long long>(left.numerator) * right.denominator
                      - static_cast<long long>(right.numerator) * left.denominator,
                  static_cast<long long>(left.denominator) * right.denominator);
}

// a/b * c/d = ac / bd
Rational operator*(const Rational& left, const Rational& right)
{
    fired("operator*");
    return answer(static_cast<long long>(left.numerator) * right.numerator,
                  static_cast<long long>(left.denominator) * right.denominator);
}

// Flip the right side and multiply: a/b / c/d = a/b * d/c = ad / bc.
// c cannot be 0, because flipping 0/3 would give 3/0.
Rational operator/(const Rational& left, const Rational& right)
{
    fired("operator/");
    if (right.numerator == 0)
    {
        throw domain_error("Error: Division by zero.");
    }
    return answer(static_cast<long long>(left.numerator) * right.denominator,
                  static_cast<long long>(left.denominator) * right.numerator);
}

// Denominators are always positive, so a/b < c/d exactly when ad < cb (and > likewise).
bool operator<(const Rational& left, const Rational& right)
{
    fired("operator<");
    return static_cast<long long>(left.numerator) * right.denominator
         < static_cast<long long>(right.numerator) * left.denominator;
}

bool operator>(const Rational& left, const Rational& right)
{
    fired("operator>");
    return static_cast<long long>(left.numerator) * right.denominator
         > static_cast<long long>(right.numerator) * left.denominator;
}

// Both sides are in lowest terms, so equal values (2/4 and 1/2) have identical members.
bool operator==(const Rational& left, const Rational& right)
{
    fired("operator==");
    return left.numerator == right.numerator && left.denominator == right.denominator;
}

string Rational::toString() const
{
    return to_string(numerator) + '/' + to_string(denominator);
}

// The trace goes after the value so the driver's result rows stay on one line.
ostream& operator<<(ostream& out, const Rational& value)
{
    return out << value.toString() << "  [operator<< fired]";
}

void Rational::set(long long newNumerator, long long newDenominator)
{
    if (newDenominator == 0)
    {
        throw invalid_argument("Error: Denominator cannot be zero.");
    }
    reduce(newNumerator, newDenominator);
    const int reducedDenominator = toInt(newDenominator); // check both before storing
    numerator = toInt(newNumerator);
    denominator = reducedDenominator;
}
