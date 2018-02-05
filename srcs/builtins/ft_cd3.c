/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 11:38:51 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/05 10:28:32 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	**delete_and_paste(char **arr, int i)
{
	char	**new;
	int		j;
	int		y;

	new = (char **)malloc(sizeof(char *) * ft_tablen(arr));
	y = 0;
	j = -1;
	while (arr[++j])
	{
		if (j == i || j + 1 == i)
			free(arr[j]);
		else
		{
			new[y] = arr[j];
			y++;
		}
	}
	new[y] = NULL;
	return (new);
}

char	*paste_strs(char *str, char *new)
{
	char	*tmp;
	char	*tmp2;

	if (!str)
		str = ft_strjoin("/", new);
	else
	{
		tmp = str;
		tmp2 = ft_strjoin("/", new);
		str = ft_strjoin(str, tmp2);
		ft_strdel(&tmp2);
		ft_strdel(&tmp);
	}
	return (str);
}

char	*paste_path(char *s1, char *s2)
{
	char	*tmp;
	char	*path;

	if (s1[ft_strlen(s1) - 1] != '/')
	{
		tmp = ft_strjoin(s1, "/");
		path = ft_strjoin(tmp, s2);
		ft_strdel(&tmp);
	}
	else
		path = ft_strjoin(s1, s2);
	return (path);
}
