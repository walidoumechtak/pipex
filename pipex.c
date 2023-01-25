/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:22:35 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/25 13:20:01 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_perror(void)
{
	perror("Failed to open file");
	exit(1);
}

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->cmd1 = get_cmd_from_input(av[2]);
	ptr->cmd2 = get_cmd_from_input(av[3]);
	ptr->path_cmd1 = path_cmd(ptr, env, ptr->cmd1[0]);
	ptr->path_cmd2 = path_cmd(ptr, env, ptr->cmd2[0]);
	ptr->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	ptr->fd_infile = open(av[1], O_RDONLY);
	if (ptr->fd_infile == -1 && ac == 5)
		ft_perror();
	if (ptr->path_cmd2 == NULL && ac == 5)
	{
		ft_printf("commande not found : %s\n", ptr->cmd2[0]);
		if (ptr->path_cmd1 != NULL)
		{
			free(ptr);
			exit(1);
		}
	}
	if (ptr->path_cmd2 == NULL && ptr->path_cmd1 == NULL && ac == 5)
	{
		ft_printf("commande not found : %s", ptr->cmd1[0]);
		free(ptr);
		exit(1);
	}
}

void	dup_and_execev(t_pipe *ptr, int n, char **env)
{
	if (n == 1)
	{
		close(ptr->fd[0]);
		dup2(ptr->fd_infile, 0);
		dup2(ptr->fd[1], 1);
		execve(ptr->path_cmd1, ptr->cmd1, env);
		close(ptr->fd[1]);
	}
	else
	{
		close(ptr->fd[1]);
		dup2(ptr->fd[0], 0);
		dup2(ptr->fd_outfile, 1);
		execve(ptr->path_cmd2, ptr->cmd2, env);
		close(ptr->fd[0]);
	}
}

void	ft_errors(char *s)
{
	ft_printf("%s\n", s);
	exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*ptr;

	ptr = malloc(sizeof(t_pipe));
	if (!ptr)
		return (1);
	init_struct_elem(ptr, ac, av, env);
	if (ac == 5)
	{
		if (pipe(ptr->fd) < 0)
			ft_errors("failed to pipe");
		ptr->pid = fork();
		if (ptr->pid < 0)
			ft_errors("failed to fork");
		if (ptr->pid == 0)
			dup_and_execev(ptr, 1, env);
		else
			dup_and_execev(ptr, 2, env);
		close(ptr->fd[0]);
		close(ptr->fd[1]);
		while (wait(NULL) != -1)
			;
	}
	else
		write(2, "to many argements !\n", 20);
	free(ptr);
}
