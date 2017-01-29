# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 06:09:56 by gmonein           #+#    #+#              #
#    Updated: 2017/01/29 15:17:17 by gmonein          ###   ########.fr        #
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
        srcs/lib/ft_strnew.c \
        srcs/lib/ft_strsplit.c \
        srcs/lib/ft_strsub.c \
        srcs/lib/ft_bzero.c \
        srcs/lib/ft_memset.c \
        srcs/lib/ft_memalloc.c \
        srcs/lib/ft_strjoin.c \
		new_ls.c \

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

test: all
	@echo "------------------------------------------------------------------"
	./ft_ls -l
	@echo "------------------------------------------------------------------"
	./ft_ls -r
	@echo "-------------------------------------------------------------------"
	./ft_ls -l includes
	@echo "-------------------------------------------------------------------"
	./ft_ls -l includes Makefile ft_ls
	@echo "-------------------------------------------------------------------"
	./ft_ls -C includes Makefile ft_ls
	@echo "-------------------------------------------------------------------"
	./ft_ls -C includes Makefile ft_ls | cat -e
	@echo "-------------------------------------------------------------------"

re: fclean all 
