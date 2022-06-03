#include "minishell.h"

extern int	g_status;

static void	mini_getpid(t_prompt *p)
{
    printf("////Get_pid_id\n");
	pid_t	pid;

	pid = fork();
	printf("pid = %i\n", pid);
	if (pid < 0)
	{
		//mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	printf("pid - 1 = %i\n", pid - 1); //first pid
	p->pid = pid - 1;
}

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
    printf("///init_variables\n");
	char	*num; //?
    
    //GET PWD with getcwd, répertoire actuel dans envp
	str = getcwd(NULL, 0);
    printf("getcwd PWD = %s\n", str);
    //SET PWD in prompt.envp to actuel repo
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);

    //GET SHLVL shell levels from envp
    str = mini_getenv("SHLVL", prompt.envp, 5);
    printf("GetSHLVL = %s\n", str);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
    printf("num = %s\n", num);
	free(str);
    //SET SHLVL in prompt.envp to + 1
	prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
	free(num);

    //GET PATH, directories to find a commands
	str = mini_getenv("PATH", prompt.envp, 4);
    printf("GetPATH = %s\n", str);
	//SET DEFAULT PATHin prompt.envp if NULL 
    if (!str) //if no path > set
	{
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	}
	free(str);

	str = mini_getenv("_", prompt.envp, 1);
    printf("Get'_' = %s\n", str);
    if (!str) // if no -> set
		prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);	
    free(str);
    return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	printf("///init_prompt\n");
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envp = ft_dup_matrix(envp);
	g_status = 0;
	mini_getpid(&prompt);   //init process 
	prompt = init_vars(prompt, str, argv);  // Init var 
	return (prompt);
}

int main(int argc, char **argv, char **envp)
{

    t_prompt    prompt;
	char		*str;
	char		*out;

    prompt = init_prompt(argv, envp);
	printf("Finish edit\n\n");

	//while (argv && argc)
	{
		//signal(SIGINT, handle_sigint);
		//signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt(prompt);
		printf("PROMPT_RETURN >> %s\n\n", str);

		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		printf("I- READLINE = %s\n\n", out);
		free(str);

		check_args(out, &prompt);
		//if (!check_args(out, &prompt))
			//break ;
	}
    

}