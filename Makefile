# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/30 09:36:39 by migusant          #+#    #+#              #
#    Updated: 2026/05/05 15:45:11 by migusant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                              PROJECT SETTINGS                                #
# **************************************************************************** #

NAME = cub3D
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a

# **************************************************************************** #
#                              COMPILER SETTINGS                               #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
MLX_FLAGS = -lm -lX11 -lXext
RM = rm -f

# **************************************************************************** #
#                             DIRECTORY STRUCTURE                              #
# **************************************************************************** #

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# **************************************************************************** #
#                              SOURCE FILES                                    #
# **************************************************************************** #

SRC_FILES = main.c \
			parse_file.c \
			parse_elements.c \
			parse_colors.c \
			parse_map.c \
			validate_map.c \
			validate_enclosure.c \
			window.c \
			input.c \
			game_loop.c \
			render.c \
			cleanup.c \
			validate_map_helpers.c \
			raycast.c \
			raycast_helpers.c \
			dda.c \
			column.c \
			collision.c \
			minimap.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# **************************************************************************** #
#                                 TARGETS                                      #
# **************************************************************************** #

all: $(LIBFT) $(MINILIBX) $(NAME)

MAP ?= maps/example_1.cub

v: all
	@clear && valgrind --leak-check=full --show-leak-kinds=all \
		--track-fds=yes --track-origins=yes \
		--suppressions=$(shell pwd)/mlx.supp -s ./$(NAME) $(MAP)

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@echo "$(YELLOW)Building MiniLibX...$(RESET)"
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR)includes -I$(MLX_DIR) -c $< -o $@

# **************************************************************************** #
#                              CLEANING RULES                                  #
# **************************************************************************** #

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)Object files cleaned.$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo "$(RED)$(NAME) removed.$(RESET)"; \
	fi
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all v clean fclean re