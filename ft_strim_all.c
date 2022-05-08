#include "minishell.h"

static int	malloc_len(char const *s1)
{
	int	count;
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	count = 0;
	dquote = 0;
	squote = 0;
	while (s1 && s1[i])
	{
		squote = (squote + (!dquote && s1[i] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !squote) || (s1[i] == '\'' && !dquote))
			count++;
		i++;
	}
	if (squote || dquote) //quote non fermé
		return (-1);
	return (count);
}

char	*ft_strtrim_all(char const *s1, int squote, int dquote)
{
    printf("///*ft_strim_all quotes= %s\n", s1);
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1; //parcourir trimed*
	i[0] = 0; //parcour s1 = arg
	count = malloc_len(s1); //nbr de mots entre quotes ou nbr de quotes
    printf("count = %d\n", count);

	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]]) //duplicate s1 in trimed only if not quotes
	{
        //printf("s1[%d] = %c\n", i[0], s1[i[0]]);
		squote = (squote + (!dquote && s1[i[0]] == '\'')) % 2;
		dquote = (dquote + (!squote && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
			&& ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
        //printf("trimed[%d] = %c\n", i[1], trimmed[i[1]]);
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}
