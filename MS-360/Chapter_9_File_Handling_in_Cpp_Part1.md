# Chapter 9: File Handling in C++ (Part 1)

## Introduction to File Handling

File handling is one of the most important aspects of programming, allowing applications to store and retrieve data persistently. C++ provides robust file handling capabilities through its stream classes, which offer a consistent and type-safe approach to dealing with files.

In this chapter, we'll explore how to perform file operations in C++, starting with the fundamental stream concepts and progressing to practical file reading and writing techniques.

## 9.1 Streams (ifstream, ofstream, fstream)

### Stream Hierarchy in C++

C++ file handling is built around the concept of streams. A stream is an abstraction that represents a sequence of bytes, whether they're coming from a file, keyboard, network, or any other source or destination.

The C++ stream classes are organized in a hierarchy:

```
         ios_base
            |
            v
            ios
            /\
           /  \
          /    \
         /      \
        v        v
    istream    ostream
    /  |        |  \
   /   |        |   \
  v    v        v    v
ifstream iostream ofstream
          |
          v
       fstream
```

- **ios_base**: The base class that provides basic functionality common to all stream classes
- **ios**: Adds formatting capabilities to the streams
- **istream**: Base class for input streams
- **ostream**: Base class for output streams
- **iostream**: Combined input and output capabilities
- **ifstream**: Input file stream - for reading from files
- **ofstream**: Output file stream - for writing to files
- **fstream**: File stream with both input and output capabilities

### Header Files for File Handling

```cpp
#include <fstream>   // For file streams (ifstream, ofstream, fstream)
#include <iostream>  // For standard streams (cin, cout)
#include <sstream>   // For string streams (stringstream)
```

### ifstream (Input File Stream)

An `ifstream` object is used to read data from a file:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Create an input file stream
    ifstream inputFile;
    
    // Open file
    inputFile.open("example.txt");
    
    // Alternative way to open file (constructor method)
    // ifstream inputFile("example.txt");
    
    // Check if file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Read data from file
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    
    // Close the file when done
    inputFile.close();
    
    return 0;
}
```

### ofstream (Output File Stream)

An `ofstream` object is used to write data to a file:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Create an output file stream
    ofstream outputFile;
    
    // Open file (will create if doesn't exist, or truncate if it does)
    outputFile.open("output.txt");
    
    // Alternative way to open file (constructor method)
    // ofstream outputFile("output.txt");
    
    // Check if file opened successfully
    if (!outputFile.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }
    
    // Write data to file
    outputFile << "Hello, File I/O in C++!" << endl;
    outputFile << "This is a second line of text." << endl;
    
    // Close the file when done
    outputFile.close();
    
    cout << "Data written to file successfully." << endl;
    
    return 0;
}
```

### fstream (File Stream)

An `fstream` object can be used for both reading and writing:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Create a file stream
    fstream fileStream;
    
    // Open for both reading and writing
    fileStream.open("data.txt", ios::in | ios::out | ios::app);
    
    // Check if file opened successfully
    if (!fileStream.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Write to file
    fileStream << "Adding new content to the file." << endl;
    
    // Reset file position to beginning for reading
    fileStream.seekg(0, ios::beg);
    
    // Read file content
    string line;
    cout << "File content:" << endl;
    while (getline(fileStream, line)) {
        cout << line << endl;
    }
    
    // Close the file
    fileStream.close();
    
    return 0;
}
```

### File Opening Modes

When opening a file, you can specify a mode that determines how the file should be treated:

| Mode Flag | Description |
|-----------|-------------|
| `ios::in` | Open for input operations (reading) |
| `ios::out` | Open for output operations (writing) - truncates existing file by default |
| `ios::app` | Append mode - all output is appended to the end of the file |
| `ios::ate` | Open and seek to the end of file immediately after opening |
| `ios::trunc` | Truncate the file to zero length if it exists (default for `ios::out`) |
| `ios::binary` | Open in binary mode rather than text mode |

You can combine these flags using the bitwise OR operator (`|`):

```cpp
// Open for reading and writing without truncating
fstream file("data.txt", ios::in | ios::out);

// Open in append mode
ofstream outFile("log.txt", ios::app);

// Open in binary mode for reading
ifstream binFile("image.png", ios::binary);

// Open for output, create if doesn't exist, and go to the end
ofstream logFile("server.log", ios::out | ios::app);
```

### Stream States and Error Handling

Stream objects maintain state flags that indicate their current condition:

- **good()**: Returns true if no errors have occurred and the stream is ready for I/O
- **eof()**: Returns true if end-of-file has been reached
- **fail()**: Returns true if a formatting error has occurred
- **bad()**: Returns true if an unrecoverable error has occurred

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream file("nonexistent.txt");
    
    if (file.good()) {
        cout << "File opened successfully." << endl;
    } else {
        cout << "File state flags:" << endl;
        cout << "- EOF flag: " << (file.eof() ? "Set" : "Not set") << endl;
        cout << "- Fail flag: " << (file.fail() ? "Set" : "Not set") << endl;
        cout << "- Bad flag: " << (file.bad() ? "Set" : "Not set") << endl;
    }
    
    // Alternative way to check if file opened successfully
    if (!file) {
        cerr << "Error opening file!" << endl;
    }
    
    // Clear error state flags
    file.clear();
    
    // Try to open a different file
    file.open("existing.txt");
    
    // Reset error state for specific error
    if (file.fail()) {
        file.clear(ios::failbit);
    }
    
    return 0;
}
```

### File Position Indicators

Stream objects maintain pointers to the current position in the file:

- **tellg()**: Returns the current position of the "get" pointer (input)
- **seekg()**: Sets the position of the "get" pointer (input)
- **tellp()**: Returns the current position of the "put" pointer (output)
- **seekp()**: Sets the position of the "put" pointer (output)

The seek functions take two parameters: the position and the seek direction:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file("data.txt", ios::in | ios::out);
    
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Get current position
    streampos initialPos = file.tellg();
    cout << "Initial position: " << initialPos << endl;
    
    // Move to the 10th byte of the file
    file.seekg(10, ios::beg);
    
    // Move 5 bytes forward from current position
    file.seekg(5, ios::cur);
    
    // Move 10 bytes before the end of file
    file.seekg(-10, ios::end);
    
    // Return to beginning of file
    file.seekg(0, ios::beg);
    
    // Go to end of file
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    cout << "File size: " << fileSize << " bytes" << endl;
    
    file.close();
    return 0;
}
```

## 9.2 Reading and Writing Text Files

### Opening and Closing Files

**Opening Files**:

There are two primary ways to open a file:

1. Using the constructor:
```cpp
ifstream inFile("input.txt");
ofstream outFile("output.txt");
fstream file("data.txt", ios::in | ios::out);
```

2. Using the `open()` method:
```cpp
ifstream inFile;
inFile.open("input.txt");

ofstream outFile;
outFile.open("output.txt", ios::out);

fstream file;
file.open("data.txt", ios::in | ios::out | ios::app);
```

**Closing Files**:

Files should be closed when they're no longer needed:

```cpp
inFile.close();
outFile.close();
file.close();
```

When a file stream object goes out of scope, its destructor automatically closes the file, but it's good practice to explicitly close files when you're done with them.

### Writing to Text Files

**Basic Writing**:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("sample.txt");
    
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }
    
    // Write basic data types
    int id = 101;
    string name = "John Doe";
    double salary = 50000.50;
    
    outFile << "ID: " << id << endl;
    outFile << "Name: " << name << endl;
    outFile << "Salary: " << salary << endl;
    
    // Write formatted data
    outFile << fixed << setprecision(2);
    outFile << "Formatted salary: $" << salary << endl;
    
    outFile.close();
    cout << "Data written successfully!" << endl;
    
    return 0;
}
```

**Append Mode**:

```cpp
ofstream logFile("application.log", ios::app);
logFile << "Log entry at " << getCurrentTime() << ": System started" << endl;
```

**Writing Character by Character**:

```cpp
ofstream outFile("char_output.txt");
string message = "Character by character";

for (char c : message) {
    outFile.put(c);
}

// Or using another method
for (size_t i = 0; i < message.length(); ++i) {
    outFile.write(&message[i], 1);
}
```

**Writing Binary Data to Text File**:

```cpp
// Not recommended, but possible
ofstream outFile("mixed.txt");
int num = 12345;
outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
```

### Reading from Text Files

**Reading Line by Line**:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inFile("sample.txt");
    
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }
    
    string line;
    
    // Read file line by line
    cout << "File content:" << endl;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    
    inFile.close();
    return 0;
}
```

**Reading Word by Word**:

```cpp
ifstream inFile("text.txt");
string word;

while (inFile >> word) {
    cout << word << endl;
}
```

**Reading Character by Character**:

```cpp
ifstream inFile("char_input.txt");
char ch;

while (inFile.get(ch)) {
    cout << ch;
}
```

**Reading Formatted Data**:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    ifstream inFile("employee.txt");
    
    if (!inFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    int id;
    string name;
    double salary;
    
    // Format of file is assumed to be:
    // 101 John_Doe 50000.50
    // 102 Jane_Smith 55000.75
    
    cout << "Employee data:" << endl;
    cout << "--------------" << endl;
    
    while (inFile >> id >> name >> salary) {
        // Replace underscores with spaces
        replace(name.begin(), name.end(), '_', ' ');
        
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: $" << fixed << setprecision(2) << salary << endl;
        cout << endl;
    }
    
    inFile.close();
    return 0;
}
```

**Checking for End of File**:

```cpp
ifstream inFile("data.txt");
string line;

while (!inFile.eof()) {
    getline(inFile, line);
    
    // Important: check if read was successful before processing
    if (!inFile.fail()) {
        cout << line << endl;
    }
}

// Better approach to avoid duplicating the last line
while (getline(inFile, line)) {
    cout << line << endl;
}
```

### Reading and Writing Mixed Data

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    double gpa;
};

void saveStudents(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename);
    
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    
    for (const auto& student : students) {
        // Replace spaces with underscores for easier parsing
        string nameNoSpaces = student.name;
        replace(nameNoSpaces.begin(), nameNoSpaces.end(), ' ', '_');
        
        outFile << student.id << " "
                << nameNoSpaces << " "
                << student.gpa << endl;
    }
    
    outFile.close();
}

vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream inFile(filename);
    
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return students;
    }
    
    Student temp;
    string nameWithUnderscores;
    
    while (inFile >> temp.id >> nameWithUnderscores >> temp.gpa) {
        // Replace underscores with spaces
        replace(nameWithUnderscores.begin(), nameWithUnderscores.end(), '_', ' ');
        temp.name = nameWithUnderscores;
        
        students.push_back(temp);
    }
    
    inFile.close();
    return students;
}

int main() {
    // Create some student records
    vector<Student> students = {
        {1001, "John Doe", 3.75},
        {1002, "Jane Smith", 3.90},
        {1003, "Bob Johnson", 3.45}
    };
    
    // Save to file
    saveStudents(students, "students.txt");
    
    // Load from file
    vector<Student> loadedStudents = loadStudents("students.txt");
    
    // Display loaded students
    cout << "Loaded students:" << endl;
    cout << "-----------------" << endl;
    
    for (const auto& student : loadedStudents) {
        cout << "ID: " << student.id << endl;
        cout << "Name: " << student.name << endl;
        cout << "GPA: " << student.gpa << endl;
        cout << endl;
    }
    
    return 0;
}
```

### Error Handling and File Management

**Proper Error Checking**:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool processFile(const string& filename) {
    ifstream inFile(filename);
    
    // Check if file opened successfully
    if (!inFile) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }
    
    string line;
    int lineCount = 0;
    
    while (getline(inFile, line)) {
        try {
            ++lineCount;
            // Process line here
            cout << "Line " << lineCount << ": " << line << endl;
            
            // Example of detecting a format error
            if (line.empty() && lineCount == 1) {
                throw runtime_error("First line cannot be empty");
            }
        }
        catch (const exception& e) {
            cerr << "Error processing line " << lineCount << ": " << e.what() << endl;
            inFile.close();
            return false;
        }
    }
    
    // Check if any errors occurred during reading
    if (inFile.bad()) {
        cerr << "Error: I/O error while reading file" << endl;
        inFile.close();
        return false;
    }
    else if (inFile.fail() && !inFile.eof()) {
        cerr << "Error: Non-integer data encountered" << endl;
        inFile.close();
        return false;
    }
    
    inFile.close();
    cout << "Successfully processed " << lineCount << " lines" << endl;
    return true;
}

int main() {
    if (processFile("example.txt")) {
        cout << "File processing succeeded" << endl;
    }
    else {
        cout << "File processing failed" << endl;
    }
    
    return 0;
}
```

**Using RAII for File Handling**:

Resource Acquisition Is Initialization (RAII) is a programming idiom where resource management is tied to object lifetime:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class FileHandler {
private:
    ifstream file;
    
public:
    FileHandler(const string& filename) : file(filename) {
        if (!file) {
            throw runtime_error("Could not open file: " + filename);
        }
    }
    
    // No need to explicitly close the file - destructor will handle it
    ~FileHandler() {
        if (file.is_open()) {
            file.close();
        }
    }
    
    bool getLine(string& line) {
        return static_cast<bool>(getline(file, line));
    }
    
    bool isGood() const {
        return file.good();
    }
};

int main() {
    try {
        FileHandler handler("example.txt");
        
        string line;
        while (handler.getLine(line)) {
            cout << line << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

### Best Practices for File Handling

1. **Always check if file operations succeeded** before proceeding with reading or writing
2. **Close files explicitly** when you're done with them
3. **Use appropriate opening modes** for your specific needs
4. **Handle errors gracefully** with proper error messages
5. **Use RAII principles** for automatic resource management
6. **Avoid mixing binary and text operations** on the same file
7. **Be careful with file paths** - consider platform differences
8. **Use stringstreams for string parsing and formatting** before file operations
9. **Implement proper error recovery** when file operations fail
10. **Consider file permissions** when accessing files

### Practical Example: A Simple CSV Parser

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> readCSV(const string& filename, char delimiter = ',') {
    vector<vector<string>> data;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return data;
    }
    
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        
        while (getline(ss, cell, delimiter)) {
            row.push_back(cell);
        }
        
        data.push_back(row);
    }
    
    file.close();
    return data;
}

void writeCSV(const string& filename, const vector<vector<string>>& data, char delimiter = ',') {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << delimiter;
            }
        }
        file << endl;
    }
    
    file.close();
}

int main() {
    // Example: Reading a CSV file
    vector<vector<string>> csvData = readCSV("employees.csv");
    
    cout << "CSV data:" << endl;
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            cout << cell << "\t";
        }
        cout << endl;
    }
    
    // Example: Modifying and writing a CSV file
    vector<vector<string>> outputData = {
        {"Name", "Department", "Salary"},
        {"John Doe", "Engineering", "75000"},
        {"Jane Smith", "Marketing", "65000"},
        {"Bob Johnson", "Finance", "85000"}
    };
    
    writeCSV("output.csv", outputData);
    cout << "Output CSV file written successfully!" << endl;
    
    return 0;
}
```

### File Handling with Exception Safety

```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

string readEntireFile(const string& filename) {
    ifstream file(filename);
    
    if (!file) {
        throw runtime_error("Could not open file: " + filename);
    }
    
    // Read entire file content
    string content((istreambuf_iterator<char>(file)), 
                   istreambuf_iterator<char>());
    
    if (file.bad()) {
        throw runtime_error("I/O error while reading file: " + filename);
    }
    
    return content;
}

void writeStringToFile(const string& filename, const string& content) {
    ofstream file(filename);
    
    if (!file) {
        throw runtime_error("Could not open file for writing: " + filename);
    }
    
    file << content;
    
    if (!file) {
        throw runtime_error("Error writing to file: " + filename);
    }
}

int main() {
    try {
        // Read a file
        string content = readEntireFile("input.txt");
        
        // Process the content
        content += "\nAdditional text added programmatically.";
        
        // Write to a new file
        writeStringToFile("output_modified.txt", content);
        
        cout << "File processing completed successfully!" << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

### Using String Streams for File Processing

String streams are particularly useful when you need to parse or format data in memory before file operations:

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Parse a line from a file into structured data
struct Record {
    int id;
    string name;
    double value;
};

Record parseLine(const string& line) {
    Record rec;
    stringstream ss(line);
    
    ss >> rec.id;
    ss >> rec.name;
    ss >> rec.value;
    
    if (ss.fail()) {
        throw runtime_error("Failed to parse line: " + line);
    }
    
    return rec;
}

// Create formatted output for a file
string formatRecord(const Record& rec) {
    stringstream ss;
    ss << rec.id << " " 
       << rec.name << " " 
       << fixed << setprecision(2) << rec.value;
    return ss.str();
}

int main() {
    // Read file into records
    vector<Record> records;
    ifstream inFile("records.txt");
    
    if (!inFile) {
        cerr << "Error opening input file" << endl;
        return 1;
    }
    
    string line;
    while (getline(inFile, line)) {
        try {
            records.push_back(parseLine(line));
        }
        catch (const exception& e) {
            cerr << "Warning: " << e.what() << endl;
            // Continue processing next line
        }
    }
    
    inFile.close();
    
    // Process records
    for (auto& rec : records) {
        rec.value *= 1.1;  // Apply 10% increase
    }
    
    // Write modified records to output file
    ofstream outFile("records_updated.txt");
    
    if (!outFile) {
        cerr << "Error opening output file" << endl;
        return 1;
    }
    
    for (const auto& rec : records) {
        outFile << formatRecord(rec) << endl;
    }
    
    outFile.close();
    
    cout << "Successfully processed " << records.size() << " records" << endl;
    return 0;
}
```

### Platform Independence in File Handling

Different operating systems use different conventions for line endings:
- Windows: `\r\n` (carriage return + line feed)
- Unix/Linux/macOS: `\n` (line feed)

Modern C++ file streams handle these differences automatically when opened in text mode, but there are still some considerations:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Platform-independent file path handling
string getFilePath(const string& directory, const string& filename) {
#ifdef _WIN32
    return directory + "\\" + filename;
#else
    return directory + "/" + filename;
#endif
}

int main() {
    string path = getFilePath("data", "records.txt");
    cout << "Platform-specific path: " << path << endl;
    
    // Open file in text mode (default)
    ifstream textFile(path);
    
    // Open file in binary mode (no line ending translation)
    ifstream binaryFile(path, ios::binary);
    
    // Check if file exists using portable code
    ifstream checkFile(path);
    if (!checkFile) {
        cout << "File does not exist or cannot be opened" << endl;
    }
    else {
        cout << "File exists and can be opened" << endl;
    }
    
    return 0;
}
```

In conclusion, C++ provides powerful file handling capabilities through its stream classes. By understanding the stream hierarchy, file operations, error handling, and best practices, you can effectively work with files in your C++ applications. Remember to always check for errors, close files when you're done with them, and use the appropriate stream types and modes for your specific requirements.
