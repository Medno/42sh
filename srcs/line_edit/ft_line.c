/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/07 14:14:39 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_clean_edit(t_edit *edit)
{
	if (edit)
	{
		ft_strdel(&(edit->comp->dir));
		ft_strdel(&(edit->comp->str));
		ft_strdel(&(edit->comp->cmd));
		edit->comp->current = NULL;
		if (edit->comp->list)
		{
			ft_clean_lcomp_list(edit->comp->list);
			edit->comp->list = NULL;
		}
		free(edit->comp);
		edit->comp = NULL;
	}
}

int		edit_end(char **line, t_edit *edit)
{
	*edit->current = move_last(*edit->current, &edit->curseur);
	*edit->current = push_new(*edit->current, '\n', &edit->curseur);
	handle_history_ret(*edit->current, edit->histo);
	*line = line_to_str(*edit->current);
	free_tline(*edit->current);
	return (0);
}

int		handle_ctrl_d_c(t_edit *edit, char **line, int i)
{
	if (i)
	{
		ft_strdel(line);
		while ((*edit->histo)->next)
			*edit->histo = (*edit->histo)->next;
		ft_strdel(&(*edit->histo)->line);
		if ((*edit->current)->next)
			*edit->current = move_last(*edit->current, &edit->curseur);
		free_tline(*edit->current);
		write(0, "\n", 1);
		return (3);
	}
	else
	{
		ft_strdel(line);
		while ((*edit->histo)->next)
			*edit->histo = (*edit->histo)->next;
		ft_strdel(&(*edit->histo)->line);
		free_tline(*edit->current);
		return (1);
	}
}

int		edit_line(char **line, t_edit *edit, t_init init)
{
	char	c;

	c = 0;
	while (reset_completion(edit->comp) && read(STDIN_FILENO, &c, 1))
	{
		if (c == 3)
			return (handle_ctrl_d_c(edit, line, 1));
		else if (c == 4 && !(*edit->current)->next && !(*edit->current)->prev)
			return (handle_ctrl_d_c(edit, line, 0));
		else if (c == '\n')
			return (edit_end(line, edit));
		else if (c == 14)
			*edit->current = hist_down(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 16)
			*edit->current = hist_up(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 27)
			*edit->current = ft_line_esc(edit);
		else
			*edit->current = ft_line_usual(edit, c, init);
	}
	return (0);
}

int		ft_line_edition(char **line, int prompt_len, t_hist **histo,
		t_init init)
{
	t_edit			edit;
	t_line			*current;
	t_curs			curseur;
	int				ret;

	if (prompt_len == -1 && ft_printf_fd(STDERR_FILENO, "{tred}> {eoc}"))
		prompt_len = 2;
	edit.prompt_len = prompt_len;
	current = create_elem(0, prompt_len + 1);
	init_hist(histo);
	init_curs(&curseur, prompt_len);
	edit.current = &current;
	edit.histo = histo;
	edit.curseur = curseur;
	edit.comp = init_t_comp();
	edit.env = init.new_env;
	edit.loc = init.loc_env;
	g_ed = &edit;
	ret = edit_line(line, &edit, init);
	ft_clean_edit(&edit);
	return (ret);
}
