##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
## 
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
## 
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:44:41 2007 Olivier Crouzet
##

## Please use configure script


all	: do_configure
	gcc -Wall -Wextra -Werror  -I /usr/X11/include -g -L /usr/X11/lib -l mlx \
		-framework OpenGL -framework AppKit my_main.c

do_configure	:
	./configure

clean	:
	./configure clean

re	: clean all
