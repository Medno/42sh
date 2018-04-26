/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:00:40 by kyazdani          #+#    #+#             */
/*   Updated: 2018/04/26 16:00:41 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_env	*create_env(char **arr)
{
	t_env	*list;
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = -1;
	list = NULL;
	while (arr[++i])
	{
		new = NULL;
		new = malloc(sizeof(t_env));
		new->name = ft_strndup(arr[i], ft_strcspn(arr[i], "="));
		new->content = ft_strdup(&arr[i][ft_strcspn(arr[i], "=") + 1]);
		new->next = NULL;
		if (!list)
			list = new;
		else
		{
			tmp = list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (list);
}

char	*ft_getenv(t_env **env, char *elem)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp && !ft_strequ(tmp->name, elem))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp->content);
}

int		count_list_len(t_env **env)
{
	int		i;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	free_list(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	while (*env)
	{
		tmp = *env;
		tmp2 = tmp;
		while (tmp->next)
			tmp = tmp->next;
		while (tmp2->next != tmp && tmp2 != tmp)
			tmp2 = tmp2->next;
		ft_strdel(&tmp->content);
		ft_strdel(&tmp->name);
		tmp2->next = NULL;
		free(tmp);
		if (tmp2 == tmp)
			break ;
	}
	*env = NULL;
}

char	**put_in_tab(t_env **env)
{
	char	**arr;
	char	*tmpstr;
	int		i;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	if (!(arr = (char **)malloc(sizeof(char *) * (count_list_len(env) + 1))))
		return (NULL);
	while (tmp)
	{
		tmpstr = ft_strjoin(tmp->name, "=");
		arr[i] = ft_strjoin(tmpstr, tmp->content);
		ft_strdel(&tmpstr);
		tmp = tmp->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}
