/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:26:45 by bantario          #+#    #+#             */
/*   Updated: 2019/12/18 17:57:37 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "libft/libft.h"
#include "get_next_line.h"
#include <math.h>

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
	t_point			**map;
	t_coord			scale;
	t_coord	pos;
	int		height;
	int		width;
	int		alt;
	size_t	smallest;
	int		color;
}					data_t;

int		get_next_line(const int fd, char **line);
