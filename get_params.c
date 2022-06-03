#include "minishell.h"

extern int	g_status;

int	get_fd(int oldfd, char *path, int flags[2]) //node->outfile, args[i], 
{
    printf("///*Get_fd old_fd = %d, arg = %s, flag[0] = %d, flag[1] = %d\n", oldfd, path, flags[0], flags[1]);
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	/*if (access(path, F_OK) == -1 && !flags[0])
		mini_perror(NDIR, path, 127);
	else if (!flags[0] && access(path, R_OK) == -1)
		mini_perror(NPERM, path, 126);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mini_perror(NPERM, path, 126);*/
	if (flags[0] && flags[1])
    {
		printf("fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666)\n"); //>> 
        fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
    }
	else if (flags[0] && !flags[1])
    {
		printf("fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666)\n"); //>outfile
        fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    }
	else if (!flags[0] && oldfd != -1)
    {
		printf("fd = open(path, O_RDONLY)\n"); //<infile
        fd = open(path, O_RDONLY);
    }
	else
    {
        printf("fd = oldfd\n");
		fd = oldfd;
    }
    printf("returned fd = %d\n", fd);
	return (fd);
}

t_mini	*get_outfile1(t_mini *node, char **args, int *i) //cmd(mini), trimed_args, i
{
    printf("///*get_outfile1 = >\n");
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
    printf("args[%d] = %s\n", *i, args[*i]);
	if (args[*i])
		node->outfile = get_fd(node->outfile, args[*i], flags);

	if (!args[*i] || node->outfile == -1)
	{
        printf("get_out1 cas !args[i] || outfile ==-1\n");
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2); //print error
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_outfile2(t_mini *node, char **args, int *i)
{
    printf("///*get_outfile2 = >>\n");
	char	*nl;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
    printf("args[%d] = %s\n", *i, args[*i]);
	if (args[++(*i)])
		node->outfile = get_fd(node->outfile, args[*i], flags); //fill outfile

	if (!args[*i] || node->outfile == -1)
	{
        printf("get_out2 cas !args[i] || outfile == -1\n");
		*i = -1;
		if (node->outfile != -1)
		{
			ft_putendl_fd(nl, 2); //print error
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile1(t_mini *node, char **args, int *i)
{
    printf("///*get_infile1 = <\n");
	char	*nl;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
    printf("args[%d] = %s\n", *i, args[*i]);
	if (args[*i])
		node->infile = get_fd(node->infile, args[*i], flags); //fill infile

	if (!args[*i] || node->infile == -1)
	{
        printf("get_in1 cas !args[i] || outfile ==-1\n");
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2); //print error
			g_status = 2;
		}
		else
			g_status = 1;
	}
	return (node);
}

t_mini	*get_infile2(t_mini *node, char **args, int *i)
{
    printf("*get_infile2 = <<\n");
	char	*aux[2];
	char	*nl;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	aux[0] = NULL;
	aux[1] = "minishell: warning: here-document delimited by end-of-file";
	nl = "minishell: syntax error near unexpected token `newline'";
	(*i)++;
    printf("args[%d] = %s\n", *i, args[*i]);
	if (args[++(*i)])
	{
		aux[0] = args[*i];
		//node->infile = get_here_doc(str, aux);
	}
	if (!args[*i] || node->infile == -1)
	{
        printf("get_in2 cas !args[i] || outfile ==-1\n");
		*i = -1;
		if (node->infile != -1)
		{
			ft_putendl_fd(nl, 2);
			g_status = 2;
		}
	}
	return (node);
}