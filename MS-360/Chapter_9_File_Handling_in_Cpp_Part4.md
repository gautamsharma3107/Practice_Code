# Chapter 9: File Handling in C++ (Part 4)

## 9.5 Error Handling in File Operations

File operations are inherently error-prone because they interact with external resources outside your program's control. Proper error handling is crucial for creating robust applications that can gracefully handle problems like missing files, permission issues, disk failures, and corrupted data.

### 9.5.1 Understanding Stream State Flags

C++ file streams maintain internal state flags to track error conditions:

1. **good()**: Returns `true` if the stream has no errors (all good)
2. **eof()**: Returns `true` if the end-of-file has been reached
3. **fail()**: Returns `true` if a logical error occurred (format error, etc.)
4. **bad()**: Returns `true` if a critical I/O error occurred (disk error, etc.)

Additionally:
- The stream object itself can be evaluated in a boolean context, equivalent to `!fail()`
- The `!` operator on a stream returns `fail()`

These states form a hierarchy of conditions:

```
good() → No errors (all flags clear)
  ↓
eof() → End of file reached (only eof bit set)
  ↓
fail() → Operation failed (failbit set, possibly eofbit too)
  ↓
bad() → Fatal error (badbit set, likely with failbit too)
```

```cpp
#include <iostream>
#include <fstream>
using namespace std;

void displayStreamState(const fstream& file) {
    cout << "Stream state flags:" << endl;
    cout << "- good(): " << (file.good() ? "true" : "false") << endl;
    cout << "- eof(): " << (file.eof() ? "true" : "false") << endl;
    cout << "- fail(): " << (file.fail() ? "true" : "false") << endl;
    cout << "- bad(): " << (file.bad() ? "true" : "false") << endl;
    cout << "- Boolean conversion: " << (file ? "true" : "false") << endl;
}

int main() {
    // Example 1: Successfully open a file
    fstream file("example.txt", ios::out);
    cout << "After opening file for writing:" << endl;
    displayStreamState(file);
    file.close();
    
    // Example 2: Try to open a protected file for writing
    fstream restrictedFile("/etc/passwd", ios::out);
    cout << "\nAfter trying to open a restricted file:" << endl;
    displayStreamState(restrictedFile);
    
    // Example 3: Reading past end of file
    file.open("example.txt", ios::in);
    file.seekg(0, ios::end);  // Go to end of file
    char c;
    file.get(c);  // Try to read past EOF
    cout << "\nAfter reading past EOF:" << endl;
    displayStreamState(file);
    
    // Example 4: Clear error flags
    file.clear();  // Reset all error flags
    cout << "\nAfter clearing error flags:" << endl;
    displayStreamState(file);
    
    file.close();
    return 0;
}
```

### 9.5.2 Basic Error Checking Techniques

#### Simple Boolean Check

The most common method of checking for file errors:

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Method 1: Check after opening
    ifstream file("nonexistent.txt");
    
    if (!file) {  // Equivalent to if (file.fail())
        cerr << "Error opening file!" << endl;
        return 1;
    }
    
    // Method 2: Check if file is open
    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return 1;
    }
    
    // Method 3: Check after read/write operations
    int value;
    file >> value;
    
    if (!file) {
        cerr << "Error reading from file!" << endl;
        return 1;
    }
    
    return 0;
}
```

#### Checking Specific Error Conditions

Different errors require different responses, so check for specific conditions:

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Open file
    ifstream file("data.txt");
    
    // Check if file opened
    if (!file) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }
    
    // Read data in a loop
    int value;
    while (file >> value) {
        // Process each value
        cout << "Read: " << value << endl;
    }
    
    // Check why the loop ended
    if (file.eof()) {
        cout << "Reached end of file normally." << endl;
    } 
    else if (file.fail()) {
        cerr << "Format error in file. Non-numeric data encountered." << endl;
        
        // We can clear the error and try to read what caused it
        file.clear();  // Reset error flags
        string badToken;
        file >> badToken;  // Read the offending data
        cerr << "Bad token: " << badToken << endl;
    }
    else if (file.bad()) {
        cerr << "Critical I/O error occurred!" << endl;
        // For bad() errors, usually best to abort the operation
        return 1;
    }
    
    file.close();
    return 0;
}
```

#### Using errno for Detailed Error Information

C++ file operations set the global `errno` variable, which provides additional details:

```cpp
#include <iostream>
#include <fstream>
#include <cerrno>   // For errno
#include <cstring>  // For strerror
using namespace std;

int main() {
    ifstream file("/root/protected.txt");  // Try to access a protected file
    
    if (!file) {
        cerr << "File error: " << strerror(errno) << " (errno=" << errno << ")" << endl;
        
        // Common errno values for file operations:
        // ENOENT (2): No such file or directory
        // EACCES (13): Permission denied
        // EMFILE (24): Too many open files
        
        switch (errno) {
            case ENOENT:
                cerr << "The file does not exist." << endl;
                break;
            case EACCES:
                cerr << "You don't have permission to access this file." << endl;
                break;
            default:
                cerr << "An unknown error occurred." << endl;
        }
        
        return errno;
    }
    
    // Rest of the code...
    file.close();
    return 0;
}
```

### 9.5.3 Exception-Based Error Handling

File streams can be configured to throw exceptions when errors occur:

```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

void readFileWithExceptions(const string& filename) {
    ifstream file(filename);
    
    // Configure the file stream to throw exceptions on error
    file.exceptions(ifstream::failbit | ifstream::badbit);
    
    try {
        // Test if file is open
        if (!file.is_open()) {
            throw runtime_error("Failed to open file: " + filename);
        }
        
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        
        // The following code won't execute if EOF is reached
        // because we didn't set the eofbit in exceptions()
    }
    catch (const ios_base::failure& e) {
        cerr << "I/O error: " << e.what() << endl;
        throw;  // Rethrow exception after logging
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        throw;  // Rethrow
    }
}

int main() {
    try {
        // Create a test file first
        {
            ofstream testFile("test.txt");
            testFile << "Line 1: This is a test file.\n";
            testFile << "Line 2: Testing exception handling.\n";
        }
        
        // Read the file with exception handling
        readFileWithExceptions("test.txt");
        
        // Try a non-existent file
        readFileWithExceptions("nonexistent.txt");
    }
    catch (const exception& e) {
        cerr << "Exception caught in main: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

### 9.5.4 RAII for File Handling

Resource Acquisition Is Initialization (RAII) is a powerful C++ technique that ensures resources (like files) are properly released:

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

// RAII wrapper for file handling
class FileGuard {
private:
    fstream file;
    string filename;
    bool is_open = false;
    
public:
    // Constructor opens the file
    FileGuard(const string& filename, ios::openmode mode) 
        : filename(filename) {
        file.open(filename, mode);
        if (!file) {
            throw runtime_error("Could not open file: " + filename);
        }
        is_open = true;
    }
    
    // No copying allowed
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;
    
    // Get access to the underlying stream
    fstream& getStream() {
        return file;
    }
    
    // Read a line from the file
    bool readLine(string& line) {
        return static_cast<bool>(getline(file, line));
    }
    
    // Write to the file
    template<typename T>
    FileGuard& operator<<(const T& data) {
        file << data;
        if (!file) {
            throw runtime_error("Error writing to file: " + filename);
        }
        return *this;
    }
    
    // Destructor automatically closes file
    ~FileGuard() {
        if (is_open) {
            try {
                file.close();
            } catch (...) {
                // Destructors should never throw
                cerr << "Error while closing file: " << filename << endl;
            }
        }
    }
};

int main() {
    try {
        // Using RAII for file writing
        {
            FileGuard outputFile("raii_example.txt", ios::out);
            outputFile << "Line 1: RAII test\n";
            outputFile << "Line 2: File will be closed automatically\n";
            outputFile << "Line 3: Even if exceptions occur\n";
            
            // File is closed automatically when outputFile goes out of scope
        }
        
        // Using RAII for file reading
        {
            FileGuard inputFile("raii_example.txt", ios::in);
            string line;
            
            cout << "File contents:" << endl;
            while (inputFile.readLine(line)) {
                cout << line << endl;
            }
            
            // File is closed automatically
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

### 9.5.5 Common File Operation Errors

Let's explore common file errors and how to handle them:

#### 1. File Not Found

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool doesFileExist(const string& filename) {
    ifstream file(filename);
    return file.good();
}

int main() {
    string filename = "nonexistent.txt";
    
    if (!doesFileExist(filename)) {
        cerr << "Error: File '" << filename << "' does not exist." << endl;
        
        // Potential recovery options:
        cout << "Options:" << endl;
        cout << "1. Create a new file" << endl;
        cout << "2. Specify a different filename" << endl;
        
        int choice;
        cout << "Enter choice (1-2): ";
        cin >> choice;
        
        if (choice == 1) {
            ofstream newFile(filename);
            if (newFile) {
                cout << "Created new empty file: " << filename << endl;
            } else {
                cerr << "Failed to create file!" << endl;
            }
        } else if (choice == 2) {
            cout << "Enter new filename: ";
            cin >> filename;
            
            if (doesFileExist(filename)) {
                cout << "File found: " << filename << endl;
            } else {
                cerr << "New file also doesn't exist!" << endl;
            }
        }
    }
    
    return 0;
}
```

#### 2. Permission Denied

```cpp
#include <iostream>
#include <fstream>
#include <cerrno>
#include <cstring>
using namespace std;

int main() {
    // Attempt to write to a file in a restricted location
    ofstream file("/etc/my_config.txt");
    
    if (!file) {
        cerr << "Error opening file: " << strerror(errno) << endl;
        
        if (errno == EACCES) {
            cerr << "Permission denied. Try running with elevated privileges." << endl;
            
            // Alternative: Try to write to a user-accessible location
            string userPath = "user_config.txt";
            cout << "Trying alternative location: " << userPath << endl;
            
            ofstream altFile(userPath);
            if (altFile) {
                altFile << "Config data that would have gone to system file" << endl;
                cout << "Successfully wrote to alternative location." << endl;
            }
        }
    }
    
    return 0;
}
```

#### 3. Disk Full Error

```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool writeWithDiskCheck(const string& filename, const string& data) {
    ofstream file(filename);
    if (!file) {
        return false;
    }
    
    file << data;
    
    if (!file) {
        if (errno == ENOSPC) {  // No space left on device
            cerr << "Disk is full!" << endl;
        } else {
            cerr << "Write error: " << strerror(errno) << endl;
        }
        return false;
    }
    
    file.close();
    return true;
}

int main() {
    // Example of writing a large amount of data, checking for disk full
    const size_t megabytes = 100;  // Try to write 100MB
    string largeData(megabytes * 1024 * 1024, 'X');  // String of X's
    
    if (!writeWithDiskCheck("large_file.dat", largeData)) {
        cerr << "Failed to write large file." << endl;
        
        // Recovery options:
        // 1. Try smaller file
        string smallerData = largeData.substr(0, largeData.size() / 10);  // 10% of original
        cout << "Trying with smaller file size..." << endl;
        
        if (writeWithDiskCheck("smaller_file.dat", smallerData)) {
            cout << "Successfully wrote smaller file." << endl;
        }
        
        // 2. Suggest cleanup
        cout << "Consider freeing up disk space and trying again." << endl;
    } else {
        cout << "Successfully wrote large file." << endl;
    }
    
    return 0;
}
```

#### 4. Format Errors

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Person {
    string name;
    int age;
    double height;
};

vector<Person> readPeopleData(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Failed to open file: " + filename);
    }
    
    vector<Person> people;
    string line;
    int lineNumber = 0;
    
    while (getline(file, line)) {
        lineNumber++;
        
        if (line.empty() || line[0] == '#') {
            continue;  // Skip empty lines and comments
        }
        
        // Try to parse the line
        Person person;
        istringstream iss(line);
        
        if (iss >> person.name >> person.age >> person.height) {
            // Successful parse
            people.push_back(person);
        } else {
            // Format error
            cerr << "Warning: Format error on line " << lineNumber 
                 << ": " << line << endl;
            
            // Try to recover with partial information
            person.name = "Unknown";
            person.age = 0;
            person.height = 0.0;
            
            istringstream retry(line);
            string token;
            
            if (retry >> token) {
                person.name = token;
                
                if (retry >> token) {
                    try {
                        person.age = stoi(token);
                        
                        if (retry >> token) {
                            try {
                                person.height = stod(token);
                            } catch (...) {
                                cerr << "  Invalid height format" << endl;
                            }
                        }
                    } catch (...) {
                        cerr << "  Invalid age format" << endl;
                    }
                }
            }
            
            cerr << "  Recovered partial data: " << person.name 
                 << ", age=" << person.age 
                 << ", height=" << person.height << endl;
            
            people.push_back(person);
        }
    }
    
    return people;
}

int main() {
    // Create a test file with some bad data
    {
        ofstream testFile("people.txt");
        testFile << "John 25 1.75\n";
        testFile << "Mary 30 1.65\n";
        testFile << "Bob thirty 1.80\n";  // Bad format for age
        testFile << "Alice 28 tall\n";     // Bad format for height
        testFile << "Mike\n";              // Missing data
        testFile << "Susan 35 1.70\n";
    }
    
    try {
        vector<Person> people = readPeopleData("people.txt");
        
        cout << "\nSuccessfully read " << people.size() << " records:" << endl;
        for (const auto& person : people) {
            cout << person.name << ", age=" << person.age 
                 << ", height=" << person.height << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    
    return 0;
}
```

#### 5. Handling Partial Reads

```cpp
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool readExactly(ifstream& file, char* buffer, size_t size) {
    file.read(buffer, size);
    size_t bytesRead = file.gcount();
    
    if (bytesRead < size) {
        cerr << "Partial read: expected " << size << " bytes, got " 
             << bytesRead << " bytes" << endl;
        return false;
    }
    
    return true;
}

int main() {
    // Create a test file
    {
        ofstream outFile("binary.dat", ios::binary);
        int values[] = {1, 2, 3, 4, 5};
        outFile.write(reinterpret_cast<char*>(values), sizeof(values));
    }
    
    // Try to read more data than available
    ifstream inFile("binary.dat", ios::binary);
    if (!inFile) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }
    
    // Get file size
    inFile.seekg(0, ios::end);
    streamsize fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);
    
    cout << "File size: " << fileSize << " bytes" << endl;
    
    // Try to read too much
    vector<char> buffer(fileSize + 10);  // Try to read 10 extra bytes
    
    inFile.read(buffer.data(), buffer.size());
    streamsize bytesRead = inFile.gcount();
    
    cout << "Requested " << buffer.size() << " bytes, actually read " 
         << bytesRead << " bytes" << endl;
    
    if (inFile.eof()) {
        cout << "End of file reached during read" << endl;
    }
    
    // Proper handling: read only what's available
    inFile.clear();  // Clear EOF flag
    inFile.seekg(0, ios::beg);  // Back to beginning
    
    vector<int> data(fileSize / sizeof(int));  // Correctly sized buffer
    
    if (readExactly(inFile, reinterpret_cast<char*>(data.data()), fileSize)) {
        cout << "Read complete data successfully:" << endl;
        for (int value : data) {
            cout << value << " ";
        }
        cout << endl;
    }
    
    inFile.close();
    return 0;
}
```

### 9.5.6 Recovery Strategies

#### 1. Retry Operations

For transient errors, a retry mechanism can help:

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

bool writeWithRetry(const string& filename, const string& data, int maxAttempts = 3) {
    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        cout << "Attempt " << attempt << " to write file..." << endl;
        
        ofstream file(filename);
        if (!file) {
            cerr << "  Failed to open file." << endl;
        } else {
            file << data;
            file.flush();  // Ensure data is written to OS buffer
            
            if (file) {
                file.close();
                cout << "  Write successful!" << endl;
                return true;
            }
            
            cerr << "  Failed to write data." << endl;
        }
        
        if (attempt < maxAttempts) {
            int delaySeconds = attempt;  // Progressive backoff
            cerr << "  Will retry in " << delaySeconds << " seconds..." << endl;
            this_thread::sleep_for(chrono::seconds(delaySeconds));
        }
    }
    
    cerr << "Failed after " << maxAttempts << " attempts." << endl;
    return false;
}

int main() {
    string data = "This is important data that must be saved correctly.";
    
    bool success = writeWithRetry("output.txt", data);
    
    if (success) {
        cout << "Data saved successfully." << endl;
    } else {
        cerr << "Failed to save data after multiple attempts." << endl;
    }
    
    return success ? 0 : 1;
}
```

#### 2. Using Backup Files

```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool safeUpdateFile(const string& filename, const string& newContent) {
    // 1. Create backup of original file if it exists
    string backupFilename = filename + ".bak";
    bool originalExists = false;
    
    {
        ifstream checkFile(filename);
        originalExists = checkFile.good();
    }
    
    if (originalExists) {
        ifstream original(filename, ios::binary);
        ofstream backup(backupFilename, ios::binary);
        
        if (!backup) {
            cerr << "Error: Failed to create backup file." << endl;
            return false;
        }
        
        // Copy content
        backup << original.rdbuf();
        
        if (!backup) {
            cerr << "Error: Failed to write to backup file." << endl;
            return false;
        }
        
        backup.close();
        original.close();
        
        cout << "Created backup: " << backupFilename << endl;
    }
    
    // 2. Write new content
    ofstream output(filename);
    if (!output) {
        cerr << "Error: Failed to open output file." << endl;
        return false;
    }
    
    output << newContent;
    
    if (!output) {
        cerr << "Error: Failed to write new content." << endl;
        
        // 3. Restore from backup if something went wrong
        if (originalExists) {
            cout << "Attempting to restore from backup..." << endl;
            
            // Close the failed output file
            output.close();
            
            // Copy backup back to original
            ifstream backupFile(backupFilename, ios::binary);
            ofstream restoreFile(filename, ios::binary);
            
            if (backupFile && restoreFile) {
                restoreFile << backupFile.rdbuf();
                
                if (restoreFile) {
                    cout << "Successfully restored from backup." << endl;
                } else {
                    cerr << "Error: Failed to restore from backup." << endl;
                }
            } else {
                cerr << "Error: Failed to open files for restore operation." << endl;
            }
        }
        
        return false;
    }
    
    output.close();
    return true;
}

int main() {
    // Create an initial file
    {
        ofstream initial("config.txt");
        initial << "# Configuration File\n";
        initial << "setting1=value1\n";
        initial << "setting2=value2\n";
    }
    
    // Update it safely
    string newContent = "# Updated Configuration\n"
                       "setting1=newvalue1\n"
                       "setting2=newvalue2\n"
                       "setting3=value3\n";
    
    if (safeUpdateFile("config.txt", newContent)) {
        cout << "File updated successfully!" << endl;
    } else {
        cerr << "Failed to update file." << endl;
    }
    
    // Read and display the current content
    cout << "\nCurrent file content:" << endl;
    cout << "--------------------" << endl;
    
    ifstream readFile("config.txt");
    if (readFile) {
        string line;
        while (getline(readFile, line)) {
            cout << line << endl;
        }
    }
    
    return 0;
}
```

#### 3. Transaction-Like Updates

```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class FileTransaction {
private:
    string filename;
    string tempFilename;
    ofstream tempFile;
    bool committed = false;
    
public:
    FileTransaction(const string& fname) 
        : filename(fname), tempFilename(fname + ".tmp") {
        
        tempFile.open(tempFilename);
        if (!tempFile) {
            throw runtime_error("Could not create temporary file: " + tempFilename);
        }
    }
    
    // Write to the transaction
    template<typename T>
    FileTransaction& operator<<(const T& data) {
        tempFile << data;
        if (!tempFile) {
            throw runtime_error("Error writing to transaction");
        }
        return *this;
    }
    
    // Commit the transaction - replace original file with temp file
    bool commit() {
        if (committed) {
            return false;  // Already committed
        }
        
        tempFile.close();
        if (tempFile.fail()) {
            cerr << "Error closing temporary file" << endl;
            return false;
        }
        
        // On some systems, rename fails if target exists
        if (remove(filename.c_str()) != 0 && errno != ENOENT) {
            cerr << "Error removing original file: " << strerror(errno) << endl;
            return false;
        }
        
        if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
            cerr << "Error committing transaction: " << strerror(errno) << endl;
            return false;
        }
        
        committed = true;
        return true;
    }
    
    // Roll back the transaction (discard changes)
    void rollback() {
        if (!committed) {
            if (tempFile.is_open()) {
                tempFile.close();
            }
            
            // Remove the temporary file
            remove(tempFilename.c_str());
        }
    }
    
    // Add a timestamp to the file (utility method)
    void addTimestamp() {
        time_t now = time(nullptr);
        char timestamp[64];
        strftime(timestamp, sizeof(timestamp), "# Timestamp: %Y-%m-%d %H:%M:%S", 
                 localtime(&now));
        
        *this << timestamp << endl;
    }
    
    // Destructor automatically rolls back if not committed
    ~FileTransaction() {
        if (!committed) {
            rollback();
        }
    }
};

int main() {
    try {
        cout << "Starting file transaction..." << endl;
        
        // Start transaction
        FileTransaction transaction("transaction_test.txt");
        
        // Add content to the transaction
        transaction.addTimestamp();
        transaction << "Line 1: This is a transactional update." << endl;
        transaction << "Line 2: Either all changes are applied, or none." << endl;
        transaction << "Line 3: This helps maintain file consistency." << endl;
        
        // More operations...
        cout << "Transaction in progress..." << endl;
        
        // Simulate user decision
        char commit;
        cout << "Commit transaction? (y/n): ";
        cin >> commit;
        
        if (commit == 'y' || commit == 'Y') {
            // Commit changes
            if (transaction.commit()) {
                cout << "Transaction committed successfully!" << endl;
            } else {
                cerr << "Failed to commit transaction." << endl;
            }
        } else {
            // Explicitly roll back (automatic if not committed)
            transaction.rollback();
            cout << "Transaction rolled back." << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
```

### 9.5.7 Best Practices for Error Handling in File Operations

1. **Always check if file operations succeeded**
   - Don't assume files will open or operations will succeed
   - Check return values and stream states

2. **Use appropriate error reporting for your audience**
   - For end users: Simple, actionable messages
   - For developers: Detailed technical information
   - Consider logging errors to files for later analysis

3. **Use RAII wrappers for file resources**
   - Ensures files are closed even if exceptions occur
   - Prevents resource leaks
   - Makes code more readable and maintainable

4. **Provide recovery mechanisms when possible**
   - Retry operations for transient errors
   - Use alternative locations if primary ones fail
   - Create backups before modifying important files

5. **Be specific about error conditions**
   - Check for specific errors (EOF, permission denied, etc.)
   - Different errors require different responses

6. **Handle format errors gracefully**
   - Provide helpful error messages with line numbers
   - Try to recover partial data when possible
   - Skip bad records rather than aborting entirely

7. **Manage partial reads and writes**
   - Check how many bytes were actually read/written
   - Don't assume operations handled all requested data

8. **Use explicit close operations with error checking**
   - Check if close operations succeeded
   - Flush buffers before closing important files

9. **Consider transaction-like approaches for critical updates**
   - Write to temporary files, then rename
   - Create backups before modifications
   - Use atomic operations when available

10. **Clean up temporary files**
    - Remove temporary files when they're no longer needed
    - Consider using unique names for temporary files
    - Handle cleanup in destructors or finally blocks

By implementing these error handling strategies, you'll create more robust file handling code that can gracefully handle the unpredictable nature of external resources like files.
