cmake_minimum_required(VERSION 3.16)
project(cub3d C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGL -framework AppKit -L../ -lmlx")
include_directories(mlx)

add_executable(cub3d
        libft/ft_lstsize.c
        libft/ft_strtrim.c
        libft/ft_calloc.c
        libft/ft_bzero.c
        libft/ft_lstadd_front.c
        libft/ft_lstiter.c
        libft/ft_lstadd_back.c
        libft/ft_lstnew.c
        libft/ft_atoi.c
        libft/ft_strdup.c
        libft/ft_strlen.c
        libft/ft_strchr.c
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        cub3d.c
        parse_cub3dfile.c
        create_map.c
        put_map2d.c
        sp_lstadd_back.c
        sp_lstnew.c
        sp_lstsize.c
        libft/ft_strncmp.c
        screen_s.c move.c)
