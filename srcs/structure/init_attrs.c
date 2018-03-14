/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:09:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/03/14 11:49:14 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_cfmakeraw(struct termios *my_state)
{
	my_state->c_lflag &= ~(ICANON | ECHO);
	my_state->c_cc[VMIN] = 1;
	my_state->c_cc[VTIME] = 0;
	my_state->c_cc[VDSUSP] = _POSIX_VDISABLE;
	my_state->c_cc[VSUSP] = _POSIX_VDISABLE;
	my_state->c_cc[VINTR] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSADRAIN, my_state);
}

void	ft_cfmakedefault(struct termios *my_state)
{
	my_state->c_lflag |= (ICANON | ECHO);
	my_state->c_cc[VINTR] = 3;
	tcsetattr(STDIN_FILENO, TCSADRAIN, my_state);
}

void	ft_cfmakeinit(struct termios *my_state)
{
	my_state->c_lflag |= (ICANON | ECHO);
	my_state->c_cc[VINTR] = 3;
	my_state->c_cc[VDSUSP] = 25;
	my_state->c_cc[VSUSP] = 26;
	tcsetattr(STDIN_FILENO, TCSADRAIN, my_state);
}
