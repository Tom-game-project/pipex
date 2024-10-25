CC = cc
AR = ar

CFLAGS = -Wextra -Werror -Wall -g
ARFLAGS= -rcs

# test files
TEST = \
       tests/atest02.c
       # tests/atest02.c

ARG_TEST = \
	       src/arg_test.c


# `argparse` module sourcess
ARGPARSE_SRC = \
	       src/argparse/argparse_helper.c

BASIC_SRC = \
	       src/basic/basic00.c

ARGPARSE_OBJ = $(ARGPARSE_SRC:.c=.o)

BASIC_OBJ = $(BASIC_SRC:.c=.o)

# object files
OBJS = \
       $(ARGPARSE_OBJ)\
       $(BASIC_OBJ)

ARGPARSE_NAME = argparse.a
BASIC_NAME = basic.a

# archive files
ARCHIVES = \
	   $(ARGPARSE_NAME)\
	   $(BASIC_NAME)

# Main pipex
MAIN_SRC = src/pipex.c
MAIN_TARGET = pipex

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SRC) $(ARCHIVES)
	$(CC) $(CFLAGS) $(MAIN_SRC) $(ARCHIVES) -o $@

# for test
a.out:  $(ARCHIVES)
	$(CC) $(CFLAGS) $(ARG_TEST) $(ARCHIVES) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ARGPARSE_NAME): $(ARGPARSE_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(BASIC_NAME): $(BASIC_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# test commands

test: $(TEST) $(ARCHIVES)
	rm -f test
	$(CC) $(CFLAGS) $(TEST) $(ARCHIVES) -o $@
	# ./test
	valgrind  --leak-check=full ./test


clean:
	rm -rf $(OBJS) $(ARCHIVES)

.PHONY: all clean fclean test re

