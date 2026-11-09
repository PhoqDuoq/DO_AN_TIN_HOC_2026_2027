#include "AVLTree.h"
#include <algorithm>
#include <cmath>

using namespace std;

AVLNode::AVLNode(const Book& b)
    : data(b), height(1), left(nullptr), right(nullptr) {}

AVLTree::AVLTree() : root(nullptr), count(0) {}

AVLTree::~AVLTree() {
    clear();
}

AVLTree::AVLTree(const AVLTree& other) : root(nullptr), count(0) {
    root = cloneHelper(other.root);
    count = other.count;
}

AVLTree& AVLTree::operator=(const AVLTree& other) {
    if (this != &other) {
        clear();
        root = cloneHelper(other.root);
        count = other.count;
    }
    return *this;
}

AVLNode* AVLTree::cloneHelper(AVLNode* node) {
    if (!node) return nullptr;
    AVLNode* newNode = new AVLNode(node->data);
    newNode->height = node->height;
    newNode->left = cloneHelper(node->left);
    newNode->right = cloneHelper(node->right);
    return newNode;
}

void AVLTree::clear() {
    destroyHelper(root);
    root = nullptr;
    count = 0;
}

void AVLTree::destroyHelper(AVLNode* node) {
    if (node) {
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }
}

int AVLTree::getNodeHeight(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::getNodeBalance(AVLNode* node) const {
    return node ? (getNodeHeight(node->left) - getNodeHeight(node->right)) : 0;
}

void AVLTree::updateNodeHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(getNodeHeight(node->left), getNodeHeight(node->right));
    }
}

int AVLTree::getHeight() const {
    return getNodeHeight(root);
}

int AVLTree::getBalance() const {
    return getNodeBalance(root);
}

/**
 * @brief Phép xoay phải (LL Rotation)
 * Áp dụng khi cây con trái cao hơn và nhánh lệch trái (Left-Left).
 * Độ phức tạp: O(1).
 */
AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Thực hiện phép xoay
    x->right = y;
    y->left = T2;

    // Cập nhật lại chiều cao của y trước, sau đó là x
    updateNodeHeight(y);
    updateNodeHeight(x);

    return x; // Nút x trở thành gốc mới của cây con
}

/**
 * @brief Phép xoay trái (RR Rotation)
 * Áp dụng khi cây con phải cao hơn và nhánh lệch phải (Right-Right).
 * Độ phức tạp: O(1).
 */
AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Thực hiện phép xoay
    y->left = x;
    x->right = T2;

    // Cập nhật lại chiều cao của x trước, sau đó là y
    updateNodeHeight(x);
    updateNodeHeight(y);

    return y; // Nút y trở thành gốc mới của cây con
}

/**
 * @brief Cân bằng lại nút cây AVL dựa trên hệ số cân bằng (Balance Factor)
 * Xử lý cả 4 trường hợp: LL, RR, LR, RL.
 * Độ phức tạp: O(1).
 */
AVLNode* AVLTree::balanceNode(AVLNode* node) {
    if (!node) return nullptr;

    updateNodeHeight(node);
    int balance = getNodeBalance(node);

    // Trường hợp 1: Mất cân bằng Lệch Trái (Left heavy)
    if (balance > 1) {
        // Trường hợp LR: Con trái bị lệch phải -> xoay trái con trái trước
        if (getNodeBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        // Trường hợp LL: Xoay phải nút hiện tại
        return rotateRight(node);
    }

    // Trường hợp 2: Mất cân bằng Lệch Phải (Right heavy)
    if (balance < -1) {
        // Trường hợp RL: Con phải bị lệch trái -> xoay phải con phải trước
        if (getNodeBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        // Trường hợp RR: Xoay trái nút hiện tại
        return rotateLeft(node);
    }

    return node;
}

bool AVLTree::insert(const Book& book) {
    if (!book.isValid()) return false;
    bool inserted = false;
    root = insertHelper(root, book, inserted);
    if (inserted) {
        count++;
    }
    return inserted;
}

AVLNode* AVLTree::insertHelper(AVLNode* node, const Book& book, bool& inserted) {
    if (!node) {
        inserted = true;
        return new AVLNode(book);
    }

    if (book.ISBN < node->data.ISBN) {
        node->left = insertHelper(node->left, book, inserted);
    } else if (book.ISBN > node->data.ISBN) {
        node->right = insertHelper(node->right, book, inserted);
    } else {
        // Trùng mã ISBN: Từ chối thêm mới
        inserted = false;
        return node;
    }

    // Tự động cân bằng lại cây sau khi chèn
    return balanceNode(node);
}

bool AVLTree::remove(const string& isbn) {
    if (isbn.empty() || !root) return false;
    bool removed = false;
    root = removeHelper(root, isbn, removed);
    if (removed) {
        count--;
    }
    return removed;
}

AVLNode* AVLTree::findMinNode(AVLNode* node) const {
    AVLNode* current = node;
    while (current && current->left) {
        current = current->left;
    }
    return current;
}

AVLNode* AVLTree::removeHelper(AVLNode* node, const string& isbn, bool& removed) {
    if (!node) {
        removed = false;
        return nullptr;
    }

    if (isbn < node->data.ISBN) {
        node->left = removeHelper(node->left, isbn, removed);
    } else if (isbn > node->data.ISBN) {
        node->right = removeHelper(node->right, isbn, removed);
    } else {
        // Đã tìm thấy nút cần xóa
        removed = true;

        // Trường hợp 1: Nút lá hoặc chỉ có 1 con
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                // Nút lá: Không có con nào
                delete node;
                node = nullptr;
            } else {
                // Nút có đúng 1 con: Thay thế bằng con của nó
                delete node;
                node = temp;
            }
        } else {
            // Trường hợp 2: Nút có 2 con
            // Tìm nút kế vị In-order (nút nhỏ nhất bên cây con phải)
            AVLNode* successor = findMinNode(node->right);
            // Sao chép dữ liệu của nút kế vị vào nút hiện tại
            node->data = successor->data;
            // Xóa nút kế vị khỏi cây con phải
            bool dummy = false;
            node->right = removeHelper(node->right, successor->data.ISBN, dummy);
        }
    }

    if (!node) return nullptr;

    // Tự động cân bằng lại cây sau khi xóa
    return balanceNode(node);
}

Book* AVLTree::search(const string& isbn) {
    AVLNode* node = searchHelper(root, isbn);
    return node ? &(node->data) : nullptr;
}

const Book* AVLTree::search(const string& isbn) const {
    AVLNode* node = searchHelper(root, isbn);
    return node ? &(node->data) : nullptr;
}

AVLNode* AVLTree::searchHelper(AVLNode* node, const string& isbn) const {
    if (!node || node->data.ISBN == isbn) {
        return node;
    }
    if (isbn < node->data.ISBN) {
        return searchHelper(node->left, isbn);
    }
    return searchHelper(node->right, isbn);
}

bool AVLTree::update(const string& isbn, const Book& newInfo) {
    Book* book = search(isbn);
    if (!book) return false;
    if (!newInfo.isValid()) return false;
    if (newInfo.ISBN != isbn) return false; // Không cho phép đổi khóa chính qua hàm update này

    book->title = newInfo.title;
    book->author = newInfo.author;
    book->category = newInfo.category;
    book->publicationYear = newInfo.publicationYear;
    book->quantity = newInfo.quantity;
    return true;
}

bool AVLTree::isBalanced() const {
    return isBalancedHelper(root);
}

bool AVLTree::isBalancedHelper(AVLNode* node) const {
    if (!node) return true;
    int balance = getNodeBalance(node);
    if (balance < -1 || balance > 1) {
        return false;
    }
    return isBalancedHelper(node->left) && isBalancedHelper(node->right);
}

void AVLTree::inorder() const {
    inorder([](const Book& b) {
        b.printTableRow();
    });
}

void AVLTree::inorder(function<void(const Book&)> visitor) const {
    inorderHelper(root, visitor);
}

void AVLTree::inorderHelper(AVLNode* node, const function<void(const Book&)>& visitor) const {
    if (!node) return;
    inorderHelper(node->left, visitor);
    visitor(node->data);
    inorderHelper(node->right, visitor);
}

vector<Book> AVLTree::toVector() const {
    vector<Book> list;
    list.reserve(count);
    inorder([&list](const Book& b) {
        list.push_back(b);
    });
    return list;
}

void AVLTree::display() const {
    if (isEmpty()) {
        cout << "Danh sach sach trong cay AVL rong!\n";
        return;
    }
    Book::printTableHeader();
    inorder();
    cout << "+---------------+--------------------------------+----------------------+-----------------+---------+-------+\n";
    cout << "Tong so sach: " << count << " | Chieu cao cay AVL: " << getHeight()
         << " | He so can bang goc: " << getBalance() << "\n";
}

bool AVLTree::isEmpty() const {
    return root == nullptr;
}

size_t AVLTree::getSize() const {
    return count;
}
