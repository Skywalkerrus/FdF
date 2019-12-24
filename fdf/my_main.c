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
		while (*line_split != NULL)
		{
			env->map[y][x].z = ft_atoi(*line_split);
			//smallest(env, x, y, 0);
			env->map[y][x].z0 = env->map[y][x].z;
			
			x++;
			line_split++;
			//printf("%s", *line_split);
		}
		//printf("\n");
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
	mlx_pixel_put(mlx_ptr, mlx_win, x2, y2, 181550);
    while(x1 != x2 || y1 != y2) 
	{
		mlx_pixel_put(mlx_ptr, mlx_win, x1, y1, 181560);
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
	while (e->scale.x * e->width > 1000 && e->scale.x > 0)
		e->scale.x -= 1;
	while (e->scale.y * e->height < -1000 && e->scale.y < 0)
		e->scale.y += 1;
	if (my_abs(e->scale.x) < my_abs(e->scale.y))
		e->scale.y = -(e->scale.x);
	else
		e->scale.x = -(e->scale.y);
}

void			draw_lines(data_t *e, int x, int y)
{
	t_coord p[2];
	
	p[0].x = e->map[y][x].xp+e->pos.x;
	p[0].y = e->map[y][x].yp+e->pos.y;
	if (x < e->width - 1)
	{
		p[1].x = e->map[y][x + 1].xp+e->pos.x;
		p[1].y = e->map[y][x + 1].yp+e->pos.y;
		draw_line(p[0].x,p[0].y,p[1].x,p[1].y,e->mlx_ptr,e->mlx_win);
	}
	if (y < e->height - 1)
	{
		p[1].x = e->map[y + 1][x].xp+e->pos.x;
		p[1].y = e->map[y + 1][x].yp+e->pos.y;
		draw_line(p[0].x,p[0].y,p[1].x,p[1].y,e->mlx_ptr,e->mlx_win);
	}
}

static int	proj_x(int x, int y, data_t *e)
{
	double ret;
	
	ret = (cos(0.523599) * (x - y));
	ret *=  e->scale.x;
	return ((int)ret);
}

static int	proj_y(int x, int y, data_t *e)
{
	double ret;
	
	ret = -e->map[y][x].z + ((x + y) * sin(0.723599));
	ret *= -e->scale.y;
	return ((int)ret);
}


void		apply_proj(data_t *e)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while (y < e->height)
	{
		while (x < e->width)
		{
			e->map[y][x].xp = proj_x(x, y, e);
			e->map[y][x].yp = proj_y(x, y, e);
			x++;
		}
		x = 0;
		y++;
	}
}

void			draw_again(data_t *e)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	apply_proj(e);
	mlx_clear_window(e->mlx_ptr, e->mlx_win);
	while (y < e->height)
	{
		while (x < e->width)
		{
			draw_lines(e, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}


static void		init_env(data_t *e)
{
	e->mlx_ptr = mlx_init();
	e->scale.x = 20;
	e->scale.y = -20;
	e->pos.x = 400;
	e->pos.y = 400;
}

int		main(int ac, char **av)
{
	data_t        data;
	
	int i = 0;
	int j = 0;
	if (ac == 2)
	{
		init_env(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		while (j < data.height)
		{
			i = 0;
			while (i < data.width)
			{
				printf("%d ",data.map[j][i].z);
				i++;
			}
			printf("\n");
			j++;
		}

		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		recalc_scale(&data);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1000, 1000, "Hello world")) == NULL)
			return (EXIT_FAILURE);
		draw_again(&data);
		mlx_key_hook(data.mlx_win, key_esc, 0);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
