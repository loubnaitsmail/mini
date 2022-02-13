#include "minishell.h"

/*char *mini_getenv(char *var, char **envp, int size_n)
{

}*/

char    **mini_setenv(char *var, char *str_val, char **envp, int size_n)
{
    printf("Set_envp\n");
    int     tab_i[2];
    char    *buff[2];

    //Security
    if (size_n < 0)
        size_n = ft_strlen(str_val);
    tab_i[0] = -1;
    buff[0] = ft_strjoin(var, "="); //PWD=
    buff[1] = ft_strjoin(buff[0], str_val); //PWD=/RepertoireActuel
    //printf("buff[0] = %s\n", buff[0]);
    //printf("buff[1] = %s\n", buff[1]);   
    free(buff[0]);

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
        
        //Compare la variable envoyé avec l'envp de i 
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