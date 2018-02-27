/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:48:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/27 15:57:57 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include "sh.h"

# define LEFT(x) ft_printf("\033[%dD", x)
# define RIGHT(x) ft_printf("\033[%dC", x)
# define DOWN(x) ft_printf("\033[%dB", x)
# define UP(x) ft_printf("\033[%dA", x)
# define NL ft_printf("\033E")

typedef struct		s_hist
{
	char			*line;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_line
{
	char			c;
	int				index;
	int				select;
	struct s_line	*next;
	struct s_line	*prev;
}					t_line;

typedef struct		s_curs
{
	int				x;
	int				y;
	int				xmax;
	int				ymax;
	struct winsize	screen;
}					t_curs;

/*
**  line_edit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					ft_line_edition(char **line, int prompt_len,
					t_hist **histo);
t_line				*ft_line_usual(t_line *current, char c, int prompt,
					t_curs *curseur);
t_line				*line_delone(t_line *cur, int prompt, t_curs *curseur);
t_line				*del_next(t_line *cur);
/*
** copy
*/
t_line				*grab_mod(t_line *current, int prompt, t_curs *curseur);
t_line				*paste_line(t_line *cur, char *str, int prompt, t_curs *curseur);
/*
** historic
*/
t_line				*hist_up(t_line *cur, t_hist **histo, int prompt, t_curs *curseur);
t_line				*hist_down(t_line *cur, t_hist **histo, int prompt, t_curs *curseur);
t_hist				*create_hist(char *str);
char				*line_to_str(t_line *cur);
void				init_hist(t_hist **histo);
void				handle_history_ret(t_line *cur, t_hist **histo);
/*
** list checkups
*/
void				increment_all(t_line *current, char c);
int					dblist_len(t_line *first);
int					full_list_len(t_line *el);
t_line				*create_elem(char c);
void				free_dblist(t_line *el);
/*
** deletion
*/
void				del_one_elem(t_line *del);
void				del_elem(t_line *first);
/*
** adding and mooving
*/
t_line				*push_new(t_line *current, char c, int prompt,
					t_curs *curseur);
t_line				*moove_left(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_right(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_up(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_down(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_first(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_last(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_rword(t_line *cur, int prompt, t_curs *curseur);
t_line				*moove_lword(t_line *cur, int prompt, t_curs *curseur);
/*
** ft_pos
*/
void				check_ynx(t_curs *curseur, int prompt, int index);
void				check_max(t_curs *curseur, int len);
void				init_curs(t_curs *curseur, int prompt);
/*
**
*/
t_line				*completion(t_line *cur, int prompt, t_curs *curseur);
/*
** termcaps setup
*/
char				*get_ttyname(void);
int					init_termcaps(void);
/*
** historic >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
t_hist				*new_hist(void);
void				hist_to_file(t_hist *historic);

#endif
