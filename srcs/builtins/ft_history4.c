/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 12:05:57 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/18 11:19:07 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		append_new(t_hist **list, t_hist *new)
{
	t_hist	*tmp;

	if (!*list)
	{
		new->nb = 1;
		*list = new;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->nb = tmp->nb + 1;
	}
}

int				append_to_list(t_hist **histo, char *str)
{
	int		fd;
	t_hist	*new;
	char	*line;

	if (str)
	{
		if ((fd = open(str, O_RDONLY)) < 0)
			return (0);
	}
	else if ((fd = open("./srcs/history/.history", O_RDONLY)) < 0)
		return (0);
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
		{
			line = ft_strjoindel(line, "\n");
			if ((new = create_hist(line)))
				append_new(histo, new);
		}
		ft_strdel(&line);
	}
	close(fd);
	return (0);
}
