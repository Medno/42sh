/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 07:51:15 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 08:55:04 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	clean_stock(char *stock, int ret)
{
	if (ret == 2)
		ft_bzero(stock, BUFF_SIZE + 1);
	else
	{
		if (!(stock = ft_strncpy(stock, &(stock[ft_strcspn(stock, "\n") + 1]),
			BUFF_SIZE + 1)))
			return (-1);
	}
	return (1);
}

static int	fill_line(char *stock, char **line)
{
	int		ret;
	char	*tmp;
	char	*tmp2;

	if (!*stock)
		return (0);
	if (!(tmp = ft_strndup(stock, ft_strcspn(stock, "\n"))))
		return (-1);
	ret = ft_strchr(stock, '\n') ? 1 : 2;
	if (!*line)
	{
		if (!(*line = ft_strdup(tmp)))
			return (-1);
	}
	else
	{
		tmp2 = *line;
		if (!(*line = ft_strjoin(*line, tmp)))
			return (-1);
		free(tmp2);
	}
	if ((clean_stock(stock, ret)) < 0)
		return (-1);
	free(tmp);
	return (ret);
}

static char	*start_struc(const int fd)
{
	static t_list	*list;
	t_sort			new_content;
	t_list			*new;
	t_list			*tmp;

	tmp = list;
	while (tmp)
	{
		if (((t_sort *)(tmp->content))->fd == fd)
			return (((t_sort *)(tmp->content))->stock);
		tmp = tmp->next;
	}
	new_content.fd = fd;
	ft_bzero(new_content.stock, BUFF_SIZE + 1);
	if (!(new = ft_lstnew((t_sort *)&new_content, sizeof(t_sort))))
		return (NULL);
	ft_lstadd(&list, new);
	return (((t_sort *)(new->content))->stock);
}

int			get_next_line(const int fd, char **line)
{
	char	*tmp_str;
	int		retour;
	char	*stock;

	if ((fd < 0 || !line) || !(stock = start_struc(fd)))
		return (-1);
	retour = 2;
	*line = NULL;
	while (retour == 2)
	{
		if (!*stock)
		{
			if (!(tmp_str = ft_strnew(BUFF_SIZE)))
				return (-1);
			if (read(fd, tmp_str, BUFF_SIZE) < 0)
				return (-1);
			if (!(stock = ft_strncpy(stock, tmp_str, BUFF_SIZE + 1)))
				return (-1);
			free(tmp_str);
		}
		if ((retour = fill_line(stock, line)) < 0)
			return (-1);
	}
	return (*line ? 1 : 0);
}
