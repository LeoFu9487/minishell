ROOT=../../..
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
TEST_FILE = main.c

test : $(ROOT)/libmsh.a $(TEST_FILE)
	make test -C $(ROOT)
	gcc $(CFLAGS) -I $(ROOT)/includes $(TEST_FILE) -L$(ROOT) -lmsh -L$(ROOT)/libft -lft -lncurses -o test

$(ROOT)/libmsh.a :
	make test -C $(ROOT)	


