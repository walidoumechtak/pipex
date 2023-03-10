/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:21:16 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/27 05:50:31 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd_bonus_1(t_pipe *ptr, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_close(ptr, 2);
	if (pid == 0)
	{
		close(ptr->fd[0]);
		dup2(ptr->fd_temp_file, 0);
		dup2(ptr->fd[1], 1);
		close(ptr->fd[1]);
		execve(ptr->path_cmd1, ptr->cmd1, env);
	}
}

void	cmd_bonus_2(t_pipe *ptr, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_close(ptr, 2);
	if (pid == 0)
	{
		close(ptr->fd[1]);
		dup2(ptr->fd[0], 0);
		dup2(ptr->fd_outfile, 1);
		close(ptr->fd[0]);
		unlink("temp");
		execve(ptr->path_cmd2, ptr->cmd2, env);
	}
}
