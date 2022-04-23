#include "minishell.h"

static int	ft_count_words(const char *s, char *c) //str, sep, count[Ø]*
{
    printf("ft_count_words str = %s, sep c = %s\n", s, c);
    //i[0] = pos caracter, i[1] = nbr words
    //q[0] = 0, q[1] = 0 -> pas de quote OU quote fermé % 2
    //q[0] = 1, q[1] != 0 -> une quote ouverte
	int		q[2]; //quotes
    int		i[2]; //pos

	i[0] = 0; 
	i[1] = 0; 

	q[0] = 0;
	q[1] = 0;
	while (s[i[0]] != '\0')
	{
        //printf("char s[%d] = %c\n", i[0], s[i[0]]);

		if (!ft_strchr(c, s[i[0]])) //s'il n'est pas un espace
		{
			i[1]++;
			while ((!ft_strchr(c, s[i[0]]) || q[0]) && s[i[0]] != '\0') //tant qu'il n'est pas un espace OU quote ouverte q[0] != 0
			{
                //printf("while i[O]++ = %d, q[0] = %d, s[i[0]] = %c\n", i[0], q[0], s[i[0]]);
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\'')) //contient " ou ' ET q[1] = 0 -> out of quote et y entre
					q[1] = s[i[0]]; //ascii 34 = " or 39 = '

				q[0] = (q[0] + (s[i[0]] == q[1])) % 2; //égale à 1 tant qu'il n'a pas trouvé la deuxième quote et 2%2=0 s'il trouve la 2ème quote
                //printf("q[O] = %d\n", q[0]);
                
				q[1] *= q[0] != 0; //= 0 when q[0] *= 0
                //printf("q[1] = %d\n", q[1]);
				i[0]++;
			}
			if (q[0]) //n'a pas trouvé la deuxième quote 
            {
				return (-1);
            }
		}
		else //s'il trouve un espace et n'est pas entre quotes ++
			i[0]++;
	}
	return (i[1]);
}

static char	**ft_fill_array(char **aux, char const *s, char *set) //i[3]*
{
    printf("ft_fill_array\n");
    //i[0] = pos caractère, i[1] = pos next word befor space, i[2] = nbr words
	int		s_len;
    int		i[3]; //pos
	int		q[2]; //quotes

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;

	q[0] = 0;
	q[1] = 0;

	s_len = ft_strlen(s);
	while (s[i[0]])
	{
        //printf("s[i[0]] = %c\n", s[i[0]]);
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0') //c'est un espace -> ++
			i[0]++;

		i[1] = i[0]; //pos after space
        //printf("i[1] = %d\n", i[1]);
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]]) //tant qu'il n'est pas un espae OU  quote ouverte "0/1 '1/0 OU pas de quote = 0/0
		{
            //printf("while i[O] = %d, s[i[0]] = %c, q[0] = %d, q[1] = %d\n", i[0], s[i[0]], q[0], q[1]);
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
            //printf("q[O] = %d\n", q[0]);
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
            //printf("q[1] = %d\n", q[1]);

			i[0]++;
		}
        //printf("i[0] = %d, i[1] = %d, s_len = %d, i[2] = %d\n", i[0], i[1], s_len, i[2]);
		if (i[1] >= s_len) //fini, with space
        {
            //printf("fini with space\n");
			aux[i[2]++] = "\0";
        }
		else
        {
            //printf("ft_sub i[0] = %d, i[1] = %d, i[2] = %d\n",  i[0],  i[1], i[2]);
            //fill tab of tab ++
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
        }
	}
	return (aux);
}

char	**ft_cmdtrim(char const *s, char *set) //str, seprateur 
{
    printf("**ft_cmtrim str = %s, sep = %s\n", s, set);

	char	**aux; //**array
	int		nwords;
	//int		i[3];
	//int		counts[2]; 

	//i[0] = 0;
	//i[1] = 0;
	//i[2] = 0;

	//counts[0] = 0; 
	//counts[1] = 0; 

	if (!s)
		return (NULL);

	nwords = ft_count_words(s, set); //counts
    printf("nwords = %d\n", nwords);

	if (nwords == -1)
		return (NULL);

	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);

	aux = ft_fill_array(aux, s, set); //i
	aux[nwords] = NULL;
    
    int j = -1;
    while(++j < nwords)
        printf("filled_tab_space[%d] = %s\n", j, aux[j]);

	return (aux);
}