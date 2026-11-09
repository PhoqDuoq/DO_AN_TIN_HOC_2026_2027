#include "AVLTree.h"
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
    cout << "                                  KIEM THU CAY AVL (AVL TREE TEST SUITE)\n";
    cout << "=========================================================================================================\n";
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";
    cout << "| Ma TC  | Ten kiem thu                   | Du lieu dau vao                  | Ket qua mong doi             | Ket qua thuc te              | KQ   |\n";
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";

    vector<TestResult> results;

    // TC01: Thêm sách vào cây rỗng
    {
        AVLTree tree;
        Book b("978-01", "Lap trinh C++", "Nguyen Van A", "Giao trinh", 2024, 10);
        bool res = tree.insert(b);
        bool ok = res && (tree.getSize() == 1) && (tree.getHeight() == 1) && (tree.search("978-01") != nullptr);
        results.push_back({
            "TC01", "Them sach vao cay rong",
            "ISBN: 978-01",
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
        results.push_back({
            "TC02", "Them ISBN trung",
            "Trung ISBN: 978-01",
            "Tu choi them, size=1",
            (!res2 && tree.getSize() == 1) ? "Tu choi them, size=1" : "Cho phep them trung (Loi)",
            ok
        });
    }

    // TC03: Tìm ISBN tồn tại
    {
        AVLTree tree;
        Book b1("978-01", "Lap trinh C++", "Nguyen Van A", "Giao trinh", 2024, 10);
        Book b2("978-02", "Cau truc du lieu", "Le Thi C", "Giao trinh", 2023, 8);
        tree.insert(b1);
        tree.insert(b2);
        Book* found = tree.search("978-02");
        bool ok = (found != nullptr) && (found->title == "Cau truc du lieu");
        results.push_back({
            "TC03", "Tim ISBN ton tai",
            "Search ISBN: 978-02",
            "Tim thay dung sach 978-02",
            found ? ("Tim thay: " + found->title) : "Khong tim thay",
            ok
        });
    }

    // TC04: Tìm ISBN không tồn tại
    {
        AVLTree tree;
        Book b1("978-01", "Lap trinh C++", "Nguyen Van A", "Giao trinh", 2024, 10);
        tree.insert(b1);
        Book* found = tree.search("978-99");
        bool ok = (found == nullptr);
        results.push_back({
            "TC04", "Tim ISBN khong ton tai",
            "Search ISBN: 978-99",
            "Tra ve nullptr (Khong tim thay)",
            found ? "Tim thay (Loi)" : "Tra ve nullptr (Khong tim thay)",
            ok
        });
    }

    // TC05: Thêm dữ liệu gây xoay LL (Left-Left)
    {
        AVLTree tree;
        tree.insert(Book("30", "Book 30", "Author", "Cat", 2020, 1));
        tree.insert(Book("20", "Book 20", "Author", "Cat", 2020, 1));
        tree.insert(Book("10", "Book 10", "Author", "Cat", 2020, 1));

        const AVLNode* root = tree.getRoot();
        bool ok = tree.isBalanced() && root && (root->data.ISBN == "20") &&
                  root->left && (root->left->data.ISBN == "10") &&
                  root->right && (root->right->data.ISBN == "30");
        results.push_back({
            "TC05", "Them du lieu gay xoay LL",
            "Chen 30 -> 20 -> 10",
            "Xoay phai LL, Goc=20, can bang",
            (root ? ("Goc=" + root->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC06: Thêm dữ liệu gây xoay RR (Right-Right)
    {
        AVLTree tree;
        tree.insert(Book("10", "Book 10", "Author", "Cat", 2020, 1));
        tree.insert(Book("20", "Book 20", "Author", "Cat", 2020, 1));
        tree.insert(Book("30", "Book 30", "Author", "Cat", 2020, 1));

        const AVLNode* root = tree.getRoot();
        bool ok = tree.isBalanced() && root && (root->data.ISBN == "20") &&
                  root->left && (root->left->data.ISBN == "10") &&
                  root->right && (root->right->data.ISBN == "30");
        results.push_back({
            "TC06", "Them du lieu gay xoay RR",
            "Chen 10 -> 20 -> 30",
            "Xoay trai RR, Goc=20, can bang",
            (root ? ("Goc=" + root->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC07: Thêm dữ liệu gây xoay LR (Left-Right)
    {
        AVLTree tree;
        tree.insert(Book("30", "Book 30", "Author", "Cat", 2020, 1));
        tree.insert(Book("10", "Book 10", "Author", "Cat", 2020, 1));
        tree.insert(Book("20", "Book 20", "Author", "Cat", 2020, 1));

        const AVLNode* root = tree.getRoot();
        bool ok = tree.isBalanced() && root && (root->data.ISBN == "20") &&
                  root->left && (root->left->data.ISBN == "10") &&
                  root->right && (root->right->data.ISBN == "30");
        results.push_back({
            "TC07", "Them du lieu gay xoay LR",
            "Chen 30 -> 10 -> 20",
            "Xoay kep LR, Goc=20, can bang",
            (root ? ("Goc=" + root->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
            ok
        });
    }

    // TC08: Thêm dữ liệu gây xoay RL (Right-Left)
    {
        AVLTree tree;
        tree.insert(Book("10", "Book 10", "Author", "Cat", 2020, 1));
        tree.insert(Book("30", "Book 30", "Author", "Cat", 2020, 1));
        tree.insert(Book("20", "Book 20", "Author", "Cat", 2020, 1));

        const AVLNode* root = tree.getRoot();
        bool ok = tree.isBalanced() && root && (root->data.ISBN == "20") &&
                  root->left && (root->left->data.ISBN == "10") &&
                  root->right && (root->right->data.ISBN == "30");
        results.push_back({
            "TC08", "Them du lieu gay xoay RL",
            "Chen 10 -> 30 -> 20",
            "Xoay kep RL, Goc=20, can bang",
            (root ? ("Goc=" + root->data.ISBN + ", Bal=" + (tree.isBalanced() ? "True" : "False")) : "Rong"),
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
        results.push_back({
            "TC09", "Xoa nut la",
            "Cay {10,20,30}, xoa nut la 10",
            "Xoa thanh cong, cay can bang",
            ok ? "Xoa thanh cong, cay can bang" : "That bai",
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
        results.push_back({
            "TC10", "Xoa nut co mot con",
            "Xoa nut 10 (co con trai 05)",
            "Nut 05 thay the 10, cay can bang",
            ok ? "Nut 05 thay the 10, cay can bang" : "That bai",
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
        results.push_back({
            "TC11", "Xoa nut co hai con",
            "Xoa nut 30 (co 2 con: 25, 35)",
            "Dung successor (35), can bang",
            ok ? "Dung successor (35), can bang" : "That bai",
            ok
        });
    }

    // TC16: Thao tác trên cây rỗng
    {
        AVLTree tree;
        bool rem = tree.remove("999");
        Book* s = tree.search("999");
        int h = tree.getHeight();
        bool ok = (!rem) && (s == nullptr) && (h == 0) && tree.isBalanced();
        results.push_back({
            "TC16", "Thao tac tren cay rong",
            "Search, Remove, Height cay rong",
            "Khong crash, tra ve false/null",
            ok ? "Khong crash, tra ve false/null" : "That bai",
            ok
        });
    }

    // TC17: Thêm nhiều sách liên tiếp (Stress test cân bằng AVL)
    {
        AVLTree tree;
        bool allInserted = true;
        for (int i = 1; i <= 60; ++i) {
            string isbn = (i < 10 ? "ISBN-0" : "ISBN-") + to_string(i);
            Book b(isbn, "Book Title " + to_string(i), "Author", "Cat", 2020 + (i % 6), 5);
            if (!tree.insert(b)) {
                allInserted = false;
                break;
            }
        }
        bool ok = allInserted && (tree.getSize() == 60) && tree.isBalanced();
        results.push_back({
            "TC17", "Them nhieu sach lien tiep",
            "Chen 60 sach lien tiep (01..60)",
            "Cay luon can bang, size=60",
            ok ? ("Cay can bang, h=" + to_string(tree.getHeight()) + ", size=60") : "Mat can bang",
            ok
        });
    }

    int passedCount = 0;
    for (const auto& r : results) {
        printTestRow(r);
        if (r.passed) passedCount++;
    }
    cout << "+--------+--------------------------------+----------------------------------+------------------------------+------------------------------+------+\n";
    cout << "Ket qua kiem thu AVL: " << passedCount << "/" << results.size() << " test cases DAT (PASS).\n\n";

    return (passedCount == (int)results.size()) ? 0 : 1;
}
