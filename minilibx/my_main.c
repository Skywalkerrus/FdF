/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/12 19:20:18 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct    data_s
{
	void          *mlx_ptr;
	void          *mlx_win;
} data_t;

int main(void)
{
	data_t        data;
	int	x;
	int	y;
	int color;

	x = y = 0;
	color = 181530;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
	    return (EXIT_FAILURE);
	while (x < 30)
	{
		mlx_pixel_put(data.mlx_ptr, data.mlx_win, x, y, 181530);
		x++;
		y++;
	}
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
