/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:13:23 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/02 15:36:43 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	**get_split_path(char *envp[])
{
	char	*path;

	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

static char	*get_pwd(char *envp[])
{
	while (!ft_strnstr(*envp, "PWD=", 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 4);
}

static char	*find_in_path(char *cmd, char **path)
{
	char	*cur_path;
	char	*cmd_path;

	cmd_path = NULL;
	while (*path)
	{
		if (cmd_path)
			free(cmd_path);
		cur_path = ft_strjoin(*path, "/");
		// TODO: Free on fail
		cmd_path = ft_strjoin(cur_path, cmd);
		free(cur_path);
		if (access(cmd_path, X_OK) != -1)
			return (cur_path);
		path++;
	}
	return (NULL);
}

static char	*get_cmd_path(char *cmd, char **path, char *pwd)
{
	char	*cur_dir;

	if (cmd[0] == '/')
		return (cmd); // TODO: Maybe use duplicate instead, so there will be no problem on free()
	else if (strchr(cmd, '/'))
	{
		cur_dir = ft_strjoin(pwd, "/");
		// TODO: Free on fail
		// TODO: Maybe check if executable, else there might be a problem...
		return (ft_strjoin(cur_dir, cmd));
	}
	else
    {
        return (find_in_path(cmd, path));
    }
}

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
	// TODO: Free on fail
	pwd = get_pwd(envp);
	i = 2;
	while (i < argc - 1)
	{
		cmds[i - 2] = get_cmd_path(argv[i], path, pwd);
		i++;
	}
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (cmds);
}

t_pxdata	*get_pxdata(int argc, char *argv[], char *envp[])
{
	t_pxdata	*result;

	result = malloc(sizeof(t_pxdata));
	if (!result)
		return (NULL); // TODO: Check if an error message needs to be sent
	result->in_fd = open(argv[1], O_RDONLY);
	result->out_fd = open(argv[--argc], O_WRONLY | O_CREAT | O_TRUNC);
	result->cmds = get_cmds(argc, argv, envp);
	return (result);
}
