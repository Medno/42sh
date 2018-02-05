/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:50:21 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/09 15:56:41 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_colors		colors_brackets(void)
{
	t_colors	colors;

	(colors.t_black) = (t_dope) { "{tblack}", "\033[30m"};
	(colors.t_red) = (t_dope) { "{tred}", "\033[31m"};
	(colors.t_green) = (t_dope) { "{tgreen}", "\033[32m"};
	(colors.t_yellow) = (t_dope) { "{tyellow}", "\033[33m"};
	(colors.t_blue) = (t_dope) { "{tblue}", "\033[34m"};
	(colors.t_mage) = (t_dope) { "{tmagenta}", "\033[35m"};
	(colors.t_cyan) = (t_dope) { "{tcyan}", "\033[36m"};
	(colors.t_white) = (t_dope) { "{twhite}", "\033[37m"};
	(colors.b_black) = (t_dope) { "{bblack}", "\033[40m"};
	(colors.b_red) = (t_dope) { "{bred}", "\033[41m"};
	(colors.b_green) = (t_dope) { "{bgreen}", "\033[42m"};
	(colors.b_yellow) = (t_dope) { "{byellow}", "\033[43m"};
	(colors.b_blue) = (t_dope) { "{bblue}", "\033[44m"};
	(colors.b_mage) = (t_dope) { "{bmagenta}", "\033[45m"};
	(colors.b_cyan) = (t_dope) { "{bcyan}", "\033[46m"};
	(colors.b_white) = (t_dope) { "{bwhite}", "\033[47m"};
	(colors.bold) = (t_dope) { "{bold}", "\033[1m"};
	(colors.underscore) = (t_dope) { "{underscore}", "\033[4m"};
	(colors.eoc) = (t_dope) { "{eoc}", "\033[0m"};
	return (colors);
}

static int		color_parse(char **str, t_colors coolors)
{
	char	*tmp;
	t_dope	*doope;

	doope = &(coolors.t_blue);
	tmp = *str;
	while (doope <= &(coolors.eoc))
	{
		if (ft_strstr(*str, doope->brackets))
		{
			*str = ft_strdup(doope->dope);
			ft_strdel(&tmp);
			break ;
		}
		doope++;
	}
	return (ft_strlen(*str));
}

static char		*parse(char *str, char **tab, t_colors colors)
{
	char		*tmp;
	int			len_string;
	int			i;

	i = -1;
	ft_strclr(str);
	while (tab[++i])
	{
		if (*tab[i] == '{')
			len_string = color_parse(&tab[i], colors);
		else
			len_string = ft_strlen(tab[i]);
		tmp = str;
		str = ft_str_join(str, tab[i], ft_strlen(str), len_string);
		ft_strdel(&tmp);
	}
	return (str);
}

int				is_valid(char *str, t_colors colors)
{
	t_dope	*doope;

	doope = &(colors.t_blue);
	while (doope <= &(colors.eoc))
	{
		if (ft_strstr(str, doope->brackets))
			return (1);
		doope++;
	}
	return (0);
}

int				handle_color(char **str, t_colors colors)
{
	char	**tab;
	int		i;

	i = 0;
	if (is_valid(*str, colors))
	{
		tab = ft_parse_brackets(*str, colors);
		*str = parse(*str, tab, colors);
		while (tab[i])
			ft_strdel(&tab[i++]);
		ft_strdel((char **)&tab);
	}
	return (ft_strlen(*str));
}
