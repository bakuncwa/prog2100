// PROG2100 Assignment 3 - Rational Number Calculator
// Rational implementation. Errors are thrown; the driver decides how to show them.

#include "Rational.h"

#include <climits>
#include <iostream>
#include <regex>
#include <stdexcept>

using namespace std;

namespace
{
    const char* const RANGE_ERROR = "Error: Value out of range. Use -2147483647 to 2147483647.";

    void fired(const char* method)
    {
        cout << "  [" << method << " fired]\n";
    }

    // INT_MIN is excluded so negation and cross-multiplication cannot overflow long long.
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

// Accepts an optional sign on either part and spaces around the slash.
// Decimals, letters and extra slashes fail the pattern.
Rational::Rational(const string& text)
{
    fired("string constructor");
    static const regex FRACTION(R"(\s*([+-]?\d+)\s*(?:/\s*([+-]?\d+)\s*)?)");
    smatch parts;

    if (!regex_match(text, parts, FRACTION))
    {
        throw invalid_argument("Error: Invalid number. Expected a fraction (-1/2) or a whole number (5).");
    }

    try
    {
        set(stoll(parts[1].str()), parts[2].matched ? stoll(parts[2].str()) : 1);
    }
    catch (const out_of_range&) // also catches stoll overflow on very long digit strings
    {
        throw out_of_range(RANGE_ERROR);
    }
}

Rational& Rational::operator=(const Rational& other)
{
    fired("operator=");
    numerator = other.numerator;
    denominator = other.denominator;
    return *this;
}

// a/b + c/d = (ad + cb) / bd
Rational operator+(const Rational& left, const Rational& right)
{
    fired("operator+");
    const long long a = left.numerator, b = left.denominator, c = right.numerator, d = right.denominator;
    return Rational::normalized(a * d + c * b, b * d);
}

// a/b - c/d = (ad - cb) / bd
Rational operator-(const Rational& left, const Rational& right)
{
    fired("operator-");
    const long long a = left.numerator, b = left.denominator, c = right.numerator, d = right.denominator;
    return Rational::normalized(a * d - c * b, b * d);
}

// a/b * c/d = ac / bd
Rational operator*(const Rational& left, const Rational& right)
{
    fired("operator*");
    const long long a = left.numerator, b = left.denominator, c = right.numerator, d = right.denominator;
    return Rational::normalized(a * c, b * d);
}

// a/b / c/d = a/b * d/c, so c cannot be 0.
Rational operator/(const Rational& left, const Rational& right)
{
    fired("operator/");
    if (right.numerator == 0)
    {
        throw domain_error("Error: Division by zero.");
    }
    const long long a = left.numerator, b = left.denominator, c = right.numerator, d = right.denominator;
    return Rational::normalized(a * d, b * c);
}

bool operator<(const Rational& left, const Rational& right)
{
    fired("operator<");
    return left.compare(right) < 0;
}

bool operator>(const Rational& left, const Rational& right)
{
    fired("operator>");
    return left.compare(right) > 0;
}

bool operator==(const Rational& left, const Rational& right)
{
    fired("operator==");
    return left.compare(right) == 0;
}

// Prints the value, then its own trace on the same line so result rows stay intact.
ostream& operator<<(ostream& out, const Rational& value)
{
    return out << value.numerator << '/' << value.denominator << "  [operator<< fired]";
}

void Rational::set(long long newNumerator, long long newDenominator)
{
    if (newDenominator == 0)
    {
        throw invalid_argument("Error: Denominator cannot be zero.");
    }
    numerator = toInt(newNumerator);
    denominator = toInt(newDenominator);
}

// Cross-multiplies; the sign flips when exactly one denominator is negative.
long long Rational::compare(const Rational& other) const
{
    const long long difference = static_cast<long long>(numerator) * other.denominator
                               - static_cast<long long>(other.numerator) * denominator;
    return (denominator < 0) == (other.denominator < 0) ? difference : -difference;
}

// Moves the sign to the numerator and reduces to lowest terms, e.g. 4/-8 -> -1/2.
Rational Rational::normalized(long long newNumerator, long long newDenominator)
{
    if (newDenominator < 0)
    {
        newNumerator = -newNumerator;
        newDenominator = -newDenominator;
    }
    const long long divisor = gcd(newNumerator, newDenominator);
    return Rational(toInt(newNumerator / divisor), toInt(newDenominator / divisor));
}
