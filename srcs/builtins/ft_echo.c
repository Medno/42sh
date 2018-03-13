/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 15:01:28 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:53:33 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_echo(t_init *init, char ***entry)
{
	char	**str;
	int		i;

	(void)init;
	str = *entry;
	str++;
	i = -1;
	if (str[0] && !ft_strcmp(str[0], "-n"))
		i = 0;
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		if (str[i + 1])
			write(1, " ", 1);
	}
	if (!str[0] || (str[0] && ft_strcmp(str[0], "-n")))
		write(1, "\n", 1);
	return (0);
}
