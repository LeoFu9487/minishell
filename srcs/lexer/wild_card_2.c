/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 22:53:33 by yfu               #+#    #+#             */
/*   Updated: 2021/06/19 02:33:56 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub_sub(char *str[4], int *is_matched, t_deque *tokens)
{
	if (*str[2] == 0)
	{
		*is_matched = 1;
		deque_push_back(tokens, init_token(str[1], _undefined));
	}
	else
	{
		ft_strcat(str[1], "/");
		if (str[2][1])
			wild_card_recursive(str[1], str[2] + 1, is_matched, tokens);
		else
			deque_push_back(tokens, init_token(str[1], _undefined));
	}
}

static void	sub(char *str[4], int *is_matched, t_deque *all_files,
t_deque *tokens)
{
	t_double_list	*iterator;

	iterator = all_files->head;
	while (iterator)
	{
		str[1] = ft_calloc(ft_strlen(str[3]) + ft_strlen(iterator->content) + 2,
				sizeof(char));
		ft_strcat(str[1], str[3]);
		ft_strcat(str[1], iterator->content);
		if ((*str[2] == 0 || is_dir(str[1])) && match(str[0], iterator->content,
				NULL, NULL))
			sub_sub(str, is_matched, tokens);
		iterator = iterator->next;
	}
}

void	wild_card_recursive(char *path, char *pattern, int *is_matched,
t_deque *tokens)
{
	t_deque			*all_files;
	char			*str[4];
	int				cnt[2];

	if (pattern[0] == '.')
		all_files = get_files_start_from_dot(path);
	else
		all_files = get_files_not_dot(path);
	str[0] = ft_calloc(ft_strlen(pattern) + 1, sizeof(char));
	cnt[0] = 0;
	while (*pattern && *pattern != '/')
		str[0][cnt[0]++] = *(pattern++);
	str[2] = pattern;
	str[3] = path;
	sub(str, is_matched, all_files, tokens);
	ft_free(path);
	ft_free(str[0]);
	deque_clear(all_files, ft_free);
}
