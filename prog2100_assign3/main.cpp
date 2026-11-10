// PROG2100 Assignment 3 - Rational Number Calculator
// Console driver: reads two rational numbers, then runs every constructor and
// overloaded operator of the Rational class. All user input is handled here.

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

    // Re-prompts until the string constructor accepts the entry; text keeps it for labels.
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

    void heading(const string& title)
    {
        cout << "\n=== " << title << " ===\n";
    }

    // Starts a two-column row: label, then the value the caller streams after it.
    ostream& row(const string& label)
    {
        return cout << "  " << left << setw(LABEL_WIDTH) << label << "= ";
    }

    void runCalculation()
    {
        heading("Enter two rational numbers");
        string firstText, secondText;
        const Rational first = readRational("First number (e.g. -1/2 or 5): ", firstText);
        const Rational second = readRational("Second number (e.g. 3/4 or -2): ", secondText);

        heading("Arithmetic (answers normalized)");
        Rational result;
        for (const char op : {'+', '-', '*', '/'})
        {
            const string label = firstText + ' ' + op + ' ' + secondText;
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
            catch (const logic_error& error) // division by zero or an answer past int range
            {
                row(label) << error.what() << '\n';
            }
        }

        heading("Comparisons");
        const bool isLess = first < second;
        row(firstText + " < " + secondText) << isLess << '\n';
        const bool isGreater = first > second;
        row(firstText + " > " + secondText) << isGreater << '\n';
        const bool isEqual = first == second;
        row(firstText + " == " + secondText) << isEqual << '\n';

        heading("Other constructors and type conversion");
        const Rational zero;
        row("Rational()") << zero << '\n';
        const Rational five(5);
        row("Rational(5)") << five << '\n';
        const Rational unreduced(4, -8);
        row("Rational(4, -8)") << unreduced << '\n';
        result = unreduced + zero;
        row("Rational(4, -8) + Rational()") << result << '\n';
        try
        {
            result = 2 + first; // 2 becomes Rational(2) through the whole number constructor
            row("2 + " + firstText) << result << '\n';
        }
        catch (const logic_error& error)
        {
            row("2 + " + firstText) << error.what() << '\n';
        }
        try
        {
            result = Rational(1, 0);
        }
        catch (const logic_error& error)
        {
            row("Rational(1, 0)") << error.what() << '\n';
        }
    }
}

int main()
{
    cout << boolalpha;
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
