#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	t_double_list *it;
	init_all(env);
	if (ac < 2)
		return (0);
	if ((it = find_env_var_line(av[1])))
		ft_putendl_fd(it->content, 1);
	ft_putendl_fd(find_env_var(av[1]), 1);
}
