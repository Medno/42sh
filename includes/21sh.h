/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  21sh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:30:49 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/05 10:30:02 by kyazdani         ###   ########.fr       */
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
/*
** builtins
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
** env_list_handler (ft_environment.c)
*/
void				free_list(t_env **env);
int					count_list_len(t_env **env);
char				**put_in_tab(t_env **env);
char				*ft_getenv(t_env **env, char *elem);
t_env				*create_env(char **arr);
/*
** addons
*/
void				put_path(t_env **env);
void				insert_env_start(t_env **env);
/*
** attrs
*/
void				ft_cfmakeraw(struct termios *my_state);
void				ft_cfmakedefault(struct termios *my_state);
/*
** line_edit
*/
int                 ft_line_edition(char **line);

char 				*get_ttyname(void);
int 				init_termcaps(void);

#endif