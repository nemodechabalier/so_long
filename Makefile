# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nde-chab <nde-chab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 13:46:16 by nde-chab          #+#    #+#              #
#    Updated: 2024/09/01 23:03:48 by nde-chab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
LIBFT = libft_all/libft_printf_gnl.a
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -Imlx_linux
MLX_FLAGS = -Lminilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
INCLUDES = -I .

SRCS_DIR = srcs/

FUNC = creat_map_and_free.c error_map.c error_gestion.c so_long.c visual.c utils.c mouv.c

SRCS = $(addprefix $(SRCS_DIR), $(FUNC))

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

# Rule to compile .c files to .o files
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(MAKE) -C libft_all/
	$(MAKE) -C minilibx-linux/
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@




# Rule to create the final executable
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	
# Default target	
all : $(NAME)

# Clean object files
clean:
	$(MAKE) -C libft_all/ clean
	rm -rf $(OBJS_DIR)

# Full clean
fclean: clean
	$(MAKE) -C libft_all/ fclean
	$(MAKE) -C minilibx-linux/ clean
	rm -f $(NAME) 

# Recompile everything
re: fclean all

.PHONY: all clean fclean re
