/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:26:45 by bantario          #+#    #+#             */
/*   Updated: 2019/12/22 20:18:34 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "libft/libft.h"
#include "get_next_line.h"

#define WIN_X 1000
#define WIN_Y 1000

# define O 0xFFFFFF
# define T 0x0E50BA
# define TH 0xC60707
# define F 0x8c0fc6
# define FI 0xe8930b
# define FV 0x04963e


typedef struct	s_point
{
	int	z;
	int	z0;
	int	xp;
	int	yp;
}	t_point;

typedef struct	s_coord
{
	int		x;
	int		y;
}	t_coord;

typedef struct    data_s
{
	void          *mlx_ptr;
	void          *mlx_win;
	void			*image;
	void			*data_addr;
	t_point			**map;
	t_coord			scale;
	t_coord	pos;
	int		height;
	int		width;
	int		alt;
	size_t	smallest;
	int		color;
	int		bts_pr_pxl;
	int		size_line;
	int		endian;
}					data_t;

int			mouse_click(int key, int x, int y, data_t *e);
int			my_abs(int numb);
void		draw_line(int x1, int y1, int x2, int y2, data_t *e);
void			lines_draw(data_t *data);
int				get_next_line(const int fd, char **line);
