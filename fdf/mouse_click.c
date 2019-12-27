/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bantario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 19:09:35 by bantario          #+#    #+#             */
/*   Updated: 2019/12/25 20:02:33 by bantario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"



int		mouse_click(int key, int x, int y, data_t *e)
{
	if (key == 1 && x && y)
	{
		if (e->color == O)
			e->color = T;
		else if (e->color == T)
			e->color = TH;
		else if (e->color == TH)
			e->color = F;
		else if (e->color == F)
			e->color = FI;
		else if (e->color == FI)
			e->color = FV;
		else
			e->color = O;
		draw_map(e);
		//lines_draw(e);
	}
	else
		printf("mouse_click: %d\n", key);
	return (0);
}
