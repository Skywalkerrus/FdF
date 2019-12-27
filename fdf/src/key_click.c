/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:30:18 by bantario          #+#    #+#             */
/*   Updated: 2019/12/27 12:59:25 by bglinda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		key_click_2(int keycode, t_data *e)
{
	if (e->pos.x > WIN_X)
		e->pos.x = 0;
	else if (e->pos.y > WIN_Y)
		e->pos.y = 0;
	else if (e->pos.x < 0)
		e->pos.x = WIN_X;
	else if (e->pos.y < 0)
		e->pos.y = WIN_Y;
	if (keycode == 69)
		e->zoom += 2;
	if (keycode == 78)
		e->zoom -= 2;
	mlx_clear_window(e->mlx_ptr, e->mlx_win);
	draw_map(e);
	return (0);
}

int		key_click(int keycode, t_data *e)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 126)
		e->pos.y -= 30;
	else if (keycode == 125)
		e->pos.y += 30;
	else if (keycode == 124)
		e->pos.x += 30;
	else if (keycode == 123)
		e->pos.x -= 30;
	if (keycode == 91)
	{
		mlx_clear_window(e->mlx_ptr, e->mlx_win);
		draw_map(e);
	}
	if (keycode == 13)
		change_height(e, 1);
	if (keycode == 1)
		change_height(e, -1);
	return (key_click_2(keycode, e));
}
