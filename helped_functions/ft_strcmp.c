/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 06:48:43 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/23 07:00:57 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	temp;

	temp = 0;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue ;
		}
		else
		{
			temp = 1;
			break ;
		}
	}
	return (temp);
}
