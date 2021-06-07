#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	init_all(env);
	builtin_env(av);
	(void)ac;
}
