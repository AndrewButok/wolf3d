/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:59:04 by abutok            #+#    #+#             */
/*   Updated: 2019/05/13 16:38:11 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	check_vector_section_intersection(t_player *vo, t_player *vv,
	t_player *so, t_player *se)
{
	double x;
	double y;

	x = ((vv->x - vo->x) * (so->x * se->y  - se->x * so->y) +
		(se->x - so->x) * (vv->x * vo->y - vo->x * vv->y)) /
		((se->y - so->y) * (vv->x - vo->x) - (se->x - so->x) * (vv->y - vo->y));
	if (x < so->x || x > se->x)
		return(0);
	y = ((se->y - so->y) * x + se->x * so->y - se->y * so->x) /
		(se->x - so->x)
	if ((so->y < se-> y && (y < so->y || y > se->y)) ||
		(so->y > se-> y && (y < se->y || y > so->y))
		return (0);
	return (1);
}

int	check_map_intersection(t_player *vo, t_player *vv)
{
	int			r;
	t_player	so;
	t_player	se;

	so.x = 0;
	so.y = 0;
	se.x = view->map_width;
	se.y = view->map_height;
	r = check_vector_section_intersection(vo, vv, &so, &se);
	if (r)
		return r;
	so.x = 0;
	so.y = 0;
	se.x = view->map_width;
	se.y = view->map_height;
	r = check_vector_section_intersection(vo, vv, &so, &se);
	return (r);
}
