/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_histo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 15:23:56 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 17:44:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_hist			*create_hist(char *str)
{
	t_hist	*new;

	if (!(new = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	new->line = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void		append_new(t_hist **list, t_hist *new)
{
	t_hist	*tmp;

	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

t_hist			*cleanup_nl_hist(t_hist **histo)
{
	t_hist	*tmp;
	t_hist	*tmp2;

	tmp = *histo;
	if (!*histo)
		return (tmp);
	if (!tmp->line || ft_strequ(tmp->line, "\n"))
	{
		ft_strdel(&tmp->line);
		if (!tmp->prev)
		{
			ft_memdel((void **)&tmp);
			return (NULL);
		}
		tmp = tmp->prev;
		tmp2 = tmp->next;
		tmp->next = NULL;
		tmp2->prev = NULL;
		ft_memdel((void **)&tmp2);
	}
	return (tmp);
}

void			hist_to_file(t_hist *historic)
{
	int		fd;
	t_hist	*tmp;

	fd = open("./srcs/history/.history", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	while (historic && historic->prev)
		historic = historic->prev;
	while (historic)
	{
		ft_putendl_fd(historic->line, fd);
		ft_strdel(&historic->line);
		tmp = historic;
		historic->prev = NULL;
		historic = historic->next;
		tmp->next = NULL;
		free(tmp);
	}
	close(fd);
}

t_hist			*new_hist(void)
{
	t_hist	*new;
	t_hist	*list;
	int		fd;
	int		i;
	char	*line;

	if ((fd = open("./srcs/history/.history", O_RDONLY)) < 0)
		return (NULL);
	line = NULL;
	list = NULL;
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		new = NULL;
		if (*line)
		{
			line = ft_strjoindel(line, "\n");
			if ((new = create_hist(line)))
				append_new(&list, new);
			new->nb = ++i;
		}
		ft_strdel(&line);
	}
	close(fd);
	return (list);
}
