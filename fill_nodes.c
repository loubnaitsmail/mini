#include "minishell.h"

void	free_content(void *content)
{
    printf("///free_content\n");
	t_mini	*node;

	node = content;
	ft_free_matrix(&node->full_cmd);
	free(node->full_path);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	if (node->outfile != STDOUT_FILENO)
		close(node->outfile);
	free(node);
}

static t_list	*stop_fill(t_list *cmds, char **args, char **temp)
{
    printf("///stop_fill\n");
	ft_lstclear(&cmds, free_content);
	ft_free_matrix(&temp);
	ft_free_matrix(&args);
	return (NULL);
}

//extend matrix with params and gérer les redirection < > << >>  et pip |
static t_mini	*get_params(t_mini *node, char **a[2], int *i) //cmd[1](mini) , temp[1] = trimed, temp[0] = args, i
{
    //**a[2]
    //temp[0] = args 
    //temp[1] = trimed_arg sans quotes
	if (a[0][*i]) 
	{
        printf("///get_params_a[0][%d] = %s\n", *i, a[0][*i]);
        printf("///get_params_a[1][%d] = %s\n", *i, a[1][*i]);
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = get_outfile2(node, a[1], i); //a[1] tmp_trimed
		else if (a[0][*i][0] == '>')
			node = get_outfile1(node, a[1], i); 
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<')
			node = get_infile2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = get_infile1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->full_cmd = ft_extend_matrix(node->full_cmd, a[1][*i]); //a[1]
		else
		{
			//mini_perror(PIPENDERR, NULL, 2);
			*i = -2;
		}
        //printf("infile = %d, outfile = %d, full_cmd = %s, full_path = %s\n", node->infile, node->outfile, *node->full_cmd, node->full_path);
		return (node);
	}
	//mini_perror(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

static t_mini	*mini_init(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->full_cmd = NULL;
	mini->full_path = NULL;
	mini->infile = STDIN_FILENO;
	mini->outfile = STDOUT_FILENO;
	return (mini);
}

static char	**get_trimmed(char **args)
{
    printf("///get_trimed\n");

	char	**temp;
	char	*aux;
	int		j;

	j = -1;
	temp = ft_dup_matrix(args);
	while (temp && temp[++j])
	{
		aux = ft_strtrim_all(temp[j], 0, 0); //enlever les quotes
        //printf("Retun_ft_strim_all aux = %s\n", aux);
		free(temp[j]);
		temp[j] = aux;
        //printf("Retun_get_trimed = %s\n", temp[j]);
	}

    while(--j > -1)
        printf("3_Trimed_quote_\"\'[%d] = %s\n", j, temp[j]);
	printf("\n");

	return (temp);
}

t_list	*fill_nodes(char **args, int i)
{
    printf("\n///fill_nodes, i = %d\n", i);
	t_list	*cmds[2];
	char	**temp[2];
    //temp[0] = tab args
    //temp[1] = tab args whithout quotes

	cmds[0] = NULL;
	temp[1] = get_trimmed(args); //tab args whithout quotes
	while (args[++i])
	{
        printf(">>%d - While fill_node_args[%d] = %s\n", i, i, args[i]);
        //printf("while args[%d] = %s\n", i + 1, args[i + 1]);
        //printf("while args[i+1][0] = %d\n", args[i + 1][0]);

		cmds[1] = ft_lstlast(cmds[0]); //prend le dernier de la list cmd[0]

        //init cmd when i = 0 or | >> ++
		if (i == 0 || (args[i][0] == '|' && args[i + 1] && args[i + 1][0])) //init list and when |
		{
			i += args[i][0] == '|'; //go to next arg if | pip
            printf("i = %d\n", i);

			ft_lstadd_back(&cmds[0], ft_lstnew(mini_init())); //lst, newlist(mini), ajoute new_init_list to cmd[Ø] (param de minishell)
			cmds[1] = ft_lstlast(cmds[0]); //prend le dernier element de la list
            printf(">>Init_cmd = %d\n", i);
		}

		temp[0] = args;
        cmds[1]->content = get_params(cmds[1]->content, temp, &i); //cmds[1]->content = node
        
        printf("Returned_i = %d\n", i);
       // printf("Returned_cmd[0] = %d\n", cmds[0]->content);
		
        if (i < 0)
			return (stop_fill(cmds[0], args, temp[1]));
        printf("args[%d] = %s\n", i, args[i]);
		if (!args[i])
			break ;
	}
	ft_free_matrix(&temp[1]);
	ft_free_matrix(&args);

	return (cmds[0]);
}
