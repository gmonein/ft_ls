# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmonein <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 06:09:56 by gmonein           #+#    #+#              #
#    Updated: 2017/01/13 23:02:02 by gmonein          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = includes

SRC = ft_bzero.c \
	  ft_strcat.c \
	  ft_strcpy.c \
	  ft_memset.c \
	  ft_strlen.c \
	  ft_strnew.c \
	  ft_strjoin.c \
	  ft_memalloc.c \
	  ft_strchr.c \
	  ft_strdup.c \
	  ft_strsub.c \
	  ft_strdel.c \
	  ft_stradd.c \
	  ft_strcmp.c \

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $^ -I $(HEADER)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
