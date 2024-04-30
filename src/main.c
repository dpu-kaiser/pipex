/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:35:21 by dkaiser           #+#    #+#             */
/*   Updated: 2024/04/30 17:37:09 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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

}
