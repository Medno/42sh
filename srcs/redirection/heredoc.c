/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:30:25 by hlely             #+#    #+#             */
/*   Updated: 2018/05/03 09:26:11 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*create_newheredoc(char *line)
{
	int		nb;
	int		fd;
	char	*wnb;
	char	*heredoc;

	nb = 0;
	heredoc = ft_strdup("/tmp/.heredoc");
	wnb = ft_itoa(nb);
	heredoc = ft_strjoindel(heredoc, wnb);
	while ((fd = open(heredoc, O_CREAT | O_EXCL | O_WRONLY, 0644)) == -1)
	{
		ft_strdel(&heredoc);
		ft_strdel(&wnb);
		nb++;
		heredoc = ft_strdup("/tmp/.heredoc");
		wnb = ft_itoa(nb);
		heredoc = ft_strjoindel(heredoc, wnb);
	}
	(line && *line) ? ft_putendl_fd(line, fd) : 0;
	close(fd);
	ft_strdel(&line);
	ft_strdel(&wnb);
	return (heredoc);
}

void	rm_here(char *heredoc)
{
	char	**arg;
	pid_t	father;

	arg = (char**)ft_memalloc(sizeof(char*) * 4);
	arg[0] = ft_strdup("/bin/rm");
	arg[1] = ft_strdup("-rf");
	arg[2] = ft_strdup(heredoc);
	arg[3] = NULL;
	father = fork();
	if (father)
		wait(0);
	else
	{
		execve("/bin/rm", arg, NULL);
		exit(0);
	}
	ft_strdel(&arg[0]);
	ft_strdel(&arg[1]);
	ft_strdel(&arg[2]);
	if (arg)
		free(arg);
}

void	del_heredoc(void)
{
	int		nb;
	int		fd;
	char	*wnb;
	char	*heredoc;

	nb = 0;
	wnb = NULL;
	heredoc = ft_strdup("/tmp/.heredoc");
	wnb = ft_itoa(nb);
	heredoc = ft_strjoindel(heredoc, wnb);
	while ((fd = open(heredoc, O_RDONLY)) != -1)
	{
		close(fd);
		rm_here(heredoc);
		nb++;
		ft_strdel(&heredoc);
		heredoc = ft_strdup("/tmp/.heredoc");
		ft_strdel(&wnb);
		wnb = ft_itoa(nb);
		heredoc = ft_strjoindel(heredoc, wnb);
	}
	ft_strdel(&heredoc);
	ft_strdel(&wnb);
}
