/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfouques <hfouques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 18:59:14 by hfouques          #+#    #+#             */
/*   Updated: 2018/03/02 11:22:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

t_line 	*go_to_start_of_str(t_line *cur, int len)
{
	t_line *tmp;

	tmp = cur;
	while (len > 0)
	{
		tmp = tmp->prev;
		len--;
	}
	return (tmp);
}

void	del_one_t_line(t_line **del)
{
	if (del && *del)
	{
	 	(*del)->next = NULL;
	 	(*del)->prev = NULL;
		free(*del);
		*del = NULL;
	}
}

void		del_after_str(t_line **elm, int len)
{
	t_line **tmp;

	tmp = elm;
	while (len > 0)
	{
		elm = &((*elm)->next);
		ft_printf("Je vais del [%c]\n", (*tmp)->c);
		del_one_t_line(tmp);
		len--;
		ft_printf("Ca degage! len = [%d]\n", len);
		tmp = elm;
	}
}

t_line *add_comp_to_list(t_line *cur, t_comp *comp)
{
	char	*tmp;
	int		i;
	t_line	*new;

	tmp = comp->current->cmd;
	i = 0;
	while (tmp && tmp[i] && tmp[i + 1])
		i++;
	while (i >= 0)
	{
		new = create_elem(tmp[i], cur->index);
		cur->prev = new;
		new->next = cur;
		cur = new;
		i--;
	}
	return (cur);
}

t_line 	*from_comp_to_list(t_line *cur, t_edit *edit)
{
	t_line *eoprefix;
	t_line *ret;

	ret = cur;
	if (edit->comp->current == NULL)
		return (ret);
	eoprefix = go_to_start_of_str(cur, ft_strlen(edit->comp->str));
	eoprefix = eoprefix->prev;
	cur = add_comp_to_list(cur, edit->comp);
	if (eoprefix)
		eoprefix->next = cur;
	cur->prev = eoprefix;
	return (ret);

}