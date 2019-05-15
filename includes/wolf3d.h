/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:24:44 by abutok            #+#    #+#             */
/*   Updated: 2019/05/14 12:43:58 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "libft.h"
# include "get_next_line.h"
# include <math.h>
# include <SDL.h>

/*
**	Screen params
*/
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 60

/*
**	Map marks
*/
# define MAP_WALL 'W'
# define MAP_PLAIN ' '
# define MAP_START 'S'

/*
**	Directions
*/
#define DIRECTION_NORTH 'N'
#define DIRECTION_SOUTH 'S'
#define DIRECTION_WEST 'W'
#define DIRECTION_EAST 'E'

enum						e_sector
{
	Wall = -1,
	Plain = 0
};

typedef struct				s_texture
{
	char				type;
	int					*texture;
}							t_texture;

typedef struct				s_player
{
	double				x;
	double				y;
	double				d;
}							t_player;

typedef struct				s_view
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	char				**map;
	size_t				map_height;
	size_t				map_width;
	t_player			*player;
	t_texture			*texture;
}							t_view;

char						**get_map(const char *filename, size_t *h,
	size_t *w);
void						draw_surface(t_view *view);
t_player					ray_cast(t_view *view, int angle);
int							check_map_intersection(t_view *view,
	t_player *player, t_player *rit);

#endif
