/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:25:43 by hyun              #+#    #+#             */
/*   Updated: 2021/12/16 14:41:42 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
	}
	return (1);
}

int	ft_exit(t_list *list, t_info* info)
{
	printf("exit\n");
	if (list->start_node->next == NULL)
		exit(0);
	if (list->start_node->next->next != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		info->exit_status = 1;
		return (1);
	}
	if (list->start_node->next && ft_isnumeric(list->start_node->next->data))
		exit(ft_atoi(list->start_node->next->data));
	else
	{
		printf("minishell: exit: %s: numeric argument required\n",
			list->start_node->next->data);
		exit(255);
	}

}
