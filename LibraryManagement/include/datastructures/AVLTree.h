#ifndef AVLTREE_H
#define AVLTREE_H

#include "Book.h"
#include <string>
#include <vector>
#include <functional>

using namespace std;

/**
 * @brief Cấu trúc nút cây AVL theo Design.pdf (Chương 4, mục 4.4.1)
 * Lưu trữ thông tin sách, chiều cao và con trỏ cây con trái/phải.
 */
struct AVLNode {
    Book data;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Book& b);
};

/**
 * @brief Lớp cây AVL tự cân bằng để quản lý sách theo mã ISBN
 * Khóa tìm kiếm và sắp xếp là ISBN (string).
 * Đảm bảo độ phức tạp O(log n) cho các thao tác Thêm, Xóa, Tìm kiếm.
 */
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    // Hỗ trợ Rule of Three / Rule of Five để quản lý bộ nhớ an toàn
    AVLTree(const AVLTree& other);
    AVLTree& operator=(const AVLTree& other);

    /**
     * @brief Thêm sách vào cây AVL theo khóa ISBN
     * @param book Đối tượng Book cần thêm
     * @return true nếu thêm thành công, false nếu trùng ISBN hoặc dữ liệu không hợp lệ
     */
    bool insert(const Book& book);

    /**
     * @brief Xóa sách khỏi cây AVL theo mã ISBN
     * @param isbn Mã ISBN cần xóa
     * @return true nếu tìm thấy và xóa thành công, false nếu không tìm thấy
     */
    bool remove(const string& isbn);

    /**
     * @brief Tìm kiếm sách theo mã ISBN
     * @param isbn Mã ISBN cần tìm
     * @return Con trỏ đến Book tìm thấy (hoặc nullptr nếu không tồn tại)
     */
    Book* search(const string& isbn);
    const Book* search(const string& isbn) const;

    /**
     * @brief Cập nhật thông tin sách theo mã ISBN
     * @param isbn Mã ISBN của sách cần cập nhật
     * @param newInfo Thông tin mới
     * @return true nếu cập nhật thành công, false nếu không tìm thấy
     */
    bool update(const string& isbn, const Book& newInfo);

    /**
     * @brief Lấy chiều cao của cây (tính từ gốc)
     * @return Chiều cao cây (0 nếu cây rỗng)
     */
    int getHeight() const;

    /**
     * @brief Lấy hệ số cân bằng tại nút gốc
     * Balance Factor = Height(Left) - Height(Right)
     * @return Hệ số cân bằng (-1, 0, 1 nếu cân bằng)
     */
    int getBalance() const;

    /**
     * @brief Kiểm tra xem toàn bộ các nút trong cây có thỏa mãn tính chất cân bằng AVL không
     * @return true nếu cây hoàn toàn cân bằng, false nếu vi phạm
     */
    bool isBalanced() const;

    /**
     * @brief Duyệt cây theo thứ tự In-order và in ra Console
     */
    void inorder() const;

    /**
     * @brief Duyệt cây In-order với callback/visitor function
     */
    void inorder(function<void(const Book&)> visitor) const;

    /**
     * @brief Chuyển toàn bộ danh sách sách sang vector theo thứ tự In-order
     */
    vector<Book> toVector() const;

    /**
     * @brief Hiển thị toàn bộ danh sách sách dạng bảng ra Console
     */
    void display() const;

    /**
     * @brief Kiểm tra cây rỗng
     */
    bool isEmpty() const;

    /**
     * @brief Lấy tổng số sách trong cây
     */
    size_t getSize() const;

    /**
     * @brief Xóa sạch toàn bộ cây và giải phóng bộ nhớ
     */
    void clear();

    /**
     * @brief Lấy con trỏ nút gốc (phục vụ kiểm thử cấu trúc và trực quan hóa)
     */
    const AVLNode* getRoot() const { return root; }

private:
    AVLNode* root;
    size_t count;

    // Các hàm phụ trợ đệ quy
    int getNodeHeight(AVLNode* node) const;
    int getNodeBalance(AVLNode* node) const;
    void updateNodeHeight(AVLNode* node);

    // Các phép xoay cây AVL
    AVLNode* rotateRight(AVLNode* y); // Phép xoay LL
    AVLNode* rotateLeft(AVLNode* x);  // Phép xoay RR
    AVLNode* balanceNode(AVLNode* node);

    AVLNode* insertHelper(AVLNode* node, const Book& book, bool& inserted);
    AVLNode* removeHelper(AVLNode* node, const string& isbn, bool& removed);
    AVLNode* searchHelper(AVLNode* node, const string& isbn) const;
    AVLNode* findMinNode(AVLNode* node) const;

    void destroyHelper(AVLNode* node);
    AVLNode* cloneHelper(AVLNode* node);
    void inorderHelper(AVLNode* node, const function<void(const Book&)>& visitor) const;
    bool isBalancedHelper(AVLNode* node) const;
};

#endif // AVLTREE_H
