/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 09:30:39 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/11 10:13:04 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			full_hist_file(t_hist **histo, char *str)
{
	int		fd;
	t_hist	*tmp;

	if (str)
		fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	else
		fd = open("./srcs/history/.history",
		O_CREAT | O_WRONLY | O_TRUNC, 0600);
	tmp = *histo;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_putstr_fd(tmp->line, fd);
		tmp = tmp->next;
	}
	close(fd);
	return (0);
}

int			replace_w_arg(t_hist **histo, char **str)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	if (*str)
	{
		ft_strdel(&(*histo)->line);
		(*histo)->line = *str[0] ? NULL : ft_strdup("");
		while (str[++i])
		{
			s = str[i + 1] ? ft_strjoin(str[i], " ") : ft_strdup(str[i]);
			if (!(*histo)->line)
				(*histo)->line = ft_strdup(s);
			else
				(*histo)->line = ft_strjoindel((*histo)->line, s);
			ft_strdel(&s);
		}
		if ((*histo)->line)
			(*histo)->line = ft_strjoindel((*histo)->line, "\n");
	}
	return (0);
}

static int	check_num(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_printf_fd(2, "42sh: history: numeric argument required\n");
			return (-1);
		}
	}
	return (ft_atoi(str));
}

int			print_history(t_hist **histo, char **str)
{
	t_hist	*tmp;
	int		nb;

	nb = -1;
	if (*str)
	{
		if (!(nb = check_num(*str)))
			return (0);
		if (nb < 0)
			return (1);
		str++;
		if (*str && ft_printf_fd(2, "42sh: history: too many arguments\n"))
			return (1);
	}
	tmp = *histo;
	while (tmp && tmp->prev && --nb)
		tmp = tmp->prev;
	while (tmp)
	{
		ft_printf("%4d  %s", tmp->nb, tmp->line);
		tmp = tmp->next;
	}
	return (0);
}
