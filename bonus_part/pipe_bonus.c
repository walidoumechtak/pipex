/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:21:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/25 13:07:59 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_perror_open(void)
{
	perror("Failed to open file");
}

void	ft_perror_fork(void)
{
	perror("Failed to create a proccess");
}

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		ptr->cmd1 = get_cmd_from_input(av[3]);
		ptr->cmd2 = get_cmd_from_input(av[4]);
		ptr->path_cmd1 = path_cmd(ptr, env, ptr->cmd1[0]);
		ptr->path_cmd2 = path_cmd(ptr, env, ptr->cmd2[0]);
		ptr->fd_outfile = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
		ptr->fd_infile = open("temp", O_WRONLY | O_CREAT, 0777);
		if (ptr->fd_infile == -1 && ac == 6)
			ft_perror_open();
		
	}
	else
	{
		ptr->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		ptr->fd_infile = open(av[1], O_RDONLY);
		if ((ptr->fd_infile < 0 || ptr->fd_outfile < 0) && ac > 5)
			ft_perror_open();
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
		unlink("temp");
		execve(ptr->path_cmd2, ptr->cmd2, env);
		close(ptr->fd[0]);
	}
}

void	read_here_doc(t_pipe *ptr, char **av, int ac)
{
	char	**arr;

	write(1, "pipe heredoc> ", 15);
	ptr->line = get_next_line(0);
	if (!ptr->line)
		return ;
	while (ptr->line)
	{
		arr = ft_split(ptr->line, '\n');
		if (ft_strcmp(arr[0], av[2]) == 0)
			break ;
		free_all(arr);
		fd_put_string(ptr->line, ptr->fd_infile);
		free(ptr->line);
		write(1, "pipe heredoc> ", 15);
		ptr->line = get_next_line(0);
	}
	if (ptr->path_cmd2 == NULL && ac == 6) // ==================
		{
			ft_printf("commande not found: %s\n", ptr->cmd2[0]);
			if (ptr->path_cmd1 != NULL)
			{
				free(ptr);
				exit(1);
			}
		}
		if (ptr->path_cmd2 == NULL && ptr->path_cmd1 == NULL && ac == 6)
		{
			ft_printf("commande not found: %s", ptr->cmd1[0]);
			free(ptr);
			exit(1);
		} // =====================
		
	free(ptr->line);
}

void	here_doc(t_pipe *ptr, int ac, char **av, char **env)
{
	init_struct_elem(ptr, ac, av, env);
	if (pipe(ptr->fd) < 0)
		return ;
	read_here_doc(ptr, av, ac);
	close(ptr->fd_infile);
	ptr->fd_infile = open("temp", O_RDONLY);
	if (ptr->fd_infile < 0)
		ft_perror_open();
	ptr->pid = fork();
	if (ptr->pid < 0)
		ft_perror_fork();
	if (ptr->pid == 0)
		dup_and_execev(ptr, 1, env);
	else
		dup_and_execev(ptr, 2, env);
	while (wait(NULL) != -1)
		;
}

void	multiple_pipe(t_pipe *ptr, int ac, char **av, char **env)
{
	int fd[2];
	int pid;
	int	i;
	
	i = 2;
	init_struct_elem(ptr, ac, av, env);
	dup2(ptr->fd_infile, 0);
	while (i < ac - 1)
	{
		ptr->cmd1 = get_cmd_from_input(av[i]);
		ptr->path_cmd1 = path_cmd(ptr, env, ptr->cmd1[0]);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (i == ac - 2)
				dup2(ptr->fd_outfile, 1);
			else
				dup2(fd[1], 1);
			execve(ptr->path_cmd1, ptr->cmd1, env);
		}
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
}

int	main(int ac, char **av, char **env)
{
	t_pipe *ptr;

	ptr = malloc(sizeof(t_pipe));
	if (!ptr)
		return (1);
	if (ft_strcmp(av[1], "here_doc") == 0 && ac == 6)
		here_doc(ptr, ac, av, env);
	else
	{
		if (ac >= 5)
			multiple_pipe(ptr, ac, av, env);
	}
	free(ptr);
}