/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_historic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 11:40:03 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 11:58:25 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static t_hist	*create_hist(char *str)
{
	t_hist	*new;

	if (!(new = (t_hist *)malloc(sizeof(t_hist))))
		return (NULL);
	new->line = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void		append_new(t_hist *list, t_hist *new)
{
	t_hist	*tmp;

	if (!list)
		list = new;
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void			hist_to_file(t_hist *historic)
{
	int		fd;

	fd = open(".history", O_CREAT, O_WRONLY);
	while (historic->prev)
		historic = historic->prev;
	while (historic)
	{
		write(fd, &historic->line, ft_strlen(historic->line));
		write(fd, "\n", 1);
		ft_strdel(&historic->line);
		historic->prev = NULL;
		historic = historic->next;
		historic->prev->next = NULL;
		free(historic->prev);
	}
}

t_hist			*new_hist(void)
{
	t_hist	*new;
	t_hist	*list;
	int		fd;
	char	*line;

	if ((fd = open(".history", O_RDONLY)) < 0)
		return (NULL);
	line = NULL;
	list = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		new = NULL;
		if ((new = create_hist(line)))
			append_new(list, new);
		ft_strdel(&line);
	}
	return (list);
}
