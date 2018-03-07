/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 11:41:13 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/07 15:00:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

extern int	g_optind;
extern char	*g_optarg;

static int	set_bits(int c, int fl)
{
	if (c == 'a')
		fl |= 1;
	else if (c == 'w')
		fl |= 2;
	else if (c == 'r')
		fl |= 4;
	else if (c == 'n')
		fl |= 8;
	else if (c == 'p')
		fl |= 16;
	else if (c == 's')
		fl |= 32;
	else if (c == 'c')
		fl |= 64;
	else if (c == 'd')
		fl |= 128;
	return (fl);
}

static int	check_bits(int fl)
{
	if ((1 & fl) && ((2 & fl) || (4 & fl) || (8 & fl)))
		return (1);
	else if ((2 & fl) && ((4 & fl) || (8 & fl)))
		return (1);
	else if ((4 & fl) && (8 & fl))
		return (1);
	return (0);
}

static int		step_2(t_hist **histo, char **str, int flags)
{
	if (!flags)
		return (print_history(histo, str));
	if (64 & flags)
		return (free_history(histo));
	if (128 & flags)
		return (free_offset_hist(histo, g_optarg));
	if (1 & flags)
		return (0);//a
	else if (2 & flags)
		return (full_hist_file(histo, *str));
	else if (4 & flags)
		return (append_to_list(histo, *str));
	else if (8 & flags)
		return (0);//n
	if (32 & flags)
		return (replace_w_arg(histo, str));
	if (16 & flags)
		return (0);//p
	return (0);
}

int		ft_history(t_hist **histo, char **str, int len)
{
	int		flags;
	int		c;

	flags = 0;
	c = 0;
	reset_ft_opt();
	while ((c = ft_getopt(len, str, "carnpswd:")) != -1)
	{
		if (ft_strchr("carnpswd", (char)c))
			flags = set_bits(c, flags);
		else if (c == ':' || c == '?')
		{
			ft_putstr_fd("history: usage: history [-c] [-d offset] [n] or \
history -awrn [filename] or history -ps arg [arg...]\n", STDERR_FILENO);
			return (1);
		}
	}
	if (check_bits(flags))
	{
		ft_putendl_fd("42sh: history: cannot use more than one of -anrw", 2);
		return (1);
	}
	else
		return (step_2(histo, &str[g_optind], flags));
}
