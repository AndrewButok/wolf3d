/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 11:17:53 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 12:42:37 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		is_drawable(t_view *view, t_player *rit, t_player *ritp)
{
	int x;
	int y;

	x = (int)floor(rit->x > ritp->x ? ritp->x : rit->x);
	y = (int)floor(rit->y > ritp->y ? ritp->y : rit->y);
	if (rit->x == floor(rit->x))
		x = (int)rit->x;
	if (rit->y == floor(rit->y))
		y = (int)rit->y;
	return (view->map[y][x] == MAP_WALL);
}

static int		check_point_accesory(t_view *view, t_player *point)
{
	return (point->x >= 0 && point->x < view->map_width &&
			point->y >= 0 && point->y < view->map_height);
}

static void		step(t_player *position, double angle)
{
	t_player	buf[2];

	buf[0].x = sin(angle) > 0 ? floor(position->x + 1) : ceil(position->x - 1);
	buf[0].y = position->y + (sin(angle) > 0 ?
		(position->x - buf[0].x) :
		(buf[0].x - position->x)) * tan(angle);
	buf[0].d = pow(buf[0].x - position->x, 2) +
		pow(buf[0].y - position->y, 2);
	buf[1].y = cos(angle) > 0 ? floor(position->y + 1) : ceil(position->y - 1);
	buf[1].x = position->x + (cos(angle) > 0 ?
		(position->y - buf[1].y) :
		(buf[1].y - position->y)) * tan(M_PI_2 - angle);
	buf[1].d = pow(buf[1].x - position->x, 2) +
		pow(buf[1].y - position->y, 2);
	position->x = buf[0].d < buf[1].d ? buf[0].x : buf[1].x;
	position->y = buf[0].d < buf[1].d ? buf[0].y : buf[1].y;
	position->d += sqrt((buf[0].d < buf[1].d ? buf[0].d : buf[1].d));
}

t_player		ray_cast(t_view *view, double angle)
{
	t_player	rit;
	t_player	ritp;

	rit = *(view->player);
	ritp = rit;
	rit.d = 0;
	step(&rit, angle);
	if ((rit.d = check_map_intersection(view, &ritp, &rit)) == 0)
		while (check_point_accesory(view, &rit) &&
			!is_drawable(view, &rit, &ritp))
		{
			ritp = rit;
			step(&rit, angle);
		}
	return (rit);
}
