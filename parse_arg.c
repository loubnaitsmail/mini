#include "minishell.h"

//extern int	g_status;

static char	**split_all(char **args, t_prompt *prompt) //array_arg, prompt
{
    printf("\nsplit_all args\n");

	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
        printf("\nwhile args = %s\n", args[i]);
		args[i] = expand_vars(args[i], -1, quotes, prompt); //var start $
        //printf("Var_expend args[%d] = %s\n\n", i, args[i]);

		//args[i] = expand_path(args[i], -1, quotes, mini_getenv("HOME", prompt->envp, 4));
        //printf("Path_expand args[%d] = %s\n\n", i, args[i]);

		//subsplit = ft_cmdsubsplit(args[i], "<|>");

		//ft_matrix_replace_in(&args, subsplit, i);

		//i += ft_matrixlen(subsplit) - 1;
        //printf("i += matrixlen = %d\n", i);

		//ft_free_matrix(&subsplit);
	}

    //int j = -1;
    //while(++j < 4)
        //printf("Extanded args[%d] = %s\n", 0, args[0]);

	return (args);
}

static void	*parse_args(char **args, t_prompt *p) //array_args, prompt
{
	int	is_exit;
	int	i;

	is_exit = 0;
	
    args = split_all(args, p); //expand var and path 

    //int j = -1;
    //while(++j < 4)
        //printf("Split_all args[%d] = %s\n", j, args[j]);

    /*p->cmds = fill_nodes(split_all(args, p), -1);
    
	if (!p->cmds)
		return (p);

	i = ft_lstsize(p->cmds);

	g_status = builtin(p, p->cmds, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &g_status, 0);
	if (!is_exit && g_status == 13)
		g_status = 0;
	if (g_status > 255)
		g_status = g_status / 255;
	if (args && is_exit)
	{
		ft_lstclear(&p->cmds, free_content);
		return (NULL);
	}*/
	return (p);
}

void	*check_args(char *out, t_prompt *p) //out_readline //prompts
{
	char	**a; //aux array_args from space separation
	t_mini	*n;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
    //history
	if (out[0] != '\0')
		add_history(out);

    //sepate args with space 
	a = ft_cmdtrim(out, " ");
	free(out);

    /*
	if (!a)
		mini_perror(QUOTE, NULL, 1);
	if (!a)
		return ("");*/

	p = parse_args(a, p);

	/*if (p && p->cmds)
		n = p->cmds->content;
	if (p && p->cmds && n && n->full_cmd && ft_lstsize(p->cmds) == 1)
		p->envp = mini_setenv("_", n->full_cmd[ft_matrixlen(n->full_cmd) - 1], \
			p->envp, 1);
	if (p && p->cmds)
		ft_lstclear(&p->cmds, free_content);*/
	return (p);
}