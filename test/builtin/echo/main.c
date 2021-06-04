#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char **envp;

void run_test(int test_id, char *arg[])
{
	if (fork())
	{
		wait(NULL);
		return ;
	}
	char *test_file = ft_itoa(test_id);
	char *ans_file = malloc((5 + ft_strlen(test_file)) * sizeof(char));
	ans_file[0] = 'a';
	ans_file[1] = 'n';
	ans_file[2] = 's';
	ans_file[3] = '_';
	for (int i = 0 ; test_file[i] ; ++i){
		ans_file[i + 4] = test_file[i];
		ans_file[i + 5] = 0;
	}
	int fd_test = open(test_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	dup2(fd_test, STDOUT_FILENO);
	builtin_echo(arg);
	int fd_ans = open(ans_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	dup2(fd_ans, STDOUT_FILENO);
	execve("/bin/echo", arg, envp);
	free(test_file);
	free(ans_file);
}

int	main(int ac, char **av, char **env)
{
	envp = env;
	(void)ac;
	(void)av;
	char *arg0[] = {"echo", "-n", "Hello World!", 0};
	run_test(0, arg0);

	char *arg1[] = {"echo", "Hello World!", 0};
	run_test(1, arg1);

	char *arg2[] = {"echo", "yoyo ", "-n", 0};
	run_test(2, arg2);

	char *arg3[] = {"echo", "-n", "-n", "-n", "OK", 0};
	run_test(3, arg3);

	char *arg4[] = {"echo", "-n ", "\\n", "-n", "OK", 0};
	run_test(4, arg4);

	char *arg5[] = {"echo", "-n ", "\n", "-n", "OK", 0};
	run_test(5, arg5);
}