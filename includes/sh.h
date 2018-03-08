/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:52:35 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/08 11:28:13 by kyazdani         ###   ########.fr       */
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
# include "lexer.h"
# include "parser.h"
# include "redir.h"
# include "completion.h"

int		g_quote;
/*
** execs
*/
int					exec_start(t_init *init);
int					check_cmd(t_cmd *cmd, t_init *init);
int					check_builtins(char **entry, t_init *init);
int					check_path(char *str, t_env **env, char **s_fin);
/*
** builtins >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
/*
** > cd <
*/
int					ft_cd(t_env **env, char **str, int len);
int					ft_cd_l(t_env **env, char *curpath, char *dir);
char				**delete_and_paste(char **arr, int i);
char				*paste_strs(char *str, char *new);
char				*paste_path(char *s1, char *s2);
int					handle_cd_error(char *str);
/*
** > echo | env | exit <
*/
int					ft_echo(char **str);
int					ft_env(t_env *env, char **entry);
int					ft_setenv(t_env **list, char *name, char *content);
int					ft_unsetenv(t_env **list, char *name);
void				ft_exit(t_init *init);
/*
** > history <
*/
int					ft_history(t_hist **histo, char **str, int len);
int					free_history(t_hist **histo);
int					free_offset_hist(t_hist **histo, char *offset);
int					print_history(t_hist **histo, char **str);
int					replace_w_arg(t_hist **histo, char **str);
int					append_to_list(t_hist **histo, char *str);
int					full_hist_file(t_hist **histo, char *str);
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
#endif
