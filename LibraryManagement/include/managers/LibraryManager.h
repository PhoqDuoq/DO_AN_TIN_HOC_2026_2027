#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include "Book.h"
#include "AVLTree.h"
#include "BSTree.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Lớp quản lý thư viện (trọng tâm Tuần 3: Quản lý sách)
 * Điều phối hoạt động đồng bộ giữa cây AVL (khóa chính ISBN)
 * và cây BST (khóa danh mục theo Tên sách).
 */
class LibraryManager {
public:
    LibraryManager();
    ~LibraryManager();

    /**
     * @brief Khởi chạy giao diện dòng lệnh Console Menu
     */
    void run();

    /**
     * @brief Thêm sách mới vào hệ thống (đồng bộ cả AVL và BST)
     * @param book Đối tượng Book
     * @param errorMsg Thông báo lỗi nếu thất bại
     * @return true nếu thêm thành công, false nếu dữ liệu sai hoặc trùng ISBN
     */
    bool addBook(const Book& book, string& errorMsg);

    /**
     * @brief Cập nhật thông tin sách
     * Nếu tên sách thay đổi, cập nhật vị trí trong BST tương ứng.
     * @param isbn Mã ISBN của sách cần cập nhật
     * @param newInfo Thông tin cập nhật mới
     * @param errorMsg Thông báo lỗi nếu thất bại
     * @return true nếu cập nhật thành công
     */
    bool updateBook(const string& isbn, const Book& newInfo, string& errorMsg);

    /**
     * @brief Xóa sách theo mã ISBN (loại bỏ khỏi cả AVL và BST)
     * @param isbn Mã ISBN cần xóa
     * @param errorMsg Thông báo lỗi nếu thất bại
     * @return true nếu xóa thành công
     */
    bool removeBook(const string& isbn, string& errorMsg);

    /**
     * @brief Tìm kiếm sách theo mã ISBN thông qua cây AVL
     * @param isbn Mã ISBN
     * @return Con trỏ đến Book hoặc nullptr
     */
    Book* searchByISBN(const string& isbn);
    const Book* searchByISBN(const string& isbn) const;

    /**
     * @brief Tìm kiếm sách theo tên sách thông qua cây BST
     * @param title Tên sách cần tìm
     * @return Danh sách sách có tên khớp
     */
    vector<Book> searchByTitle(const string& title) const;

    /**
     * @brief Hiển thị toàn bộ sách theo thứ tự ISBN (duyệt In-order AVL)
     */
    void displayBooksByISBN() const;

    /**
     * @brief Hiển thị toàn bộ sách theo thứ tự Tên sách (duyệt In-order BST)
     */
    void displayBooksByTitle() const;

    /**
     * @brief Kiểm tra tính cân bằng của cây AVL
     * @param height Chiều cao cây
     * @param balanced Kết quả kiểm tra cân bằng
     * @return true nếu cây AVL cân bằng hợp lệ
     */
    bool checkAVLBalance(int& height, bool& balanced) const;

    /**
     * @brief Lấy tổng số sách hiện có trong hệ thống
     */
    size_t getTotalBooks() const;

    /**
     * @brief Xóa toàn bộ dữ liệu trong cả hai cây
     */
    void clear();

    // Truy cập trực tiếp các cây (phục vụ kiểm thử sâu)
    const AVLTree& getAVLTree() const { return avlTree; }
    const BSTree& getBSTree() const { return bstTree; }
    AVLTree& getAVLTree() { return avlTree; }
    BSTree& getBSTree() { return bstTree; }

private:
    AVLTree avlTree; // Cấu trúc chính: AVL quản lý theo ISBN
    BSTree bstTree;  // Cấu trúc phụ: BST sắp xếp danh mục theo Tên

    // Các hàm phục vụ Console UI
    void showMenu() const;
    void handleAddBook();
    void handleUpdateBook();
    void handleRemoveBook();
    void handleSearchByISBN();
    void handleDisplayByISBN();
    void handleDisplayByTitle();
    void handleCheckAVLBalance();

    // Các hàm hỗ trợ nhập liệu an toàn từ bàn phím
    static string inputString(const string& prompt, bool allowEmpty = false);
    static int inputInt(const string& prompt, int minVal, int maxVal);
};

#endif // LIBRARYMANAGER_H
