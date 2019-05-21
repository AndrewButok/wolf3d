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
	t_vector	sp;
	t_vector	screen;
	double		d;
	double		wall_h;

	column = 0;
	screen = get_perpendicular(view->direction);
	while (column < WIN_WIDTH)
	{
		d = (column - (WIN_WIDTH / 2.0)) / WIN_WIDTH;
		sp.vector = (screen.vector * d * 2 * view->focal_distance *
				tan(FOV * M_PI / 180)) - view->position.vector;
		wall_h  = normalize(sp).y;
		d = 0;
		sp = ray_cast(view, &sp, &d);
		if (d > 0 && wall_h != 0)
		{
			wall_h = (WIN_HEIGHT * 0.6 / (d * wall_h));
			draw_column(view, (int)wall_h, column);
		}
		column++;
	}
}
