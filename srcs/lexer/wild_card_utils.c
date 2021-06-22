/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 04:02:56 by yfu               #+#    #+#             */
/*   Updated: 2021/06/23 00:55:55 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub(int cnt[2], t_double_list *iterator[2], t_deque *deque)
{
	void	*ptr;

	iterator[0] = deque->head;
	while (iterator[0] && iterator[0]->next)
	{
		if (ft_strncmp(iterator[0]->content, iterator[0]->next->content,
				ft_strlen(iterator[0]->content) + 1) > 0)
		{
			ptr = iterator[0]->content;
			iterator[0]->content = iterator[0]->next->content;
			iterator[0]->next->content = ptr;
			cnt[0] = 1;
		}
		iterator[0] = iterator[0]->next;
	}
}

void	sort_string(t_deque *deque)
{
	t_double_list	*iterator[2];
	int				cnt[2];

	if (deque->size < 2)
		return ;
	cnt[0] = 1;
	while (cnt[0])
	{
		cnt[0] = 0;
		sub(cnt, iterator, deque);
	}
}

int	match(char *p, char *s, char *star, char *sptr)
{
	while (*s)
	{
		if (*s == *p || *p == -2)
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

int	has_wild_card(char *str)
{
	while (*str)
	{
		if (*str == -1 || *str == -2)
			return (1);
		++str;
	}
	return (0);
}
