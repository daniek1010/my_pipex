/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:38:48 by danevans          #+#    #+#             */
/*   Updated: 2024/02/27 13:37:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(int pipefd[2], int x)
{
	if (x == 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		exit(0);
	}
	else if (x == 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		error();
}

int	less_args(void)
{
	write(1, "FMT > infile.txt cmd1 cmd2 outfile.txt \n", 41);
	return (0);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	return (pid);
}

int	main(int ac, char *av[], char *envp[])
{
	int		status;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac != 5)
		less_args();
	create_pipe(pipefd);
	pid1 = fork_process();
	if (pid1 == 0)
		execute_command(av, envp, pipefd, 1);
	waitpid(pid1, &status, 0);
	if (status == 256)
		close_fd(pipefd, 0);
	else
	{
		pid2 = fork_process();
		if (pid2 == 0)
			execute_command(av, envp, pipefd, 2);
		close_fd(pipefd, 1);
		waitpid(pid2, NULL, 0);
		exit(0);
	}
}
