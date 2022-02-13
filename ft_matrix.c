#include "minishell.h"

int	ft_strchr_i(const char *s, int c)
{
	unsigned char	c_unsigned;
	int				i;

	i = 0;
	if (!s)
		return (-1);
	c_unsigned = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c_unsigned)
			return (i);
		i++;
	}
	if (c_unsigned == '\0')
		return (i);
	return (-1);
}

int ft_matrixlen(char **envp)
{
    int i;

    i = 0;
    while (envp && envp[i])
    {
        i++;
    }
    return (i);
}

void    ft_free_matrix(char ***out_adrr)
{
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
    printf("Extand_Matrix\n");
    char    **out;
    int     len;
    int     i;

    i = -1;
    out = NULL;
    if (!new_str)
        return (in_envp);
    len  = ft_matrixlen(in_envp);
    out = malloc(sizeof(char *) * (len + 1));
    out[len + 1] = NULL;
    if (!out)
        return (in_envp);
    while (++i < len)
    {
        out[i] = ft_strdup(in_envp[i]);
        printf("in_envp = %s\n", in_envp[i]);
        printf("out = %s\n", out[i]);
        if (!out[i])
        {
            ft_free_matrix(&in_envp);
            ft_free_matrix(&out);
        }
    }
    out[i] = ft_strdup(new_str);
    printf("last out = %s\n", out[i]);
    ft_free_matrix(&in_envp);
    return (out);
}