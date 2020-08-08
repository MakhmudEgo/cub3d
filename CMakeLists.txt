cmake_minimum_required(VERSION 3.16)
project(cub3d C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework AppKit -I minilibx -L../minilibx -lmlx")
include_directories(minilibx)

add_executable(cub3d
        libft/ft_lstadd_front.c
        libft/ft_lstiter.c
        libft/ft_lstadd_back.c
        libft/ft_lstnew.c
        libft/ft_atoi.c
        libft/ft_strdup.c
        libft/ft_strlen.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        cub3d.c parse_cub3dfile.c)
