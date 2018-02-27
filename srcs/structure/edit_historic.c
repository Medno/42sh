/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_historic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 11:40:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:52:45 by kyazdani         ###   ########.fr       */
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

void			hist_to_file(t_hist *historic)
{
	int		fd;
	t_hist	*tmp;

	fd = open("./srcs/structure/.history", O_CREAT | O_WRONLY, 0600);
	while (historic->prev)
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
	char	*line;

	if ((fd = open("./srcs/structure/.history", O_RDONLY)) < 0)
		return (NULL);
	line = NULL;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		new = NULL;
		if ((new = create_hist(line)))
			append_new(&list, new);
		ft_strdel(&line);
	}
	close(fd);
	return (list);
}
