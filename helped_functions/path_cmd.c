/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:26:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/27 09:29:01 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	index_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])) != NULL)
			return (i);
		i++;
	}
	return (0);
}

char	*path_cmd(t_pipe *ptr, char **str, char *cmd)
{
	ptr->path.index = index_path(str);
	if (ptr->path.index == 0)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	ptr->path.removed_equal = remove_equal_from_path(str[ptr->path.index]);
	ptr->path.p = ft_split(ptr->path.removed_equal, ':');
	ptr->path.i = 0;
	while (ptr->path.p[ptr->path.i])
	{
		ptr->path.temp = ft_strjoin(ptr->path.p[ptr->path.i++], "/");
		ptr->path.joined = ft_strjoin(ptr->path.temp, cmd);
		free(ptr->path.temp);
		if (access(ptr->path.joined, F_OK) == 0)
		{
			free_all(ptr->path.p);
			free(ptr->path.removed_equal);
			return (ptr->path.joined);
		}
		free(ptr->path.joined);
	}
	free(ptr->path.removed_equal);
	return (free_all(ptr->path.p), NULL);
}
