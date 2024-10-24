CC = cc
AR = ar

CFLAGS = -Wextra -Werror -Wall -g
ARFLAGS= -rcs

# test files
TEST = \
       tests/atest00.c

# `argparse` module sourcess
ARGPARSE_SRC = \
	       src/argparse/argparse_helper.c

ARGPARSE_OBJ = $(ARGPARSE_SRC:.c=.o)


# object files
OBJS = \
       $(ARGPARSE_OBJ)

ARGPARSE_NAME = argparse.a

# archive files
ARCHIVES = \
	   $(ARGPARSE_NAME)

# Main pipex
MAIN_SRC = src/pipex.c
MAIN_TARGET = pipex

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_SRC) $(ARCHIVES)
	$(CC) $(CFLAGS) $(MAIN_SRC) $(ARCHIVES) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ARGPARSE_NAME): $(ARGPARSE_OBJ)
	$(AR) $(ARFLAGS) $@ $^

test: $(TEST) $(ARCHIVES)
	rm -f test
	$(CC) $(CFLAGS) $(TEST) $(ARCHIVES) -o $@
	# ./test
	valgrind  --leak-check=full ./test

clean:
	rm -rf $(OBJS) $(ARCHIVES)

.PHONY: all clean fclean test re

