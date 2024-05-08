/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:35:21 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/08 11:53:26 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>

static void	pipex_child(t_pxdata *data, char *envp[], int p[2])
{
	char	**cmd;
	int		status;

	close(p[0]);
	dup2(data->in_fd, 0);
	dup2(p[1], 1);
	if (!data->cmds[0])
		exit(127);
	cmd = ft_split(data->cmds[0], ' ');
	if (cmd)
	{
		status = execve(cmd[0], cmd, envp);
		ft_free_split(cmd);
		exit(status);
	}
}

static int	pipex_parent(t_pxdata *data, char *envp[], int p[2])
{
	char	**cmd;

	close(p[1]);
	dup2(p[0], 0);
	dup2(data->out_fd, 1);
	if (!data->cmds[1])
		return (EXIT_FAILURE);
	cmd = ft_split(data->cmds[1], ' ');
	if (cmd)
	{
		if (execve(cmd[0], cmd, envp))
			return (EXIT_FAILURE);
		ft_free_split(cmd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int	pipex(t_pxdata *data, char *envp[])
{
	int		result;
	int		p[2];
	pid_t	pid;

	pipe(p);
	result = EXIT_SUCCESS;
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
		pipex_child(data, envp, p);
	else
		result = pipex_parent(data, envp, p);
	close(data->in_fd);
	close(data->out_fd);
	ft_free_split(data->cmds);
	free(data);
	return (result);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pxdata	*data;

	if (argc != 5)
		return (1);
	data = get_pxdata(argc, argv, envp);
	return (pipex(data, envp));
}
