/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:21:34 by ybendavi          #+#    #+#             */
/*   Updated: 2021/10/20 15:20:08 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	error(char *text_error)
{
	perror(text_error);
	exit(EXIT_FAILURE);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && (i + j) < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
			{
				res = (char *)&big[i];
				return (res);
			}
			j++;
		}
		i++;
	}
	res = NULL;
	return (res);
}

char	**set_env(char **env)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 6) == NULL)
		i++;
	paths = ft_split(ft_strchr(env[i], '=') + 1, ':');
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	**set_args_asset(char **args, char *cmd, char **paths, int i)
{	
	args[0] = ft_strjoin(paths[i], cmd);
	i++;
	while (paths[i] && access(args[0], X_OK) == -1)
	{
		free(args[0]);
		args[0] = ft_strjoin(paths[i], cmd);
		i++;
	}
	free(cmd);
	return (args);
}

char	**set_args(char **argv, char **env)
{
	char	**args;
	char	*cmd;
	char	**paths;
	int		i;

	paths = set_env(env);
	args = ft_split(argv[0], ' ');
	cmd = ft_strdup(args[0]);
	free(args[0]);
	i = 0;
	if (access(cmd, X_OK) != -1)
		args[0] = cmd;
	else
		args = set_args_asset(args, cmd, paths, i);
	freeer(paths);
	return (args);
}
