#include "BSTree.h"
#include <iostream>

using namespace std;

BSTNode::BSTNode(const Book& b)
    : data(b), left(nullptr), right(nullptr) {}

BSTree::BSTree() : root(nullptr), count(0) {}

BSTree::~BSTree() {
    clear();
}

BSTree::BSTree(const BSTree& other) : root(nullptr), count(0) {
    root = cloneHelper(other.root);
    count = other.count;
}

BSTree& BSTree::operator=(const BSTree& other) {
    if (this != &other) {
        clear();
        root = cloneHelper(other.root);
        count = other.count;
    }
    return *this;
}

BSTNode* BSTree::cloneHelper(BSTNode* node) {
    if (!node) return nullptr;
    BSTNode* newNode = new BSTNode(node->data);
    newNode->left = cloneHelper(node->left);
    newNode->right = cloneHelper(node->right);
    return newNode;
}

void BSTree::clear() {
    destroyHelper(root);
    root = nullptr;
    count = 0;
}

void BSTree::destroyHelper(BSTNode* node) {
    if (node) {
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }
}

int BSTree::compareKeys(const string& t1, const string& i1,
                        const string& t2, const string& i2) {
    if (t1 < t2) return -1;
    if (t1 > t2) return 1;
    if (i1 < i2) return -1;
    if (i1 > i2) return 1;
    return 0;
}

bool BSTree::insert(const Book& book) {
    if (!book.isValid()) return false;
    bool inserted = false;
    root = insertHelper(root, book, inserted);
    if (inserted) {
        count++;
    }
    return inserted;
}

BSTNode* BSTree::insertHelper(BSTNode* node, const Book& book, bool& inserted) {
    if (!node) {
        inserted = true;
        return new BSTNode(book);
    }

    int cmp = compareKeys(book.title, book.ISBN, node->data.title, node->data.ISBN);
    if (cmp < 0) {
        node->left = insertHelper(node->left, book, inserted);
    } else if (cmp > 0) {
        node->right = insertHelper(node->right, book, inserted);
    } else {
        // Trùng cả tên sách lẫn ISBN -> Từ chối
        inserted = false;
        return node;
    }
    return node;
}

bool BSTree::remove(const string& title, const string& isbn) {
    if (!root) return false;
    bool removed = false;
    root = removeHelper(root, title, isbn, removed);
    if (removed) {
        count--;
    }
    return removed;
}

BSTNode* BSTree::findMinNode(BSTNode* node) const {
    BSTNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

BSTNode* BSTree::removeHelper(BSTNode* node, const string& title,
                              const string& isbn, bool& removed) {
    if (!node) {
        removed = false;
        return nullptr;
    }

    int cmp = compareKeys(title, isbn, node->data.title, node->data.ISBN);
    if (cmp < 0) {
        node->left = removeHelper(node->left, title, isbn, removed);
    } else if (cmp > 0) {
        node->right = removeHelper(node->right, title, isbn, removed);
    } else {
        // Tìm thấy nút cần xóa
        removed = true;

        if (!node->left || !node->right) {
            BSTNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            // Nút có 2 con: tìm successor nhỏ nhất bên phải
            BSTNode* successor = findMinNode(node->right);
            node->data = successor->data;
            bool dummy = false;
            node->right = removeHelper(node->right, successor->data.title, successor->data.ISBN, dummy);
        }
    }
    return node;
}

Book* BSTree::search(const string& title, const string& isbn) {
    BSTNode* node = searchHelper(root, title, isbn);
    return node ? &(node->data) : nullptr;
}

const Book* BSTree::search(const string& title, const string& isbn) const {
    BSTNode* node = searchHelper(root, title, isbn);
    return node ? &(node->data) : nullptr;
}

BSTNode* BSTree::searchHelper(BSTNode* node, const string& title,
                              const string& isbn) const {
    if (!node) return nullptr;
    int cmp = compareKeys(title, isbn, node->data.title, node->data.ISBN);
    if (cmp == 0) return node;
    if (cmp < 0) return searchHelper(node->left, title, isbn);
    return searchHelper(node->right, title, isbn);
}

vector<Book> BSTree::searchByTitle(const string& title) const {
    vector<Book> result;
    searchByTitleHelper(root, title, result);
    return result;
}

void BSTree::searchByTitleHelper(BSTNode* node, const string& title,
                                 vector<Book>& result) const {
    if (!node) return;
    if (title < node->data.title) {
        searchByTitleHelper(node->left, title, result);
    } else if (title > node->data.title) {
        searchByTitleHelper(node->right, title, result);
    } else {
        // Tên bằng nhau, nhưng có thể có các nút khác cùng tên ở cả hai nhánh
        searchByTitleHelper(node->left, title, result);
        result.push_back(node->data);
        searchByTitleHelper(node->right, title, result);
    }
}

bool BSTree::update(const string& oldTitle, const string& isbn, const Book& newInfo) {
    if (!newInfo.isValid()) return false;

    // Nếu tên sách thay đổi, vị trí trong cây BST sẽ thay đổi: cần xóa và chèn lại
    if (oldTitle != newInfo.title) {
        if (!remove(oldTitle, isbn)) return false;
        return insert(newInfo);
    }

    // Nếu tên sách không đổi, chỉ cần tìm nút và cập nhật các thuộc tính khác
    Book* book = search(oldTitle, isbn);
    if (!book) return false;
    book->author = newInfo.author;
    book->category = newInfo.category;
    book->publicationYear = newInfo.publicationYear;
    book->quantity = newInfo.quantity;
    return true;
}

void BSTree::inorder() const {
    inorder([](const Book& b) {
        b.printTableRow();
    });
}

void BSTree::inorder(function<void(const Book&)> visitor) const {
    inorderHelper(root, visitor);
}

void BSTree::inorderHelper(BSTNode* node, const function<void(const Book&)>& visitor) const {
    if (!node) return;
    inorderHelper(node->left, visitor);
    visitor(node->data);
    inorderHelper(node->right, visitor);
}

vector<Book> BSTree::toVector() const {
    vector<Book> list;
    list.reserve(count);
    inorder([&list](const Book& b) {
        list.push_back(b);
    });
    return list;
}

void BSTree::display() const {
    if (isEmpty()) {
        cout << "Danh muc sach trong cay BST rong!\n";
        return;
    }
    Book::printTableHeader();
    inorder();
    cout << "+---------------+--------------------------------+----------------------+-----------------+---------+-------+\n";
    cout << "Tong so sach trong danh muc BST: " << count << "\n";
}

bool BSTree::isEmpty() const {
    return root == nullptr;
}

size_t BSTree::getSize() const {
    return count;
}
