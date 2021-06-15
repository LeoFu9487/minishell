#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	width, height;

void	update_size(int signal)
{
	(void)signal;
	tgetent(NULL, getenv("TERM"));
	height = tgetnum("li");
	width = tgetnum("co");
	printf("height : %d\nwidth : %d\n", height, width);
}

int	main(int ac, char **av, char **env)
{
	init_all(env);
	update_size(0);
	signal(SIGWINCH, update_size);
	char *gotostr = tgetstr("cm", NULL);
	while (1)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		printf("%s", tgoto(gotostr, x, y));
	}
	(void)ac;(void)av;(void)env;

	//char buf[1024];
	//char buf2[30];
	//char *ap = buf2;
	//char *clearstr, *gotostr, *standstr;//, *stendstr;

	//tgetent(buf, getenv("TERM"));

	//clearstr = tgetstr("cl", &ap);
	//gotostr = tgetstr("cm", &ap);
	//standstr = tgetstr("so", &ap);
	//stendstr = tgetstr("se", &ap);

	/*tputs(clearstr, 1, stdout);
	tputs(tgoto(gotostr, 20, 10), 1, stdout);
	printf("Hello, ");
	fputs(standstr, stdout);
	printf("world");
	//fputs(stendstr, stdout);
	putchar('!');
	(void)ac;
	(void)av;
	(void)env;*/
}
