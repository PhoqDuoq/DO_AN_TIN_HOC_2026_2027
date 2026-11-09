#include "LibraryManager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct TestCaseResult {
    string code;
    string name;
    string input;
    string expected;
    string actual;
    bool passed;
};

int main() {
    cout << "\n========================================================================================================================\n";
    cout << "                  BANG KIEM THU TONG HOP 18 TEST CASE BAT BUOC (TUAN 3 - DO AN TIN HOC)\n";
    cout << "========================================================================================================================\n";

    vector<TestCaseResult> report;

    // TC01: Thêm sách vào cây rỗng
    {
        AVLTree tree;
        Book b("978-01", "Lap trinh C++", "Nguyen Van A", "Giao trinh", 2024, 10);
        bool res = tree.insert(b);
        bool ok = res && (tree.getSize() == 1) && (tree.getHeight() == 1) && (tree.search("978-01") != nullptr);
        report.push_back({
            "TC01", "Them sach vao cay rong",
            "Book(ISBN='978-01', Title='Lap trinh C++')",
            "Them thanh cong, size=1, h=1",
            ok ? "Them thanh cong, size=1, h=1" : "That bai",
            ok
        });
    }

    // TC02: Thêm ISBN trùng
    {
        AVLTree tree;
        Book b1("978-01", "Lap trinh C++", "Nguyen Van A", "Giao trinh", 2024, 10);
        Book b2("978-01", "Lap trinh C++ Nang Cao", "Tran Van B", "Giao trinh", 2025, 5);
        tree.insert(b1);
        bool res2 = tree.insert(b2);
        bool ok = (!res2) && (tree.getSize() == 1);
        report.push_back({
            "TC02", "Them ISBN trung",
            "Chen 2 sach cung ISBN='978-01'",
            "Tu choi them trung, size=1",
            ok ? "Tu choi them trung, size=1" : "Cho phep them trung (Loi)",
            ok
        });
    }

    // TC03: Tìm ISBN tồn tại
    {
        AVLTree tree;
        tree.insert(Book("978-01", "Lap trinh C++", "Tac gia A", "IT", 2024, 5));
        tree.insert(Book("978-02", "Cau truc du lieu", "Tac gia B", "IT", 2023, 8));
        Book* f = tree.search("978-02");
        bool ok = (f != nullptr) && (f->title == "Cau truc du lieu");
        report.push_back({
            "TC03", "Tim ISBN ton tai",
            "Tim ISBN='978-02'",
            "Tra ve dung sach 'Cau truc du lieu'",
            f ? ("Tra ve: " + f->title) : "nullptr",
            ok
        });
    }

    // TC04: Tìm ISBN không tồn tại
    {
        AVLTree tree;
        tree.insert(Book("978-01", "Lap trinh C++", "Tac gia A", "IT", 2024, 5));
        Book* f = tree.search("978-99");
        bool ok = (f == nullptr);
        report.push_back({
            "TC04", "Tim ISBN khong ton tai",
            "Tim ISBN='978-99'",
            "Thong bao khong tim thay (nullptr)",
            (f == nullptr) ? "Tra ve nullptr (Khong tim thay)" : "Tim thay sai",
            ok
        });
    }

    // TC05: Thêm dữ liệu gây xoay LL
    {
        AVLTree tree;
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        tree.insert(Book("20", "B20", "A", "C", 2020, 1));
        tree.insert(Book("10", "B10", "A", "C", 2020, 1)); // LL rotation at 30
        const AVLNode* r = tree.getRoot();
        bool ok = tree.isBalanced() && r && (r->data.ISBN == "20") &&
                  r->left && (r->left->data.ISBN == "10") &&
                  r->right && (r->right->data.ISBN == "30");
        report.push_back({
            "TC05", "Them du lieu gay xoay LL",
            "Chen 30 -> 20 -> 10 (Lech trai)",
            "Xoay phai LL, Goc=20, cay can bang",
            (r ? ("Goc=" + r->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC06: Thêm dữ liệu gây xoay RR
    {
        AVLTree tree;
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("20", "B20", "A", "C", 2020, 1));
        tree.insert(Book("30", "B30", "A", "C", 2020, 1)); // RR rotation at 10
        const AVLNode* r = tree.getRoot();
        bool ok = tree.isBalanced() && r && (r->data.ISBN == "20") &&
                  r->left && (r->left->data.ISBN == "10") &&
                  r->right && (r->right->data.ISBN == "30");
        report.push_back({
            "TC06", "Them du lieu gay xoay RR",
            "Chen 10 -> 20 -> 30 (Lech phai)",
            "Xoay trai RR, Goc=20, cay can bang",
            (r ? ("Goc=" + r->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC07: Thêm dữ liệu gây xoay LR
    {
        AVLTree tree;
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("20", "B20", "A", "C", 2020, 1)); // LR rotation at 30
        const AVLNode* r = tree.getRoot();
        bool ok = tree.isBalanced() && r && (r->data.ISBN == "20") &&
                  r->left && (r->left->data.ISBN == "10") &&
                  r->right && (r->right->data.ISBN == "30");
        report.push_back({
            "TC07", "Them du lieu gay xoay LR",
            "Chen 30 -> 10 -> 20 (Trai-Phai)",
            "Xoay kep LR, Goc=20, cay can bang",
            (r ? ("Goc=" + r->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC08: Thêm dữ liệu gây xoay RL
    {
        AVLTree tree;
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        tree.insert(Book("20", "B20", "A", "C", 2020, 1)); // RL rotation at 10
        const AVLNode* r = tree.getRoot();
        bool ok = tree.isBalanced() && r && (r->data.ISBN == "20") &&
                  r->left && (r->left->data.ISBN == "10") &&
                  r->right && (r->right->data.ISBN == "30");
        report.push_back({
            "TC08", "Them du lieu gay xoay RL",
            "Chen 10 -> 30 -> 20 (Phai-Trai)",
            "Xoay kep RL, Goc=20, cay can bang",
            (r ? ("Goc=" + r->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC09: Xóa nút lá
    {
        AVLTree tree;
        tree.insert(Book("20", "B20", "A", "C", 2020, 1));
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        bool rem = tree.remove("10");
        bool ok = rem && (tree.search("10") == nullptr) && (tree.getSize() == 2) && tree.isBalanced();
        report.push_back({
            "TC09", "Xoa nut la",
            "Cay {10,20,30}, xoa nut la 10",
            "Cay hop le va can bang, size=2",
            ok ? "Cay hop le va can bang, size=2" : "That bai",
            ok
        });
    }

    // TC10: Xóa nút có một con
    {
        AVLTree tree;
        tree.insert(Book("20", "B20", "A", "C", 2020, 1));
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        tree.insert(Book("05", "B05", "A", "C", 2020, 1));
        bool rem = tree.remove("10");
        bool ok = rem && (tree.search("10") == nullptr) && (tree.search("05") != nullptr) && tree.isBalanced();
        report.push_back({
            "TC10", "Xoa nut co mot con",
            "Xoa nut 10 (co con duy nhat 05)",
            "Cay hop le, 05 thay the, can bang",
            ok ? "Cay hop le, 05 thay the, can bang" : "That bai",
            ok
        });
    }

    // TC11: Xóa nút có hai con
    {
        AVLTree tree;
        tree.insert(Book("20", "B20", "A", "C", 2020, 1));
        tree.insert(Book("10", "B10", "A", "C", 2020, 1));
        tree.insert(Book("30", "B30", "A", "C", 2020, 1));
        tree.insert(Book("25", "B25", "A", "C", 2020, 1));
        tree.insert(Book("35", "B35", "A", "C", 2020, 1));
        bool rem = tree.remove("30");
        bool ok = rem && (tree.search("30") == nullptr) && (tree.search("25") != nullptr) &&
                  (tree.search("35") != nullptr) && tree.isBalanced();
        report.push_back({
            "TC11", "Xoa nut co hai con",
            "Xoa nut 30 (co 2 con: 25, 35)",
            "Dung successor (35) the vi, can bang",
            ok ? "Cay hop le, successor the vi, can bang" : "That bai",
            ok
        });
    }

    // TC12: Hiển thị BST bằng In-order
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
        report.push_back({
            "TC12", "Hien thi BST bang In-order",
            "Duyet 4 sach ten khong theo thu tu",
            "Danh sach theo dung thu tu ten A-Z",
            ok ? "Danh sach dung thu tu ten A-Z" : "Sai thu tu",
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
        vector<Book> res = bst.searchByTitle("Giao Trinh C++");
        bool ok = ins1 && ins2 && (bst.getSize() == 2) && (res.size() == 2);
        report.push_back({
            "TC13", "Hai sach trung ten, khac ISBN",
            "Cung ten 'Giao Trinh C++', ISBN khac",
            "Ca hai deu duoc luu trong BST",
            ok ? "Ca hai deu duoc luu (size=2)" : "That bai",
            ok
        });
    }

    // TC14: Đổi tên sách
    {
        LibraryManager mgr;
        string err;
        mgr.addBook(Book("978-01", "Sach Ban Dau", "Tac gia A", "KH", 2021, 5), err);
        Book updated("978-01", "Sach Sau Khi Doi Ten", "Tac gia A", "KH", 2021, 5);
        bool upOk = mgr.updateBook("978-01", updated, err);
        vector<Book> oldRes = mgr.searchByTitle("Sach Ban Dau");
        vector<Book> newRes = mgr.searchByTitle("Sach Sau Khi Doi Ten");
        bool ok = upOk && oldRes.empty() && (newRes.size() == 1) && (newRes[0].ISBN == "978-01");
        report.push_back({
            "TC14", "Doi ten sách",
            "Doi ten 'Sach Ban Dau' -> moi",
            "BST cap nhat dung vi tri moi",
            ok ? "BST cap nhat dung vi tri moi" : "That bai",
            ok
        });
    }

    // TC15: Xóa sách
    {
        LibraryManager mgr;
        string err;
        mgr.addBook(Book("978-11", "Kien Truc May Tinh", "Author X", "IT", 2020, 3), err);
        mgr.addBook(Book("978-22", "Mang May Tinh", "Author Y", "IT", 2021, 6), err);
        bool rmOk = mgr.removeBook("978-11", err);
        const Book* inAVL = mgr.searchByISBN("978-11");
        vector<Book> inBST = mgr.searchByTitle("Kien Truc May Tinh");
        bool ok = rmOk && (inAVL == nullptr) && inBST.empty() && (mgr.getTotalBooks() == 1);
        report.push_back({
            "TC15", "Xoa sach",
            "Xoa sach ISBN='978-11'",
            "AVL va BST dong bo loai bo sach",
            ok ? "AVL va BST dong bo loai bo sach" : "That bai",
            ok
        });
    }

    // TC16: Cây rỗng
    {
        AVLTree tree;
        bool rm = tree.remove("999");
        Book* s = tree.search("999");
        int h = tree.getHeight();
        bool ok = (!rm) && (s == nullptr) && (h == 0) && tree.isBalanced();
        report.push_back({
            "TC16", "Cay rong",
            "Thao tac remove/search tren cay rong",
            "Khong phat sinh loi, tra ve false/null",
            ok ? "Khong phat sinh loi, an toan tuyet doi" : "Phat sinh loi",
            ok
        });
    }

    // TC17: Thêm nhiều sách liên tiếp
    {
        AVLTree tree;
        bool allOk = true;
        for (int i = 1; i <= 80; ++i) {
            string isbn = (i < 10 ? "ISBN-0" : "ISBN-") + to_string(i);
            Book b(isbn, "Title " + to_string(i), "Author", "Cat", 2022, 5);
            if (!tree.insert(b)) {
                allOk = false;
                break;
            }
        }
        bool ok = allOk && (tree.getSize() == 80) && tree.isBalanced();
        report.push_back({
            "TC17", "Them nhieu sach lien tiep",
            "Chen 80 sach lien tiep vao AVL",
            "AVL van can bang (|BF|<=1 moi nut)",
            ok ? ("AVL van can bang (h=" + to_string(tree.getHeight()) + ", size=80)") : "Mat can bang",
            ok
        });
    }

    // TC18: Sửa thông tin sách
    {
        LibraryManager mgr;
        string err;
        mgr.addBook(Book("978-77", "He Dieu Hanh", "Tac gia Cu", "CS", 2020, 10), err);
        Book updated("978-77", "He Dieu Hanh", "Tac gia Moi", "Operating System", 2024, 30);
        bool upOk = mgr.updateBook("978-77", updated, err);

        const Book* fAVL = mgr.searchByISBN("978-77");
        vector<Book> fBST = mgr.searchByTitle("He Dieu Hanh");

        bool consistent = false;
        if (fAVL && !fBST.empty()) {
            consistent = (fAVL->author == "Tac gia Moi") &&
                         (fBST[0].author == "Tac gia Moi") &&
                         (fAVL->category == "Operating System") &&
                         (fBST[0].category == "Operating System") &&
                         (fAVL->publicationYear == 2024) &&
                         (fBST[0].publicationYear == 2024) &&
                         (fAVL->quantity == 30) &&
                         (fBST[0].quantity == 30);
        }
        bool ok = upOk && consistent;
        report.push_back({
            "TC18", "Sua thong tin sach",
            "Sua author, category, year, quantity",
            "Du lieu giua hai cay nhat quan",
            ok ? "Du lieu giua hai cay hoan toan nhat quan" : "Du lieu bat nhat quan",
            ok
        });
    }

    // In bảng kết quả
    cout << "+--------+--------------------------------+--------------------------------------+---------------------------------------+---------------------------------------+--------+\n";
    cout << "| Ma TC  | Noi dung kiem thu              | Du lieu dau vao                      | Ket qua mong doi                      | Ket qua thuc te                       | Status |\n";
    cout << "+--------+--------------------------------+--------------------------------------+---------------------------------------+---------------------------------------+--------+\n";

    int passCount = 0;
    for (const auto& r : report) {
        cout << "| " << left << setw(6) << r.code
             << " | " << left << setw(30) << r.name
             << " | " << left << setw(36) << r.input
             << " | " << left << setw(37) << r.expected
             << " | " << left << setw(37) << r.actual
             << " | " << (r.passed ? "\033[32mPASS\033[0m  " : "\033[31mFAIL\033[0m  ")
             << " |\n";
        if (r.passed) passCount++;
    }

    cout << "+--------+--------------------------------+--------------------------------------+---------------------------------------+---------------------------------------+--------+\n";
    cout << "\n>>> TONG KET: " << passCount << "/" << report.size() << " TEST CASES DAT YEU CAU (TY LE: "
         << (passCount * 100 / report.size()) << "%).\n\n";

    return (passCount == (int)report.size()) ? 0 : 1;
}
