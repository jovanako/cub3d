# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 20:21:28 by jkovacev          #+#    #+#              #
#    Updated: 2026/02/17 11:37:04 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
BLUE  = \033[0;34m
RESET = \033[0m

NAME		= cub3d
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz

LIBFT_DIR	= libft
MLX_DIR		= mlx_linux
GNL_DIR		= get_next_line
PARSE_DIR	= parsing
TEX_DIR		= parsing/parse_tex/
OBJ_DIR		= obj

INCLUDES	= -I. -I$(LIBFT_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -I$(PARSE_DIR) -I$(TEX_DIR)

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a

SRCS		= main.c \
			  game_cleanup.c \
			  $(GNL_DIR)/get_next_line.c \
			  $(GNL_DIR)/get_next_line_utils.c \
			  $(TEX_DIR)/parse_color.c \
			  $(TEX_DIR)/parse_path.c \
			  $(TEX_DIR)/parse_rgb.c \
			  $(TEX_DIR)/parse_tex.c \
			  $(TEX_DIR)/rgb_cleanup.c \
			  $(PARSE_DIR)/handle_errors.c \
			  $(PARSE_DIR)/parse_file.c \
			  $(PARSE_DIR)/parse_grid.c \
			  $(PARSE_DIR)/parse_line.c \
			  $(PARSE_DIR)/set_player.c \
			  $(PARSE_DIR)/validate_map.c

OBJS		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
		@echo "$(BLUE)Linking $(NAME)...$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
		@echo "$(GREEN)Build successful!$(RESET)"

$(LIBFT):
		@echo "$(BLUE)Building Libft...$(RESET)"
		@make -C $(LIBFT_DIR) bonus --no-print-directory
	
$(MLX):
		@echo "$(BLUE)Building MLX...$(RESET)"
		@make -C $(MLX_DIR) --no-print-directory

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@echo "$(BLUE)Cleaning cub3d objects...$(RESET)"
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR) --no-print-directory
		@make clean -C $(MLX_DIR) --no-print-directory

fclean:
		@echo "$(BLUE)Deep cleaning project...$(RESET)"
		@rm -rf $(OBJ_DIR)
		@rm -f $(NAME)
		@make fclean -C $(LIBFT_DIR) --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus