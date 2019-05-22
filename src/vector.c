/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 21:37:18 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 13:15:08 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double		dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double		length(t_vector v)
{
	return (sqrt(dot(v, v)));
}

t_vector	normalize(t_vector v)
{
	v = v / length(v);
	return (v);
}

t_vector	perpendicular_2d(t_vector v)
{
	t_vector result;

	result = (t_vector){0};
	if (length(v) != 1)
		v = normalize(v);
	result.x = -v.y;
	result.y = v.x;
	return (result);
}
