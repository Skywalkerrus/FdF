/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/17 19:46:17 by bantario         ###   ########.fr       */
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

int		key_esc(int keycode)
{
	if (keycode == 53)
		exit (0);
	else if (data.mlx_ptr == NULL || data.mlx_win == NULL)
		return (0);
	else
		return (0);
} // close when you press 'esc'

int		my_abs(int numb)
{
	if (numb < 0)
		return (numb * (-1));
	if (numb >= 0)
		return (numb);
	return (1);
}

static void	draw_line(int x1, int y1, int x2, int y2, data_t *mlx_ptr, data_t *mlx_win)
{
	int deltaX = my_abs(x2 - x1);
    int deltaY = my_abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
	mlx_pixel_put(mlx_ptr, mlx_win, x2, y2, 181530);
    while(x1 != x2 || y1 != y2) 
   {
		mlx_pixel_put(mlx_ptr, mlx_win, x1, y1, 181530);
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
int		main(void)
{
	data_t        data;
	int x1, y1, x2, y2;

	x1 = 0;
	y1 = 0;
	x2 = -1050;
	y2 = -1050;
	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
	    return (EXIT_FAILURE);
	draw_line(x1, y1, x2, y2, data.mlx_ptr, data.mlx_win);
	mlx_key_hook(data.mlx_win, key_esc, 0);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
