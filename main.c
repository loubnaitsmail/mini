#include "minishell.h"

static t_prompt init_variables(t_prompt prompt, char *str_cmd, char **argv, char **envp)
{
    printf("Init_variable\n");
    char    *num;
    
    //Get PWD with getcwd, répertoire actuel dans envp
    str_cmd = getcwd(NULL, 0);
    printf("getcwd = %s\n", str_cmd);
    //Set PWD in prompt.envp to actuel repo
    prompt.envp = mini_setenv("PWD", str_cmd, prompt.envp, 3);
    printf("str_cmd PWD = %s\n", str_cmd);
    free(str_cmd);

    //Get SHLVL shell levels from envp
    str_cmd = mini_getenv("SHLVL", envp, 5);
    printf("str_cmd SHLVL = %s\n", str_cmd);
    if (!str_cmd || ft_atoi(str_cmd) <= 0)
        num = ft_strdup("1");
    else
        num = ft_itoa(ft_atoi(str_cmd) + 1); //pk + 1
    printf("num = %s\n", num);
    free (str_cmd);
    //Set SHLVL in prompt.envp to + 1
    prompt.envp = mini_setenv("SHLVL", num, prompt.envp, 5);
    free(num);

    //Get PATH, directories to find a commands
    str_cmd = mini_getenv("PATH", prompt.envp, 4);
    //Set Path in prompt.envp if NULL 
    if (!str_cmd)
        prompt.envp = mini_setenv("PATH", \
        "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envp, 5);
    printf("str_cmd PATH = %s\n", str_cmd);
    free (str_cmd);

    //GET "_" ??
    str_cmd = mini_getenv("_", prompt.envp, 4);
    printf("str_cmd '_' = %s\n", str_cmd);
    //GET "_" if NULL
    if (!str_cmd)
        prompt.envp = mini_setenv("_", argv[0], prompt.envp, 1);
    printf("argv[0] = %s\n", argv[0]);
    printf("str_cmd '_' = %s\n", str_cmd);
    free (str_cmd);

    return (prompt);
}

static pid_t    mini_getpid(t_prompt *prompt)
{
    printf("Get_pid Process ID\n");
    //process ID 
    pid_t   pid;

    //fork créer un autre processeur enfant
    pid = fork();
    if (pid < 0)
    {
        //error
        return(-1);
    }
    //processus enfant
    if (!pid) 
    {
        //printf("pid 0 = %i\n", pid);
        exit (1);
    }
    //processus parent attends l'enfant 
    waitpid(pid, NULL, 0);
    //printf("pid = %i\n", pid);
    //printf("pid - 1 = %i\n", pid - 1);
    return (pid - 1); // init 
}

static t_prompt init_prompt(char **argv, char **envp)
{
    t_prompt    prompt;
    //put str directly in func 
    char        *str;

    str = NULL;
    prompt.cmds = NULL;
    //Get env 
    prompt.envp = ft_dup_matrix(envp);
    prompt.status = 0;
    //init process 
    prompt.pid = mini_getpid(&prompt);
    // Init var : 
    prompt = init_variables(prompt, str, argv, envp);
    return (prompt);
}

int main(int argc, char **argv, char **envp)
{

    t_prompt    prompt;

    prompt = init_prompt(argv, envp);

    

}