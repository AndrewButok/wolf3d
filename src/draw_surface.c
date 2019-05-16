/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:37:18 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 13:15:08 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_column(t_view *view, int wall_h, int column)
{
	int		not_draw;
	int		i;
	int		*pixels;

	i = -1;
	not_draw = (WIN_HEIGHT - wall_h) / 2;
	pixels = (int*)view->surface->pixels;
	while (++i < WIN_HEIGHT)
	{
		if (i < not_draw || i > (wall_h + not_draw))
			pixels[i * WIN_WIDTH + column] = 0;
		else
			pixels[i * WIN_WIDTH + column] = 0xff;
	}
}

void			draw_surface(t_view *view)
{
	int			column;
	double		angle;
	t_player	point;
	int			wall_h;
	double		delme;

	column = 0;
	while (column < WIN_WIDTH)
	{
		angle = atan2(((double)column) / WIN_WIDTH - 0.5, 0.6);
		point = ray_cast(view, angle + view->player->d);
		delme = (point.d * cos(angle));
		if (delme != 0)
		{
			wall_h = (int) (WIN_HEIGHT * 0.6 / delme);
			draw_column(view, wall_h, column);
		}
		column++;
	}
}
