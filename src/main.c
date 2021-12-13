/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:02:32 by dason             #+#    #+#             */
/*   Updated: 2021/12/13 19:04:15 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_argv_with_node(t_list *list)
{
	int		size;
	t_node	*node;
	char	**argv;

	node = list->start_node;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	argv = (char **)ft_calloc(size + 1, sizeof(char *));
	size = 0;
	node = list->start_node;
	while (node)
	{
		argv[size++] = ft_strdup(node->data);
		node = node->next;
	}
	argv[size] = NULL;
	return (argv);
}

int	move_to_next_command_list(t_list **list)
{
	int		has_next;

	has_next = -1;
	*list = (*list)->next;
	while ((*list) && (*list)->l_type != LTYPE_COMMAND)
	{
		has_next = 0;
		*list = (*list)->next;
	}
	return (has_next);
}

void	run(t_list *work_list, t_info info)
{
	while (work_list)
	{
		handle_redirect(work_list, &info);
		if (try_exec_builtin(work_list, &info) == -1)
			execute_non_builtin(work_list, \
				make_argv_with_node(work_list), info.envp, &info);
		swap_pipe(&info);
		if (move_to_next_command_list(&work_list) == -1)
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_info	info;
	t_list	*list;
	t_list	*work_list;

	if (init_minishell(&info, envp, argc, argv) == -1)
		return (-1);
	while (true)
	{
		input = get_user_input(&info);
		if (is_valid_input(input) == false)
			continue ;
		if (parser(&list, ft_strdup(input)) != -1)
		{
			work_list = list;
			run(work_list, info);
		}
		add_history(input);
		free(input);
		free_list_node(&list);
	}
	return (0);
}
