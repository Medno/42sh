/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 08:18:40 by kyazdani          #+#    #+#             */
/*   Updated: 2017/12/04 20:57:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	n_percent(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (*str == '%')
			count++;
		str++;
	}
	return (count);
}

static char	*ft_handle_undefined(char *str, char *charset)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (str[i])
	{
		if ((ft_isalpha(str[i]) && !ft_strchr(charset, str[i]))
				|| str[i] == '}')
			break ;
		i++;
	}
	if (!str[i])
		ft_strclr(str);
	str = ft_strdup(&str[i]);
	ft_strdel(&tmp);
	return (str);
}

static char	*ft_width_perc(t_flags flags, char *str)
{
	int		i;
	char	*new_string;
	char	*tmp;

	i = -1;
	new_string = ft_strnew(flags.width - 1);
	while (++i < flags.width - 1)
	{
		if (!flags.zero)
			new_string[i] = ' ';
		else
			new_string[i] = '0';
	}
	tmp = str;
	if (!flags.minus)
		str = ft_strjoin(new_string, str);
	else
		str = ft_strjoin(str, new_string);
	ft_strdel(&new_string);
	ft_strdel(&tmp);
	return (str);
}

int			ft_handle_percent(t_flags flags, char **str)
{
	char	*tmp;

	if (ft_strlen(*str) == 1)
	{
		tmp = *str;
		*str = ft_strdup("");
		ft_strdel(&tmp);
	}
	if (n_percent(*str) == 2)
	{
		tmp = *str;
		*str = ft_strdup("%");
		ft_strdel(&tmp);
	}
	if (ft_strlen(*str) > 1 && n_percent(*str) != 2)
		*str = ft_handle_undefined(*str, " .%-+#0123456789ljhzdiouxcsDOUXCS");
	if (flags.width > 1)
		*str = ft_width_perc(flags, *str);
	if (!(*str[0]) && (tmp = *str))
	{
		*str = ft_strdup("");
		ft_strdel(&tmp);
	}
	return (ft_strlen(*str));
}
