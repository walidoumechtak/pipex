/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:23:03 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/25 13:36:18 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef	struct s_path_cmd
{
	int i;
	char **p;
	char *res;
	char *removed_equal;
	char *joined;
	char *temp;
}				t_path_cmd;

typedef struct s_pipe
{
	int		fd[2];
	int		fd_outfile;
	int		fd_infile;
	int		fd_temp_file;
	int		pid;
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;
	char	*line;
	int	i;
	t_path_cmd	path;
}			t_pipe;

char		**ft_split(char const *s, char c);
// char		*ft_strdup(const char *s1);
// char		*ft_strjoin(char const *s1, char const *s2);
// size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strcat(char *s1, char *s2);
void		free_all(char **s);
char		*remove_equal_from_path(char *str);
char		**get_cmd_from_input(char *str);
char		*path_cmd(t_pipe *ptr, char **str, char *cmd);
void		fd_put_string(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);


void	ft_perror_fork(void);
void	ft_perror_open(void);
void ft_perror_pipe(void);

#endif