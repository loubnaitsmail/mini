#include "minishell.h"

extern int	g_status;

static char	**split_all(char **args, t_prompt *prompt) //array_arg, prompt
{
    printf("///SPLIT_ALL ARG\n");

	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
        printf("\n>> args %d = %s\n", i, args[i]);
		args[i] = expand_vars(args[i], prompt); // $VAR
        printf("Return_Var_Exp_args[%d] >> %s\n\n", i, args[i]);

		args[i] = expand_path(args[i], -1, quotes, mini_getenv("HOME", prompt->envp, 4)); // ~/src
        printf("Return_Path_Exp_args[%d] >> %s\n\n", i, args[i]);

		subsplit = ft_cmdsubsplit(args[i], "<|>"); //split

		ft_matrix_replace_in(&args, subsplit, i); // if contient set <|>
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	printf("FINISH SPLIT\n\n");
	return (args);
}

static void	*parse_args(char **args, t_prompt *p) //array_args, prompt
{
	int	is_exit;
	int	i;

	is_exit = 0;
	
    p->cmds = fill_nodes(split_all(args, p), -1); //expand var and path and split "<|>", enlever les quotes et fill node
    
	if (!p->cmds)
		return (p);

	i = ft_lstsize(p->cmds);
	printf("i_list_size = %d\n", i);

	g_status = builtin(p, p->cmds, &is_exit, 0);

     ////.....   


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
    //add to history
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

	//......
	
	return (p);
}