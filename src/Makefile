.PHONY: clean all lintercheck cppcheck test style_check gcov_report
CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11
LDFLAGS= -lcheck -L. -ldecimal
GFLAGS= -fprofile-arcs -ftest-coverage
HEADERS=decimal.h
SOURCES=decimal.c

OBJECTS=$(SOURCES:.c=.o)
OS := $(shell uname)

ifeq ($(OS), Linux) 
	LDFLAGS += -lrt -lm -lpthread -lsubunit
endif

all: decimal.a

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES)

decimal.a: $(OBJECTS)
	ar rc decimal.a $(OBJECTS)
	cp decimal.a libdecimal.a

clean:
	rm -rf $(OBJECTS) *.a *.out *.gcda *.gcno *.info *.cfg gcov_report

test: test.c decimal.a
	$(CC) decimal.a $< -o test.out $(LDFLAGS)
	./test.out

gcov_report: clean
	$(CC) $(CFLAGS) $(SOURCES) $(GFLAGS)
	ar rcs libdecimal.a $(OBJECTS)
	$(CC) -o test.out test.c $(LDFLAGS) -lgcov
	rm -f *.o
	./test.out
	lcov -c -d . -o coverage.info
	genhtml coverage.info -o gcov_report

lintercheck:
	cp ../CPPLINT.cfg CPPLINT.cfg
	cp ../cpplint.py cpplint.py
	python3 cpplint.py --extensions=c *.c *.h
	rm -rf CPPLINT.cfg
	rm -rf cpplint.py

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --suppress=invalidPointerCast  *.c *.h

style_check: linter cppcheck

leaks: test
	CK_FORK=no leaks --atExit -- ./test.out

