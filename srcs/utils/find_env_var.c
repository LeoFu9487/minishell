/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 08:00:26 by yfu               #+#    #+#             */
/*   Updated: 2021/06/08 02:13:00 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_double_list	*find_env_var_line(char *key)
{
	t_double_list	*iterator;
	size_t			key_len;

	if (!key || !*key)
		return (NULL);
	iterator = g_data.env_list->head;
	key_len = ft_strlen(key);
	while (iterator)
	{
		if (ft_strlen(iterator->content) > key_len)
			if (ft_strncmp(iterator->content, key, key_len) == 0
			&& ((char *)iterator->content)[key_len] == '=')
				return (iterator);
		iterator = iterator->next;
	}
	return (NULL);
}

char	*find_env_var(char *key)
{
	t_double_list	*iterator;

	if (ft_strncmp(key, "$?", 3) == 0)
		return (ft_itoa(g_data.exit_status));
	iterator = find_env_var_line(key);
	if (!iterator)
		return (NULL);
	return (ft_substr(iterator->content, ft_strlen(key) + 1, ft_strlen(iterator->content) - ft_strlen(key) - 1));
}
