/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:59:56 by ybendavi          #+#    #+#             */
/*   Updated: 2021/09/30 18:19:44 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		write(1, "Wrong number of arguments\n",
			ft_strlen("Wrong number of arguments\n"));
		return (1);
	}
	return (ft_pipex(argv, env));
}
