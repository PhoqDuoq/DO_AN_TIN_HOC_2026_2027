# ĐỒ ÁN TIN HỌC – HỌC KỲ I (NĂM HỌC 2026–2027)

## ĐỀ TÀI: XÂY DỰNG CHƯƠNG TRÌNH QUẢN LÝ THƯ VIỆN BẰNG C++

- **Giảng viên hướng dẫn**: ThS. Lương An Vinh
- **Sinh viên thực hiện**:
  1. Dương Hoài Phong – MSSV: DH52201205
  2. Trương Phúc Lộc – MSSV: DH52301010
- **Ngôn ngữ**: C++ (chuẩn C++11 trở lên, biên dịch với MinGW GCC)

---

## Tiến độ 10 tuần thực hiện

| Tuần | Checklist | Trạng thái |
|:---:|:---|:---:|
| **1** | [x] Repo Git &nbsp; [x] SRS.pdf &nbsp; [x] Cấu trúc thư mục | **Hoàn thành** |
| **2** | [x] Design.pdf &nbsp; [x] Sơ đồ lớp &nbsp; [x] Định nghĩa struct | **Hoàn thành** |
| **3** | [x] AVL Tree &nbsp; [x] BST Tree &nbsp; [x] Test quản lý sách (18 TC) | **Hoàn thành** |
| **4** | [ ] Hash Table &nbsp; [ ] Test quản lý độc giả | Dự kiến |
| **5** | [ ] LinkedList &nbsp; [ ] Dynamic Array &nbsp; [ ] File I/O (.dat) | Dự kiến |
| **6** | [ ] Mượn sách &nbsp; [ ] Trả sách &nbsp; [ ] Tính phạt | Dự kiến |
| **7** | [ ] Graph &nbsp; [ ] BFS/DFS gợi ý sách &nbsp; [ ] Thống kê top 10 | Dự kiến |
| **8** | [ ] Cấu trúc dữ liệu Trie &nbsp; [ ] Tích hợp hệ thống &nbsp; [ ] Demo | Dự kiến |
| **9** | [ ] Unit test toàn diện &nbsp; [ ] Bảng so sánh CTDL &nbsp; [ ] User manual | Dự kiến |
| **10**| [ ] Báo cáo tổng kết &nbsp; [ ] Video demo &nbsp; [ ] Slide &nbsp; [ ] Nộp + Ký duyệt | Dự kiến |

---

## Cấu trúc thư mục dự án

```text
DO_AN_TIN_HOC_2026_2027/
├── docs/                        # Tài liệu dự án (SRS, Design, Báo cáo các tuần)
│   ├── BaoCaoTuan1.docx
│   ├── BaoCaoTuan2.docx
│   ├── Design.pdf
│   ├── SRS.pdf
│   └── Week03_Report.md         # Báo cáo kỹ thuật chi tiết tuần 3
├── LibraryManagement/           # Toàn bộ mã nguồn chương trình (duy nhất)
│   ├── include/                 # Khai báo các module (duy nhất trong dự án)
│   │   ├── models/              # Thực thể dữ liệu (Book, Reader, BorrowRecord)
│   │   ├── datastructures/      # Cấu trúc dữ liệu tự cài đặt (AVLTree, BSTree, Trie, Graph,...)
│   │   ├── managers/            # Điều phối nghiệp vụ & file I/O (LibraryManager, FileManager)
│   │   └── ui/                  # Giao diện Console tương tác (MenuManager)
│   ├── src/                     # Cài đặt mã nguồn chi tiết (duy nhất trong dự án)
│   │   ├── models/
│   │   ├── datastructures/
│   │   ├── managers/
│   │   ├── ui/
│   │   └── main.cpp             # Điểm bắt đầu thực thi chương trình
│   ├── tests/                   # Bộ kiểm thử tự động (test_avl, test_bst, test_all)
│   ├── data/                    # Chứa các file dữ liệu (.dat)
│   ├── Makefile                 # Lệnh build & test trực tiếp trong module
│   └── README.md
├── .vscode/                     # Cấu hình IntelliSense và trình biên dịch
├── .gitignore                   # Loại trừ các file nhị phân và tạm thời
├── Makefile                     # Makefile gốc điều phối build và test toàn dự án
└── README.md                    # Tài liệu tổng quan và checklist tiến độ
```

---

## Hướng dẫn biên dịch và thực thi

### 1. Yêu cầu môi trường
- Trình biên dịch C++ hỗ trợ C++11 trở lên: `g++` (MinGW-W64 khuyến nghị bản 8.0 trở lên, dự án đã kiểm thử trên MinGW GCC 16.2.0).
- Công cụ build: `make` hoặc `mingw32-make`.

### 2. Biên dịch bằng Makefile (Khuyến nghị)

Tại thư mục gốc dự án:

```powershell
# Biên dịch chương trình chính
mingw32-make all

# Chạy toàn bộ các bộ kiểm thử tự động
mingw32-make test

# Dọn dẹp các file thực thi và object
mingw32-make clean
```

*(Nếu dùng Linux / macOS hoặc MinGW trên cmd chuẩn, có thể gõ lệnh `make all`, `make test`).*

### 3. Biên dịch trực tiếp bằng lệnh g++ thủ công

Nếu không dùng Makefile, bạn có thể biên dịch trực tiếp:

#### a. Biên dịch chương trình chính:
```bash
g++ -std=c++11 -Wall -Wextra -Iinclude src/main.cpp src/Book.cpp src/AVLTree.cpp src/BSTree.cpp src/LibraryManager.cpp -o library_management.exe
```
Chạy chương trình:
```bash
./library_management.exe
```

#### b. Biên dịch và chạy bộ kiểm thử:
```bash
# Kiểm thử cây AVL:
g++ -std=c++11 -Wall -Wextra -Iinclude tests/test_avl.cpp src/Book.cpp src/AVLTree.cpp -o test_avl.exe
./test_avl.exe

# Kiểm thử cây BST và đồng bộ:
g++ -std=c++11 -Wall -Wextra -Iinclude tests/test_bst.cpp src/Book.cpp src/AVLTree.cpp src/BSTree.cpp src/LibraryManager.cpp -o test_bst.exe
./test_bst.exe

# Kiểm thử tổng hợp 18 Test Cases (TC01 - TC18):
g++ -std=c++11 -Wall -Wextra -Iinclude tests/test_all.cpp src/Book.cpp src/AVLTree.cpp src/BSTree.cpp src/LibraryManager.cpp -o test_all.exe
./test_all.exe
```

---

## Hướng dẫn sử dụng Menu Console Tuần 3

Khi chạy `library_management.exe`, giao diện hiển thị:

```text
====================================================
  DO AN TIN HOC - HOC KY I (2026-2027)
  CHUONG TRINH QUAN LY THU VIEN BANG C++
  TUAN 3: CAI DAT VA KIEM THU AVL TREE & BST
====================================================

========== QUAN LY SACH ==========
1. Them sach
2. Cap nhat thong tin sach
3. Xoa sach theo ISBN
4. Tim kiem sach theo ISBN
5. Hien thi sach theo ISBN (AVL)
6. Hien thi sach theo ten (BST)
7. Kiem tra tinh can bang AVL
0. Thoat
==================================
Nhap lua chon: 
```

- **Phím 1**: Thêm sách mới (yêu cầu nhập đủ 6 thông tin, hệ thống tự động kiểm tra ISBN trùng lặp).
- **Phím 2**: Cập nhật thông tin sách theo ISBN (nếu đổi tên sách, hệ thống tự động cập nhật vị trí trong BST).
- **Phím 3**: Xóa sách theo ISBN (đồng bộ gỡ bỏ khỏi cả AVL và BST).
- **Phím 4**: Tra cứu thông tin chi tiết một cuốn sách bằng mã ISBN.
- **Phím 5**: Duyệt In-order cây AVL để xem toàn bộ danh mục sắp xếp theo ISBN.
- **Phím 6**: Duyệt In-order cây BST để xem danh mục sách sắp xếp theo Tên (A-Z).
- **Phím 7**: Kiểm tra trạng thái cân bằng của cây AVL, hiển thị chiều cao và hệ số cân bằng nút gốc.
- **Phím 0**: Thoát chương trình.

---

## Bảng kết quả kiểm thử Tuần 3 (18/18 PASS)

| Mã TC | Nội dung kiểm thử | Kết quả mong đợi | Kết quả thực tế | Trạng thái |
|:---:|:---|:---|:---|:---:|
| TC01 | Thêm sách vào cây rỗng | Thêm thành công, size=1, h=1 | Thêm thành công, size=1, h=1 | **PASS** |
| TC02 | Thêm ISBN trùng | Từ chối | Từ chối thêm trùng, size=1 | **PASS** |
| TC03 | Tìm ISBN tồn tại | Trả về đúng sách | Trả về: Cau truc du lieu | **PASS** |
| TC04 | Tìm ISBN không tồn tại | Thông báo không tìm thấy | Trả về nullptr (Không tìm thấy) | **PASS** |
| TC05 | Thêm dữ liệu gây xoay LL | Cây cân bằng, gốc đổi đúng | Gốc=20, Bal=True | **PASS** |
| TC06 | Thêm dữ liệu gây xoay RR | Cây cân bằng, gốc đổi đúng | Gốc=20, Bal=True | **PASS** |
| TC07 | Thêm dữ liệu gây xoay LR | Cây cân bằng, gốc đổi đúng | Gốc=20, Bal=True | **PASS** |
| TC08 | Thêm dữ liệu gây xoay RL | Cây cân bằng, gốc đổi đúng | Gốc=20, Bal=True | **PASS** |
| TC09 | Xóa nút lá | Cây vẫn hợp lệ | Cây hợp lệ và cân bằng, size=2 | **PASS** |
| TC10 | Xóa nút có một con | Cây vẫn hợp lệ | Cây hợp lệ, 05 thay thế, cân bằng | **PASS** |
| TC11 | Xóa nút có hai con | Cây vẫn hợp lệ | Cây hợp lệ, successor thế vị | **PASS** |
| TC12 | Hiển thị BST bằng In-order | Danh sách đúng thứ tự tên | Danh sách đúng thứ tự tên A-Z | **PASS** |
| TC13 | Hai sách trùng tên, khác ISBN | Cả hai đều được lưu | Cả hai đều được lưu (size=2) | **PASS** |
| TC14 | Đổi tên sách | BST cập nhật đúng | BST cập nhật đúng vị trí mới | **PASS** |
| TC15 | Xóa sách | AVL và BST đồng bộ | AVL và BST đồng bộ loại bỏ sách | **PASS** |
| TC16 | Cây rỗng | Không phát sinh lỗi | Không phát sinh lỗi, an toàn tuyệt đối | **PASS** |
| TC17 | Thêm nhiều sách liên tiếp | AVL vẫn cân bằng | AVL vẫn cân bằng (h=7, size=80) | **PASS** |
| TC18 | Sửa thông tin sách | Dữ liệu giữa hai cây nhất quán | Dữ liệu 2 cây hoàn toàn nhất quán | **PASS** |
