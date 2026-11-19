#include "LibraryManager.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <chrono>

using namespace std;

LibraryManager::LibraryManager() {}

LibraryManager::~LibraryManager() {
    clear();
}

void LibraryManager::clear() {
    avlTree.clear();
    bstTree.clear();
    readerTable.clear();
}

size_t LibraryManager::getTotalBooks() const {
    return avlTree.getSize();
}

bool LibraryManager::addBook(const Book& book, string& errorMsg) {
    // 1. Kiểm tra tính hợp lệ của dữ liệu đầu vào
    if (!book.isValid(&errorMsg)) {
        return false;
    }

    // 2. Kiểm tra ISBN trùng lặp trên cây AVL
    if (avlTree.search(book.ISBN) != nullptr) {
        errorMsg = "Ma ISBN [" + book.ISBN + "] da ton tai trong he thong. Khong the them trung!";
        return false;
    }

    // 3. Thêm vào cây AVL (cấu trúc quản lý chính)
    if (!avlTree.insert(book)) {
        errorMsg = "Loi he thong: Khong the them vao cay AVL.";
        return false;
    }

    // 4. Thêm vào cây BST (cấu trúc chỉ mục sắp xếp theo tên)
    if (!bstTree.insert(book)) {
        // Rollback hoàn tác cây AVL nếu BST thất bại để tránh mâu thuẫn dữ liệu
        avlTree.remove(book.ISBN);
        errorMsg = "Loi he thong: Khong the dong bo vao cay BST. Da hoan tac thao tac them.";
        return false;
    }

    return true;
}

bool LibraryManager::updateBook(const string& isbn, const Book& newInfo, string& errorMsg) {
    // 1. Kiểm tra dữ liệu mới hợp lệ
    if (!newInfo.isValid(&errorMsg)) {
        return false;
    }

    // 2. Không cho phép thay đổi khóa chính ISBN
    if (newInfo.ISBN != isbn) {
        errorMsg = "Khong duoc thay doi ma ISBN dinh danh cua sach.";
        return false;
    }

    // 3. Tìm sách hiện tại trong cây AVL
    Book* existing = avlTree.search(isbn);
    if (!existing) {
        errorMsg = "Khong tim thay sach co ma ISBN [" + isbn + "] de cap nhat.";
        return false;
    }

    string oldTitle = existing->title;
    Book oldBook = *existing;

    // 4. Kiểm tra xem tên sách có thay đổi không
    if (oldTitle != newInfo.title) {
        // Tên sách thay đổi: vị trí trong BST phải thay đổi
        // Xóa nút cũ trong BST theo (oldTitle, isbn)
        if (!bstTree.remove(oldTitle, isbn)) {
            errorMsg = "Loi dong bo: Khong the xoa chi muc cu trong BST.";
            return false;
        }

        // Cập nhật thông tin trong cây AVL
        if (!avlTree.update(isbn, newInfo)) {
            // Hoàn tác: chèn lại vào BST
            bstTree.insert(oldBook);
            errorMsg = "Loi cap nhat cay AVL. Da hoan tac.";
            return false;
        }

        // Thêm nút mới vào cây BST với tên mới
        if (!bstTree.insert(newInfo)) {
            // Hoàn tác cả AVL và BST
            avlTree.update(isbn, oldBook);
            bstTree.insert(oldBook);
            errorMsg = "Loi dong bo BST voi ten moi. Da hoan tac toan bo.";
            return false;
        }
    } else {
        // Tên sách không đổi: chỉ cần cập nhật các trường thuộc tính
        if (!avlTree.update(isbn, newInfo)) {
            errorMsg = "Loi cap nhat tren cay AVL.";
            return false;
        }
        if (!bstTree.update(oldTitle, isbn, newInfo)) {
            // Hoàn tác lại AVL
            avlTree.update(isbn, oldBook);
            errorMsg = "Loi cap nhat thuoc tinh tren cay BST. Da hoan tac.";
            return false;
        }
    }

    return true;
}

bool LibraryManager::removeBook(const string& isbn, string& errorMsg) {
    if (isbn.empty()) {
        errorMsg = "Ma ISBN khong duoc de trong.";
        return false;
    }

    // 1. Tìm sách trong AVL để lấy tên sách tương ứng
    Book* found = avlTree.search(isbn);
    if (!found) {
        errorMsg = "Khong tim thay sach co ma ISBN [" + isbn + "] de xoa.";
        return false;
    }

    string title = found->title;
    Book backupBook = *found;

    // 2. Xóa khỏi cây AVL
    if (!avlTree.remove(isbn)) {
        errorMsg = "Loi khi xoa sach khoi cay AVL.";
        return false;
    }

    // 3. Xóa khỏi cây BST
    if (!bstTree.remove(title, isbn)) {
        // Hoàn tác lại trên cây AVL để bảo đảm tính toàn vẹn
        avlTree.insert(backupBook);
        errorMsg = "Loi khi xoa sach khoi cay BST. Da hoan tac thao tac xoa tren AVL.";
        return false;
    }

    return true;
}

Book* LibraryManager::searchByISBN(const string& isbn) {
    return avlTree.search(isbn);
}

const Book* LibraryManager::searchByISBN(const string& isbn) const {
    return avlTree.search(isbn);
}

vector<Book> LibraryManager::searchByTitle(const string& title) const {
    return bstTree.searchByTitle(title);
}

void LibraryManager::displayBooksByISBN() const {
    avlTree.display();
}

void LibraryManager::displayBooksByTitle() const {
    bstTree.display();
}

bool LibraryManager::checkAVLBalance(int& height, bool& balanced) const {
    height = avlTree.getHeight();
    balanced = avlTree.isBalanced();
    return balanced;
}

bool LibraryManager::addReader(const Reader& reader) {
    return readerTable.insert(reader);
}

bool LibraryManager::updateReader(const Reader& reader) {
    return readerTable.update(reader);
}

bool LibraryManager::removeReader(const string& cmnd) {
    return readerTable.remove(cmnd);
}

const Reader* LibraryManager::searchReader(const string& cmnd) const {
    return readerTable.find(cmnd);
}

void LibraryManager::compareReaderSearch(const string& cmnd) const {
    const vector<Reader> readers = readerTable.toVector();
    size_t sequentialSteps = 0;
    const Reader* sequentialResult = nullptr;
    chrono::steady_clock::time_point sequentialStart = chrono::steady_clock::now();
    for (size_t i = 0; i < readers.size(); ++i) {
        ++sequentialSteps;
        if (readers[i].CMND == cmnd) {
            sequentialResult = &readers[i];
            break;
        }
    }
    chrono::steady_clock::time_point sequentialEnd = chrono::steady_clock::now();
    chrono::steady_clock::time_point hashStart = chrono::steady_clock::now();
    const Reader* hashResult = readerTable.find(cmnd);
    chrono::steady_clock::time_point hashEnd = chrono::steady_clock::now();
    cout << "Hash table (separate chaining): " << (hashResult ? "tim thay" : "khong tim thay")
         << ", bucket " << readerTable.bucketIndex(cmnd) << ", thoi gian "
         << chrono::duration_cast<chrono::nanoseconds>(hashEnd - hashStart).count() << " ns\n";
    cout << "Tim tuan tu: " << (sequentialResult ? "tim thay" : "khong tim thay")
         << ", so buoc " << sequentialSteps << ", thoi gian "
         << chrono::duration_cast<chrono::nanoseconds>(sequentialEnd - sequentialStart).count() << " ns\n";
}

// ================= GIAO DIỆN CONSOLE MENU =================

void LibraryManager::showMenu() const {
    cout << "\n========== QUAN LY SACH ==========\n";
    cout << "1. Them sach\n";
    cout << "2. Cap nhat thong tin sach\n";
    cout << "3. Xoa sach theo ISBN\n";
    cout << "4. Tim kiem sach theo ISBN\n";
    cout << "5. Hien thi sach theo ISBN (AVL)\n";
    cout << "6. Hien thi sach theo ten (BST)\n";
    cout << "7. Kiem tra tinh can bang AVL\n";
    cout << "8. Quan ly doc gia (Hash Table)\n";
    cout << "0. Thoat\n";
    cout << "==================================\n";
    cout << "Nhap lua chon: ";
}

string LibraryManager::inputString(const string& prompt, bool allowEmpty) {
    string result;
    while (true) {
        cout << prompt;
        getline(cin, result);

        size_t start = result.find_first_not_of(" \t\r\n");
        size_t end = result.find_last_not_of(" \t\r\n");
        if (start == string::npos) {
            result = "";
        } else {
            result = result.substr(start, end - start + 1);
        }

        if (allowEmpty || !result.empty()) {
            return result;
        }
        cout << "[!] Du lieu khong duoc de trong, vui long nhap lai.\n";
    }
}

int LibraryManager::inputInt(const string& prompt, int minVal, int maxVal) {
    int value;
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) {
            cin.clear();
            continue;
        }

        stringstream ss(line);
        if ((ss >> value) && (ss >> ws).eof()) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            cout << "[!] Gia tri phai nam trong khoang [" << minVal << " .. " << maxVal << "]. Vui long nhap lai.\n";
        } else {
            cout << "[!] Dinh dang so khong hop le, vui long nhap lai.\n";
        }
    }
}

void LibraryManager::handleAddBook() {
    cout << "\n--- THEM SACH MOI ---\n";
    string isbn = inputString("Nhap ISBN: ");

    if (searchByISBN(isbn)) {
        cout << "[!] Loi: Ma ISBN [" << isbn << "] da ton tai trong he thong!\n";
        return;
    }

    string title = inputString("Nhap ten sach: ");
    string author = inputString("Nhap tac gia: ");
    string category = inputString("Nhap the loai: ");
    int year = inputInt("Nhap nam xuat ban (1000 - 2027): ", 1000, 2027);
    int qty = inputInt("Nhap so luong (>= 0): ", 0, 1000000);

    Book newBook(isbn, title, author, category, year, qty);
    string errorMsg;
    if (addBook(newBook, errorMsg)) {
        cout << "[+] Them sach thanh cong!\n";
    } else {
        cout << "[!] Them sach that bai: " << errorMsg << "\n";
    }
}

void LibraryManager::handleUpdateBook() {
    cout << "\n--- CAP NHAT THONG TIN SACH ---\n";
    string isbn = inputString("Nhap ma ISBN cua sach can cap nhat: ");
    Book* existing = searchByISBN(isbn);
    if (!existing) {
        cout << "[!] Khong tim thay sach voi ISBN: " << isbn << "\n";
        return;
    }

    cout << "\nThong tin hien tai cua sach:\n";
    existing->printDetails();

    cout << "\nNhap thong tin moi (Nhan Enter de giu nguyen):\n";
    string newTitle = inputString("Ten sach moi: ", true);
    if (newTitle.empty()) newTitle = existing->title;

    string newAuthor = inputString("Tac gia moi: ", true);
    if (newAuthor.empty()) newAuthor = existing->author;

    string newCategory = inputString("The loai moi: ", true);
    if (newCategory.empty()) newCategory = existing->category;

    cout << "Nam xuat ban hien tai: " << existing->publicationYear << "\n";
    string yearStr = inputString("Nam xuat ban moi (Enter de giu nguyen): ", true);
    int newYear = existing->publicationYear;
    if (!yearStr.empty()) {
        try {
            int y = stoi(yearStr);
            if (y >= 1000 && y <= 2027) newYear = y;
            else cout << "[!] Nam khong hop le, giu nguyen gia tri cu.\n";
        } catch (...) {
            cout << "[!] Dinh dang so khong hop le, giu nguyen gia tri cu.\n";
        }
    }

    cout << "So luong hien tai: " << existing->quantity << "\n";
    string qtyStr = inputString("So luong moi (Enter de giu nguyen): ", true);
    int newQty = existing->quantity;
    if (!qtyStr.empty()) {
        try {
            int q = stoi(qtyStr);
            if (q >= 0) newQty = q;
            else cout << "[!] So luong phai >= 0, giu nguyen gia tri cu.\n";
        } catch (...) {
            cout << "[!] Dinh dang so khong hop le, giu nguyen gia tri cu.\n";
        }
    }

    Book updated(isbn, newTitle, newAuthor, newCategory, newYear, newQty);
    string errorMsg;
    if (updateBook(isbn, updated, errorMsg)) {
        cout << "[+] Cap nhat thong tin sach thanh cong!\n";
    } else {
        cout << "[!] Cap nhat that bai: " << errorMsg << "\n";
    }
}

void LibraryManager::handleRemoveBook() {
    cout << "\n--- XOA SACH THEO ISBN ---\n";
    string isbn = inputString("Nhap ma ISBN can xoa: ");
    Book* found = searchByISBN(isbn);
    if (!found) {
        cout << "[!] Khong tim thay sach voi ISBN: " << isbn << "\n";
        return;
    }

    cout << "Thong tin sach can xoa:\n";
    found->printDetails();
    string confirm = inputString("Ban co chac chan muon xoa sach nay? (y/n): ");
    if (confirm == "y" || confirm == "Y") {
        string errorMsg;
        if (removeBook(isbn, errorMsg)) {
            cout << "[+] Xoa sach thanh cong khoi ca AVL va BST!\n";
        } else {
            cout << "[!] Xoa that bai: " << errorMsg << "\n";
        }
    } else {
        cout << "[-] Da huy thao tac xoa.\n";
    }
}

void LibraryManager::handleSearchByISBN() {
    cout << "\n--- TIM KIEM SACH THEO ISBN ---\n";
    string isbn = inputString("Nhap ma ISBN can tim: ");
    Book* found = searchByISBN(isbn);
    if (found) {
        cout << "[+] Tim thay sach trong cay AVL:\n";
        found->printDetails();
    } else {
        cout << "[!] Khong tim thay sach nao co ma ISBN: " << isbn << "\n";
    }
}

void LibraryManager::handleDisplayByISBN() {
    cout << "\n--- DANH SACH SACH THEO MA ISBN (DUYET AVL IN-ORDER) ---\n";
    displayBooksByISBN();
}

void LibraryManager::handleDisplayByTitle() {
    cout << "\n--- DANH MUC SACH THEO TEN (DUYET BST IN-ORDER) ---\n";
    displayBooksByTitle();
}

void LibraryManager::handleCheckAVLBalance() {
    cout << "\n--- KIEM TRA TINH CAN BANG CAY AVL ---\n";
    int height = 0;
    bool balanced = false;
    checkAVLBalance(height, balanced);

    cout << "Chieu cao cay AVL : " << height << "\n";
    cout << "He so can bang goc: " << avlTree.getBalance() << "\n";
    cout << "So luong nut      : " << avlTree.getSize() << "\n";
    if (balanced) {
        cout << "[OK] Cay AVL dang CAN BANG hoan hao (moi nut co |BF| <= 1).\n";
    } else {
        cout << "[CANH BAO] Cay AVL KHONG can bang!\n";
    }
}

void LibraryManager::handleReaderMenu() {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========== QUAN LY DOC GIA ==========" << endl
             << "1. Them doc gia\n2. Tim doc gia theo CMND\n3. Hien thi danh sach\n"
             << "4. Cap nhat doc gia\n5. Xoa doc gia\n6. So sanh Hash va tim tuan tu\n0. Quay lai\n";
        choice = inputInt("Nhap lua chon: ", 0, 6);
        if (choice == 1) {
            Reader reader;
            reader.CMND = inputString("CMND: ");
            reader.fullName = inputString("Ho ten: ");
            reader.email = inputString("Email (co the de trong): ", true);
            reader.phone = inputString("Dien thoai (co the de trong): ", true);
            reader.cardType = inputString("Loai the (co the de trong): ", true);
            cout << (addReader(reader) ? "[+] Them doc gia thanh cong.\n" : "[!] Ma CMND bi trung hoac thong tin khong hop le.\n");
        } else if (choice == 2) {
            string cmnd = inputString("Nhap CMND can tim: ");
            const Reader* reader = searchReader(cmnd);
            if (reader) cout << reader->CMND << " | " << reader->fullName << " | " << reader->email << " | " << reader->phone << " | " << reader->cardType << "\n";
            else cout << "Khong tim thay doc gia.\n";
        } else if (choice == 3) {
            displayReaders();
        } else if (choice == 4) {
            string cmnd = inputString("CMND doc gia can cap nhat: ");
            const Reader* existing = searchReader(cmnd);
            if (!existing) { cout << "Khong tim thay doc gia.\n"; continue; }
            Reader reader = *existing;
            string value = inputString("Ho ten moi (Enter giu nguyen): ", true); if (!value.empty()) reader.fullName = value;
            value = inputString("Email moi (Enter giu nguyen): ", true); if (!value.empty()) reader.email = value;
            value = inputString("Dien thoai moi (Enter giu nguyen): ", true); if (!value.empty()) reader.phone = value;
            value = inputString("Loai the moi (Enter giu nguyen): ", true); if (!value.empty()) reader.cardType = value;
            cout << (updateReader(reader) ? "[+] Cap nhat thanh cong.\n" : "[!] Cap nhat that bai.\n");
        } else if (choice == 5) {
            string cmnd = inputString("CMND doc gia can xoa: ");
            cout << (removeReader(cmnd) ? "[+] Da xoa doc gia.\n" : "Khong tim thay doc gia.\n");
        } else if (choice == 6) {
            compareReaderSearch(inputString("Nhap CMND can tim/so sanh: "));
        }
    }
}

void LibraryManager::run() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        choice = inputInt("", 0, 8);

        switch (choice) {
            case 1:
                handleAddBook();
                break;
            case 2:
                handleUpdateBook();
                break;
            case 3:
                handleRemoveBook();
                break;
            case 4:
                handleSearchByISBN();
                break;
            case 5:
                handleDisplayByISBN();
                break;
            case 6:
                handleDisplayByTitle();
                break;
            case 7:
                handleCheckAVLBalance();
                break;
            case 8:
                handleReaderMenu();
                break;
            case 0:
                cout << "\nCam on ban da su dung chuong trinh Quan ly Thu vien. Tam biet!\n";
                break;
            default:
                cout << "[!] Lua chon khong hop le. Vui long chon lai!\n";
                break;
        }
    }
}
