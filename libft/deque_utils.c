/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:58:29 by yfu               #+#    #+#             */
/*   Updated: 2021/06/11 12:49:16 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_double_list	*double_list_init(void *ptr)
{
	t_double_list	*double_list;

	double_list = ft_malloc(1, sizeof(t_double_list));
	if (!double_list)
		return (NULL);
	double_list->content = ptr;
	double_list->next = NULL;
	double_list->last = NULL;
	return (double_list);
}

void	deque_clear(t_deque *deque, void (*f)(void*))
{
	if (deque == NULL)
		return ;
	while (deque->size)
		deque_pop_back(deque, f);
}

void	deque_pop_one(t_deque *deque, t_double_list *target, void (*f)(void *))
{
	if (!deque || !target || deque->size == 0)
		return ;
	if (target == deque->head)
		deque_pop_front(deque, f);
	else if (target == deque->tail)
		deque_pop_back(deque, f);
	else
	{
		--(deque->size);
		target->last->next = target->next;
		target->next->last = target->last;
		if (f)
			f(target->content);
		ft_free(target);
	}
}
