#include "minishell.h"

char    *mini_getenv(char *var, char **envp, int size_n)
{
    printf("////Get_envp = %s\n", var);
    int i;
    int new_size;

    i = 0;
    if (size_n < 0)
        size_n = ft_strlen(var);

    //Tant qu'il n'a pas de '='
    //condition null ft_strch, var ne contient jamais =
    while (!ft_strchr(var, '=') && envp && envp[i])
    {
        // Compare la taille de la var avec la distance jusqu'au '='
        new_size = size_n;

        //Partie à vérifier
        if (new_size < ft_strchr_i(envp[i], '='))
            new_size = ft_strchr_i(envp[i], '=');

        // Comparaison parfaite envp[i] == var sur new_size = size_n -> return valeur apres = 
        if (!ft_strncmp(envp[i], var, new_size))
            return (ft_substr(envp[i], new_size + 1, ft_strlen(envp[i])));
        i++;
    }
    return (NULL);
}

char    **mini_setenv(char *var, char *str_value, char **envp, int size_n)
{
    printf("///Set_envp = %s, value = %s\n", var, str_value);
    int     tab_i[2];
    char    *buff[2];

    if (size_n < 0)
        size_n = ft_strlen(var);
    
    tab_i[0] = -1;
    buff[0] = ft_strjoin(var, "="); //PWD+=
    buff[1] = ft_strjoin(buff[0], str_value); //PWD=+/RepertoireActuel   
    free(buff[0]);

    //Tant qu'il n'a pas de '='
    //Compare la taille str avant l'egale= boff 
    while (!ft_strchr(var, '=') && envp && envp[++tab_i[0]])
    {
        tab_i[1] = size_n;

        //Partie à vérifier ?
        if (tab_i[1] < ft_strchr_i(envp[tab_i[0]], '='))
            tab_i[1] = ft_strchr_i(envp[tab_i[0]], '=');
        
        // Comparaison parfaite envp[i] == var
        if (!ft_strncmp(envp[tab_i[0]], var, tab_i[1]))
        {
            buff[0] = envp[tab_i[0]];
            envp[tab_i[0]] = buff[1];
            free(buff[0]);
            printf("envp_seted = %s\n", envp[tab_i[0]]);
            return (envp);
        }
    }

    // ? quand
    printf("??? extend **envp whith buff[1] = %s\n", buff[1]);
    envp = ft_extend_matrix(envp, buff[1]);
    free(buff[1]);
    return(envp);
}