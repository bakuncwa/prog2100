// PROG2100 Assignment 3 - Rational Number Calculator
// Console driver. Reads two rational numbers, then demonstrates every
// constructor and overloaded operator of the Rational class.

#include "Rational.h"

#include <exception>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace
{
    const int LABEL_WIDTH = 32;

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
            const string answer = readRequired(prompt);
            if (answer == "y" || answer == "Y" || answer == "n" || answer == "N")
            {
                return answer == "y" || answer == "Y";
            }
            cout << "Error: Invalid response. Expected Y or N.\n";
        }
    }

    // Re-prompts until the string constructor accepts the entry.
    Rational readRational(const string& prompt, string& text)
    {
        while (true)
        {
            text = readRequired(prompt);
            try
            {
                return Rational(text);
            }
            catch (const logic_error& error)
            {
                cout << error.what() << '\n';
            }
        }
    }

    void heading(const char* title)
    {
        cout << "\n=== " << title << " ===\n";
    }

    // Starts a two-column row: label, then the value the caller streams after it.
    ostream& row(const string& label)
    {
        return cout << "  " << left << setw(LABEL_WIDTH) << label << "= ";
    }

    // Runs result = first <op> second, then cout << result. Division by zero or an
    // answer outside int range prints the error instead.
    void showArithmetic(char op, const Rational& first, const Rational& second,
                        const string& a, const string& b, Rational& result)
    {
        const string label = a + ' ' + op + ' ' + b;
        try
        {
            switch (op)
            {
            case '+': result = first + second; break;
            case '-': result = first - second; break;
            case '*': result = first * second; break;
            default:  result = first / second; break;
            }
            row(label) << result << '\n';
        }
        catch (const logic_error& error)
        {
            row(label) << error.what() << '\n';
        }
    }

    // Runs once at start-up: the constructors that the calculation loop does not use.
    void demonstrateConstructors()
    {
        heading("Constructor demonstrations");
        const Rational zero;
        row("Rational()") << zero << '\n';
        const Rational five(5);
        row("Rational(5)") << five << '\n';
        const Rational unreduced(4, -8);
        row("Rational(4, -8)") << unreduced << '\n';
        row("Rational(4, -8).toString()") << unreduced.toString() << '\n';
        try
        {
            const Rational invalid(1, 0);
        }
        catch (const logic_error& error)
        {
            row("Rational(1, 0)") << error.what() << '\n';
        }
    }

    // One calculation: reads two numbers, then runs every operator on them.
    // Each operation runs on its own line before its row is printed,
    // so every "fired" message appears above the row it belongs to.
    void runCalculation()
    {
        heading("Enter two rational numbers");
        string a, b;
        const Rational first = readRational("First fraction or whole number (e.g. -1/2 or 5): ", a);
        const Rational second = readRational("Second fraction or whole number (e.g. 3/-4 or -2): ", b);
        a = '(' + a + ')'; // brackets keep labels such as (1/2) / (3/4) readable
        b = '(' + b + ')';

        heading("Numbers entered");
        row(a) << first << '\n';
        row(b) << second << '\n';

        heading("Arithmetic (answers in lowest terms)");
        Rational result;
        for (const char op : {'+', '-', '*', '/'})
        {
            showArithmetic(op, first, second, a, b, result);
        }

        heading("Comparisons");
        const bool isLess = first < second;
        row(a + " < " + b) << isLess << '\n';
        const bool isGreater = first > second;
        row(a + " > " + b) << isGreater << '\n';
        const bool isEqual = first == second;
        row(a + " == " + b) << isEqual << '\n';

        heading("Whole number with a fraction");
        try
        {
            result = 2 + first; // 2 becomes Rational(2) through the whole number constructor
            row("2 + " + a) << result << '\n';
        }
        catch (const logic_error& error)
        {
            row("2 + " + a) << error.what() << '\n';
        }
    }
}

int main()
{
    cout << boolalpha; // comparisons print true/false
    cout << "Rational Number Calculator\n"
         << "Enter fractions such as -1/2 or 3/-4, or whole numbers such as 5.\n"
         << "Decimals and other characters are not accepted.\n";

    try
    {
        demonstrateConstructors();
        do
        {
            runCalculation();
        } while (askYesNo("\nCalculate again? (y/n): "));
    }
    catch (const exception& error)
    {
        cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
