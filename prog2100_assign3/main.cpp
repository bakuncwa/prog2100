// PROG2100 Assignment 3 - Rational Number Calculator
// Console driver. Reads two rational numbers, then demonstrates every
// constructor and overloaded operator of the Rational class.

#include "Rational.h"

#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace
{
    const int LABEL_WIDTH = 30;

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

    // Prints the answer, or the error if the operation throws
    // (division by zero, zero denominator, or an answer outside int range).
    template <typename Operation>
    void showResult(const string& label, Operation operation)
    {
        try
        {
            const Rational answer = operation();
            row(label) << answer << '\n';
        }
        catch (const logic_error& error)
        {
            row(label) << error.what() << '\n';
        }
    }

    void runCalculation()
    {
        heading("Enter two rational numbers");
        string a, b;
        const Rational first = readRational("First number (e.g. -1/2 or 5): ", a);   // string constructor
        const Rational second = readRational("Second number (e.g. 3/4 or -2): ", b); // string constructor

        heading("Values as stored (normalized)");
        row(a) << first << '\n';
        row(b) << second << '\n';

        heading("Arithmetic");
        showResult(a + " + " + b, [&] { return first + second; });
        showResult(a + " - " + b, [&] { return first - second; });
        showResult(a + " * " + b, [&] { return first * second; });
        showResult(a + " / " + b, [&] { return first / second; });

        heading("Comparisons");
        row(a + " < " + b) << (first < second) << '\n';
        row(a + " > " + b) << (first > second) << '\n';
        row(a + " == " + b) << (first == second) << '\n';

        heading("Other constructors and operators");
        // Each object is built on its own line so its constructor message prints above its row.
        const Rational zero;
        row("Rational()") << zero << '\n';
        const Rational five(5);
        row("Rational(5)") << five << '\n';
        const Rational unreduced(4, -8);
        row("Rational(4, -8)") << unreduced << '\n';
        showResult("Rational(1, 0)", [] { return Rational(1, 0); });

        Rational assigned; // 0/1 until the assignment below
        assigned = first;
        row("assigned = " + a) << assigned << '\n';
        row(a + ".toString()") << first.toString() << '\n';

        // 2 is converted to Rational(2) by the whole number constructor.
        showResult("2 + " + a, [&] { return 2 + first; });
    }
}

int main()
{
    cout << boolalpha; // comparisons print true/false
    cout << "Rational Number Calculator\n";

    try
    {
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
