// PROG2100 Assignment 1 - Conversion (alternate version)
// Same behavior as main.cpp, written as flat free functions with hand-rolled
// path checks instead of regex, for comparison.
// Converts a C++ source file into an HTML file that displays identically
// to the source when viewed in a browser (< and > escaped, wrapped in <PRE>).

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <exception>

using namespace std;

const int MAX_PATH_LENGTH = 260;       // Windows MAX_PATH
const int MAX_FILENAME_LENGTH = 255;   // Windows filename component limit

// Programmer-defined exception, thrown when opening, reading, writing or
// closing one of the files fails.
struct FileStreamException
{
    string message;
    string path;
    FileStreamException(const string& msg, const string& filePath) : message(msg), path(filePath) {}
};

// --- validation ---
string extractFilename(const string& path);
string getBaseNameForReservedCheck(const string& filename);
string toUpperCase(const string& s);
bool hasExtension(const string& filename, const string& extension);
bool isValidWindowsFilename(const string& filename);
bool isValidPath(const string& path, string& reason);

// --- I/O prompting ---
string promptForPath(const string& prompt, const string& extension);
string openInputFile(ifstream& in);
string openOutputFile(ofstream& out);

// --- conversion ---
string replaceAll(const string& source, const string& target, const string& replacement);
string convertLine(const string& line);
void convertFile(ifstream& in, ofstream& out, const string& inPath, const string& outPath);
bool closeFiles(ifstream& in, ofstream& out, const string& inPath, const string& outPath);

int main()
{
    ifstream inFile;
    ofstream outFile;

    string cppPath = openInputFile(inFile);
    string htmlPath = openOutputFile(outFile);

    bool converted = false;
    try
    {
        convertFile(inFile, outFile, cppPath, htmlPath);
        converted = true;
    }
    catch (const FileStreamException& e)       // programmer-defined
    {
        cout << "Error: " << e.message << " (" << e.path << ")" << endl;
    }
    catch (const ios_base::failure& e)         // library
    {
        cout << "Stream error during conversion: " << e.what() << endl;
    }
    catch (const exception& e)                 // any other library exception
    {
        cout << "Unexpected error during conversion: " << e.what() << endl;
    }
    catch (...)                                // default
    {
        cout << "An unknown error occurred during conversion." << endl;
    }

    bool closed = closeFiles(inFile, outFile, cppPath, htmlPath);

    if (!converted || !closed)
    {
        cout << "Conversion did not complete successfully." << endl;
        return 1;
    }

    cout << "Done. Wrote " << htmlPath << endl;
    return 0;
}

string openInputFile(ifstream& in)
{
    bool opened = false;
    string path;

    while (!opened)
    {
        path = promptForPath("Enter path to source .cpp file (e.g. c:\\bobFile.cpp): ", ".cpp");
        try
        {
            in.open(path);
            if (in.fail())
            {
                throw FileStreamException("Could not open the source file. Check the path and try again", path);
            }
            opened = true;
        }
        catch (const FileStreamException& e)
        {
            cout << e.message << " (" << e.path << ")" << endl;
            in.clear();    // reset failbit so the next open() attempt can succeed
        }
        catch (...)
        {
            cout << "An unknown error occurred opening the source file." << endl;
            in.clear();
        }
    }

    return path;
}

string openOutputFile(ofstream& out)
{
    bool opened = false;
    string path;

    while (!opened)
    {
        path = promptForPath("Enter path for output .html file (e.g. c:\\bobFile.html): ", ".html");
        try
        {
            out.open(path);
            if (out.fail())
            {
                throw FileStreamException("Could not create the output file. Check that the folder exists and try again", path);
            }
            opened = true;
        }
        catch (const FileStreamException& e)
        {
            cout << e.message << " (" << e.path << ")" << endl;
            out.clear();
        }
        catch (...)
        {
            cout << "An unknown error occurred creating the output file." << endl;
            out.clear();
        }
    }

    return path;
}

string promptForPath(const string& prompt, const string& extension)
{
    string path;
    bool valid = false;

    while (!valid)
    {
        cout << prompt;
        if (!getline(cin, path))
        {
            // Input stream closed (e.g. Ctrl+Z / Ctrl+D) - nothing more to read.
            cout << endl << "No input available. Exiting." << endl;
            exit(1);
        }

        string filename = extractFilename(path);
        string reason;

        if (!hasExtension(filename, extension))
        {
            cout << "File must have a " << extension << " extension." << endl;
        }
        else if (!isValidWindowsFilename(filename))
        {
            cout << "\"" << filename << "\" is not a valid Windows filename." << endl;
        }
        else if (!isValidPath(path, reason))
        {
            cout << "\"" << path << "\" is not a valid path: " << reason << endl;
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
        // Control characters (0-31) are also not allowed.
        if (static_cast<unsigned char>(filename[i]) < 32)
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

bool isValidPath(const string& path, string& reason)
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

    // Optional drive prefix, e.g. "c:". A colon is only legal right after the drive letter.
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

    // A leading separator is allowed (root of the drive), so skip one.
    if (start < path.length() && (path[start] == '\\' || path[start] == '/'))
    {
        start++;
    }

    // Every folder name between separators must itself be a valid Windows name.
    // The last component is the filename, which is validated separately.
    size_t componentStart = start;
    for (size_t i = start; i < path.length(); i++)
    {
        if (path[i] != '\\' && path[i] != '/')
        {
            continue;
        }

        string folder = path.substr(componentStart, i - componentStart);
        if (folder.empty())
        {
            reason = "path contains an empty folder name (doubled separator).";
            return false;
        }
        if (folder != "." && folder != ".." && !isValidWindowsFilename(folder))
        {
            reason = "folder name \"" + folder + "\" is not valid on Windows.";
            return false;
        }
        componentStart = i + 1;
    }

    return true;
}

// Custom equivalent of a library "replace all" routine: returns a copy of
// source with every occurrence of target replaced by replacement.
string replaceAll(const string& source, const string& target, const string& replacement)
{
    if (target.empty())
    {
        return source;
    }

    string result;
    size_t searchFrom = 0;
    size_t found = source.find(target, searchFrom);

    while (found != string::npos)
    {
        // Copy the text before the match, then the replacement instead of the match.
        result += source.substr(searchFrom, found - searchFrom);
        result += replacement;

        // Resume searching after the matched text, so a replacement that
        // contains the target can't cause an infinite loop.
        searchFrom = found + target.length();
        found = source.find(target, searchFrom);
    }

    result += source.substr(searchFrom);
    return result;
}

string convertLine(const string& line)
{
    string result = replaceAll(line, "<", "&lt;");
    result = replaceAll(result, ">", "&gt;");
    return result;
}

void convertFile(ifstream& in, ofstream& out, const string& inPath, const string& outPath)
{
    // Let the library throw ios_base::failure on unrecoverable stream errors.
    // (failbit is left off because getline sets it normally at end of file.)
    in.exceptions(ios::badbit);
    out.exceptions(ios::badbit);

    out << "<PRE>" << endl;

    string line;
    while (getline(in, line))
    {
        out << convertLine(line) << endl;
        if (out.fail())
        {
            throw FileStreamException("Failed writing to the output file", outPath);
        }
    }

    // getline stops at end of file; anything else means the read failed.
    if (!in.eof())
    {
        throw FileStreamException("Failed reading from the source file", inPath);
    }

    out << "</PRE>" << endl;
    if (out.fail())
    {
        throw FileStreamException("Failed writing to the output file", outPath);
    }
}

bool closeFiles(ifstream& in, ofstream& out, const string& inPath, const string& outPath)
{
    bool success = true;

    // getline sets failbit when it reaches end of file, so clear it first;
    // otherwise fail() below would report a close error that didn't happen.
    in.clear();

    try
    {
        in.close();
        if (in.fail())
        {
            throw FileStreamException("Failed to close the source file", inPath);
        }
    }
    catch (const FileStreamException& e)
    {
        cout << "Error: " << e.message << " (" << e.path << ")" << endl;
        success = false;
    }
    catch (const ios_base::failure& e)
    {
        cout << "Stream error closing the source file: " << e.what() << endl;
        success = false;
    }
    catch (...)
    {
        cout << "An unknown error occurred closing the source file." << endl;
        success = false;
    }

    try
    {
        out.close();    // flushes buffered output, so write errors can surface here
        if (out.fail())
        {
            throw FileStreamException("Failed to close the output file", outPath);
        }
    }
    catch (const FileStreamException& e)
    {
        cout << "Error: " << e.message << " (" << e.path << ")" << endl;
        success = false;
    }
    catch (const ios_base::failure& e)
    {
        cout << "Stream error closing the output file: " << e.what() << endl;
        success = false;
    }
    catch (...)
    {
        cout << "An unknown error occurred closing the output file." << endl;
        success = false;
    }

    return success;
}
