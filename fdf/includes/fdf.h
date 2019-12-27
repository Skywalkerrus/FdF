/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:26:45 by bantario          #+#    #+#             */
/*   Updated: 2019/12/23 15:34:07 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <math.h>

# define WIN_X 1000
# define WIN_Y 1000

# define O 0xFFFFFF
# define T 0x0E50BA
# define TH 0xC60707
# define F 0x8c0fc6
# define FI 0xe8930b
# define FV 0x04963e

typedef struct	s_point
{
	int			z;
	int			z0;
	int			xp;
	int			yp;
}				t_point;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*image;
	void		*data_addr;
	t_point		**map;
	t_coord		scale;
	t_coord		pos;
	int			height;
	int			width;
	int			alt;
	size_t		smallest;
	int			color;
	int			zoom;
}				t_data;

void			put_str_on_win(t_data *e);
int				key_click(int keycode, t_data *e);
int				mouse_click(int key, int x, int y, t_data *e);
int				my_abs(int numb);
void			draw_line(t_coord p1, t_coord p2, t_data *e);
void			lines_draw(t_data *data);
int				get_next_line(const int fd, char **line);
void			draw_map(t_data *data);
void			rot_x(t_data *data);
void			change_height(t_data *e, int c);
void			read_args(char *filepath, t_data *env);
void			parse_args(char *filepath, t_data *env);
void			errors(int numb);
void			smallest(t_data *e, int x, int y);
void			max_z(t_data *e, int x, int y);
void			def_coord(t_data *data);
void			change_height(t_data *e, int c);
void			draw_map(t_data *data);

#endif
