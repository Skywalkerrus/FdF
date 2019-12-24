#include "fdf.h"



static void		init_env(data_t *e)
{
	e->mlx_ptr = mlx_init();
	e->scale.x = 20;
	e->scale.y = -20;
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
	
	x = 0;
	y = 0;
	while(y < data->height)
	{
		x = 0;
		while(x < data->width)
		{
			data->map[y][x].xp = x * 50;
			data->map[y][x].yp = y * 50;
			x++;
		}
		y++;
	}
}

void draw_map(data_t *data)
{
	int x = 0;
	int y = 0;
	//t_coord point[2];
//	int x1;
//	int y1;
//	data->map[y][x].xp = data->pos.x;
//	data->map[y][x].yp = data->pos.y;
//	printf("x1 = %d\n",x1);
//	printf("y1 = %d\n",y1);
	def_coord(data);
	//mlx_clear_window(data->mlx_ptr, data->mlx_win);
	//int x1 = data->pos.x + data->map[y][x].xp;
	//int y1 = data->pos.y + data->map[y][x].yp;
	while(y < data->height)
	{
		x = 0;
		//data->map[y][x].xp =  data->pos.x;
		while(x < data->width)
		{
			if (y + 1 < data->height && data->map[y][x].z == 0 && data->map[y + 1][x].z == 0)
				draw_line(data->map[y][x].xp,data->map[y][x].yp,data->map[y + 1][x].xp,data->map[y + 1][x].yp,data);
			if (x + 1 < data->width && data->map[y][x].z == 0 && data->map[y][x + 1].z == 0)
				draw_line(data->map[y][x].xp,data->map[y][x].yp,data->map[y][x +1].xp,data->map[y][x + 1].yp,data);


//			if (y + 1 < data->height && data->map[y][x].z == 0 && data->map[y + 1][x].z == 0)
//				draw_line(x1,y1,x1,y1,data);
//			if (x + 1 < data->width && data->map[y][x].z == 0 && data->map[y][x + 1].z == 0)
//				draw_line(x1,y1,x1,y1,data);
			
			printf("{%d, %d}",data->map[y][x].yp,data->map[y][x].xp);
			x+=1;
		}
		printf("\n");
		y+=1;
		//x1 = data->pos.x;
	//	y1 += 50;
	}
}


int		main(int ac, char **av)
{
	data_t        data;
//
//	int i = 0;
//	int j = 0;
	if (ac == 2)
	{
		init_env(&data);
		parse_args(av[1], &data);
		read_args(av[1], &data);
		printf("data.height = %d\n",data.height);
		printf("data.width = %d\n",data.width);
//		while (j < data.height)
//		{
//			i = 0;
//			while (i < data.width)
//			{
//				printf("%d ",data.map[j][i].z);
//				i++;
//			}
//			printf("\n");
//			j++;
//		}
		if ((data.mlx_ptr = mlx_init()) == NULL)
			return (EXIT_FAILURE);
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 2000, 2000, "Hello world")) == NULL)
			return (EXIT_FAILURE);
		draw_map(&data);
		mlx_key_hook(data.mlx_win, key_esc, 0);
		mlx_loop(data.mlx_ptr);
	}
	return (EXIT_SUCCESS);
}
