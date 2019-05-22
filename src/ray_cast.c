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
	int	x;
	int y;

	if (i->x != floor(i->x))
		x = (int)floor(i->x);
	else if (dir->x < 0)
		x = (int)(i->x - 1);
	else
		x = (int)(i->x);
	if (i->y != floor(i->y))
		y = (int)floor(i->y);
	else if (dir->y < 0)
		y = (int)(i->y - 1);
	else
		y = (int)(i->y);
	if (view->map[y][x] == MAP_WALL && i->x == x)
		return (DIRECTION_SOUTH);
	if (view->map[y][x] == MAP_WALL && i->x == x + 1)
		return (DIRECTION_NORTH);
	if (view->map[y][x] == MAP_WALL && i->y == y)
		return (DIRECTION_WEST);
	if (view->map[y][x] == MAP_WALL && i->y == y + 1)
		return (DIRECTION_EAST);
	return (-1);
}



static t_vector		step(t_vector *i, t_vector *direction, char v)
{
	t_vector	vec;

	vec = 0;
	if (v == 0 && direction->y != 0)
	{
		vec.x = ((direction->x > 0) ? floor(i->x + 1) : ceil(i->x - 1)) - i->x;
		vec.y = vec.x * direction->x / direction->y;
	}
	if (v == 1 && direction->x != 0)
	{
		vec.y = ((direction->y > 0) ? floor(i->y + 1) : ceil(i->y - 1)) - i->y;
		vec.x = vec.y * direction->y / direction->x;
	}
	return (vec);
}

static void			select_step(t_vector *i, t_vector *direction, double *dist)
{
	t_vector	dx;
	t_vector	dy;

	dx = step(i, direction, 0);
	dy = step(i, direction, 1);
	if ((dx.x == 0 && dx.y == 0) || length(dy) < length(dx))
	{
		*i += dy;
		*dist += length(dy);
	}
	if ((dy.x == 0 && dy.y == 0) || length(dy) >= length(dx))
	{
		*i += dx;
		*dist += length(dx);
	}
}

static int			check_point_accessory(t_view *view, t_vector *point)
{
	return (point->x >= 0 && point->x < view->map_width &&
			point->y >= 0 && point->y < view->map_height);
}

char				ray_cast(t_view *view, t_vector *direction, double *d)
{
	t_vector	i;
	double		vector_length;
	char		side;

	vector_length = *d;
	i = (*direction) * vector_length + view->position;
	*d = 0;
	side = 0;
	if (((*d) = check_map_intersection(view, &i, direction)) == 0)
		while (check_point_accessory(view, &i) &&
			(side = is_drawable(view, &i, direction)) == -1)
			select_step(&i, direction, d);
	*d *= vector_length;
	return (side);
}
