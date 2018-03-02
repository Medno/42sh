/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 11:20:02 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void		from_list_to_comp(t_line *cur, t_comp *comp)
{
	comp->cmd = line_to_str(cur);
	comp->pos = cur->index + 1;
}

static t_line 	*go_to_start_of_str(t_line *cur, int len)
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

static t_line 	*from_comp_to_list(t_line *cur, t_edit *edit)
{
	t_line *to_del;
	t_line *ret;

	if (edit->comp->current == NULL)
		return (cur);


	to_del = go_to_start_of_str(cur, ft_strlen(edit->comp->str));
	ret = cur;
	to_del = to_del->prev;
	char *str;
	int i;

	str = edit->comp->current->cmd;
	i = 0;
	while (str && str[i] && str[i + 1])
		i++;
	t_line *new;
	while (i >= 0)
	{
		new = create_elem(str[i]);
		cur->prev = new;
		new->next = cur;
		cur = new;
		i--;
	}
	if (to_del)
		to_del->next = cur;
	cur->prev = to_del;
	return (ret);
}


/*
**	On creer le t_comp
**	On remplit le t_comp en fonction de la list
**	On modifie le t_comp en fonction de la completion
**	On modifie la list en fonction du t_comp
*/

t_line	*completion(t_edit *edit)
{
	t_line *tmp;
	t_line *first;

	tmp = *edit->current;
	if (tmp->c == '0' && tmp->prev == NULL)
		return (*edit->current);
	from_list_to_comp(*edit->current, edit->comp);
	do_completion(edit->comp, edit->env);
	*edit->current = from_comp_to_list(*edit->current, edit);
	
	first = *edit->current; while (first->prev) { first = first->prev; }
	int i = 0;
	t_line *t = first; ft_printf("List a afficher = "); while (t) {ft_printf("[%c]", t->c ); t->index = i++; t = t->next;} ft_putchar('\n');
	return (*edit->current);
}
