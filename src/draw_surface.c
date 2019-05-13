/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:37:18 by abutok            #+#    #+#             */
/*   Updated: 2019/05/13 16:09:55 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		step(t_player *position, int angle)
{
	t_player	buf[2];
	double		dx;
	double		dy;

	buf[0].x = sin(angle) > 0 ? ceil(position->x) : floor(position->x);
	buf[0].y = position->y + (sin(angle) > 0 ?
		(position->x - floor(position->x)) :
		(ceil(position->x) - position->x)) * tan(angle);
	buf[0].d = sqrt(pow(buf[0].x + position.x, 2) +
		pow(buf[0].y + position.y, 2));
	buf[1].y = cos(angle) > 0 ? ceil(position->y) : floor(position->y);
	buf[1].x = position->x + (cos(angle) > 0 ?
		(position->y - floor(position->y)) :
		(ceil(position->y) - position->y)) * tan(M_PI_2 - angle);
	buf[1].d = sqrt(pow(buf[1].x + position.x, 2) +
			pow(buf[0].y + position.y, 2));
	position->x = buf[0].d < buf[1].d ? buf[0].x : buf[1].x;
	position->y = buf[0].d < buf[1].d ? buf[0].y : buf[1].y;
	position->d += buf[0].d < buf[1].d ? buf[0].d : buf[1].d;
}

static double	ray_cast(const t_player *player, int angle)
{
	t_player	rit;

	rit = *player;
	rit.d = 0;
	step(&rit);
	if ((rit.d = check_map_intersection(view, player, &rit)) == 0)
		while (!check_point())
		{
			step(&rit);
		}
	return (rit.d);
}

void			draw_surface(t_view *view)
{
	int		column;
	double	angle;
	double	distance;

	column = 0;
	while (column < WIN_WIDTH)
	{
		angle = atan2(((double)column) / WIN_WIDTH - 0.5, 0.2);
		distance = ray_cast(view, &(view->player), angle);
		column++;
	}
}
