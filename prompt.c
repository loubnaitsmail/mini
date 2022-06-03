#include "minishell.h"

int	g_status;

static char	*get_home(t_prompt prompt)
{
    printf("///GET_HOME\n");
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ "); // à changer

	home = mini_getenv("HOME", prompt.envp, 4); //get HOME

	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]); // ADD ~"
		free(temp);
	}
	free(home);
	home = ft_strjoin(pwd, " ");
	free(pwd);
	return (home);
}

static char	*get_user(t_prompt prompt)
{
    printf("///GET_USER\n");
	char	**user;
	char	*temp;

	user = NULL;
	//exec cmd whoami to get user
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
    if (!user)
		user = ft_extend_matrix(user, "guest");
	temp = ft_strjoin("", *user);
	ft_free_matrix(&user);
	return (temp);
}


char	*mini_getprompt(t_prompt prompt)
{
	printf("///Get_PROMPT\n");
	char	*temp; //*user
	char	*temp2; //*full_user
	char	*aux;   //*home

	temp = get_user(prompt);
    printf("USER_RETURN >> %s\n", temp);
	temp2 = ft_strjoin(temp, "@minishell"); //Add @minishell
	free(temp);
	aux = get_home(prompt);
    printf("HOME_RETURN >> %s\n", aux);
	temp = ft_strjoin(temp2, " ");
	free(temp2);
	temp2 = ft_strjoin(temp, aux);
	free(aux);
	free(temp);
	temp = ft_strjoin(temp2, "$ ");
	free(temp2);
	return (temp);
}

