all:
	gcc -Wall -Wextra -Werror *.c libft/libft.a -o lem-in

debug:
	gcc -Wall -Wextra -Werror *.c libft/libft.a -g
