TARGET = ./main.out
TARGET_TEST = ./main_tests.out
HDRS_DIR = project/include/

SRCS = \
       project/src/main.c \
       project/src/manage_functions.c \
	   project/src/welcome_mes_func.c \
       project/src/write_read_stream.c

SRCS_TEST = \
		project/tests/main_tests.c \
		project/src/write_read_stream.c

.PHONY: all allofmain build rebuild check test memtest clean testbuild testrebuild testoftest memtestoftest testclean

all: allofmain testrebuild
allofmain: clean check test memtest

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

$(TARGET_TEST): $(SRCS_TEST)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)

build: $(TARGET)

rebuild: clean build

check:
	./run_linters.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat

testbuild: $(TARGET_TEST)

testrebuild: testclean testbuild

testclean:
	rm -rf $(TARGET_TEST) *.dat
