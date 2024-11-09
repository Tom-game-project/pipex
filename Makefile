CC = cc
AR = ar

CFLAGS = -Wextra -Werror -Wall -g
ARFLAGS= -rcs

# test files
TEST = \
       tests/atest02.c
       # tests/atest02.c

ARG_TEST = \
	   src/test.c

# `argparse` module sourcess
ARGPARSE_SRC = \
	       src/argparse/argparse_helper.c

BASIC_SRC = \
	       src/basic/basic00.c

PIPELINE_SRC = \
	       src/pipeline/pipeline.c \
               src/pipeline/pipeline2.c

EXECUTOR_SRC = \
	       src/executer/executor_helper.c \
	       src/executer/no_allocation.c


ARGPARSE_OBJ = $(ARGPARSE_SRC:.c=.o)
BASIC_OBJ = $(BASIC_SRC:.c=.o)
PIPELINE_OBJ = $(PIPELINE_SRC:.c=.o)
EXECUTOR_OBJ = $(EXECUTOR_SRC:.c=.o)

# object files
OBJS = \
       $(ARGPARSE_OBJ)\
       $(BASIC_OBJ) \
       $(PIPELINE_OBJ)\
       $(EXECUTOR_OBJ)

ARGPARSE_NAME = argparse.a
BASIC_NAME = basic.a
PIPELINE_NAME = pipeline.a
EXECUTOR_NAME = executor.a


# archive files
ARCHIVES = \
	   $(ARGPARSE_NAME)\
	   $(BASIC_NAME)\
	   $(PIPELINE_NAME)\
	   $(EXECUTOR_NAME)

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

$(PIPELINE_NAME): $(PIPELINE_OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(EXECUTOR_NAME): $(BASIC_OBJ) $(EXECUTOR_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# test commands

test: $(TEST) $(ARCHIVES)
	rm -f test
	$(CC) $(CFLAGS) $(TEST) $(ARCHIVES) -o $@
	# ./test
	valgrind  --leak-check=full ./test

clean:
	rm -rf $(OBJS) $(ARCHIVES)

fclean: clean
	rm -f $(MAIN_TARGET)

re: fclean all

.PHONY: all clean fclean test re

