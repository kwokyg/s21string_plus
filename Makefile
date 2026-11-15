CC := gcc
CFLAGS := -std=c11 -Wall -Werror -Wextra 
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

TARGET := s21_string.a
TEST_TARGET := test_runner

LIB_SRCS := s21_mem.c s21_str_basic.c s21_str_search.c s21_strerror.c s21_sprintf.c
LIB_OBJS := $(LIB_SRCS:.c=.o)
HDRS := s21_string.h s21_sprintf.h

TEST_SRCS := tests/test_part1.c tests/test_sprintf.c
TEST_OBJS := $(TEST_SRCS:.c=.o)

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    CHECK_FLAGS := -lcheck
else
    CHECK_FLAGS := -lcheck -lm -lpthread -lsubunit
endif

.PHONY: all clean test gcov_report leaks format cppcheck rebuild

all: $(TARGET)

$(TARGET): $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -I. -c $< -o $@

tests/%.o: tests/%.c $(HDRS)
	$(CC) $(CFLAGS) -I. -c $< -o $@

test: $(TARGET) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(TARGET) $(CHECK_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRCS) $(TEST_SRCS) $(CHECK_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)
	lcov -t "s21_string_report" -o report.info -c -d . --exclude "tests/*"
	genhtml -o report report.info
	@echo "Отчет сгенерирован в папке report/index.html"

format: 
	clang-format -style=Google -i $(LIB_SRCS) $(HDRS) $(TEST_SRCS)

cppcheck:
	cppcheck -enable=all --suppress=missingIncludeSystem $(LIB_SRCS) $(HDRS)

leaks: test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(TEST_TARGET)
else
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./$(TEST_TARGET) 
endif

clean: 
	rm -f $(LIB_OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)
	rm -f *.gcno *.gcda *.gcov report report.info

rebuild: clean all