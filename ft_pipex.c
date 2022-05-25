/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybendavi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:48:55 by ybendavi          #+#    #+#             */
/*   Updated: 2021/10/20 20:28:44 by ybendavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	child1_process(int *pfd, char ***args, int *fds, char **env)
{
	close(pfd[0]);
	if (dup2(fds[0], 0) != -1)
	{
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve(args[0][0], &args[0][0], env);
		error("command not found");
		exit(EXIT_FAILURE);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}

int	child2_process(int *pfd, char ***args, int *fds, char **env)
{
	close(pfd[1]);
	dup2(pfd[0], 0);
	if (dup2(fds[1], 1) != -1)
	{
		close(pfd[0]);
		execve(args[1][0], &args[1][0], env);
		perror("command not found");
		freeer(args[0]);
		freeer(args[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		freeer(args[0]);
		freeer(args[1]);
		exit(EXIT_FAILURE);
	}
}

int	parent_process(int *pfd, int status, pid_t child1, pid_t child2)
{
	close(pfd[0]);
	close(pfd[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_pipe(char ***args, int *fds, char **env)
{
	int		pfd[2];
	int		status;
	int		code;
	pid_t	child1;
	pid_t	child2;

	if (pipe(pfd) == -1)
		error(NULL);
	child1 = fork();
	if (child1 < 0)
		perror(NULL);
	if (child1 == 0)
		child1_process(pfd, args, fds, env);
	child2 = fork();
	if (child2 < 0)
		perror(NULL);
	if (child2 == 0)
		code = child2_process(pfd, args, fds, env);
	else
		code = parent_process(pfd, status, child1, child2);
	return (code);
}

int	ft_pipex(char **argv, char **env)
{
	char	**args[2];
	int		fds[2];
	int		status_code;

	fds[0] = open(argv[1], O_RDONLY);
	if (fds[0] == -1)
		perror(argv[1]);
	fds[1] = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0666 | O_TRUNC);
	if (fds[1] == -1)
		perror(argv[4]);
	args[0] = set_args(&argv[2], env);
	args[1] = set_args(&argv[3], env);
	status_code = ft_pipe(args, fds, env);
	freeer(args[0]);
	freeer(args[1]);
	close(fds[0]);
	close(fds[1]);
	return (status_code);
}
