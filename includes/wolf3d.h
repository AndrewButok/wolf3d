/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:24:44 by abutok            #+#    #+#             */
/*   Updated: 2019/05/04 22:53:06 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
#define WOLF3D_H
#include "libft.h"
#include "get_next_line.h"
#include <SDL.h>
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

enum						e_sector
{
	Wall = -1,
	Start = 0
};

typedef struct				s_texture
{
	enum e_sector		type;
	int					*texture;
}							t_texture;

typedef struct				s_sector
{
	enum e_sector		type;
	struct s_sector		*n;
	struct s_sector		*s;
	struct s_sector		*e;
	struct s_sector		*w;
}							t_sector;

typedef struct				s_view
{
	SDL_Window	*window;
	SDL_Surface	*surface;
	t_sector	*position;
	t_texture	*texture;
}							t_view;

#endif
