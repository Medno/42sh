/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_glob.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 11:51:24 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/21 14:43:00 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"

static t_glpath	*create_new_glob(char *s)
{
	t_glpath	*new;

	if (!(new = (t_glpath *)malloc(sizeof(t_glpath))))
		return (NULL);
	new->str = ft_strdup(s);
	new->elem.nb = 0;
	new->elem.offs = 0;
	new->elem.pathv = NULL;
	ft_bzero(&new->elem, sizeof(t_glob));
	new->next = NULL;
	return (new);
}

static int		new_list_elem(char *s, t_glpath **list)
{
	t_glpath	*new;
	t_glpath	*tmp;

	if (!(new = create_new_glob(s)))
		return (0);
	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

static void		check_quotes(char c, uint8_t *quotes)
{
	if ((c == '\"' && !*quotes) || (c == '\"' && *quotes == 1))
		*quotes ^= 1;
	if ((c == '\'' && !*quotes) || (c == '\'' && *quotes == 2))
		*quotes ^= 2;
}

t_glpath		*parse_glob(char *str, int len)
{
	t_glpath	*list;
	char		buf[len];
	uint8_t		quotes;
	int			i;

	ft_bzero(&buf[0], len + 1);
	i = -1;
	list = NULL;
	while (*str)
	{
		buf[++i] = *str;
		if (i == len - 1 || i == len)
			break ;
		check_quotes(*str, &quotes);
		if (*str == ' ' && !quotes && new_list_elem(&buf[0], &list) && (i = -1))
			ft_bzero(&buf[0], len + 1);
		else if (*str == '\\')
		{
			str++;
			buf[++i] = *str;
		}
		str++;
	}
	if (buf[0])
		new_list_elem(&buf[0], &list);
	return (list);
}
