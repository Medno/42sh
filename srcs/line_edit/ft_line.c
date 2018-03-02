/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:57:34 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/02 11:35:25 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

static int	edit_end(char **line, t_line *elm, t_hist **histo)
{
	handle_history_ret(elm, histo);
	*line = line_to_str(elm);
	free_dblist(elm);
	write(STDIN_FILENO, "\n", 1);
	return (1);
}

t_line		*ft_line_esc_2(t_line *cur, int prompt, t_curs *curseur, char *buf)
{
	if (ft_strequ(buf, "[1;2A"))
		cur = moove_up(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2B"))
		cur = moove_down(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2C"))
		cur = moove_rword(cur, prompt, curseur);
	else if (ft_strequ(buf, "[1;2D"))
		cur = moove_lword(cur, prompt, curseur);
	return (cur);
}

t_line		*ft_line_esc(t_line *cur, int len, t_curs *curseur, t_hist **histo)
{
	char	buf[8];

	ft_bzero(&buf, 8);
	read(STDIN_FILENO, &buf, 8);
	if (ft_strequ(buf, "[A"))
		cur = hist_up(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[B"))
		cur = hist_down(cur, histo, len, curseur);
	else if (ft_strequ(buf, "[C"))
		cur = moove_right(cur, len, curseur);
	else if (ft_strequ(buf, "[D"))
		cur = moove_left(cur, len, curseur);
	else if (ft_strequ(buf, "[H"))
		cur = moove_first(cur, len, curseur);
	else if (ft_strequ(buf, "[F"))
		cur = moove_last(cur, len, curseur);
	else if (ft_strequ(buf, "[3~"))
		cur = del_next(cur);
	else
		cur = ft_line_esc_2(cur, len, curseur, buf);
	return (cur);
}

int			edit_line(char **line, t_edit *edit)
{
	char	c;

	c = 0;
	if (edit->prompt_len == -1)
	{
		edit->prompt_len = 2;
		ft_printf_fd(STDERR_FILENO, "{tred}> {eoc}");
	}
	while (/*reset_completion(c, edit->comp) && */read(STDIN_FILENO, &c, 1))
	{
		if (c == 4 && !(*edit->current)->next && !(*edit->current)->prev)
			return (0);//HANDLE_CTRLD_exit
		else if (c == '\n')
		{
			*edit->current = moove_last(*edit->current,
					edit->prompt_len, &edit->curseur);
			return (edit_end(line, *edit->current, edit->histo));
		}
		else if (c == 14)
			*edit->current = hist_down(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 16)
			*edit->current = hist_up(*edit->current, edit->histo,
					edit->prompt_len, &edit->curseur);
		else if (c == 27)
			*edit->current = ft_line_esc(*edit->current, edit->prompt_len,
					&edit->curseur, edit->histo);
		else
			*edit->current = ft_line_usual(edit, c);
	}
	return (0);
}

int			ft_line_edition(char **line, int prompt_len, t_hist **histo,
			t_env *env)
{
	t_edit			edit;
	t_line			*current;
	t_curs			curseur;
	int				ret;

	ret = 0;
	current = create_elem(0);
	init_hist(histo);
	init_curs(&curseur, prompt_len);
	edit.current = &current;
	edit.histo = histo;
	edit.prompt_len = prompt_len;
	edit.curseur = curseur;
	edit.comp = init_t_comp();
	edit.env = env;
	if (edit_line(line, &edit))
		ret = 1;
	ft_clean_edit(&edit);
	return (ret);
}
