/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_equal_from_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woumecht <woumecht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:24:02 by woumecht          #+#    #+#             */
/*   Updated: 2023/01/19 20:24:28 by woumecht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*remove_equal_from_path(char *str)
{
	char	**arr;
	char	*res;

	res = NULL;
	arr = ft_split(str, '=');
	res = ft_strjoin(res, arr[1]);
	free_all(arr);
	return (res);
}