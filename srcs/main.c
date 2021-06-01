#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc > 1)
		message_exit(1, "minishell doesn't take any arguments", 1);
	
	(void)env;
}