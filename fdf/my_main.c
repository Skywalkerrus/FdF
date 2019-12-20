/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/20 19:23:20 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		init_list(data_t *e)
{
	e->scale.x = 30;
	e->scale.y = -30;
	e->pos.x = 400;
	e->pos.y = 400;
	e->alt = 1;
	e->color = 0x0E50BA;
}

int		my_abs(int numb)
{
	if (numb < 0)
		return (numb * (-1));
	if (numb >= 0)
		return (numb);
	return (1);
}

void	invalid_map(int numb)
{
	if (numb == 1)
	{
		ft_putstr("Map is invalid\n");
		exit(1);
	}
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
				invalid_map(1);
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

static void		recalc_scale(data_t *e)
{
	while (e->scale.x * e->width > WIN_X && e->scale.x > 0)
		e->scale.x -= 1;
	while (e->scale.y * e->height < -WIN_Y && e->scale.y < 0)
		e->scale.y += 1;
	if (my_abs(e->scale.x) < my_abs(e->scale.y))
		e->scale.y = -(e->scale.x);
	else
		e->scale.x = -(e->scale.y);
}

int		main(int ac, char **av)
{
	data_t        data;
	int x1, y1, x2, y2;

	if (3 > ac > 0)
	{
		init_list(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		printf("scale x: %d\n", data.scale.x);
		printf("scale y: %d\n", data.scale.y);
		recalc_scale(&data);
		printf("scale x: %d\n", data.scale.x);
		printf("scale y: %d\n", data.scale.y);
		x1 = 0;
		y1 = 0;
		x2 = 50;
		y2 = 50;
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "Hello world")) == NULL)
			return (EXIT_FAILURE);
		draw_line(x1, y1, x2, y2, data.mlx_ptr, data.mlx_win);
		if ((data.image = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y)) == NULL)
			return(EXIT_FAILURE);
		data.data_addr = mlx_get_data_addr(data.image, &data.bts_pr_pxl, &data.size_line, &data.endian);
		printf("bts_pr_pxl: %d\n", data.bts_pr_pxl);
		printf("size_line: %d\n", data.size_line);
		printf("endian: %d\n", data.endian);
		mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.image, WIN_X, WIN_Y);
		mlx_key_hook(data.mlx_win, key_esc, 0);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
