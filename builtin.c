 #include "minishell.h"

 extern int	g_status;

int	builtin(t_prompt *prompt, t_list *cmd, int *is_exit, int n) //n = 0 //cmds
{
	char	**a; //full_path 
    char *cmd_pt;
    cmd_pt = ((t_mini *)cmd->content)->full_path;
    printf("///builtin, n = %d, cmd = %s\n", n, cmd_pt);


	while (cmd)
	{
		a = ((t_mini *)cmd->content)->full_cmd;
        printf("a = %s\n", *a);

		n = 0;
		if (a)
			n = ft_strlen(*a);
        //printf("n strlen(a) = %d\n", n);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
        {
            printf(">>>exit\n");
			//g_status = mini_exit(cmd, is_exit);
        }
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2) //pk en dernière cmd
        {
            printf(">>>cd\n");
			//g_status = mini_cd(prompt);
        }
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
        {
            printf(">>>export\n");
			//g_status = mini_export(prompt);
        }
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
        {
            printf(">>>unset\n");
			//g_status = mini_unset(prompt);
        }
		else
		{
            printf(">>>EXECUTE\n");
			//signal(SIGINT, SIG_IGN);
			//signal(SIGQUIT, SIG_IGN);
			//exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
    printf("g_status = %d\n", g_status);
	return (g_status);
}