/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:15:16 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/11 15:45:31 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*g_optarg;
int		g_opterr = 1;
int		g_optind = 1;
int		g_optopt;

static int			ft_init(int ac, char *const av[])
{
	if (ft_strequ(av[g_optind], "--"))
	{
		g_optind++;
		return (-1);
	}
	if (g_optind >= ac || !av[g_optind] || ft_strequ(av[g_optind], "-")
		|| *av[g_optind] != '-')
		return (-1);
	g_optopt = 0;
	g_optarg = NULL;
	return (0);
}

static int			get_error(int err, char *const av[], const char *opt_string,
					char c)
{
	g_optopt = (int)c;
	if (err)
	{
		if (g_opterr)
		{
			ft_putstr_fd(av[0], STDERR_FILENO);
			ft_putstr_fd(": option requires an argument -- ", STDERR_FILENO);
			write(STDERR_FILENO, &c, 1);
			write(STDERR_FILENO, "\n", 1);
		}
		if (*opt_string + 1 == ':')
			return (':');
	}
	else if (g_opterr)
	{
		ft_putstr_fd(av[0], STDERR_FILENO);
		ft_putstr_fd(": illegal option -- ", STDERR_FILENO);
		write(STDERR_FILENO, &c, 1);
		write(STDERR_FILENO, "\n", 1);
	}
	return ('?');
}

static char			get_next_char(const char **opt_addr, char *const av[])
{
	if (!*opt_addr)
		*opt_addr = av[g_optind] + 1;
	else
		*opt_addr += 1;
	return (**opt_addr);
}

int					ft_getopt(int ac, char *const av[], const char *optstring)
{
	static const char	*opt_addr = NULL;
	const char			*chr;

	if (ft_init(ac, av))
		return (-1);
	g_optopt = (int)get_next_char(&opt_addr, av);
	if (ft_isalnum((int)*opt_addr) && (chr = ft_strchr(optstring, g_optopt)))
	{
		if (*(chr + 1) == ':')
		{
			if (!av[g_optind + 1] && !*(opt_addr + 1) && !(opt_addr = NULL))
				return (get_error(1, av, chr, g_optopt));
			else if (!*(opt_addr + 1) && (g_optind++))
				g_optarg = av[g_optind];
			else
				g_optarg = (char *)(opt_addr + 1);
			g_optind++;
			opt_addr = NULL;
		}
		else if (!*(opt_addr + 1) && (g_optind++))
			opt_addr = NULL;
		return (g_optopt);
	}
	opt_addr = NULL;
	return (get_error(0, av, chr, g_optopt));
}

void				reset_ft_opt(void)
{
	g_optarg = NULL;
	g_opterr = 1;
	g_optind = 1;
	g_optopt = 0;
}
