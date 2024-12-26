CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TFLAGS = -lcheck -lm -lsubunit
GFLAGS = -fprofile-arcs -ftest-coverage

all: test

clean:
	rm -f tests *.o *.a *.gcda *.gcno *.info *.log
	rm -rf html

test: s21_matrix.a tests.c s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c
	$(CC) $(CFLAGS) -c tests.c
	$(CC) $(CFLAGS) *.o -o tests $(TFLAGS) s21_matrix.a
	./tests

s21_matrix.a: s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c
	ar crs s21_matrix.a *.o

gcov_report: s21_matrix.c tests.c
	$(CC) $(CFLAGS) $(GFLAGS) -c s21_matrix.c
	$(CC) $(CFLAGS) $(GFLAGS) -c tests.c
	$(CC) $(CFLAGS) $(GFLAGS) *.o -o tests $(TFLAGS)
	./tests
	lcov -t "REPORT" -o REPORT.info -c -d .
	genhtml -o html REPORT.info
	open html/index.html

valgrind: s21_matrix.a tests.c s21_matrix.c
	$(CC) $(CFLAGS) -c s21_matrix.c
	$(CC) $(CFLAGS) -c tests.c
	$(CC) $(CFLAGS) *.o -o tests $(TFLAGS) s21_matrix.a
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./tests

clang:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h