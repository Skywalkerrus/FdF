/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bglinda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:56:45 by bglinda           #+#    #+#             */
/*   Updated: 2019/12/27 13:19:55 by bglinda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		max_z(t_data *e, int x, int y)
{
	size_t max_z;

	max_z = my_abs(e->map[y][x].z);
	if ((!e->smallest && max_z != 0) || (e->smallest > max_z && max_z != 0))
		e->smallest = max_z;
}

int			change_zoom(t_data *e)
{
	while (e->scale.x * e->width > WIN_X && e->scale.x > 0)
		e->scale.x -= 1;
	while (e->scale.y * e->height > WIN_Y && e->scale.y > 0)
		e->scale.y -= 1;
	if (e->scale.x < e->scale.y)
		e->zoom = e->scale.x;
	else
		e->zoom = e->scale.y;
	return (e->zoom);
}

void		def_coord(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			data->map[y][x].xp = ((cos(0.523599)
						* (x - y)) * data->zoom) + data->pos.x;
			data->map[y][x].yp = ((-data->map[y][x].z
					+ ((x + y) * sin(0.723599))) * data->zoom) + data->pos.y;
			x++;
		}
		y++;
	}
}

void		change_height(t_data *e, int c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < e->height)
	{
		while (x < e->width)
		{
			if (e->map[y][x].z0 != 0)
			{
				if (c == 1)
					e->map[y][x].z = e->map[y][x].z + e->map[y][x].z0 + 1;
				else
					e->map[y][x].z = e->map[y][x].z - e->map[y][x].z0 - 1;
				e->map[y][x].xp = ((cos(0.523599)
						* (x - y)) * e->zoom) + e->pos.x;
				e->map[y][x].yp = ((-e->map[y][x].z +
						((x + y) * sin(0.723599))) * e->zoom) + e->pos.y;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
