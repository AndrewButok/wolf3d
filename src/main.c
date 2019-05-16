/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:23:56 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 12:42:57 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		level_init(char *level_name, t_view *view)
{
	int		x;
	int		y;
	char	*start_ptr;

	view->map = get_map(level_name, &(view->map_height), &(view->map_width));
	if (view->map == NULL)
		return ;
	y = -1;
	while (++y < (int)view->map_height)
		if ((start_ptr = ft_strchr(view->map[y], MAP_START)) != NULL)
			break ;
	if (start_ptr != NULL)
		x = (start_ptr - view->map[y]) / sizeof(char);
	else
	{
		x = -1;
		y = -1;
	}
	view->player = (t_player*)malloc(sizeof(t_player));
	view->player->x = (double)x + 0.5;
	view->player->y = (double)y + 0.5;
	view->player->d = M_PI_2;
}

static void	view_init(t_view **view_ptr)
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
	level_init("test.map", view);
}

int			main(void)
{
	t_view		*view;
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
		{
			if ((event_iterator.type == SDL_KEYDOWN &&
				event_iterator.key.keysym.sym == SDLK_ESCAPE) ||
				(event_iterator.type == SDL_WINDOWEVENT &&
					event_iterator.window.event == SDL_WINDOWEVENT_CLOSE))
				exit_flag = 1;
			view->player->d += event_iterator.type != SDL_KEYDOWN ? 0 :
					(event_iterator.key.keysym.sym == SDLK_d ? 0.017 * 6 :
					 (event_iterator.key.keysym.sym == SDLK_a ? -0.017 * 6 : 0));
			draw_surface(view);
			SDL_UpdateWindowSurface(view->window);
		}
	}
	return (0);
}
