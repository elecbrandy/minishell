/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 00:58:04 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 17:15:14 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_node(t_node *node)
{
	int		cnt;
	t_node	*cur;

	cnt = 0;
	cur = node;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	return (cnt);
}

void redirect_io(int in_fd, int out_fd)
{
	if (in_fd != STDIN)
	{
		if (dup2(in_fd, STDIN) == -1)
		{
			exit(1); // Error
		}
		fprintf(stderr, "in_fd : %d\n", in_fd);
		close(in_fd);
	}
	if (out_fd != STDOUT)
	{
		if (dup2(out_fd, STDOUT) == -1)
		{
			exit(1); // Error
		}
		fprintf(stderr, "out_fd : %d\n", out_fd);
		close(out_fd);
	}
}

void	wait_process(int cnt)
{
	int	status;
	int	i;

	i = 0;
	while (i < cnt)
	{
		wait(&status);
		i++;
	}
}

void close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
