/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 04:02:56 by yfu               #+#    #+#             */
/*   Updated: 2021/06/16 04:05:25 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sub(int cnt[2], t_double_list *iterator[2], t_deque *deque)
{
	void	*ptr;
	char	*str[2];

	iterator[0] = deque->head;
	while (iterator[0]->next)
	{
		str[0] = ft_strdup(iterator[0]->content);
		str[1] = ft_strdup(iterator[0]->next->content);
		cnt[1] = -1;
		while (str[0][++cnt[1]])
			str[0][cnt[1]] = ft_toupper(str[0][cnt[1]]);
		cnt[1] = -1;
		while (str[1][++cnt[1]])
			str[1][cnt[1]] = ft_toupper(str[1][cnt[1]]);
		if (ft_strncmp(str[0], str[1], ft_strlen(str[0] + 1)) > 0)
		{
			ptr = iterator[0]->content;
			iterator[0]->content = iterator[0]->next->content;
			iterator[0]->next->content = ptr;
			cnt[0] = 1;
		}
		ft_free(str[0]);
		ft_free(str[1]);
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
