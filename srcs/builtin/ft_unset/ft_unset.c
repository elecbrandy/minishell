/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:38 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/27 22:02:47 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_unset
	- unset the environment variable
	- if there is no argument, do nothing

	error_log
	- 0 : Success
	- 1 : minishell: unset: `%s': not a valid identifier (invalid key)
	- ex : perror
*/

static void	ft_unset_error(int error, char *path);
static int	unset_witharg(t_env *env, t_node *node);
static void	delete_env(t_env *env, char *key);

void	ft_unset(t_env *head_env, t_node *node)
{
	int	error;

	if (ft_arrlen_2d(node->cmd) == 1 || head_env == NULL)
		return ;
	else
	{
		error = unset_witharg(head_env, node);
		if (error != 0)
			ft_unset_error(error, node->cmd[1]);
	}
}

static int	unset_witharg(t_env *head_env, t_node *node)
{
	int     i;
	char    *key;
	char    *value;

	i = 1;
	while (node->cmd[i])
	{
		if (!is_valid_key(node->cmd[i]))
			return (1);
		else
			delete_env(head_env, node->cmd[i]);
		i++;
	}
	return (0);
}

static void	delete_env(t_env *head_env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = head_env;
	prev = NULL;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				head_env = cur->next;
			ft_free((void **)&cur->cmd);
			ft_free((void **)&cur->key);
			ft_free((void **)&cur->value);
			ft_free((void **)&cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static void ft_unset_error(int error, char *path)
{
	if (error == 0)
		return ;
	else if (error == 1)
	{
		g_signal_error = 1;
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	else
		print_error();
}
