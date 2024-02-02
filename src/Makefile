CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g

LIBS=-lcheck
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS += -lsubunit -lm
endif

TARGET=s21_math

SRCS=s21_math.c

OBJS=$(SRCS:.c=.o) #s21_math.o

TEST_SRC=check_s21_math.c

TEST_TARG=test

all: s21_math.a test gcov_report

s21_math.a:
	$(CC) $(SRCS) $(CFLAGS) -c
	ar rsc libs21_math.a $(OBJS)
	ranlib libs21_math.a
	ar rsc s21_math.a $(OBJS)
	ranlib s21_math.a
	rm -f $(OBJS)

test: s21_math.a
	$(CC) $(TEST_SRC) $(CFLAGS) $(LIBS) -L. -ls21_math -o $(TEST_TARG)
	./$(TEST_TARG)
	rm -f $(TEST_TARG) *.o

gcov_report: 
	$(CC) --coverage $(FLAGS) $(SRCS) $(TEST_SRC) -o $(TEST_TARG) $(LIBS)
	./$(TEST_TARG)
	lcov -t "$(TEST_TARG)" -o $(TEST_TARG).info -c -d .
	genhtml -o report $(TEST_TARG).info
	rm -f *.gcda *.gcno *.info $(TEST_TARG)

check_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n *.[ch] ../tests/*.[ch]
	rm -rf .clang-format

fix_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i *.[ch] tests/*.[ch]
	rm -rf .clang-format

clean_lib:
	rm -f *.[oa]

clean_cov:
	rm -f *.gcno *.gcda *.info *.gcov $(TEST_TARG)

clean: clean_lib clean_cov
	rm -f $(TEST_TARG)
	rm -rf report

rebuild: clean all