all:
	gcc -Wall -Wextra -Werror *.c libft/libft.a

debug:
	gcc -Wall -Wextra -Werror *.c libft/libft.a -g
