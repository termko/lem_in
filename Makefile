NAME = lem-in
FLAGS = -Wall -Wextra -Werror
SRC = backtrack.c checks.c cycle.c dijkstra.c flow.c free.c free_lemin.c get_node.c\
	  init_ants.c init_edges.c init_lemin.c init_node.c main.c misc.c new_path.c\
	  print.c read.c utils.c step.c
OBJ = backtrack.o checks.o cycle.o dijkstra.o flow.o free.o free_lemin.o get_node.o\
	  init_ants.o init_edges.o init_lemin.o init_node.o main.o misc.o new_path.o\
	  print.o read.o utils.o step.o
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@gcc -o $(NAME) $(SRC) $(LIBFT)

$(LIBFT):
	@make -C libft

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all

debug:
	@gcc -Wall -Wextra -Werror *.c libft/libft.a -g

.PHONY: all, re, clean, fclean
