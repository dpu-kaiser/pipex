/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:19:31 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/08 11:40:01 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	**get_split_path(char *envp[])
{
	char	*path;

	while (!ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*get_pwd(char *envp[])
{
	while (!ft_strnstr(*envp, "PWD=", 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (*envp + 4);
}

char	*find_in_path(char *cmd, char **path)
{
	char	*cur_path;
	char	*cmd_path;

	cmd_path = NULL;
	while (*path)
	{
		if (cmd_path)
			free(cmd_path);
		cur_path = ft_strjoin(*path, "/");
		if (!cur_path)
			return (NULL);
		cmd_path = ft_strjoin(cur_path, cmd);
		free(cur_path);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) != -1)
			return (cmd_path);
		path++;
	}
	return (NULL);
}
