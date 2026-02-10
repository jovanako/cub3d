# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 20:21:28 by jkovacev          #+#    #+#              #
#    Updated: 2026/02/10 20:56:16 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

OBJS		= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@make clean -C $(LIBFT_DIR)
		rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re