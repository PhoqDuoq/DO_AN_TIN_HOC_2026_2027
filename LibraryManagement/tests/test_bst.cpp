#include "BSTree.h"
#include "LibraryManager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct TestResult {
    string testId;
    string testName;
    string input;
    string expected;
    string actual;
    bool passed;
};

void printTestRow(const TestResult& r) {
    cout << "| " << left << setw(6) << r.testId
         << " | " << left << setw(30) << r.testName
         << " | " << left << setw(32) << r.input
         << " | " << left << setw(28) << r.expected
         << " | " << left << setw(28) << r.actual
         << " | " << (r.passed ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
         << " |\n";
}

int main() {
    cout << "\n=========================================================================================================\n";
    cout << "                 KIEM THU CAY BST VA DONG BO AVL-BST (BST & SYNC TEST SUITE)\n";
    cout << "=========================================================================================================\n";
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";
    cout << "| Ma TC  | Ten kiem thu                   | Du lieu dau vao                  | Ket qua mong doi             | Ket qua thuc te              | KQ   |\n";
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";

    vector<TestResult> results;

    // TC12: Hiển thị BST bằng In-order (Thứ tự tăng dần theo tên)
    {
        BSTree bst;
        bst.insert(Book("978-03", "Toan Roi Rac", "Author A", "Math", 2021, 5));
        bst.insert(Book("978-01", "Cau Truc Du Lieu", "Author B", "CS", 2022, 4));
        bst.insert(Book("978-04", "Tri Tue Nhan Tao", "Author C", "AI", 2024, 7));
        bst.insert(Book("978-02", "Giai Thuat", "Author D", "CS", 2023, 6));

        vector<Book> list = bst.toVector();
        bool sorted = true;
        for (size_t i = 1; i < list.size(); ++i) {
            if (list[i - 1].title > list[i].title) {
                sorted = false;
                break;
            }
        }
        bool ok = sorted && (list.size() == 4) && (list[0].title == "Cau Truc Du Lieu") && (list[3].title == "Tri Tue Nhan Tao");
        results.push_back({
            "TC12", "Hien thi BST bang In-order",
            "Chen 4 sach co ten ngau nhien",
            "Danh sach sap xep A-Z theo ten",
            ok ? "Danh sach dung thu tu A-Z" : "Sai thu tu",
            ok
        });
    }

    // TC13: Hai sách trùng tên, khác ISBN
    {
        BSTree bst;
        Book b1("978-01", "Giao Trinh C++", "Nguyen Van A", "Giao trinh", 2020, 10);
        Book b2("978-02", "Giao Trinh C++", "Tran Thi B", "Tai lieu", 2022, 5);

        bool ins1 = bst.insert(b1);
        bool ins2 = bst.insert(b2);
        vector<Book> searchRes = bst.searchByTitle("Giao Trinh C++");

        bool ok = ins1 && ins2 && (bst.getSize() == 2) && (searchRes.size() == 2);
        results.push_back({
            "TC13", "Hai sach trung ten, khac ISBN",
            "Ten: 'Giao Trinh C++', ISBN khac",
            "Ca 2 sach deu duoc luu trong BST",
            ok ? "Luu ca 2 thanh cong, size=2" : "That bai",
            ok
        });
    }

    // TC14: Đổi tên sách (BST cập nhật đúng vị trí)
    {
        LibraryManager manager;
        string err;
        manager.addBook(Book("978-01", "Sach Cu", "Tac gia A", "Khoa hoc", 2021, 5), err);

        Book updatedBook("978-01", "Sach Moi Cap Nhat", "Tac gia A", "Khoa hoc", 2021, 5);
        bool updateOk = manager.updateBook("978-01", updatedBook, err);

        vector<Book> oldSearch = manager.searchByTitle("Sach Cu");
        vector<Book> newSearch = manager.searchByTitle("Sach Moi Cap Nhat");

        bool ok = updateOk && oldSearch.empty() && (newSearch.size() == 1) && (newSearch[0].ISBN == "978-01");
        results.push_back({
            "TC14", "Doi ten sach (Cap nhat BST)",
            "Doi 'Sach Cu' -> 'Sach Moi...'",
            "BST xoa vi tri cu, them vi tri moi",
            ok ? "Chi muc BST cap nhat chinh xac" : "That bai",
            ok
        });
    }

    // TC15: Xóa sách (AVL và BST đồng bộ)
    {
        LibraryManager manager;
        string err;
        manager.addBook(Book("978-10", "Lap Trinh Java", "Author X", "IT", 2020, 3), err);
        manager.addBook(Book("978-20", "Lap Trinh Python", "Author Y", "IT", 2021, 6), err);

        bool remOk = manager.removeBook("978-10", err);

        const Book* inAVL = manager.searchByISBN("978-10");
        vector<Book> inBST = manager.searchByTitle("Lap Trinh Java");
        bool ok = remOk && (inAVL == nullptr) && inBST.empty() && (manager.getTotalBooks() == 1);

        results.push_back({
            "TC15", "Xoa sach (Dong bo AVL & BST)",
            "Xoa sach ISBN 978-10",
            "Loai bo khoi ca AVL va BST",
            ok ? "Ca 2 cay deu dong bo loai bo sach" : "That bai",
            ok
        });
    }

    // TC18: Sửa thông tin sách (Dữ liệu giữa 2 cây nhất quán)
    {
        LibraryManager manager;
        string err;
        manager.addBook(Book("978-99", "Co So Du Lieu", "Nguyen Van A", "CS", 2020, 10), err);

        Book modified("978-99", "Co So Du Lieu", "Pham Van Dong", "Database", 2023, 25);
        bool updOk = manager.updateBook("978-99", modified, err);

        const Book* fromAVL = manager.searchByISBN("978-99");
        vector<Book> fromBST = manager.searchByTitle("Co So Du Lieu");

        bool consistent = false;
        if (fromAVL && !fromBST.empty()) {
            consistent = (fromAVL->author == "Pham Van Dong") &&
                         (fromBST[0].author == "Pham Van Dong") &&
                         (fromAVL->quantity == 25) &&
                         (fromBST[0].quantity == 25) &&
                         (fromAVL->publicationYear == 2023) &&
                         (fromBST[0].publicationYear == 2023);
        }

        bool ok = updOk && consistent;
        results.push_back({
            "TC18", "Sua thong tin sach (Nhat quan)",
            "Doi Tac gia, The loai, Nam, SL",
            "Du lieu giua AVL va BST nhat quan",
            ok ? "Du lieu 2 cay hoan toan nhat quan" : "Bat dong bo",
            ok
        });
    }

    int passedCount = 0;
    for (const auto& r : results) {
        printTestRow(r);
        if (r.passed) passedCount++;
    }
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";
    cout << "Ket qua kiem thu BST & Dong bo: " << passedCount << "/" << results.size() << " test cases DAT (PASS).\n\n";

    return (passedCount == (int)results.size()) ? 0 : 1;
}
