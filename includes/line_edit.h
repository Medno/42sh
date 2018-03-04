/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:48:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/04 16:31:24 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include "sh.h"
# include "types.h"

void				ansi(char *str, int x, int fd);
void				ft_clean_edit(t_edit *edit);

int					count_selected(t_line *cur);
char				*foo_paste(t_line *cur);
t_line				*ft_line_esc(t_line *cur, int len, t_curs *curseur,
					t_hist **histo);
t_line				*ft_line_esc_2(t_line *cur, t_curs *curseur, char *buf);
/*
**  line_edit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					ft_line_edition(char **line, int prompt_len, t_hist **histo, t_env *env);
t_line				*ft_line_usual(t_edit *edit, char c);
t_line				*line_delone(t_line *cur, t_curs *curseur);
t_line				*del_next(t_line *cur);
/*
** copy
*/
t_line				*grab_mod(t_line *current, t_curs *curseur);
t_line				*paste_line(t_line *cur, char *str, t_curs *curseur);
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
void				increment_all(t_line *current, int c);
int					line_len(t_line *first);
int					last_index(t_line *el);
t_line				*create_elem(char c, int len);
void				free_dblist(t_line *el);
/*
** deletion
*/
void				del_one_elem(t_line *del);
void				del_elem(t_line *first);
/*
** adding and mooving
*/
t_line				*push_new(t_line *current, char c, t_curs *curseur);
t_line				*moove_left(t_line *cur, t_curs *curseur);
t_line				*moove_right(t_line *cur, t_curs *curseur);
t_line				*moove_up(t_line *cur, t_curs *curseur);
t_line				*moove_down(t_line *cur, t_curs *curseur);
t_line				*moove_first(t_line *cur, t_curs *curseur);
t_line				*moove_last(t_line *cur, t_curs *curseur);
t_line				*moove_rword(t_line *cur, t_curs *curseur);
t_line				*moove_lword(t_line *cur, t_curs *curseur);
/*
** ft_pos
*/
void				check_ynx(t_curs *curseur, int index);
void				check_max(t_curs *curseur, int len);
void				init_curs(t_curs *curseur, int prompt);
/*
**
*/
t_line				*completion(t_edit *edit);
/*
** historic >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
t_hist				*new_hist(void);
void				hist_to_file(t_hist *historic);

#endif
