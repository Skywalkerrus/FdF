#include "fdf.h"


int get_height(char *argv)
{
	int fd;
	int height;
	char *line;
	
	height = 0;
	fd = open(argv, O_RDONLY);
	while(get_next_line(fd, &line) > 0)
		height++;
	close(fd);
	return (height);
}

int get_width(char *argv)
{
	int fd;
	int width;
	char *line;
	
	width = 0;
	fd = open(argv, O_RDONLY);
	get_next_line(fd,&line);
	width = ft_ctword(line,' ');
//	while (get_next_line(fd, &line) > 0)
//		if (ft_ctword(line, ' ') != width)
//			return (1);
	close(fd);
	return (width);
}

void			parse_args(char *filepath, data_t *env)
{
	int index;
	
	index = 0;
	env->height = get_height(filepath);
	env->width = get_width(filepath);
	env->map = (t_point **)malloc(sizeof(t_point *) * env->height);
	while (index < env->height)
	{
		env->map[index] = (t_point *)malloc(sizeof(t_point) * env->width);
		index++;
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
		x = 0;
		line_split = ft_strsplit(line, ' ');
		while (*line_split != NULL)
		{
			env->map[y][x].z = ft_atoi(*line_split);
			x++;
			line_split++;
		}
		y++;
	}
	close(fd);
}

