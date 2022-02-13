#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include "libft/libft.h"
# include <sys/types.h>

typedef struct s_prompt
{
    t_list  *cmds;
    char    **envp;
    pid_t   pid;
    int     status;
}               t_prompt;

//matrix
char    **ft_dup_matrix(char **envp);
char    **ft_extend_matrix(char **in_envp, char *new_str);
int     ft_matrixlen(char **envp);
void    ft_free_matrix(char ***out_adrr);

//environement
char    **mini_setenv(char *var, char *str_val, char **envp, int size_n);




//libft
int     ft_strchr_i(const char *s, int c);



#endif