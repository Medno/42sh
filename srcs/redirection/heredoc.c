/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 16:30:25 by hlely             #+#    #+#             */
/*   Updated: 2018/03/09 17:11:23 by hlely            ###   ########.fr       */
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
	ft_putendl_fd(line, fd);
	close(fd);
	ft_strdel(&line);
	ft_strdel(&wnb);
	return (heredoc);
}

void	rm_here(char *heredoc)
{
	char	**arg;

	//FREE ARG
	arg = (char**)ft_memalloc(sizeof(char*) * 3);
	arg[0] = ft_strdup("/bin/rm");
	arg[1] = ft_strdup(heredoc);
	arg[2] = NULL;
	execve("/bin/rm", arg, NULL);
}

void	del_heredoc(void)
{
	pid_t	father;
	int		nb;
	int		fd;
	char	*wnb;
	char	*heredoc;

	nb = 0;
	heredoc = ft_strdup("/tmp/.heredoc");
	wnb = ft_itoa(nb);
	heredoc = ft_strjoindel(heredoc, wnb);
	while ((fd = open(heredoc, O_RDONLY)) != -1)
	{
		close(fd);
		father = fork();
		if (father)
			wait(0);
		else
		{
			rm_here(heredoc);
			exit(0);
		}
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
