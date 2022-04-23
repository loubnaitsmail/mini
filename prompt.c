#include "minishell.h"

int	g_status;

static char	*get_home(t_prompt prompt)
{
    printf("GET_HOME\n");
	char	*temp;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
    //printf("pwd = %s", pwd);

	if (!pwd)
		pwd = ft_strdup("∅ ");

	home = mini_getenv("HOME", prompt.envp, 4);
    //printf("home = %s\n", home);

	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		temp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
        //printf("pwd ~= %s\n", pwd);
		free(temp);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
    //printf("pwd final = %s\n", pwd);
	return (pwd);
}

static char	*get_user(t_prompt prompt)
{
    printf("GET_USER\n");
	char	**user;
	char	*temp;

	user = NULL;
	exec_custom(&user, "/usr/bin/whoami", "whoami", prompt.envp);
	printf("User after exec_cmd whoami= %s\n", *user);
    if (!user)
		user = ft_extend_matrix(user, "guest");    
    //COLORS USERS
	temp = ft_strjoin("", *user);
	ft_free_matrix(&user);
    //printf("temp = %s\n", temp);
	return (temp);
}


char	*mini_getprompt(t_prompt prompt)
{
	char	*temp; //*user
	char	*temp2; //*full_user
	char	*aux;   //*home

	temp = get_user(prompt);
    printf("USER_RETURN = %s\n", temp);
	temp2 = ft_strjoin(temp, "@minishell");
    printf("USER_temp2+ = %s\n", temp2);
	free(temp);

	aux = get_home(prompt);
    printf("HOME_RETURN = %s\n", aux);

	temp = ft_strjoin(temp2, aux);
    printf("USER+HOME = %s\n", temp);
	free(aux);
	free(temp2);

	if (!g_status || g_status == -1)
		temp2 = ft_strjoin(temp, BLUE);
	else
		temp2 = ft_strjoin(temp, RED);

	free(temp);
	temp = ft_strjoin(temp2, "$ ");
	free(temp2);
	temp2 = ft_strjoin(temp, DEFAULT);
	free(temp);
    printf("FINAL_temp2 = %s\n", temp2);
	return (temp2);
}