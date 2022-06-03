#include "minishell.h"

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
    printf("/////EXPAND_PATH ~ = %s, var = %s\n", str, var);
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
        //pas de quote " ET pas de quote ' ET contient ~ ET (first element OR not after apres $)
		//il faut un "~/src"
		if (!quotes[0] && !quotes[1] && str[i] == '~' && \
             (i == 0 || str[i - 1] != '$'))
		{
 			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			//return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
            return (str);
		}
	}
	free(var);
	return (str);
}

static char	*get_substr_var(char *str, int i, t_prompt *prompt) //arg //Get $VAR
{
    printf("////*get_substr_var arg = %s, i = %d\n", str, i);
	char	*aux;
	int		pos;
	char	*path;
	char	*var;

	pos = ft_strchars_i(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0); //pos du deuxième /" ou set ex espace

	if (pos == -1)
		pos = ft_strlen(str) - 1; //if pas de set, put str len

	aux = ft_substr(str, 0, i - 1); //stocker ce qu'il y a avant $, ex le 1er "
	var = mini_getenv(&str[i], prompt->envp, ft_strchars_i(&str[i], "\"\'$|>< ")); //get_var, env, size_n = str jusqu'au 2ème " ou set, return null if not found

    //?? quel cas ?
	if (!var && str[i] == '$')
    {
		var = ft_itoa(prompt->pid);
        printf("itoa var ? = %s\n", var);
    }
	else if (!var && str[i] == '?')
    {
        printf("itoa g_status = %s\n", var);
		//var = ft_itoa(g_status);
    }

	path = ft_strjoin(aux, var); //ajouter l'avant & stocké dans aux, ex : " 
	free(aux);
	aux = ft_strjoin(path, &str[i + pos]); //ajouter tout ce qui vient après le 2émé " ou |\"\'$?>< 
    free(var);
	free(path);
	free(str);
	printf("substr_var = %s\n", aux);
	return (aux);
}

char	*expand_vars(char *str, t_prompt *prompt) //arg, i, quotes[2], prompt
{
    printf("///EXPAND_VAR $ = %s\n", str);
    int		quotes[2];
    int		i;

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i]) //parcourir l'argument 
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2; //quote ' 0 if not, 1 if contient
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2; //quote " 0 if not, 1 if contient

        //si str arrive au $ && pas de quotes ' quote[0] = 0  && ((pas de quote " ET contient Set) OU (contient quote " et contient Set))
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; A") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"B") && quotes[1])))
        {
            str = get_substr_var(str, ++i, prompt); //put value from env
			//return (expand_vars(str, -1, quotes, prompt)); //enlever la récusivitée 
            return(str);
        }
	}
	return (str);
}
