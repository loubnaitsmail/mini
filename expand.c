#include "minishell.h"

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
    printf("/////Path_expand str = %s, var = %s\n", str, var);
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
        //printf("0_quotrs[0] = %d\n", quotes[0]);
        //printf("0_quotrs[1] = %d\n", quotes[1]);
        //pas de quote " ET pas de quote ' ET contient ~ ET (first element OR not after apres $)
		//il faut un "~/src"
		if (!quotes[0] && !quotes[1] && str[i] == '~' && \
             (i == 0 || str[i - 1] != '$'))
		{
            //printf("quotrs[0] = %d\n", quotes[0]);
            //printf("quotrs[1] = %d\n", quotes[1]);
            //printf("i = %d, str[i - 1] = %c\n]", i, str[i-1]);

			aux = ft_substr(str, 0, i);
            //printf("Path aux = %s\n", aux);

			path = ft_strjoin(aux, var);
            //printf("Path path = %s\n", path);

			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
            //printf("Path aux substr = %s\n", aux);

			free(str);
			str = ft_strjoin(path, aux);
            //printf("Path str = %s\n", str);

			free(aux);
			free(path);
			//return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
            return (str);
		}
	}
	free(var);
    //printf("Path_expended = %s\n", str);
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
    //printf("pos = %d\n", pos);

	if (pos == -1)
		pos = ft_strlen(str) - 1; //if pas de set, put str len
    //printf("last pos = %d\n", pos);

	aux = ft_substr(str, 0, i - 1); //stocker ce qu'il y a avant $, ex le 1er "
    //printf("aux_substr i-1(%d)= %s\n", i-1, aux);

	var = mini_getenv(&str[i], prompt->envp, ft_strchars_i(&str[i], "\"\'$|>< ")); //get_var, env, size_n = str jusqu'au 2ème " ou set, return null if not found
    //printf("var_getenv = %s\n", var);

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
    //printf("path_aux_var = %s\n", path);

    //printf("str = %s, i + pos = %d\n", str, i+pos);
	aux = ft_strjoin(path, &str[i + pos]); //ajouter tout ce qui vient après le 2émé " ou |\"\'$?>< 
	//printf("aux return = %s\n", aux);

    free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, t_prompt *prompt) //arg, i, quotes[2], prompt
{
    printf("///Var_expend, str = %s\n", str);
    int		quotes[2];
    int		i;

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i]) //parcourir l'argument 
	{
        //printf("while str[%d] = %s\n", i, str);
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2; //quote ' 0 if not, 1 if contient
        //printf("-quotrs[0] = %d\n", quotes[0]);
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2; //quote " 0 if not, 1 if contient
        //printf("-quotrs[1] = %d\n", quotes[1]);

        //si str arrive au $ && pas de quotes ' quote[0] = 0  && ((pas de quote " ET contient Set) OU (contient quote " et contient Set))
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\"") && quotes[1])))
        {
            //printf("quotrs[0] = %d\n", quotes[0]);
            //printf("quotrs[1] = %d\n", quotes[1]); 

            str = get_substr_var(str, ++i, prompt); //put value from env
            //printf("substr = %s\n", str);
			//return (expand_vars(str, -1, quotes, prompt)); //enlever la récusivitée 
            return(str);
        }
	}

    //printf("Var_expended str = %s\n\n", str);
	return (str);
}
