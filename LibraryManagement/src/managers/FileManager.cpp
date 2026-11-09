#include "FileManager.h"

#include <fstream>
#include <sstream>
using namespace std;

FileManager::FileManager() = default;

FileManager::~FileManager() = default;

string FileManager::trim(const string& value) const {
    const string whitespace = " \t\n\r";
    size_t start = value.find_first_not_of(whitespace);
    if (start == string::npos) return "";
    size_t end = value.find_last_not_of(whitespace);
    return value.substr(start, end - start + 1);
}

bool FileManager::saveBooks(const string& filePath, const vector<string>& records) {
    ofstream out(filePath);
    if (!out.is_open()) return false;
    for (const auto& record : records) {
        out << record << '\n';
    }
    return true;
}

bool FileManager::loadBooks(const string& filePath, vector<string>& records) {
    ifstream in(filePath);
    if (!in.is_open()) return false;
    string line;
    while (getline(in, line)) {
        if (!line.empty()) {
            records.push_back(trim(line));
        }
    }
    return true;
}

bool FileManager::saveReaders(const string& filePath, const vector<string>& records) {
    ofstream out(filePath);
    if (!out.is_open()) return false;
    for (const auto& record : records) {
        out << record << '\n';
    }
    return true;
}

bool FileManager::loadReaders(const string& filePath, vector<string>& records) {
    ifstream in(filePath);
    if (!in.is_open()) return false;
    string line;
    while (getline(in, line)) {
        if (!line.empty()) {
            records.push_back(trim(line));
        }
    }
    return true;
}

bool FileManager::saveBorrows(const string& filePath, const vector<string>& records) {
    ofstream out(filePath);
    if (!out.is_open()) return false;
    for (const auto& record : records) {
        out << record << '\n';
    }
    return true;
}

bool FileManager::loadBorrows(const string& filePath, vector<string>& records) {
    ifstream in(filePath);
    if (!in.is_open()) return false;
    string line;
    while (getline(in, line)) {
        if (!line.empty()) {
            records.push_back(trim(line));
        }
    }
    return true;
}
