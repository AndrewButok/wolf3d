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

static int 			is_drawable(t_view *view, t_vector *i, t_vector *v)
{
	int sign;

	if (i->x == floor(i->x))
	{
		sign = v->x > 0 ? -1 : 1;
		return (view->map[(int)floor(i->y)][(int)(i->x + sign)] == MAP_WALL ||
				view->map[(int)floor(i->y)][(int)i->x] == MAP_WALL);
	}
	sign = v->y > 0 ? -1 : 1;
	return (view->map[(int)(i->y + sign)][(int)floor(i->x)] == MAP_WALL ||
			view->map[(int)i->y][(int)floor(i->x)] == MAP_WALL);
}

static int			check_point_accessory(t_view *view, t_vector *i)
{
	return (i->x >= 0 && i->x <= view->map_width - 1 &&
			i->y >= 0 && i->y <= view->map_height - 1);
}

static void 		step(t_vector *position, t_vector *direction, double *d)
{
	t_vector	buf[2];
	double		dd[2];

	buf[0].x = direction->x > 0 ? floor(position->x + 1) :
			ceil(position->x - 1);
	buf[0].y = position->y + (direction->x > 0 ?
			(position->x - buf[0].x) :
			(buf[0].x - position->x)) * direction->x / direction->y;
	dd[0] = pow(buf[0].x - position->x, 2) +
			pow(buf[0].y - position->y, 2);
	buf[1].y = direction->y > 0 ? floor(position->y + 1) :
			ceil(position->y - 1);
	buf[1].y = position->x + (direction->y > 0 ?
			(position->y - buf[1].y) :
			(buf[1].y - position->y)) * direction->y / direction->x;
	dd[1] = pow(buf[1].x - position->x, 2) +
			pow(buf[1].y - position->y, 2);
	position->x = dd[0] < dd[1] ? buf[0].x : buf[1].x;
	position->y = dd[0] < dd[1] ? buf[0].y : buf[1].y;
	*d += sqrt((dd[0] < dd[1] ? dd[0] : dd[1]));

}

t_vector			ray_cast(t_view *view, t_vector *direction, double *d)
{
	t_vector iterator;

	iterator.vector = direction->vector + view->position.vector;
	*direction = normalize(*direction);
	//if ((*d = check_map_intersection(view, &iterator, direction)) == 0)
		while (check_point_accessory(view, &iterator) &&
			!is_drawable(view, &iterator, direction))
		{
			printf("k");
			step(&iterator, direction, d);
		}
	printf("%d\n", is_drawable(view, &iterator, direction));
	return	iterator;
}