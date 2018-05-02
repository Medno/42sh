/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:48:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/23 16:39:47 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include "sh.h"

/*
**  line_edit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					ft_line_edition(char **line, int prompt_len,
					t_hist **histo, t_init init);
t_line				*ft_line_usual(t_edit *edit, char c, t_init init);
t_line				*line_delone(t_line *cur, t_curs *curseur);
t_line				*del_next(t_line *cur, t_curs *curseur);
void				ansi(char *str, int x, int fd);
t_line				*ft_line_esc(t_edit *edit);
t_line				*ft_line_esc_2(t_edit *edit, char *buf);
/*
** copy
*/
t_line				*select_word(char **str, t_line *cur, t_curs *curseur);
t_line				*select_all(char **str, t_line *cur, t_curs *curseur);
t_line				*paste_selected_line(char *str, t_line *cur,
					t_curs *curseur);
/*
** historic
*/
t_line				*hist_up(t_line *cur, t_hist **histo, int prompt,
					t_curs *curseur);
t_line				*hist_down(t_line *cur, t_hist **histo, int prompt,
					t_curs *curseur);
t_hist				*create_hist(char *str);
void				init_hist(t_hist **histo);
void				handle_history_ret(t_line *cur, t_hist **histo);
t_hist				*new_hist(void);
void				hist_to_file(t_hist *historic);
/*
** search
*/
char				lookup_history(t_edit *edit, t_init init);
char				*search_hist(t_edit *edit, char *look, char c);
char				*add_char_str(char *look, char c);
t_line				*clear(t_edit *edit, char *buf);
/*
** list checkups
*/
void				ft_clean_edit(t_edit *edit);
t_line				*create_elem(char c, int len);
int					last_index(t_line *el);
int					full_tline_len(t_line *el);
int					parted_tline_len(t_line *cur);
void				free_one_tline(t_line *del);
void				free_tline(t_line *first);
void				increment_all(t_line *current, t_curs *curseur, int c);
char				*line_to_str(t_line *cur);
t_line				*str_to_line(char *str, int prompt, t_curs *curseur);
int					edit_end(char **line, t_edit *edit);
/*
** adding and mooving
*/
t_line				*push_new(t_line *current, char c, t_curs *curseur);
t_line				*move_left(t_line *cur, t_curs *curseur);
t_line				*move_right(t_line *cur, t_curs *curseur);
t_line				*move_up(t_line *cur, t_curs *curseur);
t_line				*move_down(t_line *cur, t_curs *curseur);
t_line				*move_first(t_line *cur, t_curs *curseur);
t_line				*move_last(t_line *cur, t_curs *curseur);
t_line				*move_rword(t_line *cur, t_curs *curseur);
t_line				*move_lword(t_line *cur, t_curs *curseur);
t_line				*clearscreen(t_edit *edit, t_init init);
/*
** ft_pos
*/
void				check_ynx(t_curs *curseur, int index);
void				check_ynx_nl(t_curs *curseur, t_line *cur);
void				check_max(t_curs *curseur, int len);
void				check_screen(t_curs *curseur);
void				init_curs(t_curs *curseur, int prompt);
/*
** completion
*/
t_line				*completion(t_edit *edit);
t_line				*completion_inv(t_edit *edit);
#endif
