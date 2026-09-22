// PROG2100 Assignment 1 - Conversion
// Same behavior as main.cpp, written with different names and techniques
// for comparison: regex for path shape, <filesystem> for directory checks,
// a namespace instead of a flat list of free functions, and a do-while retry loop.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

namespace WindowsPath
{
    const size_t MAX_FULL_PATH = 260;
    const size_t MAX_NAME_LENGTH = 255;

    // Matches an absolute Windows path: drive letter, colon, backslash, then
    // any run of non-reserved characters. Demonstrates <regex> for the shape
    // check instead of hand-rolled substring scanning.
    const regex WINDOWS_PATH_SHAPE(R"(^[A-Za-z]:\\[^<>:"/\\|?*]+(\\[^<>:"/\\|?*]+)*$)");

    string fileNameOnly(const string& fullPath)
    {
        size_t cut = fullPath.find_last_of("\\/");
        return (cut == string::npos) ? fullPath : fullPath.substr(cut + 1);
    }

    string toUpper(const string& text)
    {
        string upper = text;
        transform(upper.begin(), upper.end(), upper.begin(),
                  [](unsigned char c) { return static_cast<char>(toupper(c)); });
        return upper;
    }

    string nameBeforeFirstDot(const string& fileName)
    {
        size_t dot = fileName.find('.');
        return (dot == string::npos) ? fileName : fileName.substr(0, dot);
    }

    bool endsWithExtension(const string& fileName, const string& extension)
    {
        if (fileName.length() < extension.length())
        {
            return false;
        }
        string tail = fileName.substr(fileName.length() - extension.length());
        return toUpper(tail) == toUpper(extension);
    }

    bool isReservedDeviceName(const string& fileName)
    {
        static const vector<string> reserved = {
            "CON", "PRN", "AUX", "NUL",
            "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
            "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
        };
        string base = toUpper(nameBeforeFirstDot(fileName));
        return find(reserved.begin(), reserved.end(), base) != reserved.end();
    }

    bool isLegalFileName(const string& fileName)
    {
        if (fileName.empty() || fileName.length() > MAX_NAME_LENGTH)
        {
            return false;
        }
        if (fileName.back() == ' ' || fileName.back() == '.')
        {
            return false;
        }
        if (isReservedDeviceName(fileName))
        {
            return false;
        }
        const string illegal = "<>:\"/\\|?*";
        return fileName.find_first_of(illegal) == string::npos;
    }

    bool isWellFormedFullPath(const string& fullPath)
    {
        if (fullPath.empty() || fullPath.length() > MAX_FULL_PATH)
        {
            return false;
        }
        // A bare filename (no drive/backslash) is also accepted here so the
        // program still runs on a Mac during the demo; only reject strings
        // that *look like* a path but are malformed.
        bool looksLikeFullPath = fullPath.find('\\') != string::npos || fullPath.find(':') != string::npos;
        if (!looksLikeFullPath)
        {
            return true;
        }
        return regex_match(fullPath, WINDOWS_PATH_SHAPE);
    }
}

string escapeAngleBrackets(const string& sourceLine)
{
    string escaped;
    escaped.reserve(sourceLine.size());
    for (char ch : sourceLine)
    {
        if (ch == '<')
        {
            escaped += "&lt;";
        }
        else if (ch == '>')
        {
            escaped += "&gt;";
        }
        else
        {
            escaped += ch;
        }
    }
    return escaped;
}

void writeHtmlBody(ifstream& sourceStream, ofstream& destStream)
{
    destStream << "<PRE>\n";
    string sourceLine;
    while (getline(sourceStream, sourceLine))
    {
        destStream << escapeAngleBrackets(sourceLine) << "\n";
    }
    destStream << "</PRE>\n";
}

string requestValidatedPath(const string& promptText, const string& requiredExtension, bool mustAlreadyExist)
{
    string enteredPath;
    bool accepted = false;

    do
    {
        cout << promptText;
        getline(cin, enteredPath);

        string justTheName = WindowsPath::fileNameOnly(enteredPath);

        if (!WindowsPath::endsWithExtension(justTheName, requiredExtension))
        {
            cout << "Expected a " << requiredExtension << " file.\n";
            continue;
        }
        if (!WindowsPath::isLegalFileName(justTheName))
        {
            cout << "\"" << justTheName << "\" is not a legal Windows filename.\n";
            continue;
        }
        if (!WindowsPath::isWellFormedFullPath(enteredPath))
        {
            cout << "\"" << enteredPath << "\" is not a well-formed path.\n";
            continue;
        }
        if (mustAlreadyExist && !fs::exists(enteredPath))
        {
            cout << "No file found at \"" << enteredPath << "\".\n";
            continue;
        }
        if (!mustAlreadyExist)
        {
            fs::path parent = fs::path(enteredPath).parent_path();
            if (!parent.empty() && !fs::exists(parent))
            {
                cout << "Folder does not exist: \"" << parent.string() << "\".\n";
                continue;
            }
        }

        accepted = true;
    }
    while (!accepted);

    return enteredPath;
}

int main()
{
    string sourcePath = requestValidatedPath(
        "Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp", true);

    string destinationPath = requestValidatedPath(
        "Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html", false);

    ifstream sourceStream(sourcePath);
    ofstream destStream(destinationPath);

    writeHtmlBody(sourceStream, destStream);

    sourceStream.close();
    destStream.close();

    cout << "Done. Wrote " << destinationPath << endl;
    return 0;
}
