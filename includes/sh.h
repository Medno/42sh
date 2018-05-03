/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 08:52:35 by kyazdani          #+#    #+#             */
/*   Updated: 2018/05/03 15:25:32 by hlely            ###   ########.fr       */
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
# include <dirent.h>
# include <termios.h>
# include "libft.h"
# include "ft_printf.h"
# include "types.h"
# include "line_edit.h"
# include "lexer.h"
# include "parser.h"
# include "expansion.h"
# include "exec.h"
# include "redir.h"
# include "completion.h"
# include "vlocal.h"

int		g_quote;
int		g_status;
int		g_oldstatus;
t_init	*g_in;
t_edit	*g_ed;

int					init_all(char **env, t_init *init);
int					read_stdin(char **environ);
int					main_step_2(t_init *init);
/*
** signals
*/
void				sig_write_nl(void);
void				sigint_prompt(void);
void				catch_and_reset(int sig);
/*
** builtins >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
/*
** > cd <
*/
int					ft_cd(t_init *init, char ***entry);
int					ft_cd_l(t_init *init, char *curpath, char *dir);
int					handle_cd_error(char *str);
int					do_cd_home(t_init *init);
int					do_move(char *path, t_init *init, int p);
char				*ft_handle_cdpath(t_init *init, char *dir, int *do_print);

/*
** > echo | env | exit <
*/
void				ft_set_tmp(t_init *init, t_ast *ast, char **arg);
void				clean_init(t_init *init);
char				**cpytab(char **dest, char **src);
char				**shift_arg(char **arg);
int					ft_echo(char **str);
int					ft_env(t_init *init, t_ast *ast, char **entry);
int					ft_setenv(t_env **env, char *name, char *value);
int					ft_setenv_init(t_init *init, char **arg);
int					ft_unsetenv(t_env **list, char *name);
int					ft_biunsetenv(t_init *init, char ***name);
int					ft_exit(t_init *init, char **arg);
int					usage_env(void);
int					ft_print_env(t_env *env, char c);
void				fork_env_cmd(t_init *init, t_ast *ast, char *path);
/*
** > history <
*/
int					ft_history(t_hist **histo, char **entry);
int					free_history(t_hist **histo);
int					free_offset_hist(t_hist **histo, char *offset);
int					print_history(t_hist **histo, char **str);
int					replace_w_arg(t_hist **histo, char **str);
int					append_to_list(t_hist **histo, char *str);
int					full_hist_file(t_hist **histo, char *str);
t_hist				*cleanup_nl_hist(t_hist **histo);
/*
** environment >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
void				free_list(t_env **env);
int					count_list_len(t_env **env);
char				**put_in_tab(t_env **env);
char				*ft_getenv(t_env **env, char *elem);
char				*ft_getenvloc(t_init *init, char *elem);
t_env				*create_env(char **arr);
t_env				*cpyenv(t_env *env);
void				insert_env_start(t_env **env);
/*
** addons >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
int					put_path(t_init *init);
/*
** attrs >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
void				ft_cfmakeraw(struct termios *my_state);
void				ft_cfmakedefault(struct termios *my_state);
void				ft_cfmakeinit(struct termios *my_state);
/*
** path checking >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
*/
char				*paste_path(char *p1, char *p2);
void				free_pathlist(t_path **orig);
t_path				*create_path(char *str);
t_path				*new_pathlist(char *str);
void				remove_elem(t_path *elem, t_path **orig);
void				set_path_info(t_init *init, t_path *pathlist);
char				*pathlist_to_str(t_path *pathlist);
int					go_to_last(char *str, char c);
#endif
