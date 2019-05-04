/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:23:56 by abutok            #+#    #+#             */
/*   Updated: 2019/05/04 22:51:12 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void 	view_init(t_view **view_ptr)
{
	t_view		*view;

	errno = 0;
	view = (t_view*)malloc(sizeof(t_view));
	if (errno != 0)
	{
		perror("View malloc error.");
		return ;
	}
	*view_ptr = view;
	view->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	view->surface = SDL_GetWindowSurface(view->window);
}

int		main(void)
{
	t_view 		*view;
	SDL_Event	event_iterator;
	int			exit_flag;

	view = NULL;
	view_init(&view);
	if (view == NULL)
		return (-1);
	exit_flag = 0;
	while (!exit_flag)
	{
		while (SDL_PollEvent(&event_iterator))
			if ((event_iterator.type == SDL_KEYDOWN &&
				event_iterator.key.keysym.sym == SDLK_ESCAPE) ||
				(event_iterator.type == SDL_WINDOWEVENT &&
					event_iterator.window.event == SDL_WINDOWEVENT_CLOSE))
					exit_flag = 1;
			else if (event_iterator.type == SDL_WINDOWEVENT_EXPOSED)
				SDL_UpdateWindowSurface(view->window);
	}
	return (0);
}
