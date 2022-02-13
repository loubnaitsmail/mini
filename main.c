#include "minishell.h"

static t_prompt init_variables(t_prompt prompt, char *str_cmd, char **argv, char **envp)
{
    printf("Init_variable\n");
    char    *num;
    
    //PWD with getcwd, récupére le répertoire actuel dans envp
    str_cmd = getcwd(NULL, 0);
    printf("getcwd = %s\n", str_cmd);
    prompt.envp = mini_setenv("PWD", str_cmd, prompt.envp, 3);
    free(str_cmd);

    //
    //str_cmd = mini_getenv("SHLVL", envp, 5);


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
    //get env 
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