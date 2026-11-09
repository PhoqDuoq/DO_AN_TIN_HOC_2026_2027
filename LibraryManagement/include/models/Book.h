#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Cấu trúc dữ liệu Book theo đúng đặc tả Design.pdf (Chương 4, mục 4.3.1)
 * và yêu cầu tuần 3 của đồ án Quản lý Thư viện.
 */
struct Book {
    string ISBN;                 // Mã định danh duy nhất của sách
    string title;                // Tên sách
    string author;               // Tên tác giả
    string category;             // Thể loại sách
    int publicationYear;         // Năm xuất bản
    int quantity;                // Số lượng sách hiện có trong thư viện

    // Khởi tạo mặc định
    Book();

    // Khởi tạo có tham số
    Book(const string& isbn,
         const string& t,
         const string& a,
         const string& c,
         int year,
         int qty);

    /**
     * @brief Kiểm tra tính hợp lệ của dữ liệu sách theo ràng buộc trong Design.pdf
     * - ISBN không được rỗng
     * - title không được rỗng
     * - author không được rỗng
     * - publicationYear > 0 và <= năm hiện tại (2027)
     * - quantity >= 0
     * @param errorMsg Chuỗi chứa thông báo lỗi (nếu có)
     * @return true nếu dữ liệu hợp lệ, ngược lại false
     */
    bool isValid(string* errorMsg = nullptr) const;

    // Hiển thị thông tin sách dạng chi tiết
    void printDetails() const;

    // In thông tin sách trên một dòng bảng
    void printTableRow() const;

    // In tiêu đề bảng dữ liệu sách
    static void printTableHeader();

    // Các toán tử so sánh hỗ trợ kiểm thử và đối sánh
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
};

#endif // BOOK_H
