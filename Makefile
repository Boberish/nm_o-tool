# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaylor <jaylor@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 09:35:25 by jaylor            #+#    #+#              #
#    Updated: 2018/12/04 16:30:56 by jaylor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

HEADERS = includes

CFLAGS += -I$(HEADERS) -Wall -Werror -Wextra -g -fsanitize=address 

FILESO =	main.o \
			nm.o \
			parsing.o \
			utilities.o \
			load_info.o \
			type_64.o \
			print.o \
			binary_tree.o \

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

all: $(NAME)

$(NAME): $(FILESO) $(LIBFT)
	gcc -o $(NAME) $^ $(CFLAGS)

%.o: srcs/%.c
	gcc -o $@ -c $< $(CFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(FILESO) 
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
