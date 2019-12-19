/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/18 19:49:40 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// for Rinat
int		my_abs(int numb)
{
	if (numb < 0)
		return (numb * (-1));
	if (numb >= 0)
		return (numb);
	return (1);
}

static int		get_info(char *filepath, int c)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	fd = open(filepath, O_RDONLY);
	if (c == 1)
	{
		while (get_next_line(fd, &line) > 0)
			ret++;
		close(fd);
	}
	else
	{
		get_next_line(fd, &line);
		ret = ft_ctword(line, ' ');
		while (get_next_line(fd, &line) > 0)
			if (ft_ctword(line, ' ') != ret)
				return (1);
		close(fd);
	}
	return (ret);
}

void			parse_args(char *filepath, data_t *env)
{
	int index;

	index = 0;
	env->height = get_info(filepath, 1); //dlyna
	env->width = get_info(filepath, 2); // shirina
	env->map = (t_point **)malloc(sizeof(t_point *) * env->height);
	while (index < env->height)
	{
		env->map[index] = (t_point *)malloc(sizeof(t_point) * env->width);
		index++;
	}
}


static void	smallest(data_t *e, int x, int y, int c)
{
	size_t tmp;

	if (c == 0)
	{
		tmp = my_abs(e->map[y][x].z);
		if ((!e->smallest && tmp != 0) || (e->smallest > tmp && tmp != 0))
			e->smallest = tmp;
	}
	else
	{
		if (!e->smallest)
			e->smallest = 1;
		while (y < e->height)
		{
			while (x < e->width)
			{
				e->map[y][x].z /= e->smallest;
				e->map[y][x].z0 /= e->smallest;
				x++;
			}
			x = 0;
			y++;
		}
	}
}

void	read_args(char *filepath, data_t *env)
{
	int		fd;
	char	*line;
	char	**line_split;
	int		x;
	int		y;

	x = 0;
	y = 0;
	fd = open(filepath, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		line_split = ft_strsplit(line, ' ');
		//printf("\n");
		while (*line_split != NULL)
		{
			env->map[y][x].z = ft_atoi(*line_split);
			//printf("%d", env->map[y][x].z);
			smallest(env, x, y, 0);
			env->map[y][x].z0 = env->map[y][x].z;
			//printf("%d", env->map[y][x].z);
			x++;
			line_split++;
		}
		x = 0;
		y++;
	}
	close(fd);
	smallest(env, 0, 0, 1);
}

int		key_esc(int keycode)
{
	if (keycode == 53)
		exit (0);
	else
		return (0);
} // close when you press 'esc'

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

int		main(int ac, char **av)
{
	data_t        data;
	int x1, y1, x2, y2;

	if (ac > 0)
	{
		parse_args(av[1], &data);
		read_args(av[1], &data);
		x1 = 0;
		y1 = 0;
		x2 = 50;
		y2 = 50;
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "Hello world")) == NULL)
			return (EXIT_FAILURE);
		draw_line(x1, y1, x2, y2, data.mlx_ptr, data.mlx_win);
		mlx_key_hook(data.mlx_win, key_esc, 0);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
