/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyun <hyun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:03:07 by hyun              #+#    #+#             */
/*   Updated: 2021/12/13 10:08:11 by hyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preprocess_pipe_read(t_info *info)
{
	dup2(info->pipe_out[READ_END], STDIN_FILENO);
	close(info->pipe_out[READ_END]);
}

void	preprocess(t_info *info, t_list *list)
{
	if (info->has_pipe_in)
		preprocess_pipe_write(info);
	if (list->prev && list->prev->l_type == LTYPE_PIPE)
		preprocess_pipe_read(info);
	if (info->has_redirect_l1)
		preprocess_l1(info);
	if (info->has_redirect_l2)
		preprocess_l2(info);
	if (info->has_redirect_r1)
		preprocess_r1(info);
	if (info->has_redirect_r2)
		preprocess_r2(info);
}
