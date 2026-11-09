#ifndef BSTREE_H
#define BSTREE_H

#include "Book.h"
#include <string>
#include <vector>
#include <functional>

using namespace std;

/**
 * @brief Cấu trúc nút cây BST theo Design.pdf (Chương 4, mục 4.4.2)
 * Lưu trữ thông tin sách và con trỏ đến các nhánh cây con trái/phải.
 */
struct BSTNode {
    Book data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Book& b);
};

/**
 * @brief Cây tìm kiếm nhị phân (BST) quản lý danh mục sách theo tên
 * - Khóa sắp xếp chính: title (tên sách tăng dần).
 * - Khóa phụ: ISBN (khi có nhiều sách trùng tên sách).
 * - Hỗ trợ duyệt In-order để xuất danh sách sách theo bảng chữ cái.
 */
class BSTree {
public:
    BSTree();
    ~BSTree();

    // Quản lý bản sao an toàn (Rule of Three)
    BSTree(const BSTree& other);
    BSTree& operator=(const BSTree& other);

    /**
     * @brief Thêm sách vào cây BST
     * Khóa sắp xếp chính là tên sách, khóa phụ là ISBN.
     * @param book Thông tin sách
     * @return true nếu thêm thành công, false nếu sách đã tồn tại (trùng cả title và ISBN)
     */
    bool insert(const Book& book);

    /**
     * @brief Xóa sách khỏi cây BST theo cặp (title, ISBN)
     * @param title Tên sách
     * @param isbn Mã ISBN của sách
     * @return true nếu tìm thấy và xóa thành công, false nếu không tìm thấy
     */
    bool remove(const string& title, const string& isbn);

    /**
     * @brief Tìm kiếm chính xác sách theo cả (title, ISBN)
     * @param title Tên sách
     * @param isbn Mã ISBN
     * @return Con trỏ đến Book tìm thấy hoặc nullptr
     */
    Book* search(const string& title, const string& isbn);
    const Book* search(const string& title, const string& isbn) const;

    /**
     * @brief Tìm tất cả các sách có tên khớp với title được cung cấp
     * @param title Tên sách cần tìm
     * @return Danh sách các sách trùng tên
     */
    vector<Book> searchByTitle(const string& title) const;

    /**
     * @brief Cập nhật thông tin sách trong BST
     * Nếu tên sách thay đổi, vị trí trong BST sẽ được tái cấu trúc lại.
     * @param oldTitle Tên sách cũ
     * @param isbn Mã ISBN
     * @param newInfo Thông tin sách mới
     * @return true nếu cập nhật thành công
     */
    bool update(const string& oldTitle, const string& isbn, const Book& newInfo);

    /**
     * @brief Duyệt cây In-order và in ra Console
     */
    void inorder() const;

    /**
     * @brief Duyệt cây In-order với callback/visitor function
     */
    void inorder(function<void(const Book&)> visitor) const;

    /**
     * @brief Chuyển toàn bộ danh sách sách sang vector theo thứ tự tên sách
     */
    vector<Book> toVector() const;

    /**
     * @brief Hiển thị danh mục sách theo thứ tự tên ra Console
     */
    void display() const;

    /**
     * @brief Kiểm tra cây rỗng
     */
    bool isEmpty() const;

    /**
     * @brief Lấy số lượng nút trong cây
     */
    size_t getSize() const;

    /**
     * @brief Xóa toàn bộ cây và giải phóng bộ nhớ
     */
    void clear();

    /**
     * @brief Hàm so sánh 2 khóa (title, ISBN)
     * @return < 0 nếu (t1, i1) < (t2, i2); 0 nếu bằng nhau; > 0 nếu lớn hơn
     */
    static int compareKeys(const string& t1, const string& i1,
                           const string& t2, const string& i2);

private:
    BSTNode* root;
    size_t count;

    BSTNode* insertHelper(BSTNode* node, const Book& book, bool& inserted);
    BSTNode* removeHelper(BSTNode* node, const string& title, const string& isbn, bool& removed);
    BSTNode* searchHelper(BSTNode* node, const string& title, const string& isbn) const;
    void searchByTitleHelper(BSTNode* node, const string& title, vector<Book>& result) const;
    BSTNode* findMinNode(BSTNode* node) const;

    void destroyHelper(BSTNode* node);
    BSTNode* cloneHelper(BSTNode* node);
    void inorderHelper(BSTNode* node, const function<void(const Book&)>& visitor) const;
};

#endif // BSTREE_H
