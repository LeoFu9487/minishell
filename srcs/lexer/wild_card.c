/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 02:45:09 by yfu               #+#    #+#             */
/*   Updated: 2021/06/19 02:23:50 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_deque	*get_files_not_dot(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	t_deque			*all_files;

	if (ft_strncmp(path, "", 1) == 0)
		path = ".";
	all_files = deque_init();
	d = opendir(path);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (dir->d_name[0] != '.')
				deque_push_back(all_files, ft_strdup(dir->d_name));
		}
		closedir(d);
	}
	sort_string(all_files);
	return (all_files);
}

t_deque	*get_files_start_from_dot(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	t_deque			*all_files;

	if (ft_strncmp(path, "", 1) == 0)
		path = ".";
	all_files = deque_init();
	d = opendir(path);
	if (d)
	{
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			if (dir->d_name[0] == '.')
				deque_push_back(all_files, ft_strdup(dir->d_name));
		}
		closedir(d);
	}
	sort_string(all_files);
	return (all_files);
}

static char	*get_new_pattern(int cnt[2], char *pattern)
{
	char	*new_pattern;

	new_pattern = ft_calloc(ft_strlen(pattern) + 1, sizeof(char));
	cnt[0] = 0;
	cnt[1] = -1;
	while (pattern[++cnt[1]])
	{
		if (cnt[1] != 0 && pattern[cnt[1] - 1] == '/' && pattern[cnt[1]] == '/')
			continue ;
		new_pattern[cnt[0]++] = pattern[cnt[1]];
	}
	return (new_pattern);
}

void	wild_card(t_deque *tokens, char *pattern)
{
	int		is_matched;
	int		cnt[2];
	char	*new_pattern;

	is_matched = 0;
	new_pattern = get_new_pattern(cnt, pattern);
	if (new_pattern[0] == '/')
		wild_card_recursive(ft_strdup("/"), new_pattern + 1,
			&is_matched, tokens);
	else
		wild_card_recursive(ft_strdup(""), new_pattern, &is_matched, tokens);
	if (is_matched == 0)
	{
		cnt[0] = -1;
		while (pattern[++cnt[0]])
			if (pattern[cnt[0]] == -1)
				pattern[cnt[0]] = '*';
		deque_push_back(tokens, init_token(pattern, _undefined));
	}
	ft_free(new_pattern);
}
