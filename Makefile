CFLAGS= -g -Wextra -Wall -Werror
LIBS	:= -lft -L./lib/libft
NAME = push_swap
OBJECTS = src/sort.o src/stack.o src/actions.o src/naive_optimizer.o src/main.o src/optimizer_actions.o src/optimizer.o src/error.o src/executor.o src/roadtrip_sort.o src/roadtrip_utils.o src/rotation_optimizer.o src/s_optimizer.o src/sort_utils.o src/tab_verifyer.o
DEPS = -I./include -I./lib/libft

all: space
	@echo "\033[1;32mMaking libft:\033[0m"
	@$(MAKE) -C ./lib/libft 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for libft\033[0m\n")
	@echo "\033[1;32mMaking push_swap:\033[0m"
	@$(MAKE) $(NAME) 2>&1 | (grep -v "make\[1\]" || echo "\033[1;33mNothing to be done for push_swap\033[0m\n")

$(NAME): $(OBJECTS) include/push_swap.h
	@echo
	$(CC) $(OBJECTS) $(LIBS) -o $(NAME) $(CFLAGS) $(DEPS)
	@echo "\033[1;32mpush_swap compiled\033[0m"
	@echo

clean:
	@rm -f $(OBJECTS)
	@echo "\033[1;31mpush_swap cleaned\033[0m"

fclean: libclean clean
	@rm -f $(NAME)

libclean:
	@$(MAKE) -C ./lib/libft fclean

re: fclean space all

space:
	@echo

%.o: %.c include/push_swap.h
	cc -c -o $@ $< $(CFLAGS) $(DEPS)

.PHONY: clean fclean re all libclean space
