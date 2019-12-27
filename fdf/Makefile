# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bglinda <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 16:23:03 by bglinda           #+#    #+#              #
#    Updated: 2019/07/05 16:23:31 by bglinda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: all, $(NAME), clean, fclean, re

NAME = fdf

IDIR = ./includes/
INCS = libft.h	\
	   fdf.h \
	   get_next_line.h

SDIR = ./src/
SRCS = my_main.c get_next_line.c drawing.c mouse_click.c \
       my_abs.c read_map.c  key_click.c iso.c

SRCC = $(addprefix $(SDIR),$(SRCS))

OBJS = $(SRCS:.c=.o)

FLAG = -Wall -Werror -Wextra

$(NAME):
	@make fclean -C ./libft/ && make -C ./libft/
	gcc $(FLAG) -c $(SRCC) -I$(IDIR)
	gcc $(FLAG) $(OBJS) ./libft/libft.a -L/usr/local/lib/ \
	-I/usr/local/include -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	@make -C ./libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
