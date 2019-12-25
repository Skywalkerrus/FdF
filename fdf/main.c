/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bglinda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 14:34:11 by bglinda           #+#    #+#             */
/*   Updated: 2019/12/25 14:34:13 by bglinda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		init_env(data_t *e)
{
	e->mlx_ptr = mlx_init();
	e->scale.x = 20;
	e->scale.y = 20;
	e->pos.x = 400;
	e->pos.y = 400;
}

int		my_abs(int numb)
{
	if (numb < 0)
		return (numb * (-1));
	if (numb >= 0)
		return (numb);
	return (1);
}

int		key_esc(int keycode)
{
	if (keycode == 53)
		exit (0);
	else
		return (0);
} // close when you press 'esc'


int	recalc_scale(data_t *e)
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


void	draw_line(int x1, int y1, int x2, int y2, data_t *e)
{
	int deltaX = my_abs(x2 - x1);
	int deltaY = my_abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	mlx_pixel_put(e->mlx_ptr, e->mlx_win, x2, y2, 181530);
	while(x1 != x2 || y1 != y2)
	{
		mlx_pixel_put(e->mlx_ptr, e->mlx_win, x1, y1, 181530);
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

void def_coord(data_t *data)
{
	int x;
	int y;
	int zoom;
	
	x = 0;
	y = 0;
	zoom = recalc_scale(data);
	printf("zoom = %d\n", zoom);
	while(y < data->height)
	{
		x = 0;
		while(x < data->width)
		{
			//data->map[y][x].z *= zoom;
			data->map[y][x].xp = ((cos(0.523599) * (x - y)) * zoom) + data->pos.x ;
			data->map[y][x].yp = ((-data->map[y][x].z + ((x + y) * sin(0.723599))) * zoom) + data->pos.y;
			x++;
		}
		y++;
	}
}

void draw_map(data_t *data)
{
	int x = 0;
	int y = 0;

	def_coord(data);
	while(y < data->height)
	{
		x = 0;
		while(x < data->width)
		{
			if (y + 1 < data->height)
				draw_line(data->map[y][x].xp,data->map[y][x].yp,data->map[y + 1][x].xp,data->map[y + 1][x].yp,data);
			if (x + 1 < data->width)
				draw_line(data->map[y][x].xp,data->map[y][x].yp,data->map[y][x +1].xp,data->map[y][x + 1].yp,data);
			printf("{%d,%d,%d}",data->map[y][x].yp,data->map[y][x].xp,data->map[y][x].z);
			x+=1;
		}
		printf("\n");
		y+=1;
	}
}


int		main(int ac, char **av)
{
	data_t        data;
	
	if (ac == 2)
	{
		init_env(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "Hello world")) == NULL)
			return (EXIT_FAILURE);
		draw_map(&data);
		mlx_key_hook(data.mlx_win, key_esc, 0);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
