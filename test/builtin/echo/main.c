#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	builtin_echo(av + 1);
	(void)ac;
}
