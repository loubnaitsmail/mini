#include "minishell.h"

char    *mini_getenv(char *var, char **envp, int size_n)
{
    printf("Get_envp VAR = %s\n", var);
    int i;
    int new_size;

    i = 0;
    if (size_n < 0)
        size_n = ft_strlen(var);

    //Tant qu'il n'a pas de '='
    //condition null ft_strch, var ne contient jamais =
    while (!ft_strchr(var, '=') && envp && envp[i])
    {
        //printf("\nWHILE i = %d, env[i] = %s\n", i, envp[i]);
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

        // Comparaison parfaite envp[i] == var sur new_size = size_n -> return valeur apres = 
        //printf("Compare i = %d, new_size = %d, envp[i] = %s, var = %s, \n", i, new_size, envp[i], var);
        if (!ft_strncmp(envp[i], var, new_size))
            return (ft_substr(envp[i], new_size + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);
}

char    **mini_setenv(char *var, char *str_value, char **envp, int size_n)
{
    printf("Set_envp VAR = %s, str_value = %s\n", var, str_value);
    int     tab_i[2];
    char    *buff[2];

    if (size_n < 0)
        size_n = ft_strlen(var);
    
    tab_i[0] = -1;
    buff[0] = ft_strjoin(var, "="); //PWD+=
    buff[1] = ft_strjoin(buff[0], str_value); //PWD=+/RepertoireActuel
    //printf("buff[0] = %s\n", buff[0]);
    //printf("buff[1] = %s\n", buff[1]);   
    free(buff[0]);

    //Tant qu'il n'a pas de '='
    //condition null ft_strch, var ne contient jamais =
    //Compare la taille str avant l'egale= boff 
    while (!ft_strchr(var, '=') && envp && envp[++tab_i[0]])
    {
        //printf("tab_i[0] = %d, envp[tab_i[0]] = %s\n", tab_i[0], envp[tab_i[0]]);
        //printf("\nWHILE ft_strchr(var, '=') = %s\n", ft_strchr(var, '='));
        tab_i[1] = size_n;
        //printf("tab_i[1] = %d\n", tab_i[1]);

        //Partie inutile 
        if (tab_i[1] < ft_strchr_i(envp[tab_i[0]], '='))
        {
            tab_i[1] = ft_strchr_i(envp[tab_i[0]], '=');
            //printf("If > tab_i[1] = %d\n", tab_i[1]);
            //printf("envp[tab_i[0]] = %s\n", envp[tab_i[0]]);
            //printf("Nbr befor EGAL= tab_i[1] = %d\n", tab_i[1]);
        }
        
        // Comparaison parfaite envp[i] == var
        //printf("Compare tab_i[0] = %d, tab_i[1] = %d, envp[tab_i[0]] = %s, var = %s\n", tab_i[0], tab_i[1], envp[tab_i[0]], var);
        if (!ft_strncmp(envp[tab_i[0]], var, tab_i[1]))
        {
            //printf("buff[0] = %s\n", buff[0]);
            //printf("buff[1] = %s\n", buff[1]); 
            buff[0] = envp[tab_i[0]];
            envp[tab_i[0]] = buff[1];
            //printf("buff[0] =  envp[tab_i[0]] = %s\n", buff[0]);
            printf("envp[tab_i[0]] = %s\n", envp[tab_i[0]]);
            free(buff[0]);
            return (envp);
        }
    }
    // ? quand
    printf("extend **envp whith buff[1] = %s\n", buff[1]);
    envp = ft_extend_matrix(envp, buff[1]);
    free(buff[1]);
    return(envp);
}