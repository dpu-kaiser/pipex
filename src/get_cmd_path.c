/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:35:47 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/08 11:39:44 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_absolute_cmd_path(char *cmd, char *pwd)
{
	char	*cur_dir;
	char	*result;

	cur_dir = ft_strjoin(pwd, "/");
	if (!cur_dir)
		return (NULL);
	result = ft_strjoin(cur_dir, cmd);
	free(cur_dir);
	if (!result)
		return (NULL);
	if (access(result, X_OK) == -1)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

static char	*get_cmd_path_with_args(char *cmd, char **path)
{
	int		len;
	char	*lone_cmd;
	char	*cmd_path;
	char	*result;

	len = ft_strchr(cmd, ' ') - cmd + 1;
	lone_cmd = malloc(len * sizeof(char));
	if (!lone_cmd)
		return (NULL);
	ft_strlcpy(lone_cmd, cmd, len);
	cmd_path = find_in_path(lone_cmd, path);
	free(lone_cmd);
	if (!cmd_path)
		return (NULL);
	result = ft_strjoin(cmd_path, ft_strchr(cmd, ' '));
	free(cmd_path);
	return (result);
}

char	*get_cmd_path(char *cmd, char **path, char *pwd)
{
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	else if (ft_strchr(cmd, '/'))
	{
		return (get_absolute_cmd_path(cmd, pwd));
	}
	else if (ft_strchr(cmd, ' '))
	{
		return (get_cmd_path_with_args(cmd, path));
	}
	else
	{
		return (find_in_path(cmd, path));
	}
}
