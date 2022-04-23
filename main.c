#include "minishell.h"

//extern int	g_status;

static void	mini_getpid(t_prompt *p)
{
    printf("Get_pid Process ID\n");
    //process ID 
	pid_t	pid;

	pid = fork();
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
    //printf("pid = %i\n", pid);
    //printf("pid - 1 = %i\n", pid - 1);
	waitpid(pid, NULL, 0);

	p->pid = pid - 1;
}

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
    printf("Init_variable\n");
	char	*num;
	/*int i = -1;
	while (prompt.envp[++i])
		printf("set_envp[i] = %s\n", prompt.envp[i]);*/

    
    //GET PWD with getcwd, répertoire actuel dans envp
	str = getcwd(NULL, 0);
    printf("Getcwd str_cmd PWD = %s\n", str);
    //SET PWD in prompt.envp to actuel repo
	prompt.envp = mini_setenv("PWD", str, prompt.envp, 3);
	free(str);

    //GET SHLVL shell levels from envp
    str = mini_getenv("SHLVL", prompt.envp, 5);
    printf("Get str_cmd SHLVL = %s\n", str);
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
    printf("Get str_cmd PATH = %s\n", str);
	//SET DEFAULT PATHin prompt.envp if NULL 
    if (!str)
	{
		prompt.envp = mini_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 4);
	}
	free(str);

    //GET "_" ??
	str = mini_getenv("_", prompt.envp, 1);
    printf("Get str_cmd '_' = %s\n", str);
	//SET "_" argv[0]  if NULL
    if (!str)
		prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);	
    free(str);
    //printf("argv[0] = %s\n", argv[0]);
    return (prompt);
}

static t_prompt	init_prompt(char **argv, char **envp)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
    //GET env   
	prompt.envp = ft_dup_matrix(envp);

	//g_status = 0;

    //init process 
	mini_getpid(&prompt);

    // Init var 
	prompt = init_vars(prompt, str, argv);
	return (prompt);
}

int main(int argc, char **argv, char **envp)
{

    t_prompt    prompt;
	char		*str;
	char		*out;


    prompt = init_prompt(argv, envp);
	//while (argv && argc)
	{
		//signal(SIGINT, handle_sigint);
		//signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt(prompt);
		printf("str getprompt = %s\n", str);

		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		printf("out readline = %s\n", out);
		free(str);

		check_args(out, &prompt);
		//if (!check_args(out, &prompt))
			//break ;
	}
    

}