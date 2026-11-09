#include "Book.h"
#include <iomanip>
#include <ctime>

using namespace std;

Book::Book()
    : ISBN(""), title(""), author(""), category(""), publicationYear(0), quantity(0) {}

Book::Book(const string& isbn,
           const string& t,
           const string& a,
           const string& c,
           int year,
           int qty)
    : ISBN(isbn), title(t), author(a), category(c), publicationYear(year), quantity(qty) {}

bool Book::isValid(string* errorMsg) const {
    if (ISBN.empty()) {
        if (errorMsg) *errorMsg = "Ma ISBN khong duoc de trong.";
        return false;
    }
    if (title.empty()) {
        if (errorMsg) *errorMsg = "Ten sach khong duoc de trong.";
        return false;
    }
    if (author.empty()) {
        if (errorMsg) *errorMsg = "Ten tac gia khong duoc de trong.";
        return false;
    }

    // Lấy năm hiện tại để kiểm tra ràng buộc không vượt quá năm hiện tại
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int currentYear = (now != nullptr) ? (now->tm_year + 1900) : 2027;
    if (currentYear < 2027) currentYear = 2027;

    if (publicationYear <= 0 || publicationYear > currentYear) {
        if (errorMsg) {
            *errorMsg = "Nam xuat ban phai hop le (0 < nam <= " + to_string(currentYear) + ").";
        }
        return false;
    }
    if (quantity < 0) {
        if (errorMsg) *errorMsg = "So luong sach phai lon hon hoac bang 0.";
        return false;
    }

    return true;
}

void Book::printDetails() const {
    cout << "----------------------------------------\n";
    cout << "ISBN        : " << ISBN << "\n";
    cout << "Ten sach    : " << title << "\n";
    cout << "Tac gia     : " << author << "\n";
    cout << "The loai    : " << category << "\n";
    cout << "Nam XB      : " << publicationYear << "\n";
    cout << "So luong    : " << quantity << "\n";
    cout << "----------------------------------------\n";
}

void Book::printTableHeader() {
    cout << "+---------------+--------------------------------+----------------------+-----------------+---------+-------+\n";
    cout << "| " << left << setw(13) << "ISBN"
         << " | " << left << setw(30) << "Ten sach"
         << " | " << left << setw(20) << "Tac gia"
         << " | " << left << setw(15) << "The loai"
         << " | " << right << setw(7) << "Nam XB"
         << " | " << right << setw(5) << "SL"
         << " |\n";
    cout << "+---------------+--------------------------------+----------------------+-----------------+---------+-------+\n";
}

void Book::printTableRow() const {
    string dispTitle = (title.length() > 30) ? (title.substr(0, 27) + "...") : title;
    string dispAuthor = (author.length() > 20) ? (author.substr(0, 17) + "...") : author;
    string dispCategory = (category.length() > 15) ? (category.substr(0, 12) + "...") : category;

    cout << "| " << left << setw(13) << ISBN
         << " | " << left << setw(30) << dispTitle
         << " | " << left << setw(20) << dispAuthor
         << " | " << left << setw(15) << dispCategory
         << " | " << right << setw(7) << publicationYear
         << " | " << right << setw(5) << quantity
         << " |\n";
}

bool Book::operator==(const Book& other) const {
    return ISBN == other.ISBN &&
           title == other.title &&
           author == other.author &&
           category == other.category &&
           publicationYear == other.publicationYear &&
           quantity == other.quantity;
}

bool Book::operator!=(const Book& other) const {
    return !(*this == other);
}
