/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:52:35 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/13 13:32:11 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XXI_SH_H
# define XXI_SH_H

# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <term.h>
# include <dirent.h>
# include <termios.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct		s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

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

typedef enum		e_token
{
	STR, INT, REDIR, QUOTE, SEMICOLON, NONE
}					t_token;

typedef struct		s_lex
{
	t_token			token;
	char			*value;
	int				number;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;
/*
 ** builtins >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
void				ft_cd(t_env **env, char **str, int len);
void				ft_cd_l(t_env **env, char *curpath, char *dir);
char				**delete_and_paste(char **arr, int i);
char				*paste_strs(char *str, char *new);
char				*paste_path(char *s1, char *s2);
void				handle_cd_error(char *str);
void				ft_echo(t_env **env, char **str);
void				ft_env(t_env *env, char **entry);
void				ft_setenv(t_env **list, char *name, char *content);
void				ft_unsetenv(t_env **list, char *name);
/*
 ** environment >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
void				free_list(t_env **env);
int					count_list_len(t_env **env);
char				**put_in_tab(t_env **env);
char				*ft_getenv(t_env **env, char *elem);
t_env				*create_env(char **arr);
void				insert_env_start(t_env **env);
/*
 ** addons >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
int					put_path(t_env **env);
/*
 ** historic >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
t_hist				*new_hist(void);
void				hist_to_file(t_hist *historic);
/*
 ** attrs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
void				ft_cfmakeraw(struct termios *my_state);
void				ft_cfmakedefault(struct termios *my_state);
/*
 **  line_edit >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 */
int					ft_line_edition(char **line, int prompt_len, t_hist **histo);
t_line				*ft_line_usual(t_line *current, char c, int prompt, t_curs *curseur);
t_line				*line_delone(t_line *cur, int prompt, t_curs *curseur);
t_line				*del_next(t_line *cur);
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
 *** termcaps setup
 */
char				*get_ttyname(void);
int					init_termcaps(void);
/*
** lexer manipulation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
t_lex				*lexer(char *str);
t_lex				*init_lexer(void);
void				del_lex(t_lex *first);
int					isredir(char c);
t_lex				*lex_copy_str(t_lex *new, char *str, int *i);
t_lex				*lex_copy_int(t_lex *new, char *str, int *i);
t_lex				*lex_copy_redir(t_lex *new, char *str, int *i);
t_lex				*lex_copy_quote(t_lex *new, char *str, int *i, int len);


#endif
