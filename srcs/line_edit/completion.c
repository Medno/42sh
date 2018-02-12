/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/12 12:02:56 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

t_line	*completion(t_line *cur, int prompt, t_curs *curseur)
{
	(void)prompt;
	(void)curseur;
	return (cur);
}

char	*get_complete(char *str)
{
	DIR				*dir;
	struct dirent	*directory;

	dir = opendir(".");
	while ((directory = readdir(dir)))
	{
	}
	(void)str;
	return (str);
}
