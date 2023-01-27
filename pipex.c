/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 05:27:00 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/27 09:59:56 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(t_pipe *ptr, char **av, int ac)
{
	if ((ptr->fd_infile < 0) && ac == 5)
		ft_printf("no such file or directory: %s\n", av[1]);
	if ((ptr->fd_outfile < 0) && ac == 5)
		ft_perror_open(ptr);
	if (ptr->path_cmd2 == NULL && ac == 5)
	{
		ft_printf("commande not found : %s\n", ptr->cmd2[0]);
		if (ptr->path_cmd1 != NULL)
		{
			free(ptr);
			exit(127);
		}
	}
	if (ptr->path_cmd2 == NULL && ptr->path_cmd1 == NULL && ac == 5)
	{
		ft_printf("commande not found : %s", ptr->cmd1[0]);
		free(ptr);
		exit(127);
	}
}

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->cmd1 = get_cmd_from_input(av[2]);
	ptr->cmd2 = get_cmd_from_input(av[3]);
	ptr->path_cmd1 = path_cmd(ptr, env, ptr->cmd1[0]);
	ptr->path_cmd2 = path_cmd(ptr, env, ptr->cmd2[0]);
	ptr->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	ptr->fd_infile = open(av[1], O_RDONLY);
	handle_error(ptr, av, ac);
}

void	cmd1(t_pipe *ptr, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_perror_fork(ptr);
	if (pid == 0)
	{
		close(ptr->fd[0]);
		if (ptr->fd_infile < 0)
			ft_perror_open(ptr);
		if (!ptr->path_cmd1)
		{
			ft_printf("commande not found : %s\n", ptr->cmd1[0]);
			exit(127);
		}
		dup2(ptr->fd_infile, 0);
		dup2(ptr->fd[1], 1);
		close(ptr->fd[1]);
		execve(ptr->path_cmd1, ptr->cmd1, env);
	}
}

void	cmd2(t_pipe *ptr, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_perror_fork(ptr);
	if (pid == 0)
	{
		close(ptr->fd[1]);
		dup2(ptr->fd[0], 0);
		dup2(ptr->fd_outfile, 1);
		close(ptr->fd[0]);
		execve(ptr->path_cmd2, ptr->cmd2, env);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*ptr;

	if (ac == 5)
	{
		ptr = malloc(sizeof(t_pipe));
		if (!ptr)
			return (2);
		if (pipe(ptr->fd) < 0)
			ft_perror_pipe(ptr);
		init_struct_elem(ptr, ac, av, env);
		cmd1(ptr, env);
		cmd2(ptr, env);
		close(ptr->fd[0]);
		close(ptr->fd[1]);
		while (wait(NULL) != -1)
			;
		free(ptr);
	}
	else
		ft_printf("number of argements is not correct ...\n");
	return (0);
}
