/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:58:22 by bantario          #+#    #+#             */
/*   Updated: 2019/12/25 19:39:30 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void		init_list(data_t *e)
{
	e->scale.x = 30;
	e->scale.y = 30;
	e->pos.x = 400;
	e->pos.y = 400;
	e->alt = 1;
	e->color = TH;
}

void	errors(int numb)
{
	if (numb == 1)
	{
		ft_putstr("Map is invalid\n");
		exit(1);
	}
	if (numb == 2)
	{
		ft_putstr("No arguments.\n");
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
				errors(1);
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
			smallest(env, x, y, 0);
			env->map[y][x].z0 = env->map[y][x].z;
			x++;
			line_split++;
		}
		x = 0;
		y++;
	}
	close(fd);
	smallest(env, 0, 0, 1);
}

//static void		recalc_scale(data_t *e)
//{
//	while (e->scale.x * e->width > WIN_X && e->scale.x > 0)
//		e->scale.x -= 1;
//	while (e->scale.y * e->height < -WIN_Y && e->scale.y < 0)
//		e->scale.y += 1;
//	if (my_abs(e->scale.x) < my_abs(e->scale.y))
//		e->scale.y = -(e->scale.x);
//	else
//		e->scale.x = -(e->scale.y);
//}


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

int		win_close(data_t *e)
{
	(void)e;
	exit (0);
}

int		main(int ac, char **av)
{
	data_t        data;

	if (ac != 2)
		errors(2);
	else
	{
		init_list(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		recalc_scale(&data);
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, WIN_X, WIN_Y, "Hello world")) == NULL)
			return (EXIT_FAILURE);
<<<<<<< HEAD
		if ((data.image = mlx_new_image(data.mlx_ptr, WIN_X, WIN_Y)) == NULL)
			return(EXIT_FAILURE);
		data.data_addr = mlx_get_data_addr(data.image, &data.bts_pr_pxl, &data.size_line, &data.endian);
		draw_map(&data);
		//lines_draw(&data);
		mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.image, WIN_X, WIN_Y);
=======
		lines_draw(&data);
>>>>>>> 55ed0b2df74c838a9619390c7e24096ecb019e08
		mlx_key_hook(data.mlx_win, key_click, &data);
		mlx_mouse_hook(data.mlx_win, mouse_click, &data);
		mlx_hook(data.mlx_win, 17, 0, win_close, &data);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
