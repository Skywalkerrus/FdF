# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bantario <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/22 14:09:50 by bantario          #+#    #+#              #
#    Updated: 2019/12/23 15:32:43 by bantario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -Wall -Wextra -Werror  -I /usr/X11/include -g -L /usr/X11/lib -l mlx \
	-framework OpenGL -framework AppKit my_main.c \
	get_next_line.c draw_line.c  my_abs.c \
	mouse_click.c key_click.c libft/libft.a
