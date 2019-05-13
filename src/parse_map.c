/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:16:37 by abutok            #+#    #+#             */
/*   Updated: 2019/05/13 10:32:27 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <fcntl.h>

static int	is_valid_map(const t_list *list)
{
	size_t	length;
	int		i;

	if (list == NULL)
		return (0);
	length = list->content_size;
	i = 0;
	while (list != NULL)
	{
		if (list->content_size != length)
			return (0);
		i++;
		list = list->next;
	}
	return (i);
}

static void	do_nothing(void *u1, size_t u2)
{
	u1 = NULL;
	u2 = 0;
}

static char	**convert_map(t_list **list, size_t *h, size_t *w)
{
	t_list	*iterator;
	char	**map;
	int		i;

	if ((*h = is_valid_map(*list)) == 0)
	{
		ft_lstdel(list, &do_nothing);
		return (NULL);
	}
	map = (char**)malloc(sizeof(char*) * (*h));
	iterator = *list;
	*w = iterator->content_size - 1;
	i = 0;
	while (iterator != NULL)
	{
		map[(*h) - i - 1] = (char*)iterator->content;
		i++;
		iterator = iterator->next;
	}
	return (map);
}

char		**get_map(const char *filename, size_t *h, size_t *w)
{
	t_list	*list;
	char	*buf;
	size_t	i;
	int		map_fd;

	map_fd = open(filename, O_RDONLY);
	i = 0;
	list = NULL;
	while (get_next_line(map_fd, &buf))
	{
		ft_lstadd(&list, ft_lstnew(buf, ft_strlen(buf) + 1));
		free(buf);
	}
	close(map_fd);
	return (convert_map(&list, h, w));
}
