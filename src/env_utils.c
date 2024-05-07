/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:19:31 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/07 16:02:38 by dkaiser          ###   ########.fr       */
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

char	*get_cmd_path(char *cmd, char **path, char *pwd)
{
	char	*cur_dir;
	char *lone_cmd;
	int len;
	char *res;

	if (cmd[0] == '/')
		return (cmd); // TODO: Maybe use duplicate instead,	so there will be no problem on free()
	else if (ft_strchr(cmd, '/'))
	{
		cur_dir = ft_strjoin(pwd, "/");
		// TODO: Free on fail
		// TODO: Maybe check if executable, else there might be a problem...
		return (ft_strjoin(cur_dir, cmd));
	}
	else if (ft_strchr(cmd, ' '))
	{
		len = ft_strchr(cmd, ' ') - cmd + 1;
		lone_cmd = malloc(len * sizeof(char));
		// TODO: Free on fail
		ft_strlcpy(lone_cmd, cmd, len);
		res = find_in_path(lone_cmd, path);
		if (!res)
			return (NULL);
		return(ft_strjoin(res, ft_strchr(cmd, ' ')));
	}
	else
	{
		return (find_in_path(cmd, path));
	}
}
