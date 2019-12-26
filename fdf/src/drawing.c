/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:55:14 by bantario          #+#    #+#             */
/*   Updated: 2019/12/22 19:30:41 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_line(t_coord p1, t_coord p2,data_t *e)
{
	int mass[6];
	
	mass[0] = my_abs(p2.x - p1.x); // deltaX
	mass[1] = my_abs(p2.y - p1.y); // daltayY
	mass[2] = p1.x < p2.x ? 1 : -1; // signX
	mass[3] = p1.y < p2.y ? 1 : -1; // signY
	mass[4] = mass[0] - mass[1]; // error1
	mlx_pixel_put(e->mlx_ptr, e->mlx_win, p2.x, p2.y, e->color);
	while(p1.x != p2.x || p1.y != p2.y)
	{
		mlx_pixel_put(e->mlx_ptr, e->mlx_win, p1.x, p1.y, e->color);
		mass[5] = mass[4] * 2; // error2
		if (mass[5] > -mass[1])
		{
			mass[4] -= mass[1];
			p1.x += mass[2];
		}
		if (mass[5] < mass[0])
		{
			mass[4] += mass[0];
			p1.y += mass[3];
		}
	}
}

void draw_lines(data_t *data, int x,int y)
{
	t_coord p[2];
	
	p[0].x = data->map[y][x].xp;
	p[0].y = data->map[y][x].yp;
	if (y < data->height -1)
	{
		p[1].x = data->map[y + 1][x].xp;
		p[1].y = data->map[y + 1][x].yp;
		draw_line(p[0],p[1],data);
	}
	if (x < data->width - 1)
	{
		p[1].x = data->map[y][x + 1].xp;
		p[1].y = data->map[y][x + 1].yp;
		draw_line(p[0],p[1],data);
	}
	
}

void		draw_map(data_t *data)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	def_coord(data);
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			draw_lines(data,x,y);
			x += 1;
		}
		y += 1;
	}
	put_str_on_win(data);
}
