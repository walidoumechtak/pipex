/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:21:25 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/23 16:29:53 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_perror(void)
{
	perror("Failed to open file");
	exit(0);
}

void	init_struct_elem(t_pipe *ptr, int ac, char **av, char **env)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		ptr->cmd1 = get_cmd_from_input(av[3]);
		ptr->cmd2 = get_cmd_from_input(av[4]);
		ptr->path_cmd1 = path_cmd(env[6], ptr->cmd1[0]);
		ptr->path_cmd2 = path_cmd(env[6], ptr->cmd2[0]);
		ptr->fd_outfile = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
		ptr->fd_infile = open("temp", O_WRONLY | O_CREAT, 0777);
		if (ptr->fd_infile == -1 && ac == 6)
			ft_perror();
	}
	else
	{
		ptr->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		ptr->fd_infile = open(av[1], O_RDONLY);
		if (ptr->fd_infile == -1 && ac > 5)
			ft_perror();
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
	char **arr;
	
	write(1, "pipe heredoc> ", 15);
	ptr->line = get_next_line(0);
	if (!ptr->line)
		return ;
	while (ptr->line)
	{
		arr = ft_split(ptr->line, '\n');
		if (ft_strcmp(arr[0], av[2]) == 0)
			break;
		free_all(arr);
		fd_put_string(ptr->line, ptr->fd_infile);
		free(ptr->line);
		write(1, "pipe heredoc> ", 15);
		ptr->line = get_next_line(0);
	}
	if (ptr->path_cmd2 == NULL && ac == 6)
		perror("command not found");
	free(ptr->line);
}

void	here_doc(t_pipe *ptr, int ac, char **av, char **env)
{
	init_struct_elem(ptr, ac, av, env);
	if (pipe(ptr->fd) < 0)
		return ;
	pipe(ptr->fd);
	read_here_doc(ptr, av, ac);
	close(ptr->fd_infile);
	ptr->fd_infile = open("temp", O_RDONLY);
	ptr->pid = fork();
	if (ptr->pid == 0)
	{
		dup_and_execev(ptr, 1, env);
	}
	else
	{
		dup_and_execev(ptr, 2, env);
	}
	while (wait(NULL) != -1)
		;
}
// ./pipex here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file

void	multiple_pipe(t_pipe *ptr, int ac, char **av, char **env)
{
	ptr->i = 2;
	init_struct_elem(ptr, ac, av, env);
	if (pipe(ptr->fd) < 0)
		return ;
	pipe(ptr->fd);
	ptr->pid = fork();
	while (ptr->i < ac - 1)
	{
		ptr->cmd1 = get_cmd_from_input(av[ptr->i]);
		ptr->cmd2 = get_cmd_from_input(av[ptr->i + 1]);
		ptr->path_cmd1 = path_cmd(env[6], ptr->cmd1[0]);
		ptr->path_cmd2 = path_cmd(env[6], ptr->cmd2[0]);
		if (ptr->pid == 0)
		{
			dup_and_execev(ptr, 1, env);
		}
		else
		{
			dup_and_execev(ptr, 2, env);
		}
		ptr->i += 2;
	}
	while (wait(NULL) != -1)
		;
}

int	main(int ac, char **av, char **env)
{
	t_pipe	*ptr;

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