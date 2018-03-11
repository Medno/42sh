/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:23:35 by hlely             #+#    #+#             */
/*   Updated: 2018/03/11 16:37:51 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	check_alnum(char *str)
{
	int		j;

	j = 0;
	while (str[j] && str[j] != '=')
	{
		if (!ft_isalnum(str[j]))
			return (0);
		j++;
	}
	return (1);
}

int		is_valid_identifier(char *arg, int print)
{
	if (!(ft_isalpha(arg[0]) && arg[0] != '_') || !check_alnum(arg))
	{
		if (print)
			ft_printf_fd(STDERR_FILENO,
					"42sh: unset: `%s': not a valid identifier\n", arg);
		return (0);
	}
	return (1);
}
