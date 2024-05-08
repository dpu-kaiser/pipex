/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:13:23 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/08 11:54:37 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/_types/_s_ifmt.h>
#include <unistd.h>

static char	**get_cmds(int argc, char *argv[], char *envp[])
{
	char	**cmds;
	int		i;
	char	**path;
	char	*pwd;

	cmds = malloc(sizeof(char *) * (argc - 2));
	if (!cmds)
		return (NULL);
	path = get_split_path(envp);
	if (!path)
		return (NULL);
	pwd = get_pwd(envp);
	i = 2;
	while (i < argc)
	{
		cmds[i - 2] = get_cmd_path(argv[i], path, pwd);
		i++;
	}
	cmds[i - 2] = 0;
	ft_free_split(path);
	return (cmds);
}

t_pxdata	*get_pxdata(int argc, char *argv[], char *envp[])
{
	t_pxdata	*result;

	result = malloc(sizeof(t_pxdata));
	if (!result)
		return (NULL);
	result->in_fd = open(argv[1], O_RDONLY);
	result->out_fd = open(argv[--argc], O_WRONLY | O_CREAT | O_TRUNC,
			S_IREAD | S_IWUSR);
	result->cmds = get_cmds(argc, argv, envp);
	return (result);
}
