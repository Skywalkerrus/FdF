/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:53:30 by bantario          #+#    #+#             */
/*   Updated: 2019/12/27 19:09:45 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void		def_coord(data_t *data)
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
						* (x - y)) * 10) + data->pos.x;
			data->map[y][x].yp = ((-data->map[y][x].z
					+ ((x + y) * sin(0.723599))) * 10) + data->pos.y;
			x++;
		}
		y++;
	}
}

void	lines_draw(data_t *data)
{
	int y;
	int x;
	int i;
	int cx2;
	int cy2;
	static int j;

	y = 0;
	x = 0;
	i = 0;
	j = 0;
	cx2 = (data->pos.x - data->pos.y);
	cy2 = (data->pos.x + data->pos.y) / 2; 
	//def_coord(data);
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{	
			if (y + 1 < data->height && data->map[y][x].z == 0 && data->map[y + 1][x].z == 0)
				draw_line(cx2, cy2, cx2 - 30, cy2 + 15, data); //chetko
			if (x + 1 < data->width && data->map[y][x].z == 0 && data->map[y][x + 1].z == 0)
				draw_line(cx2, cy2, cx2 + 30, cy2, data);
			cx2 += 30;
			x++;
		}
		cx2 = (data->pos.x - (data->pos.y + 30 + i));
		cy2 = (data->pos.x + (data->pos.y + 30 + i)) / 2;
		i += 30;
		y++;
	}
mlx_string_put(data->mlx_ptr, data->mlx_win, 0 , 0, FV, ft_strjoin("Pos.x: ", ft_itoa(data->pos.x)));
mlx_string_put(data->mlx_ptr, data->mlx_win, 0 , 30, FV, ft_strjoin("Pos.y: ", ft_itoa(data->pos.y)));
}
