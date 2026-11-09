CXX ?= g++
CXXFLAGS = -std=c++11 -Wall -Wextra \
           -Iinclude \
           -Iinclude/models \
           -Iinclude/datastructures \
           -Iinclude/managers \
           -Iinclude/ui \
           -static -static-libgcc -static-libstdc++

# Tu dong nhan dien g++ neu nam trong thu muc mac dinh C:/Tools/mingw64
ifeq ($(shell where g++ 2>nul),)
  ifneq ($(wildcard C:/Tools/mingw64/bin/g++.exe),)
    CXX = C:/Tools/mingw64/bin/g++.exe
  endif
endif

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = build
TEST_DIR = tests

TARGET = library_management
TEST_AVL_TARGET = test_avl
TEST_BST_TARGET = test_bst
TEST_ALL_TARGET = test_all

CORE_SRC = $(SRC_DIR)/models/Book.cpp \
           $(SRC_DIR)/datastructures/AVLTree.cpp \
           $(SRC_DIR)/datastructures/BSTree.cpp \
           $(SRC_DIR)/managers/LibraryManager.cpp

MAIN_SRC = $(SRC_DIR)/main.cpp $(CORE_SRC)

all: $(TARGET)

$(TARGET): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $@

$(TEST_AVL_TARGET): $(TEST_DIR)/test_avl.cpp $(SRC_DIR)/models/Book.cpp $(SRC_DIR)/datastructures/AVLTree.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_BST_TARGET): $(TEST_DIR)/test_bst.cpp $(CORE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_ALL_TARGET): $(TEST_DIR)/test_all.cpp $(CORE_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(TEST_AVL_TARGET) $(TEST_BST_TARGET) $(TEST_ALL_TARGET)
	@echo ----------------------------------------------------
	@echo Chay test_avl...
	@./$(TEST_AVL_TARGET)
	@echo ----------------------------------------------------
	@echo Chay test_bst...
	@./$(TEST_BST_TARGET)
	@echo ----------------------------------------------------
	@echo Chay test_all (Tong hop TC01 - TC18)...
	@./$(TEST_ALL_TARGET)

clean:
	@if exist "$(TARGET).exe" del /f /q "$(TARGET).exe"
	@if exist "$(TARGET)" del /f /q "$(TARGET)"
	@if exist "$(TEST_AVL_TARGET).exe" del /f /q "$(TEST_AVL_TARGET).exe"
	@if exist "$(TEST_BST_TARGET).exe" del /f /q "$(TEST_BST_TARGET).exe"
	@if exist "$(TEST_ALL_TARGET).exe" del /f /q "$(TEST_ALL_TARGET).exe"
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"

.PHONY: all test clean
