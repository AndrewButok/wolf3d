/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:16:37 by abutok            #+#    #+#             */
/*   Updated: 2019/05/06 16:55:57 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>

static void		del_lst_row(void *str, size_t size)
{
	free(str);
	return ;
	size = 0;
}

static size_t	list_len(const t_list *lst)
{
	size_t c;

	c = 0;
	while (lst != NULL && lst->content_size != 0)
	{
		c++;
		lst = lst->next;
	}
	return (c);
}

static int		check_map(const t_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next != NULL && lst->content_size != lst->next->content_size)
			return (0);
		lst = lst->next;
	}
	return (1);
}

static char		**make_map(const t_list *lst)
{
	char	**map;
	char	**map_iter;
	int		maxy;

	map = NULL;
	if ((maxy = list_len(lst)) == 0 && check_map(lst) == 0)
		return (NULL);
	map = (char**)ft_memalloc(sizeof(char*) * maxy + 1);
	map_iter = map;
	while (lst != NULL && map_iter != NULL)
	{
		*map_iter = ft_strdup((char*)lst->content);
		map_iter++;
		lst = lst->next;
	}
	*map_iter = NULL;
	return (map);
}

char			**get_map(char *filename)
{
	int		map_fd;
	t_list	*lst;
	char	*row;
	char	**map;

	map_fd = open(filename, O_RDONLY);
	row = NULL;
	lst = NULL;
	while (get_next_line(map_fd, &row) > 0)
	{
		ft_lstadd(&lst, ft_lstnew(row, ft_strlen(row) + 1));
		free(row);
	}
	free(row);
	map = make_map(lst);
	ft_lstdel(&lst, &del_lst_row);
	return (map);
}
