/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:23:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/19 20:27:01 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_pipe
{
	int		fd[2];
	int		fd_outfile;
	int		fd_infile;
	int		pid;
	int		stdout_copy;
	int		stdin_copy;
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
}			t_pipe;

char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strcat(char *s1, char *s2);
void	free_all(char **s);
char	*remove_equal_from_path(char *str);
char	**get_cmd_from_input(char *str);
char	*path_cmd(char *str, char *cmd);

#endif