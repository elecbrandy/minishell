/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 16:36:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	run_cmd(t_env *head_env, t_node *node);
static int	check_cmds(char **cmds, char *cmd);
static int	ft_find_word(char *str, char *word);

int	ft_execve(t_env **head_env, t_node *node, char *home, pid_t pid)
{
	int	error;

	if (is_builtin(node) != 0)
		exec_builtin(head_env, node, home, pid);
	else
	{
		error = run_cmd(*head_env, node);
		if (error == 12)
			g_signal_error = 12;
		print_error();
	}
	exit(g_signal_error);
}

static int	run_cmd(t_env *head_env, t_node *node)
{
	char	**envp;

	envp = env_list_to_array(head_env);
	if (!envp)
		return (12);
	if (execve(node->path, node->cmd, envp) == -1)
		return (127);
	return (0);
}

void	is_inchild(char *cmd)
{
	char	**cmds;

	cmds = malloc(sizeof(char *) * (18));
	cmds[17] = NULL;
	cmds[0] = ft_strdup("wc");
	cmds[1] = ft_strdup("cmp");
	cmds[2] = ft_strdup("awk");
	cmds[3] = ft_strdup("split");
	cmds[4] = ft_strdup("cat");
	cmds[5] = ft_strdup("cut");
	cmds[6] = ft_strdup("sed");
	cmds[7] = ft_strdup("tr");
	cmds[8] = ft_strdup("diff");
	cmds[9] = ft_strdup("diff3");
	cmds[10] = ft_strdup("grep");
	cmds[11] = ft_strdup("egrep");
	cmds[12] = ft_strdup("fgrep");
	cmds[13] = ft_strdup("head");
	cmds[14] = ft_strdup("tail");
	cmds[15] = ft_strdup("rev");
	cmds[16] = ft_strdup("sort");
	cmds[17] = NULL;
	check_cmds(cmds, cmd);
	free_str(cmds);
}

static int	check_cmds(char **cmds, char *cmd)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (ft_find_word(cmd, cmds[i]))
		{
			signal(SIGINT, child_handler);
			signal(SIGQUIT, child_handler);
			return (1);
		}
	}
	return (0);
}

static int	ft_find_word(char *str, char *word)
{
	int	i;
	int	j;
	int	start;

	i = -1;
	while (str[++i])
	{
		start = 0;
		if (str[i] == word[start])
		{
			j = i;
			while (str[j])
			{
				if (str[j] != word[start])
					break ;
				j++;
				start++;
				if (word[start] == 0)
					return (1);
			}
		}
	}
	return (0);
}
