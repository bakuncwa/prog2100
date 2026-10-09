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
#include <cctype>

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
    const size_t MAX_PATH_LENGTH = 260;
    const size_t MAX_NAME_LENGTH = 255;

    // Matches a Windows path: optional drive letter and colon, optional leading
    // separator, then runs of non-reserved characters split by \ or / (Windows
    // accepts both). Demonstrates <regex> for the shape check instead of
    // hand-rolled substring scanning.
    const regex WINDOWS_PATH_SHAPE(R"(^([A-Za-z]:)?[\\/]?[^<>:"/\\|?*]+([\\/][^<>:"/\\|?*]+)*$)");

    string extractFileName(const string& path)
    {
        size_t cut = path.find_last_of("\\/");
        return (cut == string::npos) ? path : path.substr(cut + 1);
    }

    string toUpper(const string& text)
    {
        string upper = text;
        transform(upper.begin(), upper.end(), upper.begin(),
                  [](unsigned char c) { return static_cast<char>(toupper(c)); });
        return upper;
    }

    // Everything before the first dot, e.g. "CON" for "CON.tar.gz".
    string baseName(const string& fileName)
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

    // Windows device names (CON, LPT1, ...) can't be used as a file or folder
    // name, even with an extension added.
    bool isDeviceName(const string& fileName)
    {
        static const vector<string> devices = {
            "CON", "PRN", "AUX", "NUL",
            "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
            "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
        };
        string base = toUpper(baseName(fileName));
        return find(devices.begin(), devices.end(), base) != devices.end();
    }

    // Applies the Windows naming rules to one file or folder name.
    // On failure, `reason` says which rule was broken.
    bool checkName(const string& name, string& reason)
    {
        if (name.empty())
        {
            reason = "name is empty.";
            return false;
        }
        if (name.length() > MAX_NAME_LENGTH)
        {
            reason = "name is longer than " + to_string(MAX_NAME_LENGTH) + " characters.";
            return false;
        }
        if (name.back() == ' ' || name.back() == '.')
        {
            reason = "name can't end with a space or a period.";
            return false;
        }
        if (isDeviceName(name))
        {
            reason = "\"" + baseName(name) + "\" is a reserved Windows device name.";
            return false;
        }

        const string illegal = "<>:\"/\\|?*";
        size_t bad = name.find_first_of(illegal);
        if (bad != string::npos)
        {
            reason = string("character '") + name[bad] + "' is not allowed.";
            return false;
        }
        for (char ch : name)
        {
            if (static_cast<unsigned char>(ch) < 32)
            {
                reason = "control characters are not allowed.";
                return false;
            }
        }
        return true;
    }

    // Applies the naming rules to every folder in the path ("." and ".." are
    // allowed), then confirms the overall shape with the regex.
    // On failure, `reason` says what's wrong.
    bool checkPath(const string& path, string& reason)
    {
        if (path.empty())
        {
            reason = "path is empty.";
            return false;
        }
        if (path.length() > MAX_PATH_LENGTH)
        {
            reason = "path is longer than " + to_string(MAX_PATH_LENGTH) + " characters.";
            return false;
        }

        // Optional drive ("c:"); a colon anywhere else is caught by checkName below.
        size_t start = 0;
        if (path.length() >= 2 && path[1] == ':')
        {
            if (!isalpha(static_cast<unsigned char>(path[0])))
            {
                reason = "drive must be a single letter followed by a colon (e.g. c:).";
                return false;
            }
            start = 2;
        }
        // A leading separator (root of the drive) is allowed.
        if (start < path.length() && (path[start] == '\\' || path[start] == '/'))
        {
            start++;
        }

        size_t separator = path.find_first_of("\\/", start);
        while (separator != string::npos)
        {
            string folder = path.substr(start, separator - start);
            if (folder.empty())
            {
                reason = "path contains an empty folder name (doubled separator).";
                return false;
            }
            string folderReason;
            if (folder != "." && folder != ".." && !checkName(folder, folderReason))
            {
                reason = "folder \"" + folder + "\": " + folderReason;
                return false;
            }
            start = separator + 1;
            separator = path.find_first_of("\\/", start);
        }

        // Final shape check; the specific checks above should catch problems first.
        if (!regex_match(path, WINDOWS_PATH_SHAPE))
        {
            reason = "path is not in the form drive:\\folder\\file.";
            return false;
        }
        return true;
    }
}

// Hand-written counterpart to a library "replace all": walks the source with
// find() and stitches together the text between matches plus the replacement.
string replaceText(const string& source, const string& findText, const string& replaceWith)
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

string escapeHtml(const string& sourceLine)
{
    return replaceText(replaceText(sourceLine, "<", "&lt;"), ">", "&gt;");
}

void writeHtml(ifstream& sourceStream, ofstream& destStream,
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
        destStream << escapeHtml(sourceLine) << "\n";
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

string requestPath(const string& promptText, const string& requiredExtension)
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

        string justTheName = WindowsPath::extractFileName(enteredPath);
        string reason;

        if (!WindowsPath::endsWithExtension(justTheName, requiredExtension))
        {
            cout << "Expected a " << requiredExtension << " file.\n";
            continue;
        }
        if (!WindowsPath::checkName(justTheName, reason))
        {
            cout << "\"" << justTheName << "\" is not a legal Windows filename: " << reason << "\n";
            continue;
        }
        if (!WindowsPath::checkPath(enteredPath, reason))
        {
            cout << "\"" << enteredPath << "\" is not a valid Windows path: " << reason << "\n";
            continue;
        }

        accepted = true;
    }
    while (!accepted);

    return enteredPath;
}

// Prompts for a validated path until the stream opens it successfully.
template <typename Stream>
string openFile(Stream& stream, const string& promptText, const string& extension,
                     const string& failureMessage)
{
    string path;
    bool opened = false;

    do
    {
        path = requestPath(promptText, extension);
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

    string sourcePath = openFile(sourceStream,
        "Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp",
        "Could not open the source file. Check that it exists and try again.");

    string destinationPath = openFile(destStream,
        "Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html",
        "Could not create the output file. Check that the folder exists and try again.");

    bool converted = false;
    try
    {
        writeHtml(sourceStream, destStream, sourcePath, destinationPath);
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
