/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:26:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/19 20:27:21 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*path_cmd(char *str, char *cmd)
{
	int i;
	char **p;
	char *res;
	char *removed_equal;
	char *joined;
	char *temp;

	removed_equal = remove_equal_from_path(str);
	p = ft_split(removed_equal, ':');
	i = 0;
	while (p[i])
	{
		temp = ft_strjoin(p[i], "/");
		joined = ft_strjoin(temp, cmd);
		free(temp);
		if (access(joined, F_OK) == 0)
		{
			res = joined;
			free_all(p);
			return (res);
		}
		i++;
	}
	free(removed_equal);
	return (free_all(p), NULL);
}