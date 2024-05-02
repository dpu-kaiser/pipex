/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:04:28 by dkaiser           #+#    #+#             */
/*   Updated: 2024/05/02 16:22:31 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>

typedef struct s_pxdata
{
	int		in_fd;
	int		out_fd;
	char	**cmds;
}			t_pxdata;

char		**get_split_path(char *envp[]);
char		*get_pwd(char *envp[]);
char		*find_in_path(char *cmd, char **path);
char		*get_cmd_path(char *cmd, char **path, char *pwd);
t_pxdata	*get_pxdata(int argc, char *argv[], char *envp[]);

#endif // PIPEX_H
