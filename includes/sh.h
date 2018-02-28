/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:52:35 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:10:13 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

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
# include "line_edit.h"
# include "types.h"

int		g_quote;

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
** attrs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
void				ft_cfmakeraw(struct termios *my_state);
void				ft_cfmakedefault(struct termios *my_state);
/*
** lexer manipulation >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
t_lex				*lexer(char *str);
t_lex				*init_lexer(void);
void				del_lex(t_lex *first);
void				print_lex(t_lex *first);
/*
** parser >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					parser(t_lex *first);
t_ast				*build_ast(t_lex *first);
t_ast				*init_ast(void);
void				del_ast(t_ast **root);
void				print_ast(t_ast *root, char *pos);
#endif
