/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bglinda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 17:56:45 by bglinda           #+#    #+#             */
/*   Updated: 2019/12/26 17:56:47 by bglinda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		max_z(data_t *e, int x, int y)
{
	size_t max_z;
	
	max_z = my_abs(e->map[y][x].z);
	if ((!e->smallest && max_z != 0) || (e->smallest > max_z && max_z != 0))
		e->smallest = max_z;
}

int			change_zoom(data_t *e)
{
	int zoom;
	
	while (e->scale.x * e->width > WIN_X && e->scale.x > 0)
		e->scale.x -= 1;
	while (e->scale.y * e->height > WIN_Y && e->scale.y > 0)
		e->scale.y -= 1;
	if (e->scale.x < e->scale.y)
		zoom = e->scale.x;
	else
		zoom = e->scale.y;
	return (zoom);
}

void		def_coord(data_t *data)
{
	int x;
	int y;
	int zoom;
	
	x = 0;
	y = 0;
	zoom = change_zoom(data);
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			data->map[y][x].xp = ((cos(0.523599)
								   * (x - y)) * zoom) + data->pos.x;
			data->map[y][x].yp = ((-data->map[y][x].z + ((x + y)
														 * sin(0.723599))) * zoom) + data->pos.y;
			x++;
		}
		y++;
	}
}

void		change_height(data_t *e, int c)
{
	int x;
	int y;
	int zoom;
	
	x = 0;
	y = 0;
	zoom = change_zoom(e);
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
				e->map[y][x].xp = ((cos(0.523599) * (x - y)) * zoom) + e->pos.x;
				e->map[y][x].yp = ((-e->map[y][x].z +
									((x + y) * sin(0.723599))) * zoom) + e->pos.y;
			}
			x++;
		}
		x = 0;
		y++;
	}
}