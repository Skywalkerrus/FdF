/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 15:30:18 by bantario          #+#    #+#             */
/*   Updated: 2019/12/25 18:42:23 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_click_2(data_t *e)
{
	if (e->pos.y < -260  || e->pos.x > 1000)
	{
<<<<<<< HEAD
		e->pos.x = 0;
		//e->pos.y = 0;
=======
		e->pos.x = 130;
		e->pos.y = 610;
>>>>>>> 55ed0b2df74c838a9619390c7e24096ecb019e08
	}
	else if (e->pos.x < 130 || e->pos.y > 610)
	{
		e->pos.x = 900;
		e->pos.y = -200;
	}
	else if (e->pos.x < 160 || e->pos.y < -170)
	{
		e->pos.x = 1000;
		e->pos.y = 550;
	}
	else if (e->pos.x > 1000 || e->pos.y > 600)
	{
		e->pos.x = 160;
		e->pos.x = -170;
	}
	mlx_clear_window(e->mlx_ptr, e->mlx_win);
	//lines_draw(e);
	draw_map(e);
	return (0);
}

int		key_click(int keycode, data_t *e)
{
	if (keycode == 53)
		exit (0);
	else if (keycode == 126)
	{
		e->pos.y -= 30;
		//e->pos.x -= 30;
	}
	else if (keycode == 125)
	{
		e->pos.y += 30;
		//e->pos.x += 30;
	}
	else if (keycode == 124)
	{
		//e->pos.y -= 30;
		e->pos.x += 30;
	}
	else if (keycode == 123)
	{
		e->pos.x -= 30;
		//e->pos.y += 30;
	}
	else
		printf("key_code: %d\n", keycode);
		return (key_click_2(e));
}
