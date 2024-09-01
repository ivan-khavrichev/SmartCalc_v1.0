CC = gcc
STD = -std=c11
WFLAGS =  -Wall -Werror -Wextra
TEST_FLAGS = -lcheck

WSL_LINK_FLAGS = -lsubunit `pkg-config --cflags --libs check`


S21_LIB = s21_calc.a
PATH_BACK = smart_calc_v1/back/
PATH_FRONT = smart_calc_v1/front/
C_FILES = $(wildcard smart_calc_v1/back/s21_*.c)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES))

TEST_C_FILES = $(wildcard tests.c)
TEST_OBJ_FILES = $(patsubst %.c, %.o, $(TEST_C_FILES))

TRASH = $(wildcard *.o *.a *.gc* *.out *.tar Documentation html latex tests test.info report $(PATH_BACK)*.o )



all: clean install

install: $(S21_LIB)
	rm -rf calc_app
	mkdir calc_app
	cd calc_app; cmake ../smart_calc_v1
	cd calc_app && make

uninstall: clean
	rm -rf smart_calc_v1/CMakeLists.txt.user
	rm -rf smart_calc_v1/build
	rm -rf calc_app

dist: clean uninstall
	rm -rf archive_calc
	mkdir archive_calc
	mkdir archive_calc/src
	cp -r ../*.md Makefile tests.c Doxyfile smart_calc_v1 archive_calc/src
	cd ../ && cp -r materials src/archive_calc
	tar cvzf archive_calc.tar archive_calc/
	rm -rf archive_calc

dvi:
	rm -rf Documentation
	doxygen
	open Documentation/html/index.html

clean:
	rm -rf $(TRASH)

rebuild: clean all

$(S21_LIB): clean $(OBJ_FILES)
	ar rc $(S21_LIB) $(OBJ_FILES)
	ranlib $(S21_LIB)
	rm -f $(BACK_P)*.o

test: clean $(S21_LIB)
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS) -lm
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests $(TEST_FLAGS) $(WSL_LINK_FLAGS) -lm
	./tests
else
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(S21_LIB) -o tests  $(TEST_FLAGS)
	./tests
endif

gcov_report: clean $(S21_LIB)
ifeq ($(shell uname -s), Linux)
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS) -o tests
else
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.c $(PATH_BACK)*.c $(PATH_BACK)*.h $(PATH_FRONT)*.cpp $(PATH_FRONT)*.h smart_calc_v1/main.cpp
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.c $(PATH_BACK)*.c $(PATH_BACK)*.h $(PATH_FRONT)*.cpp $(PATH_FRONT)*.h smart_calc_v1/main.cpp
	rm -rf .clang-format

check_leaks: clean test
ifeq ($(shell uname -s), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
else
	leaks -atExit -- ./tests
endif
