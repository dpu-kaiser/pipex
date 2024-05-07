/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:35:21 by dkaiser           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/04/30 17:37:09 by dkaiser          ###   ########.fr       */
=======
/*   Updated: 2024/05/07 14:38:13 by dkaiser          ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
<<<<<<< Updated upstream
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char *args1[] = {"/bin/cat", 0};
	char *args2[] = {"/usr/bin/grep", "libft", 0};
	int p[2];

	pipe(p);

	pid_t pid = fork();
	if (pid < 0)
	{
		exit(1);
	}
	if (pid == 0)
	{
		close(p[0]);
		int infd = open("in.txt", O_RDONLY);
		dup2(infd, 0);
		dup2(p[1], 1);

		execve(args1[0], args1, NULL);
	}
	else
	{
		wait(NULL);
		close(p[1]);
		dup2(p[0], 0);
		int outfd = open("out.txt", O_WRONLY);
		dup2(outfd, 1);
		execve(args2[0], args2, NULL);
	}

=======
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <unistd.h>
#include <stdio.h>

int pipex(t_pxdata *data, char *envp[])
{
	int p[2];
	pid_t pid;
	char **cmd;
	int status;

	pipe(p);
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		close(p[0]);
		dup2(data->in_fd, 0);
		dup2(p[1], 1);
		if (!data->cmds[0])
			exit(127);
		cmd = ft_split(data->cmds[0], ' '); // TODO: Free on fail
		status = execve(cmd[0], cmd, envp);
		free(cmd);
		exit(status);
	}
	else
	{
		close(p[1]);
		dup2(p[0], 0);
		dup2(data->out_fd, 1);
		if (!data->cmds[1])
			return (EXIT_FAILURE);
		cmd = ft_split(data->cmds[1], ' '); // TODO: Free on fail
		if (execve(cmd[0], cmd, envp))
			return (EXIT_FAILURE);
		free(cmd);
	}
	close(data->in_fd);
	close(data->out_fd);
	return (EXIT_SUCCESS);
}

int main(int argc, char *argv[], char *envp[]) {
	t_pxdata *data;

	if (argc != 5)
		return (1);

	data = get_pxdata(argc, argv, envp);
	/* if (data->in_fd < 0 || data->out_fd < 0) */
	/* 	return (1); */
	/* ft_printf("IN: %d\nOUT: %d\n", data->in_fd, data->out_fd); */
	/* int i = 0; */
	/* while (data->cmds[i]) */
	/* { */
	/* 	ft_printf("CMD [%d]: %s\n", i, data->cmds[i]); */
	/* 	i++; */
	/* } */
	return pipex(data, envp);
>>>>>>> Stashed changes
}
