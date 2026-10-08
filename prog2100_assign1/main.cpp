// PROG2100 Assignment 1 - Conversion
// Converts a C++ source file into an HTML file that displays identically
// to the source when viewed in a browser (< and > escaped, wrapped in <PRE>).
// Uses regex for the path shape check, a namespace for the Windows path rules,
// and do-while retry loops. Standard C++14 - no <filesystem> needed.

#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <cstdlib>

using namespace std;

// Programmer-defined exception for any open/read/write/close failure.
struct ConversionError
{
    string reason;
    string filePath;
    ConversionError(const string& why, const string& where) : reason(why), filePath(where) {}
};

namespace WindowsPath
{
    const size_t MAX_FULL_PATH = 260;
    const size_t MAX_NAME_LENGTH = 255;

    // Matches a Windows path: optional drive letter and colon, optional leading
    // backslash, then backslash-separated runs of non-reserved characters.
    // Demonstrates <regex> for the shape check instead of hand-rolled substring scanning.
    const regex WINDOWS_PATH_SHAPE(R"(^([A-Za-z]:)?\\?[^<>:"/\\|?*]+(\\[^<>:"/\\|?*]+)*$)");

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
        // A forward-slash path (no backslash or colon) is also accepted here so
        // the program still runs on a Mac during the demo; only reject strings
        // that *look like* a Windows path but are malformed.
        bool looksLikeWindowsPath = fullPath.find('\\') != string::npos || fullPath.find(':') != string::npos;
        if (!looksLikeWindowsPath)
        {
            return true;
        }
        return regex_match(fullPath, WINDOWS_PATH_SHAPE);
    }
}

// Hand-written counterpart to a library "replace all": walks the source with
// find() and stitches together the text between matches plus the replacement.
string replaceEvery(const string& source, const string& findText, const string& replaceWith)
{
    if (findText.empty())
    {
        return source;
    }

    string output;
    size_t copiedUpTo = 0;
    size_t match = source.find(findText);

    while (match != string::npos)
    {
        output.append(source, copiedUpTo, match - copiedUpTo);
        output += replaceWith;
        copiedUpTo = match + findText.length();   // skip past the match, never re-scan the replacement
        match = source.find(findText, copiedUpTo);
    }

    output.append(source, copiedUpTo, string::npos);
    return output;
}

string escapeAngleBrackets(const string& sourceLine)
{
    return replaceEvery(replaceEvery(sourceLine, "<", "&lt;"), ">", "&gt;");
}

void writeHtmlBody(ifstream& sourceStream, ofstream& destStream,
                   const string& sourcePath, const string& destinationPath)
{
    // badbit failures (e.g. disk errors) are raised by the library as ios_base::failure.
    // failbit is left off because getline sets it normally at end of file.
    sourceStream.exceptions(ios::badbit);
    destStream.exceptions(ios::badbit);

    destStream << "<PRE>\n";
    string sourceLine;
    while (getline(sourceStream, sourceLine))
    {
        destStream << escapeAngleBrackets(sourceLine) << "\n";
        if (destStream.fail())
        {
            throw ConversionError("Could not write to the output file.", destinationPath);
        }
    }

    if (!sourceStream.eof())
    {
        throw ConversionError("Stopped reading before the end of the source file.", sourcePath);
    }

    destStream << "</PRE>\n";
    if (destStream.fail())
    {
        throw ConversionError("Could not write to the output file.", destinationPath);
    }
}

string requestValidatedPath(const string& promptText, const string& requiredExtension)
{
    string enteredPath;
    bool accepted = false;

    do
    {
        cout << promptText;
        if (!getline(cin, enteredPath))
        {
            cout << "\nNo input available. Exiting.\n";
            exit(1);
        }

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

        accepted = true;
    }
    while (!accepted);

    return enteredPath;
}

// Prompts for a validated path until the stream opens it successfully.
template <typename Stream>
string openWithRetry(Stream& stream, const string& promptText, const string& extension,
                     const string& failureMessage)
{
    string path;
    bool opened = false;

    do
    {
        path = requestValidatedPath(promptText, extension);
        try
        {
            stream.open(path);
            if (stream.fail())
            {
                throw ConversionError(failureMessage, path);
            }
            opened = true;
        }
        catch (const ConversionError& err)
        {
            cout << err.reason << " (" << err.filePath << ")\n";
            stream.clear();   // reset failbit so the next open() can succeed
        }
        catch (...)
        {
            cout << "Unknown error while opening \"" << path << "\".\n";
            stream.clear();
        }
    }
    while (!opened);

    return path;
}

template <typename Stream>
bool closeStream(Stream& stream, const string& path)
{
    try
    {
        stream.close();   // for output, this flushes - write errors can show up here
        if (stream.fail())
        {
            throw ConversionError("Could not close the file cleanly.", path);
        }
        return true;
    }
    catch (const ConversionError& err)
    {
        cout << err.reason << " (" << err.filePath << ")\n";
    }
    catch (const ios_base::failure& e)
    {
        cout << "Stream error closing \"" << path << "\": " << e.what() << "\n";
    }
    catch (...)
    {
        cout << "Unknown error closing \"" << path << "\".\n";
    }
    return false;
}

int main()
{
    ifstream sourceStream;
    ofstream destStream;

    string sourcePath = openWithRetry(sourceStream,
        "Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp",
        "Could not open the source file. Check that it exists and try again.");

    string destinationPath = openWithRetry(destStream,
        "Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html",
        "Could not create the output file. Check that the folder exists and try again.");

    bool converted = false;
    try
    {
        writeHtmlBody(sourceStream, destStream, sourcePath, destinationPath);
        converted = true;
    }
    catch (const ConversionError& err)          // programmer-defined
    {
        cout << err.reason << " (" << err.filePath << ")\n";
    }
    catch (const ios_base::failure& e)          // library
    {
        cout << "Stream error during conversion: " << e.what() << "\n";
    }
    catch (const exception& e)                  // any other library exception
    {
        cout << "Unexpected error: " << e.what() << "\n";
    }
    catch (...)                                 // default
    {
        cout << "Unknown error during conversion.\n";
    }

    sourceStream.clear();   // getline set failbit at end of file; don't mistake it for a close error
    bool sourceClosed = closeStream(sourceStream, sourcePath);
    bool destClosed = closeStream(destStream, destinationPath);

    if (!converted || !sourceClosed || !destClosed)
    {
        cout << "Conversion did not complete successfully.\n";
        return 1;
    }

    cout << "Done. Wrote " << destinationPath << endl;
    return 0;
}
