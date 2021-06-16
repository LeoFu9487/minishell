/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 02:45:09 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 04:03:13 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_wild_card(char *str)
{
	while (*str)
	{
		if (*str == -1)
			return (1);
		++str;
	}
	return (0);
}

t_deque	*get_all_files(void)
{
	DIR				*d;
	struct dirent	*dir;
	t_deque			*all_files;

	all_files = deque_init();
	d = opendir(".");
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

int	match(char *p, char *s, char *star, char *sptr)
{
	while (*s)
	{
		if (*s == *p)
		{
			++s;
			++p;
		}
		else if (*p == -1)
		{
			star = p++;
			sptr = s;
		}
		else if (star)
		{
			s = ++sptr;
			p = star + 1;
		}
		else
			return (0);
	}
	while (*p == -1)
		++p;
	return (*p == '\0');
}

void	wild_card(t_deque *tokens, char *str)
{
	t_deque			*all_files;
	t_double_list	*iterator;
	int				cnt;

	all_files = get_all_files();
	iterator = all_files->head;
	cnt = -1;
	while (iterator)
	{
		if (match(str, iterator->content, NULL, NULL))
		{
			deque_push_back(tokens, init_token(iterator->content, _undefined));
			cnt = 1;
		}
		iterator = iterator->next;
	}
	if (cnt == -1)
	{
		while (str[++cnt])
			if (str[cnt] == -1)
				str[cnt] = '*';
		deque_push_back(tokens, init_token(str, _undefined));
	}
	deque_clear(all_files, ft_free);
}
