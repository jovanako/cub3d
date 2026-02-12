# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 20:21:28 by jkovacev          #+#    #+#              #
#    Updated: 2026/02/12 17:11:12 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
BLUE  = \033[0;34m
RESET = \033[0m

NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
GNL_DIR		= get_next_line
PARSE_DIR	= parsing
OBJ_DIR		= obj

INCLUDES	= -I. -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PARSE_DIR)

SRCS		= main.c \
			  $(GNL_DIR)/get_next_line.c \
			  $(GNL_DIR)/get_next_line_utils.c \
			  $(PARSE_DIR)/error_handling.c \
			  $(PARSE_DIR)/parsing.c \
			  $(PARSE_DIR)/path_parsing.c \
			  $(PARSE_DIR)/tex_parsing.c \
			  $(PARSE_DIR)/color_parsing.c \
			  $(PARSE_DIR)/validation.c

OBJS		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@echo "$(BLUE)Linking $(NAME)...$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Build successful!$(RESET)"

$(LIBFT):
		@echo "$(BLUE)Building Libft...$(RESET)"
		@make -C $(LIBFT_DIR) bonus --no-print-directory

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@echo "$(BLUE)Cleaning cub3d objects...$(RESET)"
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR) --no-print-directory

fclean:
		@echo "$(BLUE)Deep cleaning project...$(RESET)"
		@rm -rf $(OBJ_DIR)
		@rm -f $(NAME)
		@make fclean -C $(LIBFT_DIR) --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus