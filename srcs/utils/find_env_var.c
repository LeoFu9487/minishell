/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 08:00:26 by yfu               #+#    #+#             */
/*   Updated: 2021/06/07 08:32:42 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_var_line(char *key)
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
				return (iterator->content);
		iterator = iterator->next;
	}
	return (NULL);
}

char	*find_env_var(char *key)
{
	char	*line;

	line = find_env_var_line(key);
	if (!line)
		return (NULL);
	return (ft_substr(line, ft_strlen(key) + 1, ft_strlen(line) - ft_strlen(key) - 1));
}
