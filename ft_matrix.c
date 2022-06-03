#include "minishell.h"

int ft_matrixlen(char **envp)
{
    int i;

    i = 0;
    while (envp && envp[i])
    {
         //printf("ft_matrix_len > envp[i] = %s\n", envp[i]);
        i++;
    }
    //printf("///matrix_len = %d\n", i);
    return (i);
}

void    ft_free_matrix(char ***out_adrr)
{
    //printf("ft_free_matrix\n");
    int i;

    i = 0;
    while (out_adrr && out_adrr[0] && out_adrr[0][i])
    {
        free(out_adrr[0][i]);
        i++;
    }
    if (out_adrr)
    {
        free(out_adrr[0]);
        *out_adrr = NULL;
    }   
}

char    **ft_dup_matrix(char **envp)
{
    printf("///ft_dup_Matrix\n");
    char    **out;
    int     nbr_rows;
    int     i;

    i = 0;
    nbr_rows = ft_matrixlen(envp);
    out = malloc(sizeof(char *) * (nbr_rows + 1));
    if (!out)
        return(NULL);
    while (envp[i])
    {
        out[i] = ft_strdup(envp[i]);
        //printf("envp = %s\n", envp[i]);
        //printf("out = %s\n", out[i]);
        if (!out[i])
        {
            ft_free_matrix(&out);
            return (NULL);
        }
        i++;
    }
    out[i] = NULL;
    //
    return (out);
}

char    **ft_extend_matrix(char **in_envp, char *new_str)
{
    printf("///ft_extand_Matrix\n");
    char    **out;
    int     len;
    int     i;

    i = -1;
    out = NULL;
    if (!new_str)
        return (in_envp);
    len  = ft_matrixlen(in_envp);
    out = malloc(sizeof(char *) * (len + 2));
    out[len + 1] = NULL;
    if (!out)
        return (in_envp);
    while (++i < len)
    {
        out[i] = ft_strdup(in_envp[i]);
        if (!out[i])
        {
            ft_free_matrix(&in_envp);
            ft_free_matrix(&out);
        }
    }
    out[i] = ft_strdup(new_str);
    printf("last_out = %s\n", out[i]);
    ft_free_matrix(&in_envp);
    return (out);
}

char	**ft_matrix_replace_in(char ***big, char **small, int n)
{
    printf("///ft_replace_matrix i = %d\n", n);
	char	**aux;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!big || !*big || n < 0 || n >= ft_matrixlen(*big))
		return (NULL);
	aux = ft_calloc(ft_matrixlen(*big) + ft_matrixlen(small), sizeof(char *));
	while (aux && big[0][++i[0]])
	{
		if (i[0] != n)
			aux[++i[2]] = ft_strdup(big[0][i[0]]);
		else
		{
			while (small && small[++i[1]])
				aux[++i[2]] = ft_strdup(small[i[1]]);
		}
	}
	ft_free_matrix(big);
	*big = aux;
	return (*big);
}
