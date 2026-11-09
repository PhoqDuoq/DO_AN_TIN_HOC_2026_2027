all:
	$(MAKE) -C LibraryManagement all

test:
	$(MAKE) -C LibraryManagement test

clean:
	$(MAKE) -C LibraryManagement clean

.PHONY: all test clean
