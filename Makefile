# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caburges <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/12 19:02:31 by caburges          #+#    #+#              #
#    Updated: 2025/01/22 16:26:08 by caburges         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CFLAGS = -g -Wall -Werror -Wextra
MLX = minilibx-linux/libmlx_Linux.a
MLX_DIR = minilibx-linux

SRCS = srcs/main.c \
	srcs/initialisation.c \
	srcs/init_utils.c \
	srcs/maths.c \
	srcs/maths_utils.c \
	srcs/colour.c \
	srcs/draw.c

OBJS = $(SRCS:.c=.o)
INCLUDES_DIR = includes
LIBFT = libft/libft.a
LIBFT_DIR = libft

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	cc $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INCLUDES_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
