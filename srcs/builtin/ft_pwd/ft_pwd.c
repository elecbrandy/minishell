/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:48:20 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 14:07:53 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_node *node)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		g_signal_error = 1;
		print_error();
		return ;
	}
	ft_putstr_fd(str, node->out_fd);
	write(node->out_fd, "\n", 1);
	ft_free((void **)&str);
}
