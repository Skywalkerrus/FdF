/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:fdf/fdf.h
/*   Created: 2019/12/18 16:26:45 by bantario          #+#    #+#             */
<<<<<<< HEAD:fdf/src/my_abs.c
/*   Updated: 2019/12/23 15:34:07 by bantario         ###   ########.fr       */
=======
/*   Created: 2019/12/22 16:07:07 by bantario          #+#    #+#             */
/*   Updated: 2019/12/27 13:14:18 by bglinda          ###   ########.fr       */
>>>>>>> Mrr:fdf/src/my_abs.c
=======
/*   Updated: 2019/12/25 17:31:44 by bantario         ###   ########.fr       */
>>>>>>> 55ed0b2df74c838a9619390c7e24096ecb019e08:fdf/fdf.h
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

<<<<<<< HEAD:fdf/fdf.h
#define WIN_X 1000
#define WIN_Y 1000

# define O 0xFFFFFF
# define T 0x0E50BA
# define TH 0xC60707
# define F 0x8c0fc6
# define FI 0xe8930b
# define FV 0x04963e


typedef struct	s_point
{
	int	z;
	int	z0;
	int	xp;
	int	yp;
}	t_point;

typedef struct	s_coord
{
	int		x;
	int		y;
}	t_coord;

typedef struct    data_s
{
	void          *mlx_ptr;
	void          *mlx_win;
	void			*mlx_win1;
	void			*image;
	void			*data_addr;
	t_point			**map;
	t_coord			scale;
	t_coord	pos;
	int		height;
	int		width;
	int		alt;
	size_t	smallest;
	int		color;
	int		bts_pr_pxl;
	int		size_line;
	int		endian;
}					data_t;

int			key_click(int keycode, data_t *e);
int			mouse_click(int key, int x, int y, data_t *e);
int			my_abs(int numb);
void		draw_line(int x1, int y1, int x2, int y2, data_t *e);
void			lines_draw(data_t *data);
int				get_next_line(const int fd, char **line);
void 			draw_map(data_t *data);
=======
int		my_abs(int numb)
{
	if (numb < 0)
		return (numb * (-1));
	if (numb >= 0)
		return (numb);
	return (1);
}
>>>>>>> Mrr:fdf/src/my_abs.c
