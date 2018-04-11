/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errpars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 15:29:06 by pchadeni          #+#    #+#             */
/*   Updated: 2018/04/11 11:28:31 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_errpars(int index, char *str, char c)
{
	ft_printf_fd(STDERR_FILENO, "21sh: ");
	if (index == 1)
		ft_printf_fd(STDERR_FILENO,
				"syntax error near unexpected token `%s'\n", str);
	if (index == 2)
		ft_printf_fd(STDERR_FILENO,
				"unexpected EOF while looking for matching `%c'\n", c);
	return (1);
}
