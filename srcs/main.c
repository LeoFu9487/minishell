#include "minishell.h"

static void	init_all(t_deque **env_list, char **env) //todo
{
	*env_list = init_env(env); //todo
	g_data.exit_status = 0;
	//change SHLVL and other variables ?
}

static void	main_loop(char **env)
{
	while (1)
	{
		raw_mode_switch(on);
		catch_signal();//todo
		ft_putstr_fd(PROMPT_MESSAGE, 1);
		
		/*get_input(st, input);
		if (!is_empty(input))
		{
			hist_update(&st->history, input);
			env = concat_env(env_lst);
			st->envp = ft_split(env, '\n');
			free(env);
			disacatble_raw_mode(st);
			parse_cmdline(st, &env_lst, cmd_lst, input);
			free_2darray(st->envp);
			g_sig.sigint = 0;
			g_sig.sigquit = 0;
			g_sig.pid = 0;
		}*/
	}
	(void)env;
}

int main(int argc, char **argv, char **env)
{
	t_deque	*env_list;

	(void)argv;
	if (argc > 1)
		message_exit(1, "minishell doesn't allow any argument", 2);
	init_all(&env_list, env);
	main_loop(env);
	return (0);
}