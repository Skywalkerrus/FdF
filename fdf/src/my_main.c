/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/23 15:30:07 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

void		init_list(t_data *e)
{
	e->scale.x = 30;
	e->scale.y = 30;
	e->pos.x = (int)WIN_X * 0.4;
	e->pos.y = (int)WIN_Y * 0.3;
	e->alt = 1;
	e->color = O;
	e->zoom = e->scale.x;
}

void		errors(int numb)
{
	if (numb == 1)
	{
		ft_putstr("Map is invalid\n");
		exit(1);
	}
	if (numb == 2)
	{
		ft_putstr("Invalid count of arguments.\n");
		exit(1);
	}
}

void		put_str_on_win(t_data *e)
{
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 0,
			e->color, ft_strjoin("Position X: ", ft_itoa(e->pos.x)));
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 30,
			e->color, ft_strjoin("Position Y: ", ft_itoa(e->pos.y)));
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 60,
			e->color, "Zoom: +/-");
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 90,
			e->color, "Change color: Left Mouse's Button ");
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 120,
			e->color, "Change position: <--/^/-->/v");
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 150,
			e->color, "Hight up/down: w/s");
	mlx_string_put(e->mlx_ptr, e->mlx_win, 0, 180, e->color, "Exit: 'Esc'");
}

int			main(int ac, char **av)
{
	t_data		data;

	if (ac != 2)
		errors(2);
	else
	{
		init_list(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr,
				WIN_X, WIN_Y, "FDF")) == NULL)
			return (EXIT_FAILURE);
		draw_map(&data);
		put_str_on_win(&data);
		mlx_key_hook(data.mlx_win, key_click, &data);
		mlx_mouse_hook(data.mlx_win, mouse_click, &data);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
