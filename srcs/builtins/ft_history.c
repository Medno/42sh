/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:41:13 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/16 12:22:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int	g_optind;
extern char	*g_optarg;

static int	set_bits(int c, int fl)
{
	if (c == 'w')
		fl |= 1;
	else if (c == 'r')
		fl |= 2;
	else if (c == 's')
		fl |= 4;
	else if (c == 'c')
		fl |= 8;
	else if (c == 'd')
		fl |= 16;
	return (fl);
}

static int	step_2(t_hist **histo, char **str, int flags)
{
	if (!flags)
		return (print_history(histo, str));
	if (8 & flags)
		return (free_history(histo));
	if (16 & flags)
		return (free_offset_hist(histo, g_optarg));
	if (1 & flags)
		return (full_hist_file(histo, *str));
	if (2 & flags)
		return (append_to_list(histo, *str));
	if (4 & flags)
		return (replace_w_arg(histo, str));
	return (0);
}

int			ft_history(t_hist **histo, char **str)
{
	int		flags;
	int		c;

	flags = 0;
	c = 0;
	reset_ft_opt();
	while ((c = ft_getopt(ft_tablen(str), str, "crswd:")) != -1)
	{
		if (ft_strchr("crswd", (char)c))
			flags = set_bits(c, flags);
		else if (c == ':' || c == '?')
		{
			ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or \
history -wr [filename] or history -s arg [arg...]\n", STDERR_FILENO);
			return (1);
		}
	}
	if ((1 & flags) && (2 & flags))
	{
		ft_putendl_fd("42sh: history: cannot use more than one of -rw", 2);
		return (1);
	}
	else
		return (step_2(histo, &str[g_optind], flags));
}
