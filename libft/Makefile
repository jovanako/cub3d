# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkovacev <jkovacev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 17:22:11 by jkovacev          #+#    #+#              #
#    Updated: 2026/02/12 18:12:43 by jkovacev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[0;32m
BLUE  = \033[0;34m
RESET = \033[0m

NAME	= libft.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
DEPS	= libft.h

OBJ_DIR	= obj

SRCS	= ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_strlen.c \
		  ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_strtrim.c \
		  ft_itoa.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_strmapi.c \
		  ft_striteri.c \
		  ft_split.c \
		  error_handling.c


SRCS_BONUS	= ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_lstdelone.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Libft compiled!$(RESET)"

bonus: $(OBJS) $(OBJS_BONUS)
	@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)
	@echo "$(GREEN)Libft with Bonus compiled!$(RESET)"

$(OBJ_DIR)/%.o: %.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "$(BLUE)Cleaning Libft objects...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)Removing libft.a...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
