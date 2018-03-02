/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 14:33:20 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 14:03:21 by kyazdani         ###   ########.fr       */
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

static void		del_after_str(t_line *elm, int len)
{
	t_line *tmp;

	if (elm && elm->prev)
		elm->prev->next = NULL;	
	while (elm && len > 0)
	{
		tmp = elm;
		elm = elm->next;
		ft_printf("Je vais tuer tmp = [%c]\n", tmp->c);
		del_one_elem(tmp);
		len--;
	}
}

static t_line	*add_to_last(t_line *new, t_line *line)
{
	t_line *tmp;

	if (line == NULL)
		return (new);
	tmp = line;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (line);
}

static t_line	*go_to_last(t_line *line)
{
	t_line *tmp;

	tmp = line;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static t_line 	*from_comp_to_list(t_line *cur, t_edit *edit)
{
	t_line *first;

	first = *(edit->current);
	while (first->prev) { first = first->prev; }

	t_line *to_del;
	to_del = go_to_start_of_str(cur, ft_strlen(edit->comp->str));

	t_line *suffix;
	suffix = cur;

	del_after_str(to_del, ft_strlen(edit->comp->str));

	char *tmp; tmp = edit->comp->current->cmd;
	t_line *new;
	while (tmp && *tmp)
	{
		new = create_elem(*tmp);
		first = add_to_last(new, first);
		tmp++;
	}

	 t_line *last;
	 last = go_to_last(first);
	 last->next = suffix;
	 suffix->prev = last;
	 return (first);
}

static void	move_curseur(t_curs *curseur)
{
	;
}

static void	print_line(t_line *new, int len_end, t_curs *curseur)
{
	char	*str;
	int		i;
	t_line	*tmp;

	i = 0;
	tmp = new;
	str = ft_strnew(len_end);
	ft_printf("str = [%s] de taille [%d]\n", str, len_end);
	while (tmp->next)
	{
		str[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	ft_printf("str = [%s] de taille [%d]\n", str, len_end);
	ft_putstr_fd(str, STDIN_FILENO);
//	write(STDIN_FILENO, &str, len_end);
	if (!new->next->next && !curseur->x)
		;
	else if (new->next->next)
		move_curseur(curseur);
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

	first = *(edit->current);
	while (first->prev) { first = first->prev; }

	tmp = *edit->current;
	if (tmp->c == '0' && tmp->prev == NULL)
		return (*edit->current);
	from_list_to_comp(*edit->current, edit->comp);
	do_completion(edit->comp, edit->env);
//	ft_printf("Ma string en sortie : [%s]\n", edit->comp->cmd);
//	from_comp_to_list(cur, comp);
	return (*edit->current);
}
