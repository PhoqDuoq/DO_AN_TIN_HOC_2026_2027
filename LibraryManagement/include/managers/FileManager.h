#ifndef FILEMANAGER_H
#define FILEMANAGER_H
using namespace std;
#include <string>
#include <vector>



class FileManager {
public:
    FileManager();
    ~FileManager();

    bool saveBooks(const string& filePath, const vector<string>& records);
    bool loadBooks(const string& filePath, vector<string>& records);
    bool saveReaders(const string& filePath, const vector<string>& records);
    bool loadReaders(const string& filePath, vector<string>& records);
    bool saveBorrows(const string& filePath, const vector<string>& records);
    bool loadBorrows(const string& filePath, vector<string>& records);

private:
    string trim(const string& value) const;
};

#endif
