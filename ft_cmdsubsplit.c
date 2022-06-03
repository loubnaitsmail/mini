#include "minishell.h"

static int	ft_count_words(char *s, char *set, int count) //i
{
	//count[0] = position caracter
	//count[1] = nbr words
	//count[1] = nbr words
    //q[0] = 0, q[1] = 0 -> pas de quote OU quote fermé % 2
    //q[0] = 1, q[1] != 0 -> une quote ouverte

	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i])) //tant qu'il n'a pas trouvé de set
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2; //égale à 1 tant qu'il n'a pas trouvé la deuxième quote et 2%2=0 s'il trouve la 2ème quote
                //printf("q[O] = %d\n", q[0]);
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				//printf("q[1] = %d\n", q[1]);
				i++;
			}
			if (q[0] || q[1]) //n'a pas trouvé la deuxième quote 
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array(char **aux, char *s, char *set, int i[3])
{
    //i[0] = pos caractère
	//i[1] = pos next word befor space
	//i[2] = nbr words
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdsubsplit(char const *s, char *set) 
{
    printf("///SPLIT %s **ft_cmdsubsplit\n", set);
	char	**aux;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words((char *)s, set, 0);
    printf("nwords = %d\n", nwords);

	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, (char *)s, set, i);
	aux[nwords] = NULL;

	//print returned aux
    int j = -1;
	printf("\n");
    while(++j < nwords)
        printf("Splited_by_<|>[%d] = %s\n", j, aux[j]);
	printf("\n");

	return (aux);
}