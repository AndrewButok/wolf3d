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

static void		draw_column(t_view *view, int wall_h, int column, char wall)
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
		else if (wall == DIRECTION_NORTH)
			pixels[i * WIN_WIDTH + column] = 0xff;
		else if (wall == DIRECTION_SOUTH)
			pixels[i * WIN_WIDTH + column] = 0xff0ff;
		else if (wall == DIRECTION_EAST)
			pixels[i * WIN_WIDTH + column] = 0xff00;
		else if (wall == DIRECTION_WEST)
			pixels[i * WIN_WIDTH + column] = 0xff0000;
	}
}

void			draw_surface(t_view *view)
{
	int			column;
	t_vector	sp;
	t_vector	screen;
	double		d;
	int			wall_h;
	char 		delme;

	column = 0;
	screen = perpendicular_2d(view->direction);
	while (column < WIN_WIDTH)
	{
		d = (column - (WIN_WIDTH / 2.0)) / WIN_WIDTH;
		sp = view->focal_distance * (view->direction + 2 * d * screen *
				tan(M_PI / 6) / WIN_WIDTH);
		d = length(sp);
		sp = normalize(sp);
		delme = ray_cast(view, &sp, &d);
		if (d > 0 && sp.y != 0)
		{
			wall_h = (int)(WIN_HEIGHT * 1 / (d));
			draw_column(view, wall_h, column, delme);
		}
		column++;
	}
}
