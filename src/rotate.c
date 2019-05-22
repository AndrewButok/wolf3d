/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:23:56 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 12:42:57 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_vector		rotate(t_vector vector, double angle)
{
	t_vector new_vector;

	new_vector = 0;
	new_vector.x = vector.x * cos(angle) - vector.y * sin(angle);
	new_vector.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (new_vector);
}

void				move(t_view *view, SDL_Event *event)
{
	SDL_Keycode  *kk;

	if (event->type == SDL_KEYDOWN)
	{
		kk = &(event->key.keysym.sym);
		if (*kk == SDLK_d || *kk == SDLK_a)
			view->direction = *kk == SDLK_d ? rotate(view->direction, 0.017) :
					rotate(view->direction, -0.017);
	}
}
