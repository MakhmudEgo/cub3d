# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/11 14:02:02 by mizola            #+#    #+#              #
#    Updated: 2020/06/26 11:59:36 by mizola           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = cub3d.c create_map.c parse_cub3dfile.c put_map2d.c sp_lstadd_back.c sp_lstnew.c sp_lstsize.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c screen_s.c

OSRC = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME) $(OSRC)

$(NAME): $(SRC)
	make -C libft
	make -C libft bonus
	make -C mlx
	make -C mlx_dylib
	cp libft/libft.a ./
	cp mlx/libmlx.a ./
	cp mlx_dylib/libmlx.dylib ./
	gcc $(FLAGS) ./libft.a ./libmlx.a ./libmlx.dylib -framework OpenGl -framework AppKit $(SRC) -o $(NAME)

bonus: all

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OSRC)

fclean: clean
	make -C libft fclean
	make -C mlx clean
	make -C mlx_dylib clean
	rm -f libft.a
	rm -f libmlx.a
	rm -f libmlx.dylib
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
