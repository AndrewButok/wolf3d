/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:37:18 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 13:15:08 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int			is_drawable(t_view *view, t_vector *i, t_vector *dir)
{
	int	xs;
	int	ys;

	xs = dir->x > 0 ? 1 : -1;
	ys = dir->y > 0 ? 1 : -1;
	if (i->x == floor(i->x))
	{
		return (view->map[(int)(floor(i->y))][(int)(i->x + xs)] == MAP_WALL ||
				view->map[(int)(floor(i->y))][(int)(i->x)] == MAP_WALL);
	}
	return (view->map[(int)(i->y + ys)][(int)(floor(i->x))] == MAP_WALL ||
		view->map[(int)(i->y)][(int)(floor(i->x))] == MAP_WALL);
}

static void			step(t_vector *i, t_vector *direction, double *dist)
{
	t_vector	b[2];
	double		n_dist[2];

	b[0].x = direction->x > 0 ? floor(i->x + 1) : ceil(i->x - 1);
	b[0].y = i->y + (direction->x > 0 ?
						(i->x - b[0].x) :
						(b[0].x - i->x)) * direction->x / direction->y;
	n_dist[0] = pow(b[0].x - i->x, 2) +
			pow(b[0].y - i->y, 2);
	b[1].y = direction->y > 0 ? floor(i->y + 1) : ceil(i->y - 1);
	b[1].x = i->x + (direction->y > 0 ?
						(i->y - b[1].y) :
						(b[1].y - i->y)) * direction->y / direction->x;
	n_dist[1] = pow(b[1].x - i->x, 2) +
			pow(b[1].y - i->y, 2);
	i->x = n_dist[0] < n_dist[1] ? b[0].x : b[1].x;
	i->y = n_dist[0] < n_dist[1] ? b[0].y : b[1].y;
	*dist += sqrt((n_dist[0] < n_dist[1] ? n_dist[0] : n_dist[1]));
}

static int			check_point_accesory(t_view *view, t_vector *point)
{
	return (point->x >= 0 && point->x < view->map_width &&
			point->y >= 0 && point->y < view->map_height);
}

void				ray_cast(t_view *view, t_vector *direction, double *d)
{
	t_vector	i;

	i = (*direction) * (*d) + view->position;
	*d = 0;
	if (((*d) = check_map_intersection(view, &i, direction)) == 0)
		while (check_point_accesory(view, &i) &&
			!is_drawable(view, &i, direction))
		{
			step(&i, direction, d);
		}
}
