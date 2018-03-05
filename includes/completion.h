/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 15:48:12 by kyazdani          #+#    #+#             */
/*   Updated: 2018/02/28 11:12:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

# include "sh.h"
# include "types.h"

/*
** POUR COMPLETION
*/
void				do_completion(t_comp *comp, t_env *env);
void				get_word_to_complete(t_comp *comp);
void				comp_get_pot_cmd(t_comp *comp);
void				comp_get_pot_dir(t_comp *comp);
void				comp_get_pot_dir_exec(t_comp *comp);
void				comp_get_dir_to_open(t_comp *comp);
void				comp_sort_alphab(t_comp *comp);
void				comp_check_duplicate(t_comp *comp);

/*
**	COMPLETION TOOLS
*/
int					comp_is_first_word(t_comp *comp);
int					comp_has_slash(char *str);


t_lcomp				*lcomp_push_back(t_lcomp *list, t_lcomp *new);
t_lcomp				*init_t_lcomp(void);
t_comp				*init_t_comp(void);
void				ft_clean_lcomp(t_lcomp *elm);
void				ft_clean_lcomp_list(t_lcomp *list);
int					reset_completion(char c, t_comp *comp);
char				*comp_go_to_last_slash(char *str);

#endif