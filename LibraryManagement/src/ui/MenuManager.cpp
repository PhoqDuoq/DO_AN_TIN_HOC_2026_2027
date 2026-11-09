#include "MenuManager.h"

#include <iostream>
using namespace std;

MenuManager::MenuManager() = default;

MenuManager::~MenuManager() = default;

void MenuManager::showMainMenu() const {
    cout << "=== Main Menu ===" << endl;
    cout << "1. Book Management" << endl;
    cout << "2. Reader Management" << endl;
    cout << "3. Borrow Management" << endl;
    cout << "0. Exit" << endl;
}

void MenuManager::showBookMenu() const {
    cout << "=== Book Menu ===" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Search Book" << endl;
    cout << "3. Display Books" << endl;
}

void MenuManager::showReaderMenu() const {
    cout << "=== Reader Menu ===" << endl;
    cout << "1. Add Reader" << endl;
    cout << "2. Search Reader" << endl;
    cout << "3. Display Readers" << endl;
}

void MenuManager::showBorrowMenu() const {
    cout << "=== Borrow Menu ===" << endl;
    cout << "1. Borrow Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. Display Borrow Records" << endl;
}
