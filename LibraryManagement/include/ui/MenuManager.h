#ifndef MENUMANAGER_H
#define MENUMANAGER_H

class MenuManager {
public:
    MenuManager();
    ~MenuManager();

    void showMainMenu() const;
    void showBookMenu() const;
    void showReaderMenu() const;
    void showBorrowMenu() const;
};

#endif
