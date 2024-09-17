
CC = cc
CFLAGS = -Wextra -Werror -Wall -g

# `argparse` module sourcess
ARGPARSE_SRC = \
src/argparse/argparse_.c

# object files
ARGPARSE_OBJ = $(ARGPARSE_SRC:.c=.o)

# archive files
ARGPARSE_NAME = argparse.a

#

# archive files


