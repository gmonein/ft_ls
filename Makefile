# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 06:09:56 by gmonein           #+#    #+#              #
#    Updated: 2017/01/23 19:18:28 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

HEADER = ./includes/ \

DEB = deb

FLAGS =  -Wall -Werror -Wextra

GITFILES =  srcs \
			Makefile \

SRC = ./srcs/list_utils.c \
        srcs/misc.c \
        srcs/pars_param.c \
        srcs/print_info.c \
        srcs/print_patern.c \
        srcs/lib/ft_putnbr.c \
        srcs/lib/ft_stradd.c \
        srcs/lib/ft_strchr.c \
        srcs/lib/ft_strcmp.c \
        srcs/lib/ft_strdup.c \
        srcs/lib/ft_strlen.c \

all:
	gcc $(FLAGS) -I $(HEADER) $(SRC) -o $(NAME)
gps:
	@git add $(GITFILES); git commit -m"auto"; git push

gpl:
	@git pull

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(DEB)

re: fclean all 
