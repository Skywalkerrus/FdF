/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:55:14 by bantario          #+#    #+#             */
/*   Updated: 2019/12/25 20:29:11 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(int x1, int y1, int x2, int y2, data_t *e)
{
	int deltaX = my_abs(x2 - x1);
    int deltaY = my_abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
	mlx_pixel_put(e->mlx_ptr, e->mlx_win, x2, y2, e->color);
    while(x1 != x2 || y1 != y2) 
	{
		if (my_abs(x2) / 2 > my_abs(x1))
			e->color = TH;
		else if (my_abs(x2) / 2 < my_abs(x1))
			e->color = FV;
		mlx_pixel_put(e->mlx_ptr, e->mlx_win, x1, y1, e->color);
		const int error2 = error * 2;
        if (error2 > -deltaY) 
		{
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}
