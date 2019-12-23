/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:53:30 by bantario          #+#    #+#             */
/*   Updated: 2019/12/23 20:57:39 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	lines_draw(data_t *data)
{
	int y;
	int x;
	int i;
	int cx2;
	int cy2;

	y = 0;
	x = 0;
	i = 0;
	cx2 = (data->pos.x - data->pos.y);
	cy2 = (data->pos.x + data->pos.y) / 2;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y + 1 < data->height && data->map[y][x].z == 0 && data->map[y + 1][x].z == 0)
				draw_line(cx2, cy2, cx2 - 30, cy2 + 15, data); //draw_line(cx2, cy2, cx2 - 30, cy2 - 15, data);
				//draw_line(cx, cy, cx, cy + 30, data);
			if (x + 1 < data->width && data->map[y][x].z == 0 && data->map[y][x + 1].z == 0)
				draw_line(cx2, cy2, cx2 + 30, cy2, data); //draw_line(cx2, cy2, cx2 + 30, cy2, data);
				//draw_line(cx, cy, cx + 30, cy, data);
			cx2 += 30; // cx2 += 30;
			x++;
		} 
		cx2 = (data->pos.x - (data->pos.y + 30 + i));
		cy2 = (data->pos.x + (data->pos.y + 30 + i)) / 2;
		i += 30;
		y++;
	}
}
