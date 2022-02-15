#include "minishell.h"

char    *mini_getenv(char *var, char **envp, int size_n)
{
    printf("\nGet_envp > ");
    printf("var = %s\n", var);
    int i;
    int new_size;

    i = 0;
    if (size_n < 0)
        size_n = ft_strlen(var);

    //Tant qu'il n'a pas de '='
    //condition null ft_strch, var ne contient jamais =
    while (!ft_strchr(var, '=') && envp && envp[i])
    {
        //printf("i = %d, env[i] = %s\n", i, envp[i]);
        new_size = size_n;

        //Partie inutile 
        // Compare la taille de la var avec la distance jusqu'au '='
        //printf("search '=' i = %d\n", ft_strchr_i(envp[i], '='));
        if (new_size < ft_strchr_i(envp[i], '='))
        {
            //printf("if new_size %d < i_search\n", new_size);
            new_size = ft_strchr_i(envp[i], '=');
            //printf("new_size = i_search = %d\n", new_size);
        }

        //printf("Compare i = %d, envp[i] = %s, var = %s\n", i, envp[i], var);
        // Comparaison parfaite envp[i] == var
        if (!ft_strncmp(envp[i], var, new_size))
            return (ft_substr(envp[i], new_size + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);
}

char    **mini_setenv(char *var, char *str_value, char **envp, int size_n)
{
    printf("\nSet_envp > ");
    printf("var = %s, str_value = %s\n", var, str_value);
    int     tab_i[2];
    char    *buff[2];

    if (size_n < 0)
        size_n = ft_strlen(var);
    
    tab_i[0] = -1;
    buff[0] = ft_strjoin(var, "="); //PWD=
    buff[1] = ft_strjoin(buff[0], str_value); //PWD=/RepertoireActuel
    //printf("buff[0] = %s\n", buff[0]);
    //printf("buff[1] = %s\n", buff[1]);   
    free(buff[0]);

    //Tant qu'il n'a pas de '='
    //condition null ft_strch, var ne contient jamais =
    while (!ft_strchr(var, '=') && envp && envp[++tab_i[0]])
    {
        tab_i[1] = size_n;
        //printf("\n-- tab_i[0] = %d\n", tab_i[0]);
        //printf("-- tab_i[1] = %d\n", tab_i[1]);
        //printf("Nbr before = %d\n", ft_strchr_i(envp[tab_i[0]], '='));

        //Partie inutile 
        if (tab_i[1] < ft_strchr_i(envp[tab_i[0]], '='))
        {
            tab_i[1] = ft_strchr_i(envp[tab_i[0]], '=');
            //printf("envp[tab_i[0]] = %s\n", envp[tab_i[0]]);
            //printf("tab_i[1] = %d nbr before '='\n", tab_i[1]);
        }
        
        // Comparaison parfaite envp[i] == var
        //printf("CMP envp[tab_i[0]] = %s, var = %s, tab_i[1] = %d\n", envp[tab_i[0]], var, tab_i[1]);
        if (!ft_strncmp(envp[tab_i[0]], var, tab_i[1]))
        {
            buff[0] = envp[tab_i[0]];
            envp[tab_i[0]] = buff[1];
            //printf("buff[0] =  envp[tab[0]] = %s\n", buff[0]);
            //printf("envp[tab_i[0]] = buff[1] = %s\n", envp[tab_i[0]]);
            free(buff[0]);
            return (envp);
        }
    }
    // ? quand
    envp = ft_extend_matrix(envp, buff[1]);
    free(buff[1]);
    return(envp);
}