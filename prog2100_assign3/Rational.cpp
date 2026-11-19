// PROG2100 Assignment 3 - Rational Number Calculator
// Rational implementation. Errors are thrown; the driver decides how to show them.

#include "Rational.h"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <stdexcept>

using namespace std;

namespace
{
    const char* const RANGE_ERROR = "Error: Value out of range. Use -2147483647 to 2147483647.";

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
}

Rational::Rational(int wholeNumber)
{
    set(wholeNumber, 1);
}

Rational::Rational(int numeratorValue, int denominatorValue)
{
    set(numeratorValue, denominatorValue);
}

// Accepts "a/b" or "a", an optional sign on each part, and spaces around the parts.
// Decimals, letters, a space after a sign and extra slashes are rejected.
// Parses in place with no regex and no heap allocation.
Rational::Rational(const string& text)
{
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
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

// Members are at most INT_MAX, so every product and sum below fits in long long.
// set() normalizes and throws std::out_of_range if the answer does not fit in int.

// a/b + c/d = (ad + cb) / bd
Rational operator+(const Rational& left, const Rational& right)
{
    Rational result;
    result.set(static_cast<long long>(left.numerator) * right.denominator
                   + static_cast<long long>(right.numerator) * left.denominator,
               static_cast<long long>(left.denominator) * right.denominator);
    return result;
}

// a/b - c/d = (ad - cb) / bd
Rational operator-(const Rational& left, const Rational& right)
{
    Rational result;
    result.set(static_cast<long long>(left.numerator) * right.denominator
                   - static_cast<long long>(right.numerator) * left.denominator,
               static_cast<long long>(left.denominator) * right.denominator);
    return result;
}

// a/b * c/d = ac / bd
Rational operator*(const Rational& left, const Rational& right)
{
    Rational result;
    result.set(static_cast<long long>(left.numerator) * right.numerator,
               static_cast<long long>(left.denominator) * right.denominator);
    return result;
}

// a/b / c/d = ad / bc, so c cannot be 0.
Rational operator/(const Rational& left, const Rational& right)
{
    if (right.numerator == 0)
    {
        throw domain_error("Error: Division by zero.");
    }
    Rational result;
    result.set(static_cast<long long>(left.numerator) * right.denominator,
               static_cast<long long>(left.denominator) * right.numerator);
    return result;
}

// Denominators are always positive, so a/b < c/d exactly when ad < cb.
bool operator<(const Rational& left, const Rational& right)
{
    return static_cast<long long>(left.numerator) * right.denominator
         < static_cast<long long>(right.numerator) * left.denominator;
}

bool operator>(const Rational& left, const Rational& right)
{
    return right < left;
}

// Both sides are in lowest terms, so equal values have identical members.
bool operator==(const Rational& left, const Rational& right)
{
    return left.numerator == right.numerator && left.denominator == right.denominator;
}

ostream& operator<<(ostream& out, const Rational& value)
{
    return out << value.numerator << '/' << value.denominator;
}

// Moves the sign to the numerator and reduces to lowest terms, e.g. 4/-8 -> -1/2.
void Rational::set(long long newNumerator, long long newDenominator)
{
    if (newDenominator == 0)
    {
        throw invalid_argument("Error: Denominator cannot be zero.");
    }
    if (newDenominator < 0)
    {
        newNumerator = -newNumerator;
        newDenominator = -newDenominator;
    }
    const long long divisor = gcd(newNumerator, newDenominator);
    const int reducedDenominator = toInt(newDenominator / divisor); // check both before storing
    numerator = toInt(newNumerator / divisor);
    denominator = reducedDenominator;
}
