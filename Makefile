
CC = CC
CFLAGS = -Wextra -Werror -Wall -g

# `argparse` module sourcess
ARGPARSE_SRC = \
src/argparse/argparse_.c

ARGPARSE_OBJ = $(ARGPARSE_SRC:.c=.o)


