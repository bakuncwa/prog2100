// PROG2100 Assignment 1 - Conversion
// Converts a C++ source file into an HTML file that displays identically
// to the source when viewed in a browser (< and > escaped, wrapped in <PRE>).

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

const int MAX_PATH_LENGTH = 260;       // Windows MAX_PATH
const int MAX_FILENAME_LENGTH = 255;   // Windows filename component limit

// --- validation ---
string extractFilename(const string& path);
string getBaseNameForReservedCheck(const string& filename);
string toUpperCase(const string& s);
bool hasExtension(const string& filename, const string& extension);
bool isValidWindowsFilename(const string& filename);
bool isValidPathFormat(const string& path);

// --- I/O prompting ---
string promptForPath(const string& prompt, const string& extension);

// --- conversion ---
string convertLine(const string& line);
void convertFile(ifstream& in, ofstream& out);

int main()
{
    string cppPath = promptForPath("Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp");

    ifstream inFile;
    inFile.open(cppPath);
    while (!inFile.is_open())
    {
        cout << "Could not open that file. Please check the path and try again." << endl;
        cppPath = promptForPath("Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp");
        inFile.open(cppPath);
    }

    string htmlPath = promptForPath("Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html");

    ofstream outFile;
    outFile.open(htmlPath);
    while (!outFile.is_open())
    {
        cout << "Could not create that file. Check that the folder exists and try again." << endl;
        htmlPath = promptForPath("Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html");
        outFile.open(htmlPath);
    }

    convertFile(inFile, outFile);

    inFile.close();
    outFile.close();

    cout << "Done. Wrote " << htmlPath << endl;
    return 0;
}

string promptForPath(const string& prompt, const string& extension)
{
    string path;
    bool valid = false;

    while (!valid)
    {
        cout << prompt;
        getline(cin, path);

        string filename = extractFilename(path);

        if (!hasExtension(filename, extension))
        {
            cout << "File must have a " << extension << " extension." << endl;
        }
        else if (!isValidWindowsFilename(filename))
        {
            cout << "\"" << filename << "\" is not a valid Windows filename." << endl;
        }
        else if (!isValidPathFormat(path))
        {
            cout << "\"" << path << "\" is not a valid path (too long or malformed)." << endl;
        }
        else
        {
            valid = true;
        }
    }

    return path;
}

string extractFilename(const string& path)
{
    // Accept both separators since the demo machine may not be Windows,
    // even though the *rules* being validated are Windows rules.
    size_t lastSlash = path.find_last_of("\\/");
    if (lastSlash == string::npos)
    {
        return path;
    }
    return path.substr(lastSlash + 1);
}

string getBaseNameForReservedCheck(const string& filename)
{
    // Windows blocks e.g. "CON.txt" too, so the reserved-name check
    // is against everything before the first dot, not the whole filename.
    size_t dot = filename.find('.');
    if (dot == string::npos)
    {
        return filename;
    }
    return filename.substr(0, dot);
}

string toUpperCase(const string& s)
{
    string result = s;
    for (size_t i = 0; i < result.length(); i++)
    {
        result[i] = static_cast<char>(toupper(static_cast<unsigned char>(result[i])));
    }
    return result;
}

bool hasExtension(const string& filename, const string& extension)
{
    if (filename.length() < extension.length())
    {
        return false;
    }
    string tail = filename.substr(filename.length() - extension.length());
    return toUpperCase(tail) == toUpperCase(extension);
}

bool isValidWindowsFilename(const string& filename)
{
    if (filename.empty() || filename.length() > MAX_FILENAME_LENGTH)
    {
        return false;
    }

    // Reserved characters, per Windows file naming rules.
    const string reservedChars = "<>:\"/\\|?*";
    for (size_t i = 0; i < filename.length(); i++)
    {
        if (reservedChars.find(filename[i]) != string::npos)
        {
            return false;
        }
    }

    // Cannot end with a space or a period.
    char lastChar = filename[filename.length() - 1];
    if (lastChar == ' ' || lastChar == '.')
    {
        return false;
    }

    // Reserved device names, case-insensitive, regardless of extension.
    const string reservedNames[] = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
    };
    string base = toUpperCase(getBaseNameForReservedCheck(filename));
    for (size_t i = 0; i < sizeof(reservedNames) / sizeof(reservedNames[0]); i++)
    {
        if (base == reservedNames[i])
        {
            return false;
        }
    }

    return true;
}

bool isValidPathFormat(const string& path)
{
    if (path.empty() || path.length() > MAX_PATH_LENGTH)
    {
        return false;
    }
    return true;
}

string convertLine(const string& line)
{
    string result;
    result.reserve(line.length());

    for (size_t i = 0; i < line.length(); i++)
    {
        if (line[i] == '<')
        {
            result += "&lt;";
        }
        else if (line[i] == '>')
        {
            result += "&gt;";
        }
        else
        {
            result += line[i];
        }
    }

    return result;
}

void convertFile(ifstream& in, ofstream& out)
{
    out << "<PRE>" << endl;

    string line;
    while (getline(in, line))
    {
        out << convertLine(line) << endl;
    }

    out << "</PRE>" << endl;
}